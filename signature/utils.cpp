#include "utils.h"

#include <sys/stat.h>
#include <stdexcept>

#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>

using namespace boost::log;

BOOST_LOG_ATTRIBUTE_KEYWORD(severity_level, "Severity", logger_severity);

logger_severity parse_severity_from_string(const std::string &severity_string) {
    if (severity_string == "spam") {
        return LOG_SPAM;
    }
    if (severity_string == "info") {
        return LOG_INFO;
    }
    if (severity_string == "error") {
        return LOG_ERROR;
    }
    if (severity_string == "nothing") {
        return LOG_NOTHING;
    }
    throw std::invalid_argument("Can't parse severity from string: " + severity_string);
}

void set_logger_severity(logger_severity severity) {
    core::get()->set_filter(
            severity_level >= severity
    );
}

BOOST_LOG_GLOBAL_LOGGER_INIT(general_logger, sources::severity_logger_mt<logger_severity>) {
    sources::severity_logger_mt<logger_severity> logger;

    add_common_attributes();
    add_console_log(
            std::cout, keywords::format = "[%TimeStamp%][%ThreadID%] %Message%"
    );

    return logger;
}


long long get_file_size(const std::string &filename) {
    static struct stat64 st;
    if (stat64(filename.c_str(), &st)) {
        throw std::runtime_error("Failed to obtain input file size with stat");
    }
    return st.st_size;
}
