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
        static const string HOST = "conf.aws_iot.host";
        static const string DEFAULT_HOST = "a1j9v713o2vs6q.iot.ap-southeast-1.amazonaws.com";
        static const string CLIENT_ID = "conf.aws_iot.client_id";
        static const string DEFAULT_CLIENT_ID = "retail_rfid_reader";
        static const string THING_NAME = "conf.aws_iot.thing_name";
        static const string DEFAULT_THING_NAME = "retail_rfid_reader";
        namespace MQTT
        {
            static const string PORT = "conf.aws_iot.mqtt.port";
            static const int DEFAULT_PORT = 8883;
            static const string COMMAND_TIMEOUT = "conf.aws_iot.mqtt.command_timeout";
            static const int DEFAULT_COMMAND_TIMEOUT = 20000;
            static const string IS_CLEAN_SESSION = "conf.aws_iot.mqtt.is_clean_session";
            static const string DEFAULT_IS_CLEAN_SESSION = "true";
            static const string ALIVE_TIMEOUT = "conf.aws_iot.mqtt.alive_timeout";
            static const int DEFAULT_ALIVE_TIMEOUT = 30;
        }
        namespace CERTS
        {
            static const string ROOT_CA = "conf.aws_iot.certs.root_ca";
            static const string DEFAULT_ROOT_CA = "certs/root-ca";
            static const string CERT = "conf.aws_iot.certs.cert";
            static const string DEFAULT_CERT = "certs/caa57dffa4.cert.pem";
            static const string PRIVATE_KEY = "conf.aws_iot.certs.private_key";
            static const string DEFAULT_PRIVATE_KEY = "certs/caa57dffa4.private.key";
        }
        namespace TLS
        {
            static const string HANDSHAKE_TIMEOUT = "conf.aws_iot.tls.handshake_timeout";
            static const int DEFAULT_HANDSHAKE_TIMEOUT = 60000;
            static const string READ_TIMEOUT = "conf.aws_iot.tls.read_timeout";
            static const int DEFAULT_READ_TIMEOUT = 2000;
            static const string WRITE_TIMEOUT = "conf.aws_iot.tls.write_timeout";
            static const int DEFAULT_WRITE_TIMEOUT = 2000;
        }
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

    protected:

    public:
        Parameters(const string &conf_file);
        ~Parameters();

        template<typename T>
        void set(const ptree::path_type &conf_item, const T &value)
        {
            _conf_tree.put(conf_item, value);
        }

        string aws_iot_host() const;
        string aws_iot_client_id() const;
        string aws_iot_thing_name() const;
        int aws_iot_mqtt_port() const;
        int aws_iot_mqtt_command_timeout() const;
        bool aws_iot_mqtt_is_clean_session() const;
        int aws_iot_mqtt_alive_timeout() const;
        string aws_iot_certs_root_ca() const;
        string aws_iot_certs_cert() const;
        string aws_iot_certs_private_key() const;
        int aws_iot_tls_handshake_timeout() const;
        int aws_iot_tls_read_timeout() const;
        int aws_iot_tls_write_timeout() const;
        string rfid_reader_type() const;
        string rfid_reader_tcp_ipaddr() const;
        int rfid_reader_tcp_port() const;
        int rfid_reader_tcp_heart_beat() const;
        string rfid_reader_rs232_device() const;
        int rfid_reader_rs232_baudrate() const;
        int rfid_reader_rs232_databits() const;
        string rfid_reader_rs232_parity() const;
        int rfid_reader_rs232_stopbits() const;
};

