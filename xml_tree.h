#pragma once
#include<string>
#include<vector>
using namespace std;
struct Node
{
    string data;
    string att;
    string tag_name;
    vector<Node*>children;
    Node* Parent;


    
    Node(string Name, string Attr = "", string DataIn = "")
    {
        data = DataIn;
        att = Attr;
        tag_name = Name;
        
        Parent = NULL;
    }
};
class xml_tree
{
    Node* root;
public:
    xml_tree();
    Node* add_node(string name, string at);
    void add_child(Node* parent, Node* chil);
    void add_data(Node* n, string txt);
    Node* get_root();
    void add_root(Node* r);
    vector<Node*> get_children(Node* n); 
    string get_attributes(Node* n); 
    string get_data(Node* n);
    void print(Node* n);
};
