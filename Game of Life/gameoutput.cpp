#include "gameoutput.h"

/* The default constructor */
GameOutput::GameOutput(){
    m_gen = 0;
    m_prev = new char*[m_rows]; 
    m_prev2 = new char*[m_rows];

    for(int i = 0; i < m_rows; ++i){
        m_prev[i] = new char[m_columns]; 
        m_prev2[i] = new char[m_columns]; 
    }

    output(m_arr1); 

    while(!(isStable() || isEmpty() || isOscillating())){
        ++m_gen; 
        if(m_mode == 0){
            output(classic());
        } else if (m_mode == 1){
            output(doughnut()); 
        } else {
            output(mirror()); 
        }
    }

    if(m_display == 0 || m_display == 1){
        cout << "Press 'enter' to exit the program "; 
        cin.ignore(); 
        cin.get();
    } 
}

/* The destructor */
GameOutput::~GameOutput(){
    for(int i = 0; i < m_rows; ++i){
        delete[] m_prev[i]; 
    }
    delete[] m_arr2; 
}

/* Checking if the 2-D array is empty
* return isEmpty 
*   true = the array is empty 
*   false = the array is not empty 
*/
bool GameOutput::isEmpty(){
    bool isEmpty = true;  
    for(int i = 0; i < m_rows; ++i){
        for(int j = 0; j < m_columns; ++j){
            if(m_arr1[i][j] == 'X'){
                isEmpty = false; 
                goto end; 
            }
        }
    }
    end:
    return isEmpty; 
}

/* Checking if the 2-D array is oscillating
* return isOscillating
*   true = the array is oscillating 
*   false = the array is not oscillating
*/
bool GameOutput::isOscillating(){
    bool isOscillating = true; 
    int count = 0; 
    if(m_gen > 1){
        for(int i = 0; i < m_rows; ++i){
            for(int j = 0; j < m_columns; ++j){
                if(m_arr1[i][j] == m_prev2[i][j]){
                    ++count; 
                } 
            }
        }
    }
    if(count != m_rows*m_columns){
        isOscillating = false; 
    }
    if(m_gen == 0){
        for(int i = 0; i < m_rows; ++i){
            for(int j = 0; j < m_columns; ++j){
                m_prev2[i][j] = m_arr1[i][j]; 
            }
        }
    } else if (m_gen == 1){
        for(int i = 0; i < m_rows; ++i){
            for(int j = 0; j < m_columns; ++j){
                m_prev[i][j] = m_arr1[i][j]; 
            }
        }
    } else {
        for(int i = 0; i < m_rows; ++i){
            for(int j = 0; j < m_columns; ++j){
                m_prev2[i][j] = m_prev[i][j]; 
                m_prev[i][j] = m_arr1[i][j]; 
            }
        }
    }
    return isOscillating; 
}

/* Checking if the 2-D array is stable
* return isStable
*   true = the array is stable
*   false = the array is not stable 
*/
bool GameOutput::isStable(){
    bool isStable = true; 
    int count = 0; 
    if(m_gen > 0){
        for(int i = 0; i < m_rows; ++i){
            for(int j = 0; j < m_columns; ++j){
                if(m_prev[i][j] == m_arr1[i][j]){
                    ++count; 
                }
            }
        }
    }

    if(count != m_rows*m_columns){
        isStable = false; 
    }

    for(int i = 0; i < m_rows; ++i){
        for(int j = 0; j < m_columns; ++j){
            m_prev[i][j] = m_arr1[i][j]; 
        }
    }
    return isStable; 
}

/* The output method 
* parameter arr = the array to ouput
* outputs array based on the display condition 
*/
void GameOutput::output(char** arr){
    if (m_display == 0){
        cout << m_gen << endl; 
        for(int i = 0; i < m_rows; ++i){
            for(int j = 0; j < m_columns; ++j){
                cout << arr[i][j]; 
            }
            cout << endl; 
        }
        sleep(1);

    } else if (m_display == 1){
        cin.get(); 
        cout << m_gen << endl; 
        for(int i = 0; i < m_rows; ++i){
            for(int j = 0; j < m_columns; ++j){
                cout << arr[i][j]; 
            }
            cout << endl; 
        }
    } else {
        ofstream fout; 
        fout.open(m_output, ios::out | ios::app);
        fout << m_gen << endl; 
        for(int i = 0; i < m_rows; ++i){
            for(int j = 0; j < m_columns; ++j){
                fout << arr[i][j]; 
            }
            fout << endl; 
        }
        fout.close();   
    }
}