
#include "parameters/parameters.hpp"
#include <deque>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>

using namespace std; 
using namespace boost;
using namespace boost::asio;

class RS232DataChannel 
{
    public:
        RS232DataChannel(io_service& io_service, Parameters &param);
        void write(const char msg);
        void close();
        bool is_actived();

    private:
        static const int max_read_length = 512; // maximum amount of data to read in one operation
        void read_start(void);
        void read_complete(const boost::system::error_code& error, size_t bytes_transferred);
        void do_write(const char msg);
        void write_start(void);
        void write_complete(const boost::system::error_code& error);
        void do_close(const boost::system::error_code& error);

    private:
        bool _active;
        io_service &_io_service;
        serial_port _serial_port;
        char _read_msg[max_read_length];
        deque<char> _write_msgs;
}; 
