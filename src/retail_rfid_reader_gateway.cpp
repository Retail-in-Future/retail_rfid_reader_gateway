#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "parameters/options.hpp"
#include "parameters/parameters.hpp"
#include "aws_iot/client.hpp"

using namespace std;
using namespace boost;
using namespace boost::asio;

io_service service;
void signals_handler(const system::error_code &error, int signal_number)
{
    ignore_unused(error, signal_number);
    cout << "signal handler..." << endl;    
    service.stop();
}

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
    signal_set signals(service, SIGINT, SIGTERM);
#ifdef SIGQUIT
    signals.add(SIGQUIT);
#endif
    signals.async_wait(bind(signals_handler, _1, _2));
    Options options(argc, (char const **)argv);
    auto param = process_parameters(options);
    Client client(*param);
    client.connect();
    try {
        //RfidReader rfid_reader(service, *param, client);
        boost::thread t(bind(&io_service::run, &service));
        //while (rfid_reader.active()) {
            sleep(1);
        //}
        //rfid_reader.close();
        t.join();
    } catch (std::exception &e) {
        cerr << "Exception: " << e.what() << endl;
    }
    return 0;
}
