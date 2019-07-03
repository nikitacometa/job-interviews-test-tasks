#include <iostream>

#include <boost/log/sources/severity_feature.hpp>
#include <boost/program_options.hpp>

#include "signature.h"
#include "utils.h"

using namespace boost::program_options;

int main(int argc, const char *argv[]) {
    try {
        options_description desc{"Options"};
        desc.add_options()
                ("help,h", "Help")
                ("input-file,i", value<std::string>(), "Input file")
                ("output-file,o", value<std::string>(), "Output file")
                ("block-size,b", value<long long>(), "Size of blocks, (1mb by default, 256mb max)")
                ("severity,s", value<std::string>(), "Sets logs severity [nothing, error (default), info, spam]");

        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 0;
        }

        if (!vm.count("input-file") || !vm.count("output-file")) {
            throw std::invalid_argument("both files parameters must be provided");
        }

        if (vm.count("block-size")) {
            block_size = vm["block-size"].as<long long>();
            if (block_size <= 0 || block_size > MAX_BLOCK_SIZE) {
                throw std::invalid_argument("invalid block size provided");
            }
        }

        logger_severity logs_severity = LOG_ERROR;
        if (vm.count("severity")) {
            std::string severity_string = vm["severity"].as<std::string>();
            logs_severity = parse_severity_from_string(severity_string);
        }
        set_logger_severity(logs_severity);

        std::string input_file = vm["input-file"].as<std::string>();
        std::string output_file = vm["output-file"].as<std::string>();

        create_signature(input_file, output_file);
    }
    catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
}
