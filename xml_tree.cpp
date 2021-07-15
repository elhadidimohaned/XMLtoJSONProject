#include<iostream>
#include "xml_tree.h"

xml_tree::xml_tree()
{
    root = NULL;
}


Node* xml_tree::add_node(string name, string at) 
{
    Node* n;
    n = new Node(name, at);
    return n;
}

void xml_tree::add_child(Node* parent, Node* chil) 
{
    parent->children.push_back(chil);
    chil->Parent = parent;
}

void xml_tree::add_data(Node* n, string txt) 
{
    n->data += txt;
}

Node* xml_tree::get_root() 
{
    return root;
}
void xml_tree::add_root(Node* r) 
{
    root = r;
}

vector<Node*> xml_tree::get_children(Node* n) 
{
    return n->children;
}

string xml_tree::get_attributes(Node* n) 
{
    return n->att;

}
string xml_tree::get_data(Node* n) 
{
    return n->data;
}
void xml_tree::print(Node* n) 
{
    cout << n->tag_name << endl;
}
