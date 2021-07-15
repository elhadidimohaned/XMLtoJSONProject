//#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "parsing_xml.h"


using namespace std;

void parsing_xml(string name)
{
    ifstream inputFile;
    ofstream outputFile;
    string line;
    string parsed_line,temp;
    string x_space=" ";
    int begin_idx,end_idx;
    inputFile.open(name);
    outputFile.open("output-cutter.txt");
    while(getline(inputFile,line))
    {
        for(int j=0;j<line.length();j++)
        {
            if(line[j]=='<')
            {
                begin_idx=j;
                for(j;j<line.length();j++)
                {
                    if(line[j]=='>')
                    {
                        end_idx=j;
                        break;
                    }
                    if (j == line.length() - 1)
                    {
                        end_idx = j;
                    }
                }
            }
            else
            {
                begin_idx=j;
                for(j;j<line.length();j++)
                {
                    if(line[j]=='<')
                    {
                        end_idx=j-1;
                        j--;
                        break;
                    }
                    else
                    {
                        end_idx =j;
                    }
                }
            }
            parsed_line= line.substr(begin_idx,(end_idx-begin_idx+1));
            if(parsed_line[0]!='<')
                for(int i=0;i<parsed_line.length();i++)
                {
                    if(parsed_line[i]=='"')
                        parsed_line.replace(i,1,x_space);
                }
            if(parsed_line[0]!=' ' || parsed_line[1] !=' ' || parsed_line[2] !=' ')
                outputFile << parsed_line<<endl;
        }
    }
    inputFile.close();
    outputFile.close();
}
