#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "gameinput.h"

class GameMode : public GameInput{
    protected:
    /* The current generation array */ 
    char **m_arr1;

    /* The next generation array*/
    char **m_arr2; 

    /* The number of rows */
    int m_rows; 

    /* The number of columns */
    int m_columns; 

    /* The number of neighbors */
    int m_surrounding; 

    /* If there are two neighbors */
    bool m_two;

    public: 
    GameMode(); 
    ~GameMode(); 

    char** classic(); 
    char** mirror(); 
    char** doughnut(); 

    char rules(); 
    void increment(int i, int j); 
    void transfer(); 
}; 

#endif