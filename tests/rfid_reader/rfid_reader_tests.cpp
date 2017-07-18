//#include "rfid_reader/rfid_reader.hpp"
#include "parameters/parameters.hpp"
#include <CppUTest/TestHarness.h>

TEST_GROUP(rfid_reader_group)
{
    const string conf_file = "../conf/retail_rfid_reader_gateway.conf";
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(rfid_reader_group, test)
{
    Parameters param(conf_file);
}
