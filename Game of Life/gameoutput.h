#ifndef GAMEOUTPUT_H
#define GAMEOUTPUT_H

#include "gamemode.h"
#include <unistd.h> //pausing 

class GameOutput : public GameMode{
    private: 
    /* The generation number */
    int m_gen;

    /* The previous generation */ 
    char** m_prev; 

    /* The second previous generation */
    char** m_prev2; 

    public: 
    GameOutput(); 
    ~GameOutput(); 

    bool isEmpty(); 
    bool isOscillating(); 
    bool isStable(); 

    void output(char** arr); 
}; 

#endif