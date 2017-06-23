#include <iostream>
#include <util/logging/Logging.hpp>
#include <util/logging/LogMacros.hpp>
#include <util/logging/ConsoleLogSystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace awsiotsdk::util::Logging;
using namespace boost::property_tree;

int main(int argc, char *argv[])
{
    shared_ptr<ConsoleLogSystem> p_log_system =
        make_shared<ConsoleLogSystem>(LogLevel::Info);
    InitializeAWSLogging(p_log_system);
    ShutdownAWSLogging();
    ptree pt;
    BOOST_FOREACH(const ptree::value_type &v, pt.get_child("sked")) {
        if (v.first == "flight") {
        }
    }
    return 0;
}
