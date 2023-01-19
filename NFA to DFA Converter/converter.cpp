#include "converter.h"
#include <iostream>

/* The default constructor */
Converter::Converter() {}

/* The overloaded constructor
 * param nfa - The NFA to be converted
 */
Converter::Converter(FSA nfa)
{
    m_nfa = nfa;
    m_dfa = convert(m_nfa);
}

/* The destructor */
Converter::~Converter() {}

/* The NFA mutator
 * param nfa - the NFA to set
 */
void Converter::setNFA(FSA nfa)
{
    m_nfa = nfa;
}

/* The DFA mutator
 * param dfa - the DFA to set
 */
void Converter::setDFA(FSA dfa)
{
    m_dfa = dfa;
}

/* The NFA accessor
 * return - the NFA to get
 */
FSA Converter::getNFA()
{
    return m_nfa;
}

/* The DFA accessor
 * return - the DFA to get
 */
FSA Converter::getDFA()
{
    return m_dfa;
}

/* The converter method
 * This method converts an NFA to a DFA
 *
 * param nfa - the NFA to convert
 * return - the DFA that is converted
 */
FSA Converter::convert(FSA nfa)
{
    FSA dfa = FSA();
    // NFA members
    map<string, map<string, vector<string>>> nTransition = nfa.getTransition();
    vector<string> nStartState = nfa.getStartState();
    vector<string> nSymbols = nfa.getSymbols();
    vector<string> nAcceptStates = nfa.getAcceptStates();

    // Symbol Conversion
    vector<string> dSymbols = nSymbols;
    dSymbols.pop_back(); // remove EPS
    dfa.setSymbols(dSymbols);

    // Start State Conversion
    vector<string> dStartState = epsilon(nTransition, nStartState[0], "EPS");
    dfa.setStartState(dStartState);

    // States Conversion
    vector<string> dStates;
    dStates = allStates(nTransition, dStartState, dSymbols, dStates);
    dfa.setStates(dStates);

    // Transition Conversion
    map<string, map<string, vector<string>>> dTransition;
    string s;
    int size;
    // Set all states that don't exist to Empty
    for (int i = 0; i < dStates.size(); ++i)
    {
        for (int j = 0; j < dSymbols.size(); ++j)
        {
            s = dStates[i].substr(1, dStates[i].size() - 2);

            vector<string> state = split(s, ',');
            dTransition[dStates[i]][dSymbols[j]].push_back(stateString(nextState(nTransition, state, dSymbols[j])));
        }
    }
    dfa.setTransition(dTransition);

    // Accept States Conversion
    vector<string> dAcceptStates;
    for (int i = 0; i < dStates.size(); ++i)
    {
        for (int j = 0; j < nAcceptStates.size(); ++j)
        {
            s = dStates[i].substr(1, dStates[i].size() - 2);
            vector<string> state = split(s, ',');
            if (count(state.begin(), state.end(), nAcceptStates[j]) != 0)
            {
                dAcceptStates.push_back(dStates[i]);
            }
        }
    }
    dfa.setAcceptStates(dAcceptStates);
    return dfa;
}

/* The epsilon method
 * This method takes an state and finds the state that it is epsilon closed to
 *
 * param transition - the NFA transition table
 * param state - the current state
 * param symbol - the symbol of comparison (Should be "EPS")
 * return - a vector of strings that are epsilon closed to the current state
 */
vector<string> Converter::epsilon(map<string, map<string, vector<string>>> transition, string state, string symbol)
{
    vector<string> v;
    v.push_back(state);
    // find values that are epsilon closed
    for (int i = 0; i < transition[state][symbol].size(); ++i)
    {
        // make sure it is not epsilon closed to an empty set
        while (transition[state][symbol][i] != "{EM}")
        {
            state = transition[state][symbol][i];
            v = contains(v, state);
            // make sure it is not in an infinite loop
            if (v.size() == transition.size())
            {
                break;
            }
        }
    }
    return v;
}

/* The Next State method
 * This method gives you the next state of a current state
 *
 * param transition - the NFA transition table
 * param states - the current state
 * param symbol - the symbol of comparison
 * return - the next state with epsilon closures
 */
vector<string> Converter::nextState(map<string, map<string, vector<string>>> transition, vector<string> states, string symbol)
{
    vector<string> v;
    vector<string> e;
    string state;
    // access map for next state
    for (int i = 0; i < states.size(); ++i)
    {
        for (int j = 0; j < transition[states[i]][symbol].size(); ++j)
        {
            for (int k = 0; k < transition[states[i]][symbol].size(); ++k)
            {
                state = transition[states[i]][symbol][k];
                // check to make sure the state is not empty
                if (state != "{EM}")
                {
                    e = epsilon(transition, state, "EPS");
                    v = contains(v, state);
                }
            }
        }
        // add epsilon transition to the next state
        for (int j = 0; j < e.size(); ++j)
        {
            v = contains(v, e[j]);
        }
    }
    return v;
}

/* The contains method
 * This method adds into a vector, treating it as a set
 *
 * param v - the vector to add into
 * param s - the string to add
 * return - a set of strings
 */
vector<string> Converter::contains(vector<string> v, string s)
{
    if (count(v.begin(), v.end(), s) == 0)
    {
        v.push_back(s);
    }
    return v;
}

/* The string method for states
 * This method sorts and outputs a state into a string
 *
 * param v - the current state
 * return - the formated string
 */
string Converter::stateString(vector<string> v)
{
    string s = "{";
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); ++i)
    {
        s += v[i] + ",";
    }
    if (s.size() - 1 != 0)
    {
        s = s.substr(0, s.size() - 1) + "}";
    }
    else
    {
        s = "{EM}";
    }
    return s;
}

/* The all states method
 * This method finds all states that are accessed by the DFA
 *
 * param transition - the NFA transition
 * param state - the current state
 * param symbols - all symbols
 * param all - all of the states that are added
 * return - all of the states that are accessed by the DFA
 */
vector<string> Converter::allStates(map<string, map<string, vector<string>>> transition, vector<string> state, vector<string> symbols, vector<string> all)
{
    vector<string> next;
    string nextStr;
    bool nextBool = false;

    all = contains(all, stateString(state));

    for (int i = 0; i < symbols.size(); ++i)
    {
        next = nextState(transition, state, symbols[i]); // the next state
        nextStr = stateString(next);                     // used for comparison
        if (nextStr == "{EM}")
        {
            break;
        }
        if (next[0] != "{EM}" && next.size() != 1) // check if the state is the Empty set
        {
            nextBool = true;
        }
        if (nextBool && (count(all.begin(), all.end(), nextStr) == 0))
        {
            // using recursion to iterate through every possible combination
            all = allStates(transition, next, symbols, all);
        }
        else
        {
            all = contains(all, "{EM}"); // add the empty set to the list of all sets
        }
    }
    return all;
}

/* The method to split a string
 * This method splits a string given a delimiter
 *
 * param s - the string to split
 * param del - the delimiter
 * return - a vector of strings that are split on the delimiter
 */
vector<string> Converter::split(string s, char del)
{
    vector<string> v;
    stringstream ss(s);
    string temp;

    while (getline(ss, temp, del))
    {
        v.push_back(temp);
        ss.clear();
    }

    return v;
}