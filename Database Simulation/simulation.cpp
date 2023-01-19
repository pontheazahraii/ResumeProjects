#include "simulation.h"

/* The default constructor */
Simulation::Simulation(){
    masterStudent = new BST<Student>();
    masterFaculty = new BST<Faculty>();
    rollStudent = new GenStack<Student>();
    rollFaculty = new GenStack<Faculty>();
    optionNum = new GenStack<int>();

    fileProcessor();
    input();
}

/* The destructor */
Simulation::~Simulation(){
    delete masterStudent;
    delete masterFaculty;
    delete rollStudent;
    delete rollFaculty;
    delete optionNum;
}

/* The file processing class
* take all the information from the student and faculty tables
* populate the student and faculty trees
*/
void Simulation::fileProcessor(){
    ifstream fin;
    int count1 = 0;
    int count2 = 0;
    string line;
    string info = "";
    Student s;

    int id;
    string name;
    string level;
    string major;
    double gpa;
    int advisor;

    /* Reads from studentTable */
    fin.open("studentTable");
    if (fin){
        while(getline(fin, line)){
            if (count1 != 0){
                for(int i = 0; i < line.length(); ++i){
                    //id,name,level
                    if(line[i] != ','){
                        info += line[i];
                    } else {
                        if (count2 == 0){
                            id = stoi(info);
                        } else if (count2 == 1){
                            name = info;
                        } else if (count2 == 2){
                            level = info;
                        } else if (count2 == 3){
                            major = info;
                        } else if (count2 == 4){
                            gpa = stod(info);
                        } else if (count2 == 5){
                            advisor = stoi(info);
                        }
                        info = "";
                        ++count2;
                    }
                }
                s = Student(id, name, level, major, gpa, advisor);
                masterStudent->insert(new TreeNode<Student>(s));
                count2 = 0;
            }
        ++count1;
        line = "";
        }
    }
    fin.close();

    count1 = 0;
    count2 = 0;
    info = "";

    string department;
    int studentID;
    Faculty f;
    vector<int> v;
    int size;

    /* Reads from facultyTable */
    fin.open("facultyTable");
    if (fin){
        while(getline(fin, line)){
            if (count1 != 0){
                for(int i = 0; i < line.length(); ++i){
                    if(line[i] != ','){
                        info += line[i];
                    } else {
                        if (count2 == 0){
                            id = stoi(info);
                        } else if (count2 == 1) {
                            name = info;
                        } else if (count2 == 2){
                            level = info;
                        } else if (count2 == 3) {
                            department = info;
                        } else {
                            studentID = stoi(info);
                            v.push_back(studentID);
                        }
                        info = "";
                        ++count2;
                    }
                }
                f = Faculty(id, name, level, department, v);
                masterFaculty->insert(new TreeNode<Faculty>(f));
                size = v.size();
                for (int i = 0; i < size; ++i){
                    cout << "student: " << v.back() << endl;
                    v.pop_back();
                }
                count2 = 0;
            }
        ++count1;
        line = "";
        }
    }
    fin.close();
}

/* The method to print out all students
* option 1 on the menu
*/
void Simulation::allStudents(){
    std::cout << "ALL STUDENTS AND THEIR INFORMATION (SORTED BY ASCENDING ID #)" << std::endl;
    if (!masterStudent->isEmpty()){
        masterStudent->inOrder(masterStudent->getRoot());
    } else {
        std::cout << "There are no students" << std::endl;
    }
}

/* The method to print out all faculty
* option 2 on the menu
*/
void Simulation::allFaculty(){
    std::cout << "ALL FACULTY AND THEIR INFORMATION (SORTED BY ASCENDING ID #)" << std::endl;
    if (!masterFaculty->isEmpty()){
        masterFaculty->inOrder(masterFaculty->getRoot());
    } else {
        std::cout << "There are no faculty" << std::endl;
    }
}

/* The method to display a student given their student ID
* option 3 on the menu
* parameter id = the student id of the student being searched
*/
void Simulation::displayStudent(int id){
    std::cout << "DISPLAY ALL INFORMATION OF A STUDENT" << std::endl;
    Student s;
    while (true){
        s.setID(id);
        if (!masterStudent->contains(s)){
            std::cout << "Student does not exist" << std::endl;
            std::cout << "Input a valid student ID " << std::endl;
            allStudents();
            std::cout << "Input: ";
            id = inputNum('i');
        } else {
            s = masterStudent->find(s);
            std::cout << s << std::endl;
            return;
        }
    }
}

/* The method to display a faculty given their faculty ID
* option 4 on the menu
* parameter id = the faculty id of the faculty being searched
*/
void Simulation::displayFaculty(int id){ //display advisee info
    std::cout << "DISPLAY ALL INFORMATION OF A FACULTY" << std::endl;
    Faculty f;
    Student s;
    vector<int> v;
    int size;
    while (true){
        f.setID(id);
        if (!masterFaculty->contains(f)){
            std::cout << "Faculty does not exist" << std::endl;
            std::cout << "Input a valid facult ID " << std::endl;
            allFaculty();
            std::cout << "Input: ";
            id = inputNum('i');
        } else {
            f = masterFaculty->find(f);
            std::cout << f << std::endl;
            std::cout << "Advisee Information: " << std::endl; //this does not work
            v = f.getAdvisee();
            size = v.size();
            for (int i = 0; i < size; ++i){
                s.setID(v.at(i));
                s = masterStudent->find(s);
                std::cout << s << std::endl;
            }
            return;
        }
    }
}

/* the method to add a student to the DB
* option 7 on the menu
* parameter id = the id of the student being added
*/
void Simulation::addStudent(int id){ //doesnt let name be added, fixed
    std::cout << "ADD A NEW STUDENT" << std::endl;
    string input;
    Student s;
    s.setID(id);
    if (masterStudent->contains(s)) {
        std::cout << "Student already exists" << std::endl;
    } else {
        std::cout << "Creating new student. Enter name: ";
        getline(cin, input);
        getline(cin, input);
        s.setName(input);
        input = "";

        std::cout << "Creating new student. Enter grade level: ";
        getline(cin, input);
        s.setLevel(input);
        input = "";

        std::cout << "Creating new student. Enter major: ";
        getline(cin, input);
        s.setMajor(input);
        input = "";

        double gpa;
        std::cout << "Creating new student. Enter gpa: ";
        gpa = inputNum('d');

        s.setGPA(gpa);
        input = "";

        int facultyID;
        Faculty f;

        if (!masterFaculty->isEmpty()){
            while (true){
                allFaculty();
                std::cout << "Creating new student. Enter advisor ID: " << std::endl;
                facultyID = inputNum('i');
                f.setID(facultyID);
                if (!masterFaculty->contains(f)){
                    std::cout << "Faculty does not exist" << std::endl;
                } else {
                    s.setAdvisor(facultyID);
                    masterStudent->insert(s);
                    f.addStudent(id);
                    return;
                }
            }
        }
    }
}

/* the method to remove a student to the DB
* option 8 on the menu
* parameter id = the id of the student being removed
*/
void Simulation::removeStudent(int id){ 
    std::cout << "DELETE A STUDENT" << std::endl;
    Student s;
    Faculty f;
    int size;
    vector<int> v;
    while (true){
        s.setID(id);
        if (!masterStudent->contains(s)){
            std::cout << "Student does not exist" << std::endl;
            std::cout << "Input a valid student ID " << std::endl;
            allStudents();
            std::cout << "Input: ";
            id = inputNum('i');
        } else {
            s = masterStudent->find(s);
            // removeAdvisee(s.getID(), 1);
            cout << "Removed advisee!" << endl;
            masterStudent->deleteNode(s);
            return;
        }
    }
}

/* the method to add a faculty to the DB
* option 9 on the menu
* parameter id = the id of the faculty being added
*/
void Simulation::addFaculty(int id){ //can't add name, fixed
    std::cout << "ADD A NEW FACULTY" << std::endl;
    Faculty f;
    string input;
    f.setID(id);
    if (masterFaculty->contains(f)){
        std::cout << "Faculty already exists" << std::endl;
    } else {
        std::cout << "Creating new faculty. Enter name: ";
        getline(cin, input);
        getline(cin, input);
        f.setName(input);
        input = "";

        std::cout << "Creating new faculty. Enter level: ";
        getline(cin, input);
        f.setLevel(input);
        input = "";

        std::cout << "Creating new faculty. Enter department: ";
        getline(cin, input);
        f.setDepartment(input);
        input = "";

        masterFaculty->insert(f);
        return;
    }
}

/* the method to remove a faculty to the DB
* option 10 on the menu
* parameter id = the id of the faculty being removed
*/
void Simulation::removeFaculty(int id){
    std::cout << "REMOVE A FACULTY" << std::endl;
    Faculty f;
    int size;
    int facultyID;
    while (true){
        f.setID(id);
        if (!masterFaculty->contains(f)){
            std::cout << "Faculty does not exist" << std::endl;
            std::cout << "Input a valid faculty ID " << std::endl;
            allFaculty();
            std::cout << "Input: ";
            id = inputNum('i');
        } else {
            f = masterFaculty->find(f);
            masterFaculty->deleteNode(f);
            return;
        }
    }
}

/* The exit method
* take all the information from the trees and rewrite them into the DB
*/
void Simulation::exit(){ 
    ofstream fout; 
    Student s = Student(); 
    Faculty f = Faculty(); 
    string output; 
    int size; 
    fout.open("studentTable"); 
    output = "id,name,level,major,gpa,advisor,"; 
    fout << output << std::endl; 
    fout.close(); 
    fout.open("studentTable", ios::out | ios::app); 
    while (!masterStudent->isEmpty()){
        s = masterStudent->getRoot()->key;
        output = to_string(s.getID()) + ","; 
        output += s.getName() + ","; 
        output += s.getLevel() + ","; 
        output += s.getMajor() + ",";
        output += to_string(s.getGPA()) + ","; 
        masterStudent->deleteNode(s);
        fout << output << std::endl; 
    }
    fout.close();

    fout.open("facultyTable"); 
    output = "id,name,level,department,advisee list,"; 
    fout << output << std::endl; 
    fout.close(); 
    fout.open("facultyTable", ios::out | ios::app); 
    while (!masterFaculty->isEmpty()){
        f = masterFaculty->getRoot()->key;
        output = to_string(f.getID()) + ",";
        output += f.getName() + ",";
        output += f.getLevel() + ",";
        output += f.getDepartment() + ",";
        masterFaculty->deleteNode(f);
        fout << output << std::endl; 
    }
    fout.close();  
}

/* The input method */
void Simulation::input(){
    string option;
    int input;
    int num;
    while(true) {
        std::cout << "Input an integer for your selection: " << std::endl;
        std::cout << "   1.  Print all students and their information (sorted by ascending ID #)" << std::endl;
        std::cout << "   2.  Print all faculty and their information (sorted by ascending ID #)" << std::endl;
        std::cout << "   3.  Display all information of a student" << std::endl;
        std::cout << "   4.  Display all information of a faculty" << std::endl;
        std::cout << "   5.  Add a new student" << std::endl;
        std::cout << "   6.  Delete a student" << std::endl;
        std::cout << "   7.  Add a new faculty" << std::endl;
        std::cout << "   8.  Delete a faculty" << std::endl;
        std::cout << "   9.  Exit" << std::endl;
        std::cout << "Input: ";

        input = inputNum('i');

        if(input <= 11 && input >= 1) {
            while (true) {
                if(input == 1) {
                    allStudents();
                    enterToContinue();
                } else if (input == 2) {
                    allFaculty();
                    enterToContinue();
                } else if (input == 3) {
                    if (!masterStudent->isEmpty()){
                        std::cout << "Please enter a student ID: ";
                        displayStudent(inputNum('i'));
                    } else {
                        allStudents();
                    }
                    enterToContinue();
                } else if (input == 4) {
                    if (!masterFaculty->isEmpty()){
                        std::cout << "Please enter a faculty ID: ";
                        displayFaculty(inputNum('i'));
                    } else {
                        allFaculty();
                    }
                    enterToContinue();
                } else if (input == 5) {
                    std::cout << "Please enter a student ID: ";
                    addStudent(inputNum('i'));
                    enterToContinue();
                    num = 7;
                } else if (input == 6) {
                    if (!masterStudent->isEmpty()){
                        std::cout << "All student: " << std::endl;
                        allStudents();
                        std::cout << "Please enter a student ID: ";
                        removeStudent(inputNum('i'));
                        num = 8;
                    } else {
                        allStudents();
                    }
                    enterToContinue();
                } else if (input == 7) {
                    std::cout << "Please enter a faculty ID: ";
                    addFaculty(inputNum('i'));
                    enterToContinue();
                    num = 9;
                } else if (input == 8) {
                    if (!masterFaculty->isEmpty()){
                        std::cout << "All Faculty:" << std::endl;
                        allFaculty();
                        std::cout << "Please enter a faculty ID: ";
                        removeFaculty(inputNum('i'));
                        num = 10;
                    } else {
                        allFaculty();
                    }
                    enterToContinue();
                } else if (input == 9) {
                    exit();
                    std::cout << "exited" << std::endl;
                    return;
                }
                break;
            }
        }
    }
}

/* The method to check if a string is a number
*  parameter c = whether the number is a int or double
*  return the string converted to a number
*/
int Simulation::inputNum(char c){
    string input;
    while(true) {
        try {
            cin >> input;
            if (c == 'i'){
                return stoi(input);
            } else if (c == 'd'){
                return stod(input);
            }
        } catch (exception e) {
            std::cout << "Invalid Input. Try again: ";
        }
    }
}

/* The enter to continue method  */
void Simulation::enterToContinue(){
    std::cout << "Press 'enter' to continue to the menu: ";
    cin.ignore();
    cin.get();
}
