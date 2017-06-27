#pragma once
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/utility/string_ref.hpp>
#include <boost/serialization/singleton.hpp>

using namespace boost;
using namespace boost::property_tree;
using namespace boost::serialization;

namespace PARAM
{
    namespace AWS_IOT
    {
        static const std::string IPADDR = "conf.aws_iot.ipaddr";
        static const std::string DEFAULT_IPADDR = "10.0.0.1";
        static const std::string PORT = "conf.aws_iot.port";
        static const int DEFAULT_PORT = 1980;
        static const std::string CERT = "conf.aws_iot.cert";
        static const std::string DEFAULT_CERT = "awsiot.cert";
    }
    namespace RFID_READER
    {
        static const std::string TYPE = "conf.rfid_reader.type";
        static const std::string TYPE_TCP = "tcp";
        static const std::string TYPE_RS232 = "rs232";
        static const std::string DEFAULT_TYPE = TYPE_RS232;
        namespace TCP
        {
            static const std::string IPADDR = "conf.rfid_reader.tcp.ipaddr";
            static const std::string DEFAULT_IPADDR = "192.168.1.1";
            static const std::string PORT = "conf.rfid_reader.tcp.port";
            static const int DEFAULT_PORT = 8859;
            static const std::string HEART_BEAT = "conf.rfid_reader.tcp.heart_beat";
            static const int DEFAULT_HEART_BEAT = 10;
        }
        namespace RS232
        {
            static const std::string DEVICE = "conf.rfid_reader.rs232.device";
            static const std::string DEFAULT_DEVICE = "/dev/ttyS0";
            static const std::string BAUDRATE = "conf.rfid_reader.rs232.baudrate";
            static const int DEFAULT_BAUDRATE = 115200;
            static const std::string DATABITS = "conf.rfid_reader.rs232.databits";
            static const int DEFAULT_DATABITS = 8;
            static const std::string PARITY = "conf.rfid_reader.rs232.parity";
            static const std::string DEFAULT_PARITY = "none";
            static const std::string STOPBITS = "conf.rfid_reader.rs232.stopbits";
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
        Parameters(std::string conf_file);
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

