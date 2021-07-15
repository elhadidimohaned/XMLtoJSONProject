#ifndef XML_VALIDATOR_H
#define XML_VALIDATOR_H

#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <sstream>
#include <chrono>
#include <vector>
#include "parsing_xml.h"
#include "form_tree.h"
#include "xml_tree.h"

using namespace std;

void xml_validator(vector<int>& error_line, string file, int& num_of_errors);


#endif // XML_VALIDATOR_H
