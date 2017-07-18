#include "client_mock.hpp"
#include "parameters/parameters.hpp"
#include <string>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

using namespace std;

TEST_GROUP(aws_iot_client_group)
{
    const string conf_file = "../conf/retail_rfid_reader_gateway.conf";
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
        .andReturnValue(true);
    mock().expectOneCall("mqtt_connect")
        .onObject(client)
        .andReturnValue(true);
    mock().expectOneCall("subscribe")
        .onObject(client)
        .andReturnValue(true);
    client->connect();
    mock().checkExpectations();
    delete client;
}

TEST(aws_iot_client_group, should_unsubscribe_when_disconnect_called)
{
    Parameters param(conf_file);
    Client *client = new ClientMock(param);
    mock().expectNoCall("unsubscribe");
    client->disconnect();
    mock().checkExpectations();
    delete client;
}

