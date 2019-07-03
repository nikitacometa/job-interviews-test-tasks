#include "signature.h"

#include <fcntl.h>
#include <zconf.h>
#include <zlib.h>
#include <iostream>
#include <mutex>
#include <thread>

#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include "utils.h"

long long block_size = DEFAULT_BLOCK_SIZE;

static thread_local std::shared_ptr<char[]> thread_buffer;

static void process_block(long long block_id, int ifd, int ofd, long long file_size) {
    if (!thread_buffer) {
        thread_buffer = std::shared_ptr<char[]>(new char[block_size], [](const char *buffer) {
            delete[] buffer;
        });
    }

    long long input_pos = block_id * block_size;
    long long read = pread(ifd, thread_buffer.get(), block_size, input_pos);
    BOOST_LOG_SEV(general_logger::get(), LOG_SPAM) << read << " bytes read for block #" << block_id;
    if (read < block_size && input_pos + read < file_size) {
        throw std::runtime_error("I/O fail: unable to read input file");
    }

    unsigned long crc = crc32(0, (Bytef*)thread_buffer.get(), read);
    BOOST_LOG_SEV(general_logger::get(), LOG_SPAM) << "CRC32 of the block is 0x" << std::hex << crc << std::dec;

    long long output_pos = block_id * sizeof(unsigned long);
    unsigned int written = pwrite(ofd, (const void*)&crc, sizeof(unsigned long), output_pos);
    if (written < sizeof(int)) {
        throw std::runtime_error("I/O fail: unable to write to output file");
    }
}

void create_signature(const std::string &input_filename, const std::string &output_filename) {
    int ifd = open(input_filename.c_str(), O_RDONLY);
    int ofd = open(output_filename.c_str(), O_CREAT | O_WRONLY);
    long long file_size = get_file_size(input_filename);
    BOOST_LOG_SEV(general_logger::get(), LOG_INFO) << "input file size is " << file_size << "bytes";

    boost::asio::thread_pool thread_pool;
    for (long long block_id = 0; block_id * block_size < file_size; block_id++) {
        boost::asio::post(thread_pool, [block_id, ifd, ofd, file_size](){
            process_block(block_id, ifd, ofd, file_size);
        });
    }

    thread_pool.join();

    close(ifd);
    close(ofd);
}
