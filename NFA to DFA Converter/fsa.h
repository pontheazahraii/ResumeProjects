#ifndef FSA_H
#define FSA_H

#include <vector>
#include <map>
using namespace std;

class FSA
{
private:
    /* The set of states */
    vector<string> m_states;
    /* The input alphabet */
    vector<string> m_symbols;
    /* The accept states */
    vector<string> m_acceptStates;
    /* The start state */
    vector<string> m_startState;
    /* The transition function */
    map<string, map<string, vector<string>>> m_transition;

public:
    FSA();
    FSA(vector<string> states, vector<string> symbols, vector<string> acceptStates, vector<string> startState, map<string, map<string, vector<string>>> transition);
    ~FSA();

    void setStates(vector<string> states);
    void setSymbols(vector<string> symbols);
    void setAcceptStates(vector<string> acceptStates);
    void setStartState(vector<string> startState);
    void setTransition(map<string, map<string, vector<string>>> transition);

    vector<string> getStates();
    vector<string> getSymbols();
    vector<string> getAcceptStates();
    vector<string> getStartState();
    map<string, map<string, vector<string>>> getTransition();
    vector<string> nextState(map<string, map<string, vector<string>>> transition, string state, string symbol);
    bool contains(vector<string> v, string s);
};

#endif