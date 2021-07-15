
#include "minify.h"

void minify(string name)
{
    ifstream inFile;
    ofstream outfile;
    string input;
    inFile.open(name);
    outfile.open("output-minify.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    while (getline(inFile, input))
    {
        if (input[0] == '<' && (input[1] == '!' || input[1] == '?')) {
            continue;
        }
        else
            outfile << input;

    }
}
