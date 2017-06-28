#include "parameters/options.hpp"
#include <boost/smart_ptr.hpp>
#include <string>
#include <CppUTest/TestHarness.h>

using namespace std;
using namespace boost;

TEST_GROUP(options_group)
{
};

TEST(options_group, should_get_conf_file_path_name_from_completely_option)
{
    int argc = 3;
    char const *argv[3] = {
        "fake_program_name",
        "--config",
        "config_file_name"
    };
    auto options = boost::make_shared<Options>(argc, argv);
    string actual_config_filename = options->get_config_filename();
    string expected_config_filename = "config_file_name";
    CHECK(expected_config_filename == actual_config_filename);
}

TEST(options_group, should_get_conf_file_path_name_from_shortly_option)
{
    int argc = 3;
    char const *argv[3] = {
        "fake_program_name",
        "-c",
        "config_file_name"
    };
    auto options = boost::make_shared<Options>(argc, argv);
    string actual_config_filename = options->get_config_filename();
    string expected_config_filename = "config_file_name";
    CHECK(expected_config_filename == actual_config_filename);
}

TEST(options_group, should_get_default_conf_file_path_name_if_not_give_option)
{
    int argc = 1;
    char const *argv[1] = {
        "fake_program_name"
    };
    auto options = boost::make_shared<Options>(argc, argv);
    string actual_config_filename = options->get_config_filename();
    string expected_config_filename = Options::DEFAULT_CONF_FILENAME;
    CHECK(expected_config_filename == actual_config_filename);
}

TEST(options_group, should_get_lowercase_string_conf_item_when_give_it_by_option)
{
    int argc = 3;
    char const *argv[3] = {
        "fake_program_name",
        "-D",
        "conf.aws_IoT.ipaddr=192.168.1.1A"
    };
    auto options = boost::make_shared<Options>(argc, argv);
    vector<pair<string, Options::Value>> actual_conf_pairs = options->get_conf_pairs();
    CHECK(actual_conf_pairs.size() == 1);
    pair<string, Options::Value> actual_conf_pair = actual_conf_pairs.at(0);
    string expected_conf_item = "conf.aws_iot.ipaddr";
    string expected_conf_value = "192.168.1.1a";
    CHECK(expected_conf_item == actual_conf_pair.first);
    CHECK(actual_conf_pair.second.is_string());
    CHECK(expected_conf_value == actual_conf_pair.second.s());
}

TEST(options_group, should_get_int_conf_item_when_give_it_by_option)
{
    int argc = 3;
    char const *argv[3] = {
        "fake_program_name",
        "-D",
        "conf.aws_iot.port=65535"
    };
    auto options = boost::make_shared<Options>(argc, argv);
    vector<pair<string, Options::Value>> actual_conf_pairs = options->get_conf_pairs();
    CHECK(actual_conf_pairs.size() == 1);
    pair<string, Options::Value> actual_conf_pair = actual_conf_pairs.at(0);
    string expected_conf_item = "conf.aws_iot.port";
    int expected_conf_value = 65535;
    CHECK(expected_conf_item == actual_conf_pair.first);
    CHECK(actual_conf_pair.second.is_int());
    LONGS_EQUAL(expected_conf_value, actual_conf_pair.second.i());
}

TEST(options_group, should_get_multiple_conf_items_when_given_more_than_one)
{
    int argc = 5;
    char const *argv[5] = {
        "fake_program_name",
        "-D",
        "conf.aws_iot.port=65535",
        "--define",
        "conf.aws_iot.ipaddr=192.168.1.1"
    };
    auto options = boost::make_shared<Options>(argc, argv);
    vector<pair<string, Options::Value>> actual_conf_pairs = options->get_conf_pairs();
    CHECK(actual_conf_pairs.size() == 2);
}

TEST(options_group, should_get_conf_value_included_equalmarks_when_give_it_by_option)
{
    int argc = 3;
    char const *argv[3] = {
        "fake_program_name",
        "-D",
        "conf.aws_IoT.ipaddr=192.168.1.1A=B=C"
    };
    auto options = boost::make_shared<Options>(argc, argv);
    vector<pair<string, Options::Value>> actual_conf_pairs = options->get_conf_pairs();
    CHECK(actual_conf_pairs.size() == 1);
    pair<string, Options::Value> actual_conf_pair = actual_conf_pairs.at(0);
    string expected_conf_item = "conf.aws_iot.ipaddr";
    string expected_conf_value = "192.168.1.1a=b=c";
    CHECK(expected_conf_item == actual_conf_pair.first);
    CHECK(actual_conf_pair.second.is_string());
    CHECK(expected_conf_value == actual_conf_pair.second.s());
}
