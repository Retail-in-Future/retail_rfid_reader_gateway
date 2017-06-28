#pragma once

#include <boost/program_options.hpp>
#include <boost/variant.hpp>

using namespace boost;
using namespace boost::program_options;

class Options
{
    public:
        static const std::string DEFAULT_CONF_FILENAME;
        class Value
        {
            public:
                Value(std::string s) { _data = s; }
                Value(int i) { _data = i; }
                bool is_string() const {
                    return (_data.type() == typeid(std::string));
                }
                bool is_int() const {
                    return (_data.type() == typeid(int));
                }
                std::string s() { return get<std::string>(_data); }
                int i() { return get<int>(_data); }
            private:
                variant<int, std::string> _data;
        };

        typedef std::vector<std::string> ConfValues;

    public:
        Options(int argc, char const *argv[]);
        ~Options();
        std::string get_config_filename();
        std::vector<std::pair<std::string, Options::Value>> get_conf_pairs();

    private:
        void prepare_options_desc();
        void show_help();
        void parse_options(int argc, char const *argv[]);
        void process_conf_items();
        void process_conf_item(const std::string &conf_item);
        Options::Value generate_value(const std::string &conf_value);

    private:
        std::string _config_filename;
        std::vector<std::pair<std::string, Options::Value>> _conf_pairs;
        options_description _desc;
        ConfValues _conf_values;
};
