#include "parameters/parameters.hpp"
#include <boost/smart_ptr.hpp>
#include <string>
#include <CppUTest/TestHarness.h>

using namespace boost;

TEST_GROUP(parameters_group)
{
    const std::string valid_conf_file = "../conf/retail_rfid_reader_gateway.conf";
    const std::string invalid_conf_file = "retail_rfid_reader_gateway.conf";
    const std::string invalid_conf_item = "conf.xxx.xxx";
    const std::string new_conf_item = "conf.new.one";
    const int new_conf_value = 0xdead;
    shared_ptr<Parameters> param;
    void setup()
    {
        param = boost::make_shared<Parameters>(valid_conf_file);
    }

    void teardown()
    {
    }
};

TEST(parameters_group, should_get_parameters_when_given_valid_conf_file)
{
    std::string actual_ipaddr = param->get<std::string>(PARAM::AWS_IOT::IPADDR);
    std::string expected_ipaddr = PARAM::AWS_IOT::DEFAULT_IPADDR;
    CHECK(expected_ipaddr == actual_ipaddr);
    int actual_port = param->get<int>(PARAM::AWS_IOT::PORT);
    int expected_port = PARAM::AWS_IOT::DEFAULT_PORT;
    LONGS_EQUAL(expected_port, actual_port);
}

TEST(parameters_group, should_get_default_aws_iot_ipaddr_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    std::string actual_ipaddr = default_param->get<std::string>(PARAM::AWS_IOT::IPADDR);
    std::string expected_ipaddr = PARAM::AWS_IOT::DEFAULT_IPADDR;
    CHECK(expected_ipaddr == actual_ipaddr);
}
    
TEST(parameters_group, should_get_default_aws_iot_port_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    int actual_port = default_param->get<int>(PARAM::AWS_IOT::PORT);
    int expected_port = PARAM::AWS_IOT::DEFAULT_PORT;
    LONGS_EQUAL(expected_port, actual_port);
}
    
TEST(parameters_group, should_get_default_aws_iot_cert_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    std::string actual_cert = default_param->get<std::string>(PARAM::AWS_IOT::CERT);
    std::string expected_cert = PARAM::AWS_IOT::DEFAULT_CERT;
    CHECK(expected_cert == actual_cert);
}
    
TEST(parameters_group, should_get_default_type_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    std::string actual_type = default_param->get<std::string>(PARAM::RFID_READER::TYPE);
    std::string expected_type = PARAM::RFID_READER::DEFAULT_TYPE;
    CHECK(expected_type == actual_type);
}
    
TEST(parameters_group, should_get_default_rfid_reader_tcp_ipaddr_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    std::string actual_ipaddr = default_param->get<std::string>(PARAM::RFID_READER::TCP::IPADDR);
    std::string expected_ipaddr = PARAM::RFID_READER::TCP::DEFAULT_IPADDR;
    CHECK(expected_ipaddr == actual_ipaddr);
}
    
TEST(parameters_group, should_get_default_rfid_reader_tcp_port_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    int actual_port = default_param->get<int>(PARAM::RFID_READER::TCP::PORT);
    int expected_port = PARAM::RFID_READER::TCP::DEFAULT_PORT;
    LONGS_EQUAL(expected_port, actual_port);
}
    
TEST(parameters_group, should_get_default_rfid_reader_tcp_heart_beat_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);
    
    int actual_heart_beat = default_param->get<int>(PARAM::RFID_READER::TCP::HEART_BEAT);
    int expected_heart_beat = PARAM::RFID_READER::TCP::DEFAULT_HEART_BEAT;
    LONGS_EQUAL(expected_heart_beat, actual_heart_beat);
}

TEST(parameters_group, should_get_default_rfid_reader_rs232_device_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);
    
    std::string actual_device = default_param->get<std::string>(PARAM::RFID_READER::RS232::DEVICE);
    std::string expected_device = PARAM::RFID_READER::RS232::DEFAULT_DEVICE;
    CHECK(expected_device == actual_device);
}

TEST(parameters_group, should_get_default_rfid_reader_rs232_baudrate_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);
    
    int actual_baudrate = default_param->get<int>(PARAM::RFID_READER::RS232::BAUDRATE);
    int expected_baudrate = PARAM::RFID_READER::RS232::DEFAULT_BAUDRATE;
    LONGS_EQUAL(expected_baudrate, actual_baudrate);
}

TEST(parameters_group, should_get_default_rfid_reader_rs232_databits_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);
    
    int actual_databits = default_param->get<int>(PARAM::RFID_READER::RS232::DATABITS);
    int expected_databits = PARAM::RFID_READER::RS232::DEFAULT_DATABITS;
    LONGS_EQUAL(expected_databits, actual_databits);
}

TEST(parameters_group, should_get_default_rfid_reader_rs232_parity_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);
    
    std::string actual_parity = default_param->get<std::string>(PARAM::RFID_READER::RS232::PARITY);
    std::string expected_parity = PARAM::RFID_READER::RS232::DEFAULT_PARITY;
    CHECK(expected_parity == actual_parity);
}

TEST(parameters_group, should_get_default_rfid_reader_rs232_stopbits_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);
    
    int actual_stopbits = default_param->get<int>(PARAM::RFID_READER::RS232::STOPBITS);
    int expected_stopbits = PARAM::RFID_READER::RS232::DEFAULT_STOPBITS;
    LONGS_EQUAL(expected_stopbits, actual_stopbits);
}

TEST(parameters_group, should_catch_exception_when_give_invalide_item_path)
{
    CHECK_THROWS(ptree_bad_path, param->get<std::string>(invalid_conf_item));
}

TEST(parameters_group, should_get_new_value_when_override_old_value)
{
    std::string new_value = "192.168.1.1";
    param->set(PARAM::AWS_IOT::IPADDR, new_value);
    std::string actual_aws_ipaddr = param->get<std::string>(PARAM::AWS_IOT::IPADDR);
    std::string expected_aws_ipaddr = new_value;
    CHECK(expected_aws_ipaddr == actual_aws_ipaddr);
}

TEST(parameters_group, should_get_new_value_when_add_new_one)
{
    param->set(new_conf_item, new_conf_value);
    int actual_new_value = param->get<int>(new_conf_item);
    int expected_new_value = new_conf_value;
    CHECK(expected_new_value == actual_new_value);
}
