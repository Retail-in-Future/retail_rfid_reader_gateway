#include "parameters/parameters.hpp"
#include <boost/smart_ptr.hpp>
#include <string>
#include <CppUTest/TestHarness.h>

using namespace boost;

TEST_GROUP(parameters_group)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(parameters_group, should_get_parameters_when_given_valid_conf_file)
{
    auto param = make_shared<Parameters>("../conf/retail_rfid_reader_gateway.conf");
    std::string actual_aws_ipaddr = param->get<std::string>(PARAM::AWS_IOT_IPADDR);
    std::string expected_aws_ipaddr = "10.0.0.1";
    CHECK(expected_aws_ipaddr == actual_aws_ipaddr);
    int actual_aws_port = param->get<int>(PARAM::AWS_IOT_PORT);
    int expected_aws_port = 1980;
    LONGS_EQUAL(expected_aws_port, actual_aws_port);
}

TEST(parameters_group, should_catch_exception_when_give_invalid_conf_file)
{
    CHECK_THROWS(boost::exception, make_shared<Parameters>("retail_rfid_reader_gateway.conf"));
}

