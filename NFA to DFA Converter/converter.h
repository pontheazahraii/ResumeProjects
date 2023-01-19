#ifndef CONVERTER_H
#define CONVERTER_H

#include "fsa.h"
#include <algorithm>
#include <sstream>

class Converter
{
private:
    /* The NFA to convert */
    FSA m_nfa;
    /* The converted DFA */
    FSA m_dfa;

public:
    Converter();
    Converter(FSA nfa);
    ~Converter();

    void setNFA(FSA nfa);
    void setDFA(FSA dfa);

    FSA getNFA();
    FSA getDFA();

    FSA convert(FSA nfa);
    vector<string> epsilon(map<string, map<string, vector<string>>> transition, string state, string symbol);
    vector<string> nextState(map<string, map<string, vector<string>>> transition, vector<string> states, string symbol);
    vector<string> contains(vector<string> v, string s);
    string stateString(vector<string> v);
    vector<string> allStates(map<string, map<string, vector<string>>> transition, vector<string> state, vector<string> symbols, vector<string> all);
    vector<string> split(string s, char del);
};

#endif