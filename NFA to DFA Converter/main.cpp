#include <exception>
#include <iostream>
#include "fileprocessor.h"
using namespace std;

int main(int argc, char **argv)
{
    string fileName;

    if (argc < 2)
    { // if file name is not included in the command line
        cout << "File name not included in command line" << endl;
        cout << "What is the name of the file you want to process?: ";
        cin >> fileName;
    }
    else
    { // if file name is included in the command line
        fileName = argv[1];
    }
    FileProcessor fp = FileProcessor(fileName);
    fp.output(fp.input());
    return 0;
}