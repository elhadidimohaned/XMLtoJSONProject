#include"xml_tree.h"
#include "parsing_xml.h"
#include "form_tree.h"
#include <string>
#include <stack>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std::chrono;
using namespace std;

void form_tree(xml_tree &tree, string name)
{
    stack <int> tags;
    vector <Node*> nodes;
    ifstream inputFile;
    string input;

    auto start = high_resolution_clock::now();
    parsing_xml(name);

    inputFile.open("output.txt");
    if (!inputFile)
    {
        cout << "Error Can not open input file";
        exit(1);
    }
    
    while (getline(inputFile, input))
    {
        if (input[0] == '<' && (input[1] == '!' || input[1] == '?')) 
        {
            continue;
        }
        if (input[0] == '<' && input[1] != '/')
        {
            int index;
            for (int i = 1; i < input.length(); i++)
            {
                index = i;
                if (input[i] == ' ')
                {
                    break;
                }
            }
            string tag = input.substr(1, index - 1);
            string att = input.substr(index + 1, (input.size() - index - 2));
            nodes.push_back(tree.add_node(tag, att));

            if (tags.size() == 0) 
            {
                tree.add_root(nodes[nodes.size() - 1]);
            }
            else 
            {
                tree.add_child(nodes[tags.top()], nodes[nodes.size() - 1]);
            }
            tags.push(nodes.size() - 1);
        }
        else if (input[0] == '<' && input[1] == '/')
        {
            tags.pop();
        }
        else
        {
            tree.add_data(nodes[tags.top()], input);

        }
    }
}
