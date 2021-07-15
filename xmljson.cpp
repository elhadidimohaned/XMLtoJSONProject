#include "xmljson.h"
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include "xml_tree.h"
#include <iostream>

ofstream json_output;

void xml_cutter_json(string name)
{

    ifstream infile;
    ofstream outfile;
    string input;
    string line, temp;
    string d_q = " ";
    int start, end;
    infile.open(name);
    outfile.open("output.txt");
    while (getline(infile, input))
    {
        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] == '<')
            {
                start = i;
                for (i; i < input.length(); i++)
                {
                    if (input[i] == '>')
                    {
                        end = i;
                        break;
                    }

                }
            }
            else
            {
                start = i;
                for (i; i < input.length(); i++)
                {
                    if (input[i] == '<')
                    {
                        end = i - 1;
                        i--;
                        break;
                    }
                    else
                    {
                        end = i;
                    }

                }
            }
            line = input.substr(start, (end - start + 1));
            if (line[0] != '<')
                for (int i = 0; i < line.length(); i++)
                {
                    if (line[i] == '"')
                        line.replace(i, 1, d_q);
                }
            if (line[0] != ' ' || line[1] != ' ' || line[2] != ' ')
                outfile << line << endl;




        }
    }
    infile.close();
    outfile.close();
}


//tree creator
void tree_creator_json(xml_tree& tree, string name)
{
    string input;
    ifstream inFile;
    vector<Node*> nodes;
    stack<int>tags;
    xml_cutter_json(name);//function to make each xml tag in seprate line (the function take xml file as an inpput)
    inFile.open("output.txt");
    if (!inFile)
    {
        cout << "Unable to open file";
        //exit(1); // terminate with error
    }

    while (getline(inFile, input))
    {


        //Opening Tag			// We can take Tag name and Attribute from this line
        if (input[0] == '<' && (input[1] == '!' || input[1] == '?'))
        {
            continue;
        }
        if (input[0] == '<' && input[1] != '/')
        {

            int index;
            // Searching for the space to get the tag name only from the line
            for (int i = 1; i < input.length(); i++)
            {
                index = i;
                if (input[i] == ' ')
                {
                    //First white space in the tag
                    break;
                }
            }
            string tag = input.substr(1, index - 1);
            string att = input.substr(index + 1, (input.size() - index - 2));
            nodes.push_back(tree.add_node(tag, att));//decalre a new tag
            if (tags.size() == 0)
            {
                tree.add_root(nodes[nodes.size() - 1]);//add thre root to the tree
            }
            else
            {
                tree.add_child(nodes[tags.top()], nodes[nodes.size() - 1]);//add a child to the last opened tag
            }
            tags.push(nodes.size() - 1);//add the last opened tag to deal with it to add children or data to it

        }
        //Closing tag
        else if (input[0] == '<' && input[1] == '/')
        {
            tags.pop();//remove the last opend tag (closed) to deal with the next tag to it
        }
        //Data
        else
        {
            tree.add_data(nodes[tags.top()], input);//add data to the last opened tag

        }
    }



}
// XML TO JSON
vector<string> attribute_cutter(string s)
{
    vector<string> result;
    string temp;
    int start = 0;
    int j;
    int len = s.length();
    int counter = 0;
    for (int i = 0; i <= len; i++)
    {
        if (i < len && s[i] == '=')
        {
            temp = "\"@";
            temp += s.substr(start, i - start);
            temp += "\":";
            j = i + 1;
        }
        if (s[i] == '\"')
            counter++;
        if (counter == 2)
        {
            start = i + 2;
            temp += " ";
            temp += s.substr(j, i - j + 1);
            result.push_back(temp);
            counter = 0;
        }
    }
    return result;
}
void print_tab(int& tab)
{

        json_output << "\n";
    for (int i = 0; i < tab; i++)
        json_output << "\t";
}


void print_node(Node* ptr,int &tab,int node_type,int repeat_indecator,int repeat_max)
{

    if(node_type==1)
    {

        if(!(repeat_indecator>1 && repeat_max>1))
        {
            print_tab(tab);
            json_output<<"\""<<ptr->tag_name<<"\": ";

        }
        if(repeat_max>1 && repeat_indecator==1)
        {
            json_output<<"[";
            tab++;

        }
        if(ptr->children.size()||ptr->att.size())
        {
            print_tab(tab);
            json_output<<"{";
            tab++;
        }
    }
    if(ptr->att.size()||ptr->data.size())
    {
        if(ptr->att.size())
        {
            vector<string>attributes=attribute_cutter(ptr->att);
            int att_len=attributes.size();
            for(int i=0; i<att_len; i++)
            {
                print_tab(tab);
                json_output<<attributes[i];
                if(i!=att_len-1 ||ptr->data.size())
                {
                    json_output<<",";
                }
            }
        }
        if(ptr->data.size())
        {
            if(repeat_max>1&& !(ptr->children.size()||ptr->att.size()))
                tab++;
            print_tab(tab);
            if(node_type==0 )
            {
                json_output<<"\""<<ptr->tag_name<<"\": ";

            }
            else if(node_type==1 && (ptr->children.size()||ptr->att.size()))
            {
                json_output<<"\"#text\": ";
            }
            json_output<<"\""<<ptr->data<<"\"";
        }

    }
    if(ptr->children.size())
    {
        json_output<<",";
        int type;
        int ch_len=ptr->children.size();
        int repeat_flag=1;

        for(int i=0; i<ch_len; i++)
        {
            if(repeat_flag)
            {
                int repeat=1;
                int j=i;
                while(j+1<ch_len &&ptr->children[j]->tag_name==ptr->children[j+1]->tag_name )
                {
                    repeat++;
                    j++;
                    repeat_flag=0;
                }
                repeat_max=repeat;
                    repeat_indecator=1;
            }
            if(ptr->children[i]->att.size()|| ptr->children[i]->children.size() || repeat_max >1)
                type=1;
            else
                type=0;
            print_node(ptr->children[i],tab,type,repeat_indecator,repeat_max);
            if(repeat_max>1 && repeat_indecator<=repeat_max)
                repeat_indecator++;
            if(type==1)
            {
                tab--;
                if(ptr->children[i]->att.size()|| ptr->children[i]->children.size())
                {
                    print_tab(tab);
                    json_output<<"}";
                }
            }
            if(repeat_indecator>1 && repeat_indecator>repeat_max)
            {
                repeat_indecator=1;
                repeat_max=1;
                tab--;
                print_tab(tab);
                json_output<<"]";
                repeat_flag=1;
            }
            if(i!=ptr->children.size()-1)
                json_output<<",";
        }
    }
}


void driverjson(string name)
{
    json_output.open("output-json.txt");
    int tab = 1, repeat_indecator = 1;
    xml_tree tree;
    tree_creator_json(tree, name);
    Node* root = tree.get_root();
    json_output << "{";
    print_node(root, tab, -1, 1, 1);
    json_output << "\n}";

}
