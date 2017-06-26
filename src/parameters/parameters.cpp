#include <iostream>
#include "parameters.hpp"

Parameters::Parameters(std::string conf_file)
{
    read_xml(conf_file, m_conf_tree);
}

Parameters::~Parameters()
{
}

