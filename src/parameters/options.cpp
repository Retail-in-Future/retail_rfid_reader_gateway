#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "options.hpp"

using namespace boost::algorithm;

const std::string Options::DEFAULT_CONF_FILENAME = "conf/retail_rfid_reader_gateway.conf";

Options::Options(int argc, char const *argv[]):
    _desc("Options"),
    _config_filename(DEFAULT_CONF_FILENAME)
{
    prepare_options_desc();
    parse_options(argc, argv);
}

Options::~Options()
{
}

std::string Options::get_config_filename()
{
    return _config_filename;
}

std::vector<std::pair<std::string, Options::Value>> Options::get_conf_pairs()
{
    return _conf_pairs;
}

void Options::prepare_options_desc()
{
    _desc.add_options()
        ("help,h", "this help message.")
        ("config,c", value<std::string>(), "config file path name.")
        ("define,D", value<ConfValues>(&_conf_values), "define config items.")
        ;
}

void Options::show_help()
{
    std::cout << _desc << std::endl;
}

void Options::parse_options(int argc, char const *argv[])
{
    variables_map vm;
    try {
        const positional_options_description p; // note empty positional options
        store(command_line_parser(argc, argv).options(_desc).positional(p).run(), vm);
        notify(vm);

        if (vm.count("help")) {
            show_help();
        }
        if (vm.count("config")) {
            _config_filename = vm["config"].as<std::string>();
        }
        if (vm.count("define")) {
            process_conf_items();
        }
    } catch (const boost::program_options::error &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Options::process_conf_items()
{
    if (!_conf_values.empty()) {
        for (const auto v : _conf_values) {
            process_conf_item(v);
        }
    }
}

void Options::process_conf_item(const std::string &conf_item)
{
    std::vector<std::string> item_and_value;
    split(item_and_value, conf_item, is_any_of("="));
    if (item_and_value.size() > 1) {
        std::vector<std::string>::iterator it = item_and_value.begin();
        to_lower(*it);
        std::string conf_name = *it;
        it++;
        std::string conf_value = "";
        for (; it != item_and_value.end(); it++) {
            to_lower(*it);
            conf_value += *it;
            if (it + 1 != item_and_value.end()) {
                conf_value += "=";
            }
        }
        Options::Value v = generate_value(conf_value);
        _conf_pairs.push_back(std::make_pair(conf_name, v));
    }
}

Options::Value Options::generate_value(const std::string &conf_value)
{
    try {
        int ivalue = lexical_cast<int>(conf_value);
        return Options::Value(ivalue);
    } catch (bad_lexical_cast &e) {
        return Options::Value(conf_value);
    }
}

