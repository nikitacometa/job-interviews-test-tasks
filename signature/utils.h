#pragma once

#include <string>

#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_logger.hpp>

enum logger_severity {
     LOG_SPAM,
     LOG_INFO,
     LOG_ERROR,
     LOG_NOTHING
};

BOOST_LOG_GLOBAL_LOGGER(general_logger, boost::log::sources::severity_logger_mt<logger_severity>);

logger_severity parse_severity_from_string(const std::string &severity_string);

void set_logger_severity(logger_severity severity);

long long get_file_size(const std::string &filename);
