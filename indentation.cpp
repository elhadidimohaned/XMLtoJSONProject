#include "indentaion.h"

void indentation(string name, string outName)
{
    ifstream inFile;
    ofstream outfile;
    string input;
    bool flag = true; // dummy variable
    bool flag2 = false;
    int level = 0; // show the level of the present tag
    int level_next = 0; //identify the level of the next tag
    inFile.open(name); //open the file we will work on it
    outfile.open(outName); // open the output file
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    while (getline(inFile, input))
    {


        if (input[0] == '<' && (input[1] == '!' || input[1] == '?')) {
            continue;
        }
        else if (input[0] == '<' && input[1] != '/' && input[input.length() - 2] != '/') // if it is opening tag
        {
            flag = true;
            level = level_next;
            level_next++;

        }
        else if (input[0] == '<' && input[1] == '/') // if it is a closing tag
        {
            if (flag2 == false)

            {
                flag = true;
                level_next--;
                level = level_next;
            }
            else
            {
                flag = true;
                level = level_next;
                flag2 = false;
            }



        }
        else if (input[0] == '<' && input[1] != '/' && input[input.length() - 1] == '>' && input[input.length() - 2] == '/') // self closing tag
        {
            flag = true;

        }
        else          // sentence between openining and closing tags
        {
            flag = true;
            flag2 = true;
            level = level_next;
            level_next--;
        }
        // identify the level
        if (level == 0 && flag==true)
            outfile << input << endl;
        else if (level == 1 && flag==true)
            outfile << "\t" << input << endl;
        else if (level == 2 && flag==true)
            outfile << "\t\t" << input << endl;
        else if (level == 3 && flag==true)
            outfile << "\t\t\t" << input << endl;
        else if (level == 4 && flag == true)
            outfile << "\t\t\t\t" <<input << endl;
        else if (level == 5 && flag == true)
            outfile << "\t\t\t\t\t" << input << endl;
        else if (level == 6 && flag == true)
            outfile << "\t\t\t\t\t\t" << input << endl;
        else if (level == 7 && flag == true)
            outfile << "\t\t\t\t\t\t\t" << input << endl;


    }



}
