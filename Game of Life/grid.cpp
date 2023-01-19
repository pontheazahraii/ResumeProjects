#include "grid.h"

/* The overloaded constructor for file input
* parameter input = the input file name 
*/
Grid::Grid(string input){
    ifstream fin;  
    string line; 
    int lineNum = 1; 

    int h = 0; 

    fin.open(input); 
    while(getline(fin, line)){
        if(lineNum == 1){
            m_rows = stoi(line); 
            ++lineNum; 
        } else if (lineNum == 2){
            m_columns = stoi(line); 
            ++lineNum; 

            //make empty array 
            m_arr = new char*[m_rows]; //create the rows

            for(int i = 0; i < m_rows; ++i){ //create columns
                m_arr[i] = new char[m_columns]; 
            }
        } else {
            for(int j = 0; j < m_columns; ++j){
                m_arr[h][j] = line[j]; 
            }
            ++h; 
        }
    }
    fin.close(); 
}

/* The overloaded constructor for randomization
* parameter r = the number of rows
* parameter c = the number of columns
* parameter d = the density 
*/
Grid::Grid(int r, int c, float d){
    m_rows = r; 
    m_columns = c; 
    m_arr = new char*[m_rows]; 

    float density = d; 
    int fill = round(m_rows * m_columns * density); //fix rounding error 
    int filled = 0; 
    int randomRow; 
    int randomCol; 
    srand(time(NULL)); //new seed each time the program is run

    //initialize the arrays 
    for(int i = 0; i < m_rows; ++i){
        m_arr[i] = new char[m_columns]; 
    }

    while(fill != filled){
        randomRow = rand() % m_rows; 
        randomCol = rand() % m_columns; 

        if (m_arr[randomRow][randomCol] != 'X'){
            m_arr[randomRow][randomCol] = 'X'; 
            ++filled; 
        }
    }
}

/* The destructor */
Grid::~Grid(){
    for(int i = 0; i < m_rows; ++i){
        delete[] m_arr[i]; 
    }
    delete[] m_arr; 
}

/* The array accessor
* return m_arr = the array of the grid
*/
char** Grid::getArr(){
    return m_arr; 
}

/* The row accessor 
* return m_row = the number of rows 
*/
int Grid::getRows(){
    return m_rows; 
}

/* The column accessor 
* return m_columns = the number of columns 
*/
int Grid::getColumns(){
    return m_columns; 
}