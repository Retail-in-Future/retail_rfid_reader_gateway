#include <iostream>
#include "parameters.hpp"

using namespace std;

Parameters::Parameters(const string &conf_file)
{
    try {
        read_xml(conf_file, _conf_tree);
    } catch (const xml_parser::xml_parser_error &ex) {
    }
}

Parameters::~Parameters()
{
}

string Parameters::aws_iot_host() const
{
    return  _conf_tree.get<string>(PARAM::AWS_IOT::HOST, 
            PARAM::AWS_IOT::DEFAULT_HOST);
}

int Parameters::aws_iot_port() const
{
    return _conf_tree.get<int>(PARAM::AWS_IOT::PORT, 
            PARAM::AWS_IOT::DEFAULT_PORT);
}

string Parameters::aws_iot_client_id() const
{
    return _conf_tree.get<string>(PARAM::AWS_IOT::CLIENT_ID, 
            PARAM::AWS_IOT::DEFAULT_CLIENT_ID);
}

string Parameters::aws_iot_thing_name() const
{
    return _conf_tree.get<string>(PARAM::AWS_IOT::THING_NAME, 
            PARAM::AWS_IOT::DEFAULT_THING_NAME);
}

string Parameters::aws_iot_certs_root_ca() const
{
    return _conf_tree.get<string>(PARAM::AWS_IOT::CERTS::ROOT_CA, 
            PARAM::AWS_IOT::CERTS::DEFAULT_ROOT_CA);
}

string Parameters::aws_iot_certs_cert() const
{
    return _conf_tree.get<string>(PARAM::AWS_IOT::CERTS::CERT, 
            PARAM::AWS_IOT::CERTS::DEFAULT_CERT);
}

string Parameters::aws_iot_certs_private_key() const
{
    return _conf_tree.get<string>(PARAM::AWS_IOT::CERTS::PRIVATE_KEY, 
            PARAM::AWS_IOT::CERTS::DEFAULT_PRIVATE_KEY);
}

int Parameters::aws_iot_tls_handshake_timeout() const
{
    return _conf_tree.get<int>(PARAM::AWS_IOT::TLS::HANDSHAKE_TIMEOUT, 
            PARAM::AWS_IOT::TLS::DEFAULT_HANDSHAKE_TIMEOUT);
}

int Parameters::aws_iot_tls_read_timeout() const
{
    return _conf_tree.get<int>(PARAM::AWS_IOT::TLS::READ_TIMEOUT, 
            PARAM::AWS_IOT::TLS::DEFAULT_READ_TIMEOUT);
}

int Parameters::aws_iot_tls_write_timeout() const
{
    return _conf_tree.get<int>(PARAM::AWS_IOT::TLS::WRITE_TIMEOUT, 
            PARAM::AWS_IOT::TLS::DEFAULT_WRITE_TIMEOUT);
}

string Parameters::rfid_reader_type() const
{
    return _conf_tree.get<string>(PARAM::RFID_READER::TYPE, 
            PARAM::RFID_READER::DEFAULT_TYPE);
}

string Parameters::rfid_reader_tcp_ipaddr() const
{
    return _conf_tree.get<string>(PARAM::RFID_READER::TCP::IPADDR, 
            PARAM::RFID_READER::TCP::DEFAULT_IPADDR);
}

int Parameters::rfid_reader_tcp_port() const
{
    return _conf_tree.get<int>(PARAM::RFID_READER::TCP::PORT, 
            PARAM::RFID_READER::TCP::DEFAULT_PORT);
}

int Parameters::rfid_reader_tcp_heart_beat() const
{
    return _conf_tree.get<int>(PARAM::RFID_READER::TCP::HEART_BEAT, 
            PARAM::RFID_READER::TCP::DEFAULT_HEART_BEAT);
}

string Parameters::rfid_reader_rs232_device() const
{
    return _conf_tree.get<string>(PARAM::RFID_READER::RS232::DEVICE,
            PARAM::RFID_READER::RS232::DEFAULT_DEVICE);
}

int Parameters::rfid_reader_rs232_baudrate() const
{
    return _conf_tree.get<int>(PARAM::RFID_READER::RS232::BAUDRATE,
            PARAM::RFID_READER::RS232::DEFAULT_BAUDRATE);
}

int Parameters::rfid_reader_rs232_databits() const
{
    return _conf_tree.get<int>(PARAM::RFID_READER::RS232::DATABITS,
            PARAM::RFID_READER::RS232::DEFAULT_DATABITS);
}

string Parameters::rfid_reader_rs232_parity() const
{
    return _conf_tree.get<string>(PARAM::RFID_READER::RS232::PARITY, 
            PARAM::RFID_READER::RS232::DEFAULT_PARITY);
}

int Parameters::rfid_reader_rs232_stopbits() const
{
    return _conf_tree.get<int>(PARAM::RFID_READER::RS232::STOPBITS,
            PARAM::RFID_READER::RS232::DEFAULT_STOPBITS);
}

