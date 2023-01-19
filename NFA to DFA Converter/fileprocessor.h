#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include "converter.h"
#include <fstream>

class FileProcessor
{
private:
    /* The input file */
    string m_input;
    /* The output file */
    string m_output;

public:
    FileProcessor();
    FileProcessor(string input);
    ~FileProcessor();

    void setInput(string input);
    void setOutput(string output);

    string getInput();
    string getOutput();

    FSA input();
    void output(FSA nfa);
    vector<string> split(string s, char del);
    string strip(string s);
};

#endif