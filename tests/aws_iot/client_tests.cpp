#include "client_mock.hpp"
#include "parameters/parameters.hpp"
#include <string>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

using namespace std;

TEST_GROUP(aws_iot_client_group)
{
    const string conf_file = "../conf/retail_rfid_reader_gateway.conf";
    bool tls_init_succ = true;
    bool mqtt_connected = true;
    void setup()
    {
    }

    void teardown()
    {
        mock().clear();
    }
};

bool initialize_tls()
{
    mock().actualCall("initialize_tls");
    return mock().returnValue().getBoolValue();
}

TEST(aws_iot_client_group, should_init_config_success_when_given_correct_parameters)
{
    Parameters param(conf_file);
    Client *client = new ClientMock(param);
    mock().expectOneCall("initialize_tls")
        .onObject(client)
        .andReturnValue((bool)tls_init_succ);
    mock().expectOneCall("mqtt_connect")
        .onObject(client)
        .andReturnValue((bool)mqtt_connected);
    client->connect();
    mock().checkExpectations();
    delete client;
}
