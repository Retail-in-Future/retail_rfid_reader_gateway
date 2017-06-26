#pragma once
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/utility/string_ref.hpp>

using namespace boost;
using namespace boost::property_tree;

class Parameters
{
    private:
        ptree m_conf_tree;

    protected:

    public:
        Parameters(std::string conf_file);
        ~Parameters();

        template<typename T> 
        T get(const ptree::path_type &conf_item) const
        {
            return m_conf_tree.get<T>(conf_item);
        }
};

