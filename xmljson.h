#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include "xml_tree.h"
#include <iostream>


void xml_cutter_json(string name);
void tree_creator_json(xml_tree& tree, string name);
vector<string> attribute_cutter(string s);
void print_tab(int& tab);
void print_node(Node* ptr, int& tab, int node_type, int repeat_indecator, int repeat_max);
void driverjson(string name);
