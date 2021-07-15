//#ifndef HUFFMAN_ALGO_H
//#define HUFFMAN_ALGO_H
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

// A Tree node
struct huffman_tree_node
{
    char data;		          //character
    int freq;				  //frequency of the character
    string code;			  //huffman code for character data
    // Left and right child
    huffman_tree_node* left;
    huffman_tree_node* right;
    //struct constructer
    huffman_tree_node()
    {
        left = right = NULL;
    }
};
typedef huffman_tree_node* nodePointer;

class huffman
{
protected:
    nodePointer node_array[128];						//array for 128 characters for all Ascii Table
    ifstream input_file;							//deal with input files
    ofstream onput_file;							//deal with output files
    nodePointer child, parent, root;
    char data;
    string input_file_name, onput_file_name;
    class compare
    {/*a object funtion to set comparing rule of priority queue
        (so basiclly I pass this function as a third parameter to compare*/
    public:
        bool operator()(const nodePointer& c1, const nodePointer& c2) const
        {
            return c1->freq > c2->freq;
        }
    };
    priority_queue<nodePointer, vector<nodePointer>, compare> pq;		//priority queue of frequencies ordered from high to low
    void nodeArrayCreation();
    void traverseHuffman(nodePointer, string);							//traverse the huffman tree and get huffman code for a character
    int binaryToD(string);								//convert a 8-bit 0/1 string of binary code to a decimal integer
    string decimalToB(int);								//convert a decimal integer to a 8-bit 0/1 string of binary code
    inline void buildHuffmanTree(string&, char);						//build the huffman tree according to information from file
    void priorityQCreation();
    void huffmanTreeCreation();
    void huffmanCodesCalculation();
    void codingSaveToFile();
    void decodeRetain();
    void huffmanTreeRecreation();

public:
    huffman(string, string);                                    //constuctor that takes input and output files as parameters
    void compressor_driver();
    void decompressor_driver();
};

//#endif
