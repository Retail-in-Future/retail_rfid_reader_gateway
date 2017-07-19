#include "parameters/parameters.hpp"
#include "rs232_data_channel.hpp"
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

using namespace std; 
using namespace boost;
using namespace boost::asio;

static const int max_read_length = 512;

RS232DataChannel::RS232DataChannel(io_service &io_service, Parameters &param):
    _active(true),
    _io_service(io_service),
    _serial_port(io_service, param.rfid_reader_rs232_device())
{
    if (not _serial_port.is_open())
    {
        cerr << "Failed to open serial port\n";
        return;
    }
    serial_port_base::baud_rate baud_option(param.rfid_reader_rs232_baudrate());
    _serial_port.set_option(baud_option);
    read_start();
}

void RS232DataChannel::write(const char msg)
{
    _io_service.post(boost::bind(&RS232DataChannel::do_write, this, msg));
}

void RS232DataChannel::close()
{
    _io_service.post(boost::bind(&RS232DataChannel::do_close, this, boost::system::error_code()));
}

bool RS232DataChannel::is_actived()
{
    return _active;
}

void RS232DataChannel::read_start(void)
{
    _serial_port.async_read_some(buffer(_read_msg, max_read_length),
            boost::bind(&RS232DataChannel::read_complete,
                this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

void RS232DataChannel::read_complete(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error) {
        cout.write(_read_msg, bytes_transferred);
        read_start();
    } else {
        do_close(error);
    }
}

void RS232DataChannel::do_write(const char msg)
{
    bool write_in_progress = !_write_msgs.empty();
    _write_msgs.push_back(msg);
    if (!write_in_progress) {
        write_start();
    }
}

void RS232DataChannel::write_start(void)
{
    boost::asio::async_write(_serial_port,
            boost::asio::buffer(&_write_msgs.front(), 1),
            boost::bind(&RS232DataChannel::write_complete,
                this,
                boost::asio::placeholders::error));
}

void RS232DataChannel::write_complete(const boost::system::error_code& error)
{
    if (!error) {
        _write_msgs.pop_front();
        if (!_write_msgs.empty()) {
            write_start();
        }
    } else {
        do_close(error);
    }
}

void RS232DataChannel::do_close(const boost::system::error_code& error)
{
    if (error == boost::asio::error::operation_aborted) {
        return;
    }
    if (error) {
        cerr << "Error: " << error.message() << endl; // show the error message
    } else {
        cout << "Error: Connection did not succeed.\n";
    }
    cout << "Press Enter to exit\n";
    _serial_port.close();
    _active = false;
}
