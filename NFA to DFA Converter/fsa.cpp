#include "fsa.h"

/* The default constructor */
FSA::FSA() {}

/* The overloaded constructor
 * param states - the set of states
 * param symbols - the input alphabet
 * param acceptStates - the accept States
 * param startState - the start State
 * param transition - the transition function
 */
FSA::FSA(vector<string> states, vector<string> symbols, vector<string> acceptStates, vector<string> startState, map<string, map<string, vector<string>>> transition)
{
    m_states = states;
    m_symbols = symbols;
    m_acceptStates = acceptStates;
    m_startState = startState;
    m_transition = transition;
}

/* The destructor */
FSA::~FSA() {}

/* The states mutator
 *
 * param states - the state to set
 */
void FSA::setStates(vector<string> states)
{
    m_states = states;
}

/* The symbols mutator
 *
 * param symbols - the sybols to set
 */
void FSA::setSymbols(vector<string> symbols)
{
    m_symbols = symbols;
}

/* The accept states mutator
 *
 * param acceptStates - the accept states to set
 */
void FSA::setAcceptStates(vector<string> acceptStates)
{
    m_acceptStates = acceptStates;
}

/* The start state mutator
 *
 * param startState - the start state to set
 */
void FSA::setStartState(vector<string> startState)
{
    m_startState = startState;
}

/* The transition mutator
 *
 * param transition - the transition function to set
 */
void FSA::setTransition(map<string, map<string, vector<string>>> transition)
{
    m_transition = transition;
}

/* the states accessor
 *
 * return - the states to get
 */
vector<string> FSA::getStates()
{
    return m_states;
}

/* the symbols accessor
 *
 * return - the symbols to get
 */
vector<string> FSA::getSymbols()
{
    return m_symbols;
}

/* the accept states accessor
 *
 * return - the accept states to get
 */
vector<string> FSA::getAcceptStates()
{
    return m_acceptStates;
}

/* the start state accessor
 *
 * return - the start state to get
 */
vector<string> FSA::getStartState()
{
    return m_startState;
}

/* the transition accessor
 *
 * return - the transition function to get
 */
map<string, map<string, vector<string>>> FSA::getTransition()
{
    return m_transition;
}
