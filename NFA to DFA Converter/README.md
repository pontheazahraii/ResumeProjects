# Author

Ponthea Zahraii
2366637

# Files

- fsa.h
- fsa.cpp
- converter.h
- converter.cpp
- fileprocessor.h
- fileprocessor.cpp
- main.cpp
- Makefile

# Running Instructions

- The NFA input specification will be passed as a command line argument consisting of a file name

# File Sepecifications

## Input

- Line 1: A list of states, Q, seperated by tabs
- Line 2: A list of the symbols in Σ, seperated by tabs
  - The empty string will not be explicitly included
  - You can assume the state names do not also appear in the alphabet
- Line 3: The start state, q0 ∈ Q
- Line 4: The set of valid accept states, F, seperated by tabs
- Line 5: The token _BEGIN_ to denote the start of the transition function
- Line 6 - Line before the last: The transition function
  - Each line will be of the form **s, x = sf**
    - This is translated to mean that reading symbol x in state s causes a transition to state sf
      the string _EPS_ will be used to represent an epsilon transition
- Last Line: The token _END_ to denote the end of the transition function

## Output

- The output should be to a text file with the extension .DFA
- The output file should have the same format as the input file
- The symbol _{EM}_ is used to represent the empty state, ∅
- If {1} and {2} are states in the NFA that are comfined in the DFA, the state will be represented with the string {1, 2}

## Sources

- https://www.geeksforgeeks.org/implementing-multidimensional-map-in-c/
- https://www.techiedelight.com/check-vector-contains-given-element-cpp/
- https://cplusplus.com/articles/NhA0RXSz/
- https://stackoverflow.com/questions/11719538/how-to-use-stringstream-to-separate-comma-separated-strings
