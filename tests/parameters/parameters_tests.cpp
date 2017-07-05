#include "parameters/parameters.hpp"
#include <boost/smart_ptr.hpp>
#include <string>
#include <CppUTest/TestHarness.h>

using namespace std;
using namespace boost;

TEST_GROUP(parameters_group)
{
    const string valid_conf_file = "../conf/retail_rfid_reader_gateway.conf";
    const string invalid_conf_file = "retail_rfid_reader_gateway.conf";
    boost::shared_ptr<Parameters> param;
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
    string actual_host = param->aws_iot_host();
    string expected_host = PARAM::AWS_IOT::DEFAULT_HOST;
    CHECK(expected_host == actual_host);
    int actual_port = param->aws_iot_mqtt_port();
    int expected_port = PARAM::AWS_IOT::MQTT::DEFAULT_PORT;
    LONGS_EQUAL(expected_port, actual_port);
    string actual_parity = param->rfid_reader_rs232_parity();
    string expected_parity = PARAM::RFID_READER::RS232::DEFAULT_PARITY;
    CHECK(expected_parity == actual_parity);
}

TEST(parameters_group, should_get_default_aws_iot_host_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    string actual_host = default_param->aws_iot_host();
    string expected_host = PARAM::AWS_IOT::DEFAULT_HOST;
    CHECK(expected_host == actual_host);
}
    
TEST(parameters_group, should_get_default_aws_iot_client_id_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    string actual_client_id = default_param->aws_iot_client_id();
    string expected_client_id = PARAM::AWS_IOT::DEFAULT_CLIENT_ID;
    CHECK(expected_client_id == actual_client_id);
}
 
TEST(parameters_group, should_get_default_aws_iot_thing_name_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    string actual_thing_name = default_param->aws_iot_thing_name();
    string expected_thing_name = PARAM::AWS_IOT::DEFAULT_THING_NAME;
    CHECK(expected_thing_name == actual_thing_name);
}
    
TEST(parameters_group, should_get_default_aws_iot_mqtt_port_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    int actual_port = default_param->aws_iot_mqtt_port();
    int expected_port = PARAM::AWS_IOT::MQTT::DEFAULT_PORT;
    LONGS_EQUAL(expected_port, actual_port);
}

TEST(parameters_group, should_get_default_aws_iot_mqtt_command_timeout_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    int actual_command_timeout = default_param->aws_iot_mqtt_command_timeout();
    int expected_command_timeout = PARAM::AWS_IOT::MQTT::DEFAULT_COMMAND_TIMEOUT;
    LONGS_EQUAL(expected_command_timeout, actual_command_timeout);
}

TEST(parameters_group, should_get_default_aws_iot_mqtt_is_clean_session_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    bool actual_is_clean_session = default_param->aws_iot_mqtt_is_clean_session();
    CHECK(actual_is_clean_session);
}

TEST(parameters_group, should_get_default_aws_iot_mqtt_alive_timeout_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    int actual_alive_timeout = default_param->aws_iot_mqtt_alive_timeout();
    int expected_alive_timeout = PARAM::AWS_IOT::MQTT::DEFAULT_ALIVE_TIMEOUT;
    LONGS_EQUAL(expected_alive_timeout, actual_alive_timeout);
}

TEST(parameters_group, should_get_default_aws_iot_root_ca_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    string actual_root_ca = default_param->aws_iot_certs_root_ca();
    string expected_root_ca = PARAM::AWS_IOT::CERTS::DEFAULT_ROOT_CA;
    CHECK(expected_root_ca == actual_root_ca);
}
    
TEST(parameters_group, should_get_default_aws_iot_cert_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    string actual_cert = default_param->aws_iot_certs_cert();
    string expected_cert = PARAM::AWS_IOT::CERTS::DEFAULT_CERT;
    CHECK(expected_cert == actual_cert);
}
    
TEST(parameters_group, should_get_default_aws_iot_private_key_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    string actual_private_key = default_param->aws_iot_certs_private_key();
    string expected_private_key = PARAM::AWS_IOT::CERTS::DEFAULT_PRIVATE_KEY;
    CHECK(expected_private_key == actual_private_key);
}
    
TEST(parameters_group, should_get_default_aws_iot_tls_handshake_timeout_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    int actual_handshake_timeout = default_param->aws_iot_tls_handshake_timeout();
    int expected_handshake_timeout = PARAM::AWS_IOT::TLS::DEFAULT_HANDSHAKE_TIMEOUT;
    LONGS_EQUAL(expected_handshake_timeout, actual_handshake_timeout);
}
    
TEST(parameters_group, should_get_default_aws_iot_tls_read_timeout_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    int actual_read_timeout = default_param->aws_iot_tls_read_timeout();
    int expected_read_timeout = PARAM::AWS_IOT::TLS::DEFAULT_READ_TIMEOUT;
    LONGS_EQUAL(expected_read_timeout, actual_read_timeout);
}
    
TEST(parameters_group, should_get_default_aws_iot_tls_write_timeout_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    int actual_write_timeout = default_param->aws_iot_tls_write_timeout();
    int expected_write_timeout = PARAM::AWS_IOT::TLS::DEFAULT_WRITE_TIMEOUT;
    LONGS_EQUAL(expected_write_timeout, actual_write_timeout);
}
    
TEST(parameters_group, should_get_default_type_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    string actual_type = default_param->rfid_reader_type();
    string expected_type = PARAM::RFID_READER::DEFAULT_TYPE;
    CHECK(expected_type == actual_type);
}
    
TEST(parameters_group, should_get_default_rfid_reader_tcp_ipaddr_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    string actual_ipaddr = default_param->rfid_reader_tcp_ipaddr();
    string expected_ipaddr = PARAM::RFID_READER::TCP::DEFAULT_IPADDR;
    CHECK(expected_ipaddr == actual_ipaddr);
}
    
TEST(parameters_group, should_get_default_rfid_reader_tcp_port_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);

    int actual_port = default_param->rfid_reader_tcp_port();
    int expected_port = PARAM::RFID_READER::TCP::DEFAULT_PORT;
    LONGS_EQUAL(expected_port, actual_port);
}
    
TEST(parameters_group, should_get_default_rfid_reader_tcp_heart_beat_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);
    
    int actual_heart_beat = default_param->rfid_reader_tcp_heart_beat();
    int expected_heart_beat = PARAM::RFID_READER::TCP::DEFAULT_HEART_BEAT;
    LONGS_EQUAL(expected_heart_beat, actual_heart_beat);
}

TEST(parameters_group, should_get_default_rfid_reader_rs232_device_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);
    
    string actual_device = default_param->rfid_reader_rs232_device();
    string expected_device = PARAM::RFID_READER::RS232::DEFAULT_DEVICE;
    CHECK(expected_device == actual_device);
}

TEST(parameters_group, should_get_default_rfid_reader_rs232_baudrate_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);
    
    int actual_baudrate = default_param->rfid_reader_rs232_baudrate();
    int expected_baudrate = PARAM::RFID_READER::RS232::DEFAULT_BAUDRATE;
    LONGS_EQUAL(expected_baudrate, actual_baudrate);
}

TEST(parameters_group, should_get_default_rfid_reader_rs232_databits_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);
    
    int actual_databits = default_param->rfid_reader_rs232_databits();
    int expected_databits = PARAM::RFID_READER::RS232::DEFAULT_DATABITS;
    LONGS_EQUAL(expected_databits, actual_databits);
}

TEST(parameters_group, should_get_default_rfid_reader_rs232_parity_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);
    
    string actual_parity = default_param->rfid_reader_rs232_parity();
    string expected_parity = PARAM::RFID_READER::RS232::DEFAULT_PARITY;
    CHECK(expected_parity == actual_parity);
}

TEST(parameters_group, should_get_default_rfid_reader_rs232_stopbits_when_give_invalid_conf_file)
{
    auto default_param = boost::make_shared<Parameters>(invalid_conf_file);
    
    int actual_stopbits = default_param->rfid_reader_rs232_stopbits();
    int expected_stopbits = PARAM::RFID_READER::RS232::DEFAULT_STOPBITS;
    LONGS_EQUAL(expected_stopbits, actual_stopbits);
}

TEST(parameters_group, should_get_new_value_when_override_old_value)
{
    string new_value = "192.168.1.1";
    param->set(PARAM::AWS_IOT::HOST, new_value);
    string actual_aws_ipaddr = param->aws_iot_host();
    string expected_aws_ipaddr = new_value;
    CHECK(expected_aws_ipaddr == actual_aws_ipaddr);
}

