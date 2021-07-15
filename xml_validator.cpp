#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <sstream>
#include <chrono>
#include <vector>
#include "xml_validator.h"

using namespace std;

void xml_validator(vector<int>& error_line, string file, int& num_of_errors)
{
    ifstream inputFile;
    inputFile.open(file);
    ofstream outputFile;
    outputFile.open("output-validated.txt");
    stack <string> tagStack;
    //vector <int> error_line;
    //int v_index = 0 ;

    //int num_of_errors=0;
    string error;
    string openTag = "<";
    string forwardSlash = "/";
    string closeTag = ">";

    int line_no = 0;
    for (std::string inputLine; getline(inputFile, inputLine);)
    {
        int data = 0;
        line_no++;
        if (inputLine[0] == '<' && inputLine[inputLine.length() - 2] == '/')
        {
            outputFile << inputLine.substr(0, inputLine.length() - 2) << ">" << endl;
            stringstream str(inputLine);
            str >> inputLine;
            outputFile << "<" << "/" << inputLine.substr(1) << ">" << endl;
            continue;
        }

        if (inputLine.length() >= 2)
        {
            if (inputLine[inputLine.length() - 2] == '-' && inputLine[inputLine.length() - 1] == '>')
            {
                outputFile << inputLine << endl;
                continue;
            }
        }
        //Data Part
        if (inputLine[0] != '<')
        {

            data = 1;
            outputFile << inputLine << endl;
            stringstream str(tagStack.top());
            tagStack.pop();
            str >> inputLine;
            if (inputLine[inputLine.length() - 1] == '>')
            {
                outputFile << "<" << "/" << inputLine.substr(1) << endl;
                error = openTag + forwardSlash + inputLine.substr(1);
            }
            else
            {
                outputFile << "<" << "/" << inputLine.substr(1) << ">" << endl;
                error = openTag + forwardSlash + inputLine.substr(1) + closeTag;
            }
            getline(inputFile, inputLine);
            line_no++;
        }
        //if line is Opening tag
        if (inputLine[0] == '<' && inputLine[1] != '/')

        {
            if (data == 1)
            {
                num_of_errors++;
                error_line.push_back(line_no);
            }
            if (inputLine[1] == '!' || inputLine[1] == '?')
            {
                outputFile << inputLine << endl;
                continue;
            }
            tagStack.push(inputLine);
            outputFile << tagStack.top() << endl;
            continue;
        }
        //if line is closing tag
        if (inputLine[0] == '<' && inputLine[1] == '/')
        {
            if (tagStack.empty())
                continue;
            if (data)
            {
                data = 0;
                if (error != inputLine)
                {
                    num_of_errors++;
                    error_line.push_back(line_no);
                }
                continue;
            }

            stringstream str(tagStack.top());
            tagStack.pop();
            str >> inputLine;
            if (inputLine[inputLine.length() - 1] == '>')
            {
                outputFile << "<" << "/" << inputLine.substr(1) << endl;
                error = openTag + forwardSlash + inputLine.substr(1);
            }
            else
            {
                outputFile << "<" << "/" << inputLine.substr(1) << ">" << endl;
                error = openTag + forwardSlash + inputLine.substr(1) + closeTag;
            }
        }
    }
    while (!tagStack.empty())
    {
        string line;
        stringstream str(tagStack.top());
        tagStack.pop();
        str >> line;
        if (line[line.length() - 1] == '>')
            outputFile << "<" << "/" << line.substr(1) << endl;
        else
            outputFile << "<" << "/" << line.substr(1) << ">" << endl;

        num_of_errors++;
        //cout <<"error in line no. "<<line_no<<":"<<line<<endl;
    }

    //cout<<"no. of errors = "<<num_of_errors<<endl;
/*    for(int i=0; i < error_line.size(); i++)
        cout << error_line.at(i) <<endl;*/

}
