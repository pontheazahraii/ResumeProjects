#include "student.h"

/* The default constructor */
Student::Student(){
    m_id = -1; 
    m_name = ""; 
    m_level = ""; 
    m_major = ""; 
    m_gpa = -1.0; 
    m_advisor = -1; 
}

/* The overloaded constructor 
* parameter id = the id
* parameter name = the name 
* parameter level = the level 
* parameter major = the major 
* parameter gpa = the gpa 
* parameter advisor = the advisor 
*/
Student::Student(int id, string name, string level, string major, double gpa, int advisor){
    m_id = id; 
    m_name = name; 
    m_level = level; 
    m_major = major; 
    m_gpa = gpa; 
    m_advisor = advisor; 
}

/* The destructor */
Student::~Student(){}

/* The id accessor 
* return id
*/
int Student::getID(){
    return m_id; 
}

/* the name accessor 
* return name  
*/
string Student::getName(){
    return m_name; 
}

/* the level accessor 
* return level  
*/
string Student::getLevel(){
    return m_level; 
}

/* the major accessor 
* return major 
*/
string Student::getMajor(){
    return m_major; 
}

/* the gpa accessor 
* return gpa  
*/
double Student::getGPA(){
    return m_gpa; 
}

/* the advisor accessor
* return accessor
*/
int Student::getAdvisor(){
    return m_advisor; 
}

/* the id mutator 
* parameter id = the id 
*/
void Student::setID(int id){
    m_id = id; 
}

/* the name mutator 
* parameter name = the name 
*/
void Student::setName(string name){
    m_name = name; 
}

/* the level mutator 
* parameter level = the level 
*/
void Student::setLevel(string level){
    m_level = level; 
}
/* the major mutator 
* parameter major = the major 
*/
void Student::setMajor(string major){
    m_major = major; 
}

/* the gpa mutator 
* parameter gpa = the gpa 
*/
void Student::setGPA(double gpa){
    m_gpa = gpa; 
}

/* the advisor mutator 
* parameter advisor = the advisor 
*/
void Student::setAdvisor(int advisor){
    m_advisor = advisor; 
}

/* The == overloader
*  parameter s = the student to compare to 
*  return = if two student are == 
*/
bool Student::operator==(const Student &s){
    return this->m_id == s.m_id; 
}

/* The <= overloader
*  parameter s = the student to compare to 
*  return = if two student are <= 
*/
bool Student::operator<=(const Student &s){
    return this->m_id <= s.m_id; 
}

/* The < overloader
*  parameter s = the student to compare to 
*  return = if two student are <
*/
bool Student::operator<(const Student &s){
    return this->m_id < s.m_id; 
}

/* The >= overloader
*  parameter s = the student to compare to 
*  return = if two student are >= 
*/
bool Student::operator>=(const Student &s){
    return this->m_id >= s.m_id; 
}

/* The > overloader
*  parameter s = the student to compare to 
*  return = if two student are >
*/
bool Student::operator>(const Student &s){
    return this->m_id > s.m_id; 
}

/* The != overloader
*  parameter s = the student to compare to 
*  return = if two student are != 
*/
bool Student::operator!=(const Student &s){
    return this->m_id != s.m_id; 
}

/* The << operator */
ostream& operator<<(ostream &out, Student &s){
    out << s.toString(); 
    return out; 
}

/* The >> operator */
istream& operator>>(istream &in, Student &s){
    int id; 
    string name; 
    string level; 
    string major; 
    double gpa; 
    int advisor; 

    string line; 
    char delim; 

    in >> id >> delim; 
    getline(in, name, ','); 
    getline(in, level, ','); 
    getline(in, major, ','); 
    in >> gpa >> delim; 
    in >> advisor >> delim; 
    getline(in, line); 

    s.setID(id); 
    s.setName(name); 
    s.setLevel(level); 
    s.setMajor(major); 
    s.setGPA(gpa); 
    s.setAdvisor(advisor); 

    return in; 
}

/* The toString method 
* return = all the information as a string 
*/
string Student::toString(){
    stringstream ss;
    ss << fixed << setprecision(2) << m_gpa;

    string info = ""; 
    info += to_string(m_id) + ","; 
    info += m_name + ","; 
    info += m_level + ","; 
    info += m_major + ","; 
    info += ss.str() + ","; 
    info += to_string(m_advisor) + ","; 

    return info; 
}