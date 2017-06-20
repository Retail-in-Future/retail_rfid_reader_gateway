#include <iostream>
#include <util/logging/Logging.hpp>
#include <util/logging/LogMacros.hpp>
#include <util/logging/ConsoleLogSystem.hpp>
#include <ClientCore.hpp>

using namespace std;
using namespace awsiotsdk::util::Logging;

int main(int argc, char *argv[])
{
    shared_ptr<ConsoleLogSystem> p_log_system =
        make_shared<ConsoleLogSystem>(LogLevel::Info);
    InitializeAWSLogging(p_log_system);
    ShutdownAWSLogging();
    return 0;
}
