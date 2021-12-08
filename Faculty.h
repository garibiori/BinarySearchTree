/**
 * Faculty.h creates a faculty class that represents every faculty member
 * 
 * @author Devin Keller and Ori G
 * @version 1.0
 * @see Faculty.h
 * 
 */

#ifndef FACULTY_H
#define FACULTY_H

//Derived class (Faculty)
#include <iostream>
#include <string>
//Includes Affiliate Class
#include "Affiliate.h"
//Include DoublyLinked List template class
#include "DoublyLinkedList.h"
using namespace std;
//creates faculty class
class Faculty{
public:
    Faculty();
    Faculty(int id, string name, string level, string department);
    ~Faculty();
    int getId();
    string getName();
    string getLevel();
    string getDepartment();
    int getAdvisees();
    string toString();
    void addAdvisee(int id);
    DoublyLinkedList<int> *StudentIDs;
    bool operator<(const Faculty &s); 
    bool operator>(const Faculty &s);
    bool operator==(const Faculty &s);
    bool operator!=(const Faculty &s);
private:
    int id;
    string name;
    string level;
    string department;
    double gpa;
    int advisees; //supposed to be list
};

//Default constructor
Faculty::Faculty(){
    id = 0;
    name = " ";
    level = " ";
    department = " ";
    StudentIDs = new DoublyLinkedList<int>;
}

//Constructor
Faculty::Faculty(int id_, string name_, string level_, string department_){
    id = id_;
    name = name_;
    level = level_;
    department = department_;
    StudentIDs = new DoublyLinkedList<int>;

}

//Destructor
Faculty::~Faculty(){

}

//Returns ID of Faculty
int Faculty::getId(){
    return id;
}

//Returns Name of Faculty member
string Faculty::getName(){
    return name;
}

//Returns Level of Faculty member
string Faculty::getLevel(){
    return level;
}

//Returns Department of Faculty member
string Faculty::getDepartment(){
    return department;
}

//Returns Name of Faculty member
int Faculty::getAdvisees(){
    int count = StudentIDs->removeFront();
    return count;
}

//Adds Student ID to Student ID DoublyLinked List
void Faculty::addAdvisee(int id){
    StudentIDs->insertBack(id);
    //cout<<getAdvisees()<<endl;
}

//Returns a string displaying faculty info
string Faculty::toString(){
    return "ID: " + to_string(id) + ", Name: " + name + ", Level: " + level + ", Department: " + department; //+ ", Advisees: " + to_string(getAdvisees());;
}

//Boolean that compares the values id to sort BST
bool Faculty::operator<(const Faculty &s){
    return ((this->id < s.id) ? true : false);
}
bool Faculty::operator>(const Faculty &s){
    return ((this->id > s.id) ? true : false);
}
bool Faculty::operator==(const Faculty &s){
    return ((this->id == s.id) ? true : false);
}
bool Faculty::operator!=(const Faculty &s){
    return ((this->id != s.id) ? true : false);
}
#endif