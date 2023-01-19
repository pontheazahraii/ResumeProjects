#ifndef SIMULATION_H
#define SIMULATION_H

#include <fstream>
#include <exception>
#include "bst.h"
#include "faculty.h"
#include "student.h"
#include "genstack.h"

class Simulation{
    private:
    /* The student tree */
    BST<Student> *masterStudent; 
    /* The faculty tree */
    BST<Faculty> *masterFaculty; 

    /* The student rollback stack */
    GenStack<Student> *rollStudent; 
    /* The faculty rollback stack */
    GenStack<Faculty> *rollFaculty; 
    /* The option rollback stack */
    GenStack<int> *optionNum; 


    public: 
    Simulation(); 
    ~Simulation(); 

    void fileProcessor(); 
    bool existStudent(int id); 
    bool existFaculty(int id); 

    void allStudents(); //1
    void allFaculty(); //2
    void displayStudent(int id); //3
    void displayFaculty(int id); //4
    void addStudent(int id); //5
    void removeStudent(int id); //6
    void addFaculty(int id); //7
    void removeFaculty(int id); //8
    void exit(); //9
    void input(); //10

    int inputNum(char c); 
    void enterToContinue(); 
}; 

#endif