#include "gamemode.h"

/* The default constructor */
GameMode::GameMode(){
    m_arr1 = g->getArr(); 

    m_rows = g->getRows(); 
    m_columns = g->getColumns(); 

    m_arr2 = new char*[m_rows]; //create the rows

    for(int i = 0; i < m_rows; ++i){ //create columns
        m_arr2[i] = new char[m_columns]; 
    } 
}

/* The destructor */
GameMode::~GameMode(){
    for(int i = 0; i < m_rows; ++i){
        delete[] m_arr2[i]; 
    }
    delete[] m_arr2; 
}

/* The classic mode
* return m_arr1 = the next generation 
*/
char** GameMode::classic(){
    for (int i = 0; i < m_rows; ++i){
        for(int j = 0; j < m_columns; ++j){
            //check corners 
            if((i == 0 || i == m_rows-1) && (j == 0 || j == m_columns-1)){
                if(i == 0 && j == 0){
                    increment(0,1); 
                    increment(1,1); 
                    increment(1,0); 
                } else if (i == 0 && j == m_columns-1){
                    increment(0, m_columns-2); 
                    increment(1, m_columns-2); 
                    increment(1, m_columns-1); 
                } else if (i == m_rows-1, j == 0){
                    increment(m_rows-2, 0); 
                    increment(m_rows-2, 1); 
                    increment(m_rows-1, 1); 
                }  else {
                    increment(m_rows-2, m_columns-1); 
                    increment(m_rows-2, m_columns-2); 
                    increment(m_rows-1, m_columns-2); 
                } 
            //check edges 
            } else if ((i == 0 || i == m_rows-1) || (j == 0 || j == m_columns-1)) { 
                if(i == 0){
                    increment(0, j-1); 
                    increment(0, j+1); 
                    increment(1, j-1); 
                    increment(1, j); 
                    increment(1, j+1); 
                } else if (i == m_rows-1){
                    increment(m_rows-1, j-1); 
                    increment(m_rows-1, j+1); 
                    increment(m_rows-2, j-1); 
                    increment(m_rows-2, j); 
                    increment(m_rows-2, j+1);
                } else if (j == 0) {
                    increment(i-1, 0); 
                    increment(i+1, 0); 
                    increment(i-1, 1); 
                    increment(i, 1); 
                    increment(i+1, 1);
                } else if (j == m_columns-1){
                    increment(i-1, m_columns-1); 
                    increment(i+1, m_columns-1); 
                    increment(i-1, m_columns-2); 
                    increment(i, m_columns-2); 
                    increment(i+1, m_columns-2);
                }
            //check middle 
            } else {
                increment(i-1, j-1); 
                increment(i-1, j); 
                increment(i-1, j+1); 
                increment(i, j-1); 
                increment(i, j+1); 
                increment(i+1, j-1); 
                increment(i+1, j); 
                increment(i+1, j+1);
            }

            //check if there are two neighbors 
            if (m_surrounding == 2 && m_arr1[i][j] == 'X'){
                m_two = true; 
            } else if (m_surrounding == 2 && m_arr1[i][j] == '-'){
                m_two = false; 
            }

        m_arr2[i][j] = rules();
        }
    } 
    transfer();  
    return m_arr1; 
}

/* The doughnut mode
* return m_arr1 = the next generation 
*/
char** GameMode::doughnut(){
    for(int i = 0; i < m_rows; ++i){
        for(int j = 0; j < m_columns; ++j){
            //check edges 
            if((i == 0 || i == m_rows-1) && (j == 0 || j == m_columns-1)){
                if(i == 0 && j == 0){
                    increment(0, 1); 
                    increment(1, 1); 
                    increment(1, 0); 

                    increment(0, m_columns-1); 
                    increment(1, m_columns-1); 

                    increment(m_rows-1, 0); 
                    increment(m_rows-1, 1); 

                    increment(m_rows-1, m_columns-1); 
                } else if (i == 0 && j == m_columns-1){
                    increment(0, m_columns-2); 
                    increment(1, m_columns-2); 
                    increment(1, m_columns-1); 

                    increment(0, 0); 
                    increment(1, 0); 

                    increment(m_rows-1, m_columns-1); 
                    increment(m_rows-1, m_columns-2); 
                    
                    increment(m_rows-1, 0); 
                } else if (i == m_rows-1, j == 0){
                    increment(m_rows-2, 0); 
                    increment(m_rows-2, 1); 
                    increment(m_rows-1, 1); 

                    increment(m_rows-1, m_columns-1); 
                    increment(m_rows-2, m_columns-1); 

                    increment(0, 0); 
                    increment(0, 1); 
                    
                    increment(0, m_columns-1); 
                }  else {
                    increment(m_rows-2, m_columns-1); 
                    increment(m_rows-2, m_columns-2); 
                    increment(m_rows-1, m_columns-2); 

                    increment(m_rows-1, 0); 
                    increment(m_rows-2, 0); 

                    increment(0, m_columns-1); 
                    increment(0, m_columns-2); 
                    
                    increment(0, 0);
                }
            //check edges  
            } else if ((i == 0 || i == m_rows-1) || (j == 0 || j == m_columns-1)) { 
                if(i == 0){
                    increment(0, j-1); 
                    increment(0, j+1); 
                    increment(1, j-1); 
                    increment(1, j); 
                    increment(1, j+1); 

                    increment(m_rows-1, j-1); 
                    increment(m_rows-1, j); 
                    increment(m_rows-1, j+1);
                } else if (i == m_rows-1){
                    increment(m_rows-1, j-1); 
                    increment(m_rows-1, j+1); 
                    increment(m_rows-2, j-1); 
                    increment(m_rows-2, j); 
                    increment(m_rows-2, j+1);

                    increment(0, j-1); 
                    increment(0, j); 
                    increment(0, j+1);
                } else if (j == 0) {
                    increment(i-1, 0); 
                    increment(i+1, 0); 
                    increment(i-1, 1); 
                    increment(i, 1); 
                    increment(i+1, 1);

                    increment(i-1, m_columns-1); 
                    increment(i, m_columns-1); 
                    increment(i+1, m_columns-1); 
                } else if (j == m_columns-1){
                    increment(i-1, m_columns-1); 
                    increment(i+1, m_columns-1); 
                    increment(i-1, m_columns-2); 
                    increment(i, m_columns-2); 
                    increment(i+1, m_columns-2);

                    increment(i-1, 0); 
                    increment(i, 0); 
                    increment(i+1, 0);
                }
            //check middle 
            } else {
                increment(i-1, j-1); 
                increment(i-1, j); 
                increment(i-1, j+1); 
                increment(i, j-1); 
                increment(i, j+1); 
                increment(i+1, j-1); 
                increment(i+1, j); 
                increment(i+1, j+1);
            }
        
            //check if there are two neighbors 
            if (m_surrounding == 2 && m_arr1[i][j] == 'X'){
                m_two = true; 
            } else if (m_surrounding == 2 && m_arr1[i][j] == '-'){
                m_two = false; 
            }

        m_arr2[i][j] = rules();
        }
    }

    transfer(); 
    return m_arr1;
}

/* The mirror mode 
* return m_arr1 = the next generation 
*/
char** GameMode::mirror(){
    for (int i = 0; i < m_rows; ++i){
        for(int j = 0; j < m_columns; ++j){
            //check corners 
            if((i == 0 || i == m_rows-1) && (j == 0 || j == m_columns-1)){
                //mirror corner 
                increment(i, j); 
                increment(i, j); 
                increment(i, j); 

                if(i == 0 && j == 0){
                    increment(0,1); 
                    increment(0,1); 
    
                    increment(1,1); 

                    increment(1,0);
                    increment(1,0); 
                } else if (i == 0 && j == m_columns-1){
                    increment(0, m_columns-2);
                    increment(0, m_columns-2); 

                    increment(1, m_columns-2); 

                    increment(1, m_columns-1); 
                    increment(1, m_columns-1); 
                } else if (i == m_rows-1, j == 0){
                    increment(m_rows-2, 0); 
                    increment(m_rows-2, 0); 

                    increment(m_rows-2, 1); 

                    increment(m_rows-1, 1); 
                    increment(m_rows-1, 1); 
                }  else {
                    increment(m_rows-2, m_columns-1); 
                    increment(m_rows-2, m_columns-1); 

                    increment(m_rows-2, m_columns-2); 

                    increment(m_rows-1, m_columns-2); 
                    increment(m_rows-1, m_columns-2); 
                } 

            //check edges 
            } else if ((i == 0 || i == m_rows-1) || (j == 0 || j == m_columns-1)) { 
                increment(i, j); 
                if(i == 0){
                    increment(0, j-1); 
                    increment(0, j-1); 

                    increment(0, j+1); 
                    increment(0, j+1); 

                    increment(1, j-1); 
                    increment(1, j); 
                    increment(1, j+1); 
                } else if (i == m_rows-1){
                    increment(m_rows-1, j-1); 
                    increment(m_rows-1, j-1); 

                    increment(m_rows-1, j+1); 
                    increment(m_rows-1, j+1); 

                    increment(m_rows-2, j-1); 
                    increment(m_rows-2, j); 
                    increment(m_rows-2, j+1);
                } else if (j == 0) {
                    increment(i-1, 0);
                    increment(i-1, 0);  

                    increment(i+1, 0); 
                    increment(i+1, 0); 

                    increment(i-1, 1); 
                    increment(i, 1); 
                    increment(i+1, 1);
                } else if (j == m_columns-1){
                    increment(i-1, m_columns-1); 
                    increment(i-1, m_columns-1);

                    increment(i+1, m_columns-1); 
                    increment(i+1, m_columns-1);

                    increment(i-1, m_columns-2); 
                    increment(i, m_columns-2); 
                    increment(i+1, m_columns-2);
                }
            
            //check center 
            } else {
                increment(i-1, j-1); 
                increment(i-1, j); 
                increment(i-1, j+1); 
                increment(i, j-1); 
                increment(i, j+1); 
                increment(i+1, j-1); 
                increment(i+1, j); 
                increment(i+1, j+1);
            }
        
            //check if there are two neighbors 
            if (m_surrounding == 2 && m_arr1[i][j] == 'X'){
                m_two = true; 
            } else if (m_surrounding == 2 && m_arr1[i][j] == '-'){
                m_two = false; 
            }

        m_arr2[i][j] = rules();
        }
    } 
    transfer();  
    return m_arr1;
}

/* The rules of the game
* return char = the next generation cell
*/
char GameMode::rules(){
    char cell; 
    if (m_surrounding == 3){
        cell = 'X'; 
    } else if (m_surrounding == 2){
        if(m_two){
            cell = 'X'; 
        } else {
            cell = '-'; 
        }
    } else {
        cell = '-'; 
    }
    m_surrounding = 0; 
    return cell; 
}

/* incrementing the number of neighbors
* parameter i = the number of rows
* parameter j = the number of columns 
*/
void GameMode::increment(int i, int j){
    if(m_arr1[i][j] == 'X'){
        ++m_surrounding; 
    }
}

/* Transfer new generation to current generation*/
void GameMode::transfer(){
    for(int i = 0; i < m_rows; ++i){
        for(int j = 0; j < m_columns; ++j){
            m_arr1[i][j] = m_arr2[i][j];
        }
    }    
}