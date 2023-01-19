#ifndef GRID_H
#define GRID_H

#include <iostream> 
#include <stdlib.h> //random 
#include <time.h> //random seed 
#include <cmath> //rounding for density 
#include <fstream> 
#include <string> 
using namespace std; 

class Grid{
    private:
    /* The populated array */
    char** m_arr; 

    /* The number of rows */
    int m_rows; 
    
    /* The number of columns */
    int m_columns; 

    public: 
    Grid(string input); //file imported 
    Grid(int r, int c, float d); //random 
    ~Grid(); 

    char **getArr(); 
    int getRows(); 
    int getColumns();  
}; 

#endif