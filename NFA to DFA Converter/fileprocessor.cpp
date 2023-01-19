#include "fileprocessor.h"

/* The default constructor */
FileProcessor::FileProcessor() {}

/* The overloaded constructor 
* param input - The input file
*/
FileProcessor::FileProcessor(string input)
{
    m_input = input;
    m_output = "output.DFA";
}

/* The destructor */
FileProcessor::~FileProcessor() {}

/* The input modifier 
* param input - the input file 
*/
void FileProcessor::setInput(string input)
{
    m_input = input;
}

/* The output modifier 
* param output - the output file 
*/
void FileProcessor::setOutput(string output)
{
    m_output = output;
}

/* The input accessor 
* return - the input file 
*/
string FileProcessor::getInput()
{
    return m_input;
}

/* The output accessor 
* return - the output file 
*/
string FileProcessor::getOutput()
{
    return m_output;
}

/* The input file method
* This method reads and input file to extract and NFA from it 
* 
* return - The NFA that is in the input file  
*/
FSA FileProcessor::input()
{
    FSA nfa;
    ifstream fin;
    string line;
    int lineNum = 1;
    map<string, map<string, vector<string>>> transition;
    int size;

    string currState = "";
    string transSymbol = "";
    string nextState = "";
    string tempStr = "";

    vector<string> nStates;
    vector<string> nSymbols;

    fin.open(m_input);
    while (getline(fin, line))
    {
        // A list of states, Q, seperated by tabs
        if (lineNum == 1)
        {
            nStates = split(line, '\t');
            nfa.setStates(nStates);
        }
        // A list of the symbols in Σ, seperated by tabs
        else if (lineNum == 2)
        {
            nSymbols = split(line, '\t');
            nSymbols.push_back("EPS");
            nfa.setSymbols(nSymbols);
        }
        // The start state, q0 ∈ Q
        else if (lineNum == 3)
        {
            vector<string> nStartState = split(line, ' ');
            nfa.setStartState(nStartState);
        }
        // The set of valid accept states, F, seperated by tabs
        else if (lineNum == 4)
        {
            nfa.setAcceptStates(split(line, '\t'));
        }
        // The transition function
        // s, x = sf - extract this format from the string 
        else if (lineNum >= 5 && line != "BEGIN" && line != "END")
        {
            bool comma = false;
            bool equal = false;
            for (int i = 0; i < line.size(); ++i)
            {
                if (!comma && !equal)
                {
                    if (line[i] == ',')
                    {
                        comma = true;
                        currState = tempStr;
                        tempStr = "";
                    }
                    else if (line[i] != ' ')
                    {
                        tempStr += line[i];
                    }
                }
                else if (comma && !equal)
                {
                    if (line[i] == '=')
                    {
                        equal = true;
                        transSymbol = tempStr;
                        tempStr = "";
                    }
                    else if (line[i] != ' ')
                    {
                        tempStr += line[i];
                    }
                }
                else if (line[i] != ' ')
                {
                    tempStr += line[i];
                }
            }
            nextState = tempStr;
            tempStr = "";
        }
        ++lineNum;
        transition[currState][transSymbol].push_back(nextState);
    }
    // set all the states that are not included to Empty 
    for (int i = 0; i < nStates.size(); ++i)
    {
        for (int j = 0; j < nSymbols.size(); ++j)
        {
            if (transition[nStates[i]][nSymbols[j]].size() == 0)
            {
                transition[nStates[i]][nSymbols[j]] = {"{EM}"};
            }
        }
    }
    nfa.setTransition(transition);
    fin.close();
    return nfa;
}

/* The output file method 
* This method outputs a converted DFA to a file 
* 
* param nfa - the NFA to convert 
*/
void FileProcessor::output(FSA nfa)
{
    Converter c = Converter(nfa);
    FSA dfa = c.getDFA();

    vector<string> states = dfa.getStates();
    vector<string> symbols = dfa.getSymbols();
    vector<string> startState = dfa.getStartState();
    vector<string> acceptStates = dfa.getAcceptStates();
    map<string, map<string, vector<string>>> transition = dfa.getTransition();

    ofstream fout;
    fout.open(m_output, ios::out);

    string s = "";

    // A list of states, Q, seperated by tabs
    for (int i = 0; i < states.size(); ++i)
    {
        s += "{" + strip(states[i]) + "}\t";
    }
    fout << s << endl;
    s = "";

    // A list of the symbols in Σ, seperated by tabs
    for (int i = 0; i < symbols.size(); ++i)
    {
        s += symbols[i] + "\t";
    }
    fout << s << endl;
    s = "";

    // The start state, q0 ∈ Q
    s += "{" + strip(startState[0]);
    for (int i = 1; i < startState.size(); ++i)
    {
        s += "," + strip(startState[i]);
    }
    s += "}";
    fout << s << endl;
    s = "";

    // The set of valid accept states, F, seperated by tabs
    for (int i = 0; i < acceptStates.size(); ++i)
    {
        s += "{" + strip(acceptStates[i]) + "}\t";
    }
    fout << s << endl;
    s = "";

    // The transition function
    // s, x = sf - the format of the output 
    fout << "BEGIN" << endl;
    for (int i = 0; i < states.size(); ++i)
    {
        for (int j = 0; j < symbols.size(); ++j)
        {
            for (int k = 0; k < transition[states[i]][symbols[j]].size(); ++k)
            {
                s += "{" + strip(states[i]) += "}, ";
                s += "{" + strip(symbols[j]) += "} = ";
                s += "{" + strip(transition[states[i]][symbols[j]][k]) += "}";
                fout << s << endl;
                s = "";
            }
        }
    }
    fout << "END" << endl;

    fout.close();
}

/* The method to split a string
 * This method splits a string given a delimiter
 *
 * param s - the string to split
 * param del - the delimiter
 * return - a vector of strings that are split on the delimiter
 */
vector<string> FileProcessor::split(string s, char del)
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

/* The method strips a string of its curly braces 
* 
* param s - the string to strip 
* return - the striped string 
*/
string FileProcessor::strip(string s)
{
    string t = "";
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] != '{' && s[i] != '}')
        {
            t += s[i];
        }
    }

    return t;
}
