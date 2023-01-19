#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std; 

class Student{
    private:
    /* the id */
    int m_id; 
    /* the name */
    string m_name; 
    /* the level */
    string m_level; 
    /* the major */
    string m_major;
    /* the gpa */
    double m_gpa; 
    /* the advisor */
    int m_advisor; 
    
    public: 
    Student(); 
    Student(int id, string name, string level, string major, double gpa, int advisor); 
    ~Student(); 

    
    int getID(); 
    string getName(); 
    string getLevel(); 
    string getMajor();
    double getGPA(); 
    int getAdvisor(); 

    void setID(int id);
    void setName(string name); 
    void setLevel(string level); 
    void setMajor(string major); 
    void setGPA(double gpa); 
    void setAdvisor(int advisor); 

    bool operator==(const Student &s);  
    bool operator<=(const Student &s);
    bool operator<(const Student &s);
    bool operator>=(const Student &s);
    bool operator>(const Student &s);
    bool operator!=(const Student &s);

    friend ostream& operator<<(ostream &out, Student &s); 
    friend istream& operator>>(istream &in, Student &s);

    string toString(); 
}; 

#endif