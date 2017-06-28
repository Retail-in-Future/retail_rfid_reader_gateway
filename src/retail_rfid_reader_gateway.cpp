#include <iostream>
#include <util/logging/Logging.hpp>
#include <util/logging/LogMacros.hpp>
#include <util/logging/ConsoleLogSystem.hpp>
#include <boost/smart_ptr.hpp>
#include "parameters/options.hpp"

using namespace std;
using namespace boost;
using namespace awsiotsdk::util::Logging;

int main(int argc, char *argv[])
{
    {
        auto options = boost::make_shared<Options>(argc, (char const **)argv);
    }
    std::shared_ptr<ConsoleLogSystem> p_log_system =
        std::make_shared<ConsoleLogSystem>(LogLevel::Info);
    InitializeAWSLogging(p_log_system);
    ShutdownAWSLogging();
    return 0;
}
