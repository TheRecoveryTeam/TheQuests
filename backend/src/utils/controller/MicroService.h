//
// Created by dpudov on 12.11.18.
//

#ifndef THEQUESTS_STD_MICRO_SERVICE_H
#define THEQUESTS_STD_MICRO_SERVICE_H
#define BOOST_SPIRIT_THREADSAFE // enable thread safety to json read on property tree!

#include <boost/format.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <regex>

#endif //THEQUESTS_STD_MICRO_SERVICE_H
