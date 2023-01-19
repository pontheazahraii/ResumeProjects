#ifndef GAMEINPUT_H
#define GAMEINPUT_H

#include "grid.h"
#include <cctype>

class GameInput{
    protected:
    /* The game mode
    * 0 = classic mode
    * 1 = doughnut mode 
    * 2 = mirror mode 
    */
    int m_mode;

    /* The population of the grid 
    * 0 = file input population
    * 1 = random population 
    */
    int m_populate;

    /* The output display 
    * 0 = brief pause between generations
    * 1 = press "enter" key
    * 2 = output file 
    */
    int m_display; 

    /* The output file name */ 
    string m_output; 

    /* The array grid*/
    Grid *g; 

    public: 
    GameInput(); 
    ~GameInput(); 
}; 

#endif