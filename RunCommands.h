/**
 * RunCommands.h runs a simulation of the Student Database
 * 
 * @author Devin Keller and Ori G
 * @version 1.0
 * @see RunCommands.h
 * 
 */

#include <iostream>
#include <string>
//Imports the Student.h class to RunCommands
#include "Student.h"
//Imports the Faculty.h class to RunCommands
#include "Faculty.h"
//Imports the Affiliate.h class to RunCommands
#include "Affiliate.h"
//Imports the Student.h class to RunCommands
#include "Prompts.h"
//Imports the bst template file to RunCommands
#include "bst.h"
#include <fstream>
#include <sstream>
using namespace std;

//Creates RunCommands class
class RunCommands{
public:
    RunCommands();
    ~RunCommands();
    void takeCommands();
    void insertStudent(Student &s);
    void insertFaculty(Faculty &f);
    void fileReading(string f, string s);
    void fileWriting();

private:
    string facultyFile;
    string studentFile;
    BST<Student> *students;
    BST<Faculty> *faculty;
    DoublyLinkedList<string> *rollBackList;
};

//Default Constructor
RunCommands::RunCommands(){
    students = new BST<Student>();
    faculty = new BST<Faculty>();
}
//Default Destructor
RunCommands::~RunCommands(){

}
//take commands simulates the student database
void RunCommands::takeCommands(){
    fileReading("masterFaculty.csv", "masterStudent.csv");
    Prompts *ask = new Prompts();
    string id_;
    string name;
    string year;
    string major;
    string gpa_;
    string advisor_;
    string level;
    string department;
    //Creates DoublyLinkedList that houses strings for the rollback command
    rollBackList = new DoublyLinkedList<string>;
    bool isTrue = false;
    //Makes loops keep running until user exits it
    while(isTrue == false){
        //Asks student what command they want to use
        int getNum = ask->returnPrompts();
        //Prints student info
        if(getNum == 1){
            students->printInfo();
        }
        //Print faculty Info
        if(getNum == 2){
            faculty->printInfo();
        }
        //Takes in ID and displays that student's info
        if(getNum == 3){
            cout<<"Enter the student ID: "<<endl;
            cin>>id_;
            int id = stoi(id_);
            students->printElement(id);
        }

        //Takes ID of faculty and displays that faculty's info
        if(getNum == 4){
            cout<<"Enter the faculty ID: "<<endl;
            cin>>id_;
            int id = stoi(id_);
            faculty->printElement(id);
        }
        //display a students advisor given their ID
        if(getNum == 5){
            cout<<"Enter the Student ID: "<<endl;
            cin>>id_;
            int id = stoi(id_);
            //find the student and save their advisors id
            int facId = students->findId(id)->key.getAdvisor();
            faculty->printElement(facId);
        }
        //display all the advisor's students given the advisors id
        if(getNum==6){
            cout<<"Enter the faculty ID: "<<endl;
            cin>>id_;
            int id = stoi(id_);
            Faculty temporary = faculty->findId(id)->key;
            //Iterates through temporary IDs and displays the ID's of all the students
            for(int i = 0; i<temporary.StudentIDs->getSize();++i){
                int x = temporary.StudentIDs->removeBack();
                temporary.StudentIDs->insertFront(x);
                students->printElement(x);
            }
        }
        //Adds a student to the database
        if(getNum==7){
            cout<<"Enter Student ID: "<<endl;
            cin>> id_;
            cout <<"Enter student name: "<<endl;
            cin>>name;
            cout<<"Enter student's year: "<<endl;
            cin>>year;
            cout<<"Enter student's major: "<<endl;
            cin>>major;
            cout<<"Enter student's GPA: "<<endl;
            cin>>gpa_;
            cout<<"Enter the student's advisor's ID: "<<endl;
            cin>>advisor_;
            //Adds student info to rollback list so we can run rollback
            rollBackList->insertBack(advisor_);
            rollBackList->insertBack(gpa_);
            rollBackList->insertBack(major);
            rollBackList->insertBack(year);
            rollBackList->insertBack(name);
            rollBackList->insertBack(id_);
            rollBackList->insertBack("Add Student");
        
            int id = stoi(id_);
            double gpa = stod(gpa_);
            int advisor = stoi(advisor_);
            
            //Creates a new student and ands them to the database with their info
            insertStudent(*new Student(id,name,year,major,gpa,advisor));
             //Use search command in the doublyLinkedLinked to search for Advisors Id
            Faculty addToFac = faculty->findId(advisor)->key;
            //add Student ID to faculty's advisee lists
            addToFac.addAdvisee(id);
        }

        //Deletes a student given thier ID number
        if(getNum == 8){
            cout<<"Enter the student ID: "<<endl;
            cin>>id_;
            int id = stoi(id_);
            //finds ID of student
            Student temp = students->findId(id)->key;
            //delete student from BST
            bool deleted = students->deleteNode(temp);
            int adv = temp.getAdvisor();
            Faculty temporary = faculty->findId(adv)->key;
            for(int i = 0;i<temporary.StudentIDs->getSize();++i){
                int x = temporary.StudentIDs->removeBack();
                if(x == id){
                    break;
                }
                else{
                    temporary.StudentIDs->insertFront(x);
                }
            }
            //inserts the command that needs to be done in rollback
            rollBackList->insertBack("Delete Student");
        }
        //Adds a faculty member to the database
        if(getNum==9){
            //gets faculty data from user
            cout<<"Enter faculty ID: "<<endl;
            cin>> id_;
            cout <<"Enter faculty name: "<<endl;
            cin>>name;
            cout<<"Enter faculty's level: "<<endl;
            cin>>level;
            cout<<"Enter faculty's department: "<<endl;
            cin>>department;
            int id = stoi(id_);
            //inserts faculty in the bst
            insertFaculty(*new Faculty(id,name,level,department));
        }

        //Deletes a falculty member from BST given their ID
        if(getNum == 10){
            //gets ID
            cout<<"Enter the faculty ID: "<<endl;
            cin>>id_;
            int id = stoi(id_);
            //Deletes Falculty
            Faculty temp = faculty->findId(id)->key;
            cout<<temp.getId()<<endl;
            bool deleted = faculty->deleteNode(temp);
            cout<<temp.getId()<<endl;
        }
        //changes a student's advisor given ID and new Falculty Id
        if(getNum==11){
            int tempid;
            cout<<"Enter the student ID: "<<endl;
            cin>>id_;
            int id = stoi(id_);
            //finds student
            Student temp = students->findId(id)->key;
            int adv = temp.getAdvisor();
            //Finds falculty member
            Faculty temporary = faculty->findId(adv)->key;
            cout<<temporary.toString()<<endl;
            //Gets new Falc ID
            cout<<"Enter new faculty id: "<<endl;
            cin >>tempid;
            students->findId(id)->key.setAdvisor(tempid);
            //Deletes student from BST
            for(int i = 0;i<temporary.StudentIDs->getSize();++i){
                int x = temporary.StudentIDs->removeBack();
                if(x == id){
                    break;
                }
                else{
                    temporary.StudentIDs->insertFront(x);
                }
            }
            Faculty temporary1 = faculty->findId(tempid)->key;
            temporary1.StudentIDs->insertFront(id);
        }
        //remove an advisee from a fac member and removes studnet ID from falc list
        if(getNum==12){
            //gets id of fac that wants the student to leave
            int adv;
            cout<<"Enter faculty id you wish to edit"<<endl;
            cin>>adv;
            Faculty temporary = faculty->findId(adv)->key;
            //Gets Id of studnet you want to remove
            int id;
            cout<<"Enter the student ID you wish to remove"<<endl;
            cin>>id;
            //Removes Students from Database
            for(int i = 0;i<temporary.StudentIDs->getSize();++i){
                int x = temporary.StudentIDs->removeBack();
                if(x == id){
                    break;
                }
                else{
                    temporary.StudentIDs->insertFront(x);
                }
            }
            //temporary.StudentIDs->removeNode(id);
        }
        //rollback function undos the last command that changed the database
        if(getNum==13){
            cout << endl;
            string temp1 = rollBackList->removeBack();
            cout << temp1 <<endl;

            //IF THE LAST COMMAND WAS ADDING A STUDENT
            if(temp1 == "Add Student"){
                cout<<"Enter the student ID: "<<endl;
                //Gets student info from rollBackList
                string temp2 = rollBackList->removeBack();
                int id = stoi(temp2);
                Student temp = students->findId(id)->key;
                //gets thier advisor ID
                bool deleted = students->deleteNode(temp);
                int adv = temp.getAdvisor();
                Faculty temporary = faculty->findId(adv)->key;
                //Deletes Student
                for(int i = 0;i<temporary.StudentIDs->getSize();++i){
                    int x = temporary.StudentIDs->removeBack();
                    if(x == id){
                        break;
                    }
                    else{
                        temporary.StudentIDs->insertFront(x);
                    }
                }
                cout << "Student Deleted" << endl;
            }

            //IF LAST COMMAND WAS DELETING A STUDENT
            if (temp1 == "Delete Student"){
                //Gets student info from rollBackList
                rollBackList->removeBack();
                string id_ = rollBackList->removeBack();
                cout << "id: " << id_ << endl;
                string name = rollBackList->removeBack();
                cout << "name: " << name << endl;
                string year = rollBackList->removeBack();
                string major = rollBackList->removeBack();
                string gpa_ = rollBackList->removeBack();
                string advisor_ = rollBackList->removeBack();
                cout << id_ << endl;
                int id = stoi(id_);
                double gpa = stod(gpa_);
                int advisor = stoi(advisor_);
                cout << "Student added" << endl;
            
                insertStudent(*new Student(id,name,year,major,gpa,advisor));
                Faculty addToFac = faculty->findId(advisor)->key;
                addToFac.addAdvisee(id);
            }
        }
        //User exits program and outputs database to csv file
        if(getNum == 14){
            isTrue = true;
            cout<<"Goodbye"<<endl;
        }

    }
    fileWriting();
}

//insertStudent inserts student to the database
void RunCommands::insertStudent(Student &s){
    students->insert(s);
}

//insertFaculty inserts faculty to the database
void RunCommands::insertFaculty(Faculty &f){
    faculty->insert(f);
}

void RunCommands::fileReading(string f, string s){
    //f = "Faculty.csv"; //test
    //s = "Stuent.csv"; //test
    facultyFile = f;
    studentFile = s;
    ifstream ff;
    //opens Falulty's file
    ff.open(facultyFile);
    ifstream ss;
    string line;
    string facA[4];
    //Gets lines off of file
    while(getline(ff,line)){
        stringstream s_stream(line); //create string stream from the string
        //if lines to read
        while(s_stream.good()) {
            for(int i = 0; i<4;++i){
                getline(s_stream, facA[i], ',');
            }
            //insert each falculty member to BST
            insertFaculty(*new Faculty(stoi(facA[0]),facA[1],facA[2],facA[3]));
           
         }
    }

    //Opens Students File
    ss.open(studentFile);
    string studA[6];
    //grabs every line from falculty file
    while(getline(ss,line)){
        stringstream s_streamS(line); //create string stream from the string
        //while there are lines to read
        while(s_streamS.good()) {
            for(int i = 0; i<6;++i){
                getline(s_streamS, studA[i], ',');
            }
            //Creates student finds falculty ID and adds student ID to falculty advisees 
            Student temp(stoi(studA[0]),studA[1],studA[2],studA[3],stod(studA[4]), stoi(studA[5]));
            insertStudent(temp);
            Faculty addToFac = faculty->findId(stoi(studA[5]))->key;
            addToFac.addAdvisee(stoi(studA[0]));

         }
    }
}

//Writes database to text file
void RunCommands::fileWriting(){
    ofstream fac;
    Faculty tempF;
    //opens falcultyFile
    fac.open(facultyFile);
    //for every falculty add them to the text file
    for(int i = 0; i<faculty->getSize();++i){
        if(i == 0){
            tempF = faculty->iterate(1)->key;
        }
        else{
            tempF = faculty->iterate(2)->key;
        }
        fac<<to_string(tempF.getId())<<","<<tempF.getName()<<","<<tempF.getLevel()<<","<<tempF.getDepartment()<<endl;
    }
    //closes falculty file
    fac.close();

    ofstream stud;
    Student temp;
    //Opens student file and adds every student from database to that file
    stud.open(studentFile);
    for(int i = 0; i<students->getSize();++i){
        if(i == 0){
            temp = students->iterate(1)->key;
        }
        else{
            temp = students->iterate(2)->key;
        }
        stud<<to_string(temp.getId())<<","<<temp.getName()<<","<<temp.getYear()<<","<<temp.getMajor()<<","<<to_string(temp.getGpa())<<","<<to_string(temp.getAdvisor())<<endl;
    }
    //closes student file
    stud.close();
}
