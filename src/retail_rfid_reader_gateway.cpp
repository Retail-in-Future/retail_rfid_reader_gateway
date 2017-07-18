#include <iostream>
#include <util/logging/Logging.hpp>
#include <util/logging/LogMacros.hpp>
#include <util/logging/ConsoleLogSystem.hpp>
#include <boost/smart_ptr.hpp>
#include "parameters/options.hpp"
#include "parameters/parameters.hpp"
#include "aws_iot/client.hpp"

using namespace std;
using namespace boost;
//using namespace awsiotsdk::util::Logging;

boost::shared_ptr<Parameters> process_parameters(Options &options)
{
    string configuration_file = options.get_config_filename();
    auto param = boost::make_shared<Parameters>(configuration_file);
    auto custom_values = options.get_conf_pairs();
    for (auto &value : custom_values) {
        if (value.second.is_string()) {
            param->set(value.first, value.second.s());
        } else if (value.second.is_int()) {
            param->set(value.first, value.second.i());
        }
    }
    return param;
}

int main(int argc, char *argv[])
{
    Options options(argc, (char const **)argv);
    auto param = process_parameters(options);
    Client client(*param);
    client.connect();
    //std::shared_ptr<ConsoleLogSystem> p_log_system =
        //std::make_shared<ConsoleLogSystem>(LogLevel::Info);
    //InitializeAWSLogging(p_log_system);
    //p_log_system->Log(LogLevel::Info, "test", "test");
    //ShutdownAWSLogging();
    return 0;
}
