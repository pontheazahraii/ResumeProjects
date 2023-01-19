#include "faculty.h"

/* The default constructor */
Faculty::Faculty() {
    m_id = -1; 
    m_name = ""; 
    m_level = ""; 
    m_department = ""; 
    m_advisee = vector<int>(); 
}

/* The overloaded constructor 
* parameter id = the id
* parameter name = the name 
* parameter level = the level 
* parameter department = the department 
* parameter advisee = the advisee list 
*/
Faculty::Faculty(int id, string name, string level, string department, vector<int> advisee){
    m_id = id; 
    m_name = name; 
    m_level = level; 
    m_department = department; 
    m_advisee = advisee; 
}

/* The destructor */
Faculty::~Faculty(){}

/* The id accessor 
*  return = the id 
*/
int Faculty::getID(){
    return m_id; 
} 

/* The name accessor 
*  return = the name 
*/
string Faculty::getName(){
    return m_name; 
}

/* The level accessor 
*  return = the level 
*/
string Faculty::getLevel(){
    return m_level; 
} 

/* The department accessor 
*  return = the department 
*/
string Faculty::getDepartment(){
    return m_department; 
}

/* The advisee list accessor 
*  return = the advisee list 
*/
vector<int> Faculty::getAdvisee(){
    return m_advisee; 
}

/* The id mutator 
*  parameter id = the id 
*/
void Faculty::setID(int id){
    m_id = id; 
}

/* The name mutator 
*  parameter name = the name 
*/
void Faculty::setName(string name){
    m_name = name; 
} 

/* The level mutator 
*  parameter level = the level 
*/
void Faculty::setLevel(string level){
    m_level = level; 
}

/* The department mutator 
*  parameter department = the department 
*/
void Faculty::setDepartment(string department){
    m_department = department; 
}

/* The advisee list mutator 
*  parameter advisee = the advisee list  
*/
void Faculty::setAdvisee(vector<int> advisee){
    m_advisee = advisee; 
}

/* The == overloader
*  parameter f = the faculty to compare to 
*  return = if two faculty are == 
*/
bool Faculty::operator==(const Faculty &f){
    return this->m_id == f.m_id; 
}

/* The <= overloader
*  parameter f = the faculty to compare to 
*  return = if two faculty are <= 
*/
bool Faculty::operator<=(const Faculty &f){
    return this->m_id <= f.m_id; 
}

/* The < overloader
*  parameter f = the faculty to compare to 
*  return = if two faculty are < 
*/
bool Faculty::operator<(const Faculty &f){
    return this->m_id < f.m_id; 
}

/* The >= overloader
*  parameter f = the faculty to compare to 
*  return = if two faculty are >= 
*/
bool Faculty::operator>=(const Faculty &f){
    return this->m_id >= f.m_id; 
}

/* The > overloader
*  parameter f = the faculty to compare to 
*  return = if two faculty are > 
*/
bool Faculty::operator>(const Faculty &f){
    return this->m_id > f.m_id; 
}

/* The != overloader
*  parameter f = the faculty to compare to 
*  return = if two faculty are != 
*/
bool Faculty::operator!=(const Faculty &f){
    return this->m_id != f.m_id; 
}

/* The << overloader */
ostream& operator<<(ostream &out, Faculty &f){
    out << f.toString(); 
    return out; 
}

/* The >> overloader */
istream& operator>>(istream &in, Faculty &f){
    int id; 
    string name; 
    string level; 
    string department; 
    vector<int> *advisee; 

    int student; 
    string line; 
    char delim;  
    
    in >> id >> delim; 
    getline(in, name, ','); 
    getline(in, level, ','); 
    getline(in, department, ','); 

    getline(in, line); 
    stringstream ss(line); 
    while (!ss.eof() && line != ""){
        ss >> student >> delim; 
        if (student) {
            f.addStudent(student); 
        }
    }

    f.setID(id); 
    f.setName(name); 
    f.setLevel(level); 
    f.setDepartment(department); 

    return in;     
}

/* The toString method 
* return = all the information as a string 
*/
string Faculty::toString(){
    string info = ""; 
    int size; 

    info += to_string(m_id) + ","; 
    info += m_name + ","; 
    info += m_level + ","; 
    info += m_department + ","; 
    
    size = m_advisee.size(); 
    for (int i = 0; i < size; ++i){
        info += to_string(m_advisee.back()) + ","; 
        m_advisee.pop_back(); 
    }
    return info; 
}

/* The method to add a student to the advisee list 
* parameter student = to add to the advisee list 
*/
void Faculty::addStudent(int student){
    m_advisee.push_back(student); 
}