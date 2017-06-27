#include <iostream>
#include "parameters.hpp"

Parameters::Parameters(std::string conf_file)
{
    try {
        read_xml(conf_file, _conf_tree);
    } catch (const xml_parser::xml_parser_error &ex) {
        default_value();
    }
}

Parameters::~Parameters()
{
}

void Parameters::default_value()
{
    _conf_tree.add(PARAM::AWS_IOT::IPADDR, PARAM::AWS_IOT::DEFAULT_IPADDR);
    _conf_tree.add(PARAM::AWS_IOT::PORT, PARAM::AWS_IOT::DEFAULT_PORT);
    _conf_tree.add(PARAM::AWS_IOT::CERT, PARAM::AWS_IOT::DEFAULT_CERT);

    _conf_tree.add(PARAM::RFID_READER::TYPE, PARAM::RFID_READER::DEFAULT_TYPE);

    _conf_tree.add(PARAM::RFID_READER::TCP::IPADDR, PARAM::RFID_READER::TCP::DEFAULT_IPADDR);
    _conf_tree.add(PARAM::RFID_READER::TCP::PORT, PARAM::RFID_READER::TCP::DEFAULT_PORT);
    _conf_tree.add(PARAM::RFID_READER::TCP::HEART_BEAT, PARAM::RFID_READER::TCP::DEFAULT_HEART_BEAT);

    _conf_tree.add(PARAM::RFID_READER::RS232::DEVICE, PARAM::RFID_READER::RS232::DEFAULT_DEVICE);
    _conf_tree.add(PARAM::RFID_READER::RS232::BAUDRATE, PARAM::RFID_READER::RS232::DEFAULT_BAUDRATE);
    _conf_tree.add(PARAM::RFID_READER::RS232::DATABITS, PARAM::RFID_READER::RS232::DEFAULT_DATABITS);
    _conf_tree.add(PARAM::RFID_READER::RS232::PARITY, PARAM::RFID_READER::RS232::DEFAULT_PARITY);
    _conf_tree.add(PARAM::RFID_READER::RS232::STOPBITS, PARAM::RFID_READER::RS232::DEFAULT_STOPBITS);
}
