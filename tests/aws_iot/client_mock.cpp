#include "client_mock.hpp"
#include <CppUTestExt/MockSupport.h>

using namespace std;
using namespace awsiotsdk;

ClientMock::ClientMock(const Parameters &param)
    : Client(param)
{

}

bool ClientMock::initialize_tls()
{
    mock().actualCall("initialize_tls").onObject(this);
    return mock().returnValue().getBoolValue();
}

bool ClientMock::mqtt_connect()
{
    mock().actualCall("mqtt_connect").onObject(this);
    return mock().returnValue().getBoolValue();
}

