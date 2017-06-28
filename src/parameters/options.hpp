#pragma once

#include <boost/program_options.hpp>
#include <boost/variant.hpp>

using namespace std;
using namespace boost;
using namespace boost::program_options;

class Options
{
    public:
        static const string DEFAULT_CONF_FILENAME;
        class Value
        {
            public:
                Value(string s) { _data = s; }
                Value(int i) { _data = i; }
                bool is_string() const {
                    return (_data.type() == typeid(string));
                }
                bool is_int() const {
                    return (_data.type() == typeid(int));
                }
                string s() { return get<string>(_data); }
                int i() { return get<int>(_data); }
            private:
                variant<int, string> _data;
        };

        typedef vector<string> ConfValues;

    public:
        Options(int argc, char const *argv[]);
        ~Options();
        string get_config_filename();
        vector<pair<string, Options::Value>> get_conf_pairs();

    private:
        void prepare_options_desc();
        void show_help();
        void parse_options(int argc, char const *argv[]);
        void process_conf_items();
        void process_conf_item(const string &conf_item);
        Options::Value generate_value(const string &conf_value);

    private:
        string _config_filename;
        vector<pair<string, Options::Value>> _conf_pairs;
        options_description _desc;
        ConfValues _conf_values;
};
