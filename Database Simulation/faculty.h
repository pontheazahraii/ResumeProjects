#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std; 

class Faculty{
    private:
    /* The id */
    int m_id; 
    /* The name */
    string m_name; 
    /* The level */
    string m_level; 
    /* The department */
    string m_department;
    /* The advisee list */
    vector<int> m_advisee; 
    
    public: 
    Faculty(); 
    Faculty(int id, string name, string level, string department, vector<int> advisee); 
    ~Faculty(); 

    
    int getID(); 
    string getName(); 
    string getLevel(); 
    string getDepartment(); 
    vector<int> getAdvisee(); 

    void setID(int id);
    void setName(string name); 
    void setLevel(string level); 
    void setDepartment(string department); 
    void setAdvisee(vector<int> advisee); 

    bool operator==(const Faculty &f);  
    bool operator<=(const Faculty &f);
    bool operator<(const Faculty &f);
    bool operator>=(const Faculty &f);
    bool operator>(const Faculty &f);
    bool operator!=(const Faculty &f);

    friend ostream& operator<<(ostream &out, Faculty &f); 
    friend istream& operator>>(istream &in, Faculty &f);

    string toString(); 
    void addStudent(int student); 
}; 

#endif