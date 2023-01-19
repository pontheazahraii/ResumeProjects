#include "gameinput.h"

/* The default constructor
* m_populate = populates an array based on user input
* m_mode = asks user for which mode they would like to play in
* m_display = asks the user how they would like to display output
*/
GameInput::GameInput(){
    string input;
    string mapfile;  

    int rows; 
    int columns; 
    float density;

    cout << "Welcome to the Game of Life" << endl; 

    //m_populate 
    cout << "Would you to provide a map file of the world or would you like a random assignment?" << endl;
    cout << "   Input 0 to provide a map file" << endl; 
    cout << "   Input 1 for random assignment" << endl; 
    while(true){
        cout << "Input: "; 
        cin >> input; 
        if (input == "0" || input == "1"){
            m_populate = stoi(input); 
            break; 
        } else {
            cout << "Invalid input, please input 0 or 1" << endl; 
            cout << "   Input 0 to provide a map file" << endl; 
            cout << "   Input 1 for random assignment" << endl;
        }
    }

    //conditions in m_populate 
    if(m_populate == 0){
        ifstream fin; 
        cout << "What is the name of the map file you would like to use?" << endl; 
        while(true){
            cout << "Input: "; 
            cin >> mapfile; 
            fin.open(mapfile);
            if(fin){
                break; 
            } else {
                cout << "File does not exist, please try again" << endl; 
            }
        }
        fin.close(); 
        g = new Grid(mapfile); 
    } else {
        //rows 
        cout << "How many rows would you like the map to have?" << endl; 
        while(true){
            cout << "Input: ";
            cin >> input;

            if(isdigit(input[0])){
                rows = stoi(input);
            } 
            
            if (rows > 0) { //check for valid input
                break; 
            } else {
                cout << "Invalid entry, please input a positive integer" << endl; 
            }
        } 

        //columns
        cout << "How many columns would you like the map to have?" << endl; 
        while(true){
            cout << "Input: ";
            cin >> input;

            if(isdigit(input[0])){
                columns = stoi(input);
            } 
            
            if (columns > 0) { //check for valid input
                break; 
            } else {
                cout << "Invalid entry, please input a positive integer" << endl; 
            }
        }

        //density 
        cout << "What density of your map would you like to have filled?" << endl; 
        cout << "   Pick a decimal value between 0 and 1" << endl; 
        while(true){
            cout << "Input: ";
            cin >> input;

            if(isdigit(input[0])){
                density = stof(input);
            } 
            
            if (density >= 0 && density <= 1) { //check for valid input
                break; 
            } else {
                cout << "Invalid entry, please input a number between 0 and 1" << endl; 
            }
        }

        g = new Grid(rows, columns, density);
    }

    //m_mode 
    cout << "What game mode would you like to play in?" << endl;
    cout << "   Input 0 for Classic Mode" << endl; 
    cout << "   Input 1 for Doughnut Mode" << endl; 
    cout << "   Input 2 for Mirror Mode" << endl; 
    while(true){
        cout << "Input: "; 
        cin >> input; 
        if (input == "0" || input == "1" || input == "2"){
            m_mode = stoi(input); 
            break; 
        } else {
            cout << "Invalid input, please input 0, 1, or 2" << endl; 
            cout << "   Input 0 for Classic Mode" << endl; 
            cout << "   Input 1 for Doughnut Mode" << endl; 
            cout << "   Input 2 for Mirror Mode" << endl; 
        }
    }

    //m_display
    cout << "How would you like to view the output?" << endl;
    cout << "   Input 0 for a brief pause between generations" << endl; 
    cout << "   Input 1 to press the 'enter' key in order to view generations" << endl; 
    cout << "   Input 2 to output to a file" << endl; 
    while(true){
        cout << "Input: "; 
        cin >> input; 
        if (input == "0" || input == "1" || input == "2"){
            m_display = stoi(input); 
            break; 
        } else {
            cout << "Invalid input, please input 0, 1, or 2" << endl; 
            cout << "   Input 0 for a brief pause between generations" << endl; 
            cout << "   Input 1 to press the 'enter' key in order to view generations" << endl; 
            cout << "   Input 2 to output to a file" << endl; 
        }
    }

    //file name for display
    if (m_display == 2){
        cout << "What is the name of the file you would like to output to?" << endl; 
        cout << "Input: ";
        cin >> m_output;   
    }
}

/* The destructor */
GameInput::~GameInput(){
    delete g; 
}