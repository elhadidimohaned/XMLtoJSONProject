#include "huffmanCompressorHeader.h"

void huffman::decompressor_driver()
{
    huffmanTreeRecreation();
    decodeRetain();
}

void huffman::compressor_driver()
{
    priorityQCreation();
    huffmanTreeCreation();
    huffmanCodesCalculation();
    codingSaveToFile();
}

void huffman::nodeArrayCreation()
{
    for (int i = 0; i < 128; i++)
    {
        node_array[i] = new huffman_tree_node;
        node_array[i]->freq = 0;
        node_array[i]->data = i;
    }
}

void huffman::traverseHuffman(nodePointer node, string code)
{
    if (node->left == NULL && node->right == NULL)
    {
        node->code = code;
    }
    else
    {
        traverseHuffman(node->left, code + '0');
        traverseHuffman(node->right, code + '1');
    }
}

int huffman::binaryToD(string in)		//converts to rotated binary to decimal
{
    int result = 0;
    for (int i = 0; i < in.size(); i++)
        result = result * 2 + in[i] - '0';
    return result;
}

string huffman::decimalToB(int in)		//returns the rotated decimal to binary again
{
    string temp = "";
    string result = "";
    while (in)
    {
        temp += ('0' + in % 2);
        in /= 2;
    }
    result.append(8 - temp.size(), '0');					//append '0' ahead to let the result become fixed length of 8
    for (int i = temp.size() - 1; i >= 0; i--)				//reorder in right format
    {
        result += temp[i];
    }
    return result;
}

inline void huffman::buildHuffmanTree(string& path, char A_C)			//inline used to get some speed
{//build a new branch according to the input code
    nodePointer current = root;
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i] == '0')
        {
            if (current->left == NULL)
                current->left = new huffman_tree_node;
            current = current->left;
        }
        else if (path[i] == '1')
        {
            if (current->right == NULL)
                current->right = new huffman_tree_node;
            current = current->right;
        }
    }
    current->data = A_C;											//data is attached to the leaf
}

huffman::huffman(string in, string out)
{
    input_file_name = in;											//input file
    onput_file_name = out;											//output file
    nodeArrayCreation();											//initializing the node array func
}
void huffman::priorityQCreation()											//creates priority queue
{
    input_file.open(input_file_name);
    input_file.get(data);								//returns a character in data
    while (!input_file.eof())							//loop untill no data left
    {
        node_array[data]->freq++;		//increases the freq by one for each character encountered
        input_file.get(data);
    }
    input_file.close();
    for (int i = 0; i < 128; i++)
    {
        if (node_array[i]->freq)		//push into PQ every character that is not zero (not encountered)
        {
            pq.push(node_array[i]);
        }
    }
}

void huffman::huffmanTreeCreation()
{
    priority_queue<nodePointer, vector<nodePointer>, compare> temp(pq);
    while (temp.size() > 1)
    {       //create the huffman tree with highest frequecy characher being leaf from
            //bottom to top (reversed order)
        root = new huffman_tree_node;
        root->freq = 0;
        root->left = temp.top();
        root->freq += temp.top()->freq;
        temp.pop();
        root->right = temp.top();
        root->freq += temp.top()->freq;
        temp.pop();
        temp.push(root);		//pop two nodes add them to each other
                                //then push the result node agian into the PQ
    }
}

void huffman::huffmanCodesCalculation()						//used to call the protected func traverseHuffman
{
    traverseHuffman(root, "");
}

void huffman::codingSaveToFile()
{
    input_file.open(input_file_name);
    onput_file.open(onput_file_name,  ios::binary);
    string in = "", s = "";

    in += (char)pq.size();												//the first byte saves the size of the priority queue
    priority_queue<nodePointer, vector<nodePointer>, compare> temp(pq);
    while (!temp.empty())
    {//get all characters and their huffman codes for output
        nodePointer current = temp.top();
        in += current->data;
        s.assign(127 - current->code.size(), '0'); 						//set the codes with a fixed 128-bit string to get it back using the same method
        s += '1';														//'1' indicates the start of huffman code
        s.append(current->code);                                        //this means i put zeros then 1 to indicate the start of real code then add the code
        in += (char)binaryToD(s.substr(0, 8));
        for (int i = 0; i < 15; i++)
        {//cut into 8-bit binary codes that can convert into saving char needed for binary file
            s = s.substr(8);
            in += (char)binaryToD(s.substr(0, 8));
        }
        temp.pop();
    }
    s.clear();

    input_file.get(data);
    while (!input_file.eof())
    {//get the huffman code
        s += node_array[data]->code;
        while (s.size() > 8)
        {
            in += (char)binaryToD(s.substr(0, 8));  //get every 8 bits into a single byte
            s = s.substr(8);
        }
        input_file.get(data);
    }
    int count = 8 - s.size();
    if (s.size() < 8)
    {
        s.append(count, '0');  // zeros to the end to have a fixed size
    }
    in += (char)binaryToD(s);
    in += (char)count;

    onput_file.write(in.c_str(), in.size());
    input_file.close();
    onput_file.close();
}

void huffman::huffmanTreeRecreation()
{
    input_file.open(input_file_name, ios::binary);
    unsigned char size;
    input_file.read(reinterpret_cast<char*>(&size), 1);
    root = new huffman_tree_node;
    for (int i = 0; i < size; i++)
    {
        char A_C;
        unsigned char hCode[16];		//16 chars is the result of 128/8 (fixed sized huffman codes in encode)
        input_file.read(&A_C, 1);
        input_file.read(reinterpret_cast<char*>(hCode), 16);
        string hS = "";
        for (int i = 0; i < 16; i++)  // get the real 128 bits
        {
            hS += decimalToB(hCode[i]);
        }
        int j = 0;
        while (hS[j] == '0')           // added unnessesaty zeros are removed to get the real code
        {
            j++;
        }
        hS = hS.substr(j + 1);
        buildHuffmanTree(hS, A_C);
    }
    input_file.close();
}

void huffman::decodeRetain()
{
    input_file.open(input_file_name,  ios::binary);
    onput_file.open(onput_file_name);
    unsigned char size;
    input_file.read(reinterpret_cast<char*>(&size), 1);     // basiclly seekg Sets the position of the next character to be extracted from the input stream.
    input_file.seekg(-1, ios::end);
    char count0;
    input_file.read(&count0, 1);
    input_file.seekg(1 + 17 * size, ios::beg);				//this will move to the start of original text (decoded)

    vector<unsigned char> text;
    unsigned char segment;
    input_file.read(reinterpret_cast<char*>(&segment), 1);
    while (!input_file.eof())
    {
        text.push_back(segment);
        input_file.read(reinterpret_cast<char*>(&segment), 1);
    }
    nodePointer current = root;
    string path;
    for (int i = 0; i < text.size() - 1; i++)   // translation is done by the loop
    {
        path = decimalToB(text[i]);
        if (i == text.size() - 2)
            path = path.substr(0, 8 - count0);
        for (int j = 0; j < path.size(); j++)
        {
            if (path[j] == '0')
                current = current->left;
            else
                current = current->right;
            if (current->left == NULL && current->right == NULL)
            {
                onput_file.put(current->data);
                current = root;
            }
        }
    }
    input_file.close();
    onput_file.close();
}
