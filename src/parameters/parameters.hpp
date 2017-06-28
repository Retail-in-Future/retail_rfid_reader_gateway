#pragma once
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/utility/string_ref.hpp>
#include <boost/serialization/singleton.hpp>

using namespace std;
using namespace boost;
using namespace boost::property_tree;
using namespace boost::serialization;

namespace PARAM
{
    namespace AWS_IOT
    {
        static const string IPADDR = "conf.aws_iot.ipaddr";
        static const string DEFAULT_IPADDR = "10.0.0.1";
        static const string PORT = "conf.aws_iot.port";
        static const int DEFAULT_PORT = 1980;
        static const string CERT = "conf.aws_iot.cert";
        static const string DEFAULT_CERT = "awsiot.cert";
    }
    namespace RFID_READER
    {
        static const string TYPE = "conf.rfid_reader.type";
        static const string TYPE_TCP = "tcp";
        static const string TYPE_RS232 = "rs232";
        static const string DEFAULT_TYPE = TYPE_RS232;
        namespace TCP
        {
            static const string IPADDR = "conf.rfid_reader.tcp.ipaddr";
            static const string DEFAULT_IPADDR = "192.168.1.1";
            static const string PORT = "conf.rfid_reader.tcp.port";
            static const int DEFAULT_PORT = 8859;
            static const string HEART_BEAT = "conf.rfid_reader.tcp.heart_beat";
            static const int DEFAULT_HEART_BEAT = 10;
        }
        namespace RS232
        {
            static const string DEVICE = "conf.rfid_reader.rs232.device";
            static const string DEFAULT_DEVICE = "/dev/ttyS0";
            static const string BAUDRATE = "conf.rfid_reader.rs232.baudrate";
            static const int DEFAULT_BAUDRATE = 115200;
            static const string DATABITS = "conf.rfid_reader.rs232.databits";
            static const int DEFAULT_DATABITS = 8;
            static const string PARITY = "conf.rfid_reader.rs232.parity";
            static const string DEFAULT_PARITY = "none";
            static const string STOPBITS = "conf.rfid_reader.rs232.stopbits";
            static const int DEFAULT_STOPBITS = 1;
        }
    }
};

class Parameters: public singleton<Parameters>
{
    private:
        ptree _conf_tree;

        void default_value();

    protected:

    public:
        Parameters(const string &conf_file);
        ~Parameters();

        template<typename T> 
        T get(const ptree::path_type &conf_item) const
        {
            return _conf_tree.get<T>(conf_item);
        }

        template<typename T>
        void set(const ptree::path_type &conf_item, const T &value)
        {
            _conf_tree.put(conf_item, value);
        }
};

