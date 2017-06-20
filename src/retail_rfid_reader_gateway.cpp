#include <iostream>
#include <util/logging/Logging.hpp>
#include <util/logging/LogMacros.hpp>
#include <util/logging/ConsoleLogSystem.hpp>
#include <ClientCore.hpp>

int main(int argc, char *argv[])
{
    std::shared_ptr<awsiotsdk::util::Logging::ConsoleLogSystem> p_log_system =
        std::make_shared<awsiotsdk::util::Logging::ConsoleLogSystem>(awsiotsdk::util::Logging::LogLevel::Info);
    awsiotsdk::util::Logging::InitializeAWSLogging(p_log_system);
    awsiotsdk::util::Logging::ShutdownAWSLogging();
    return 0;
}
