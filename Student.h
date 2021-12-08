/**
 * Student.h creates a student class that represents every student member
 * 
 * @author Devin Keller and Ori G
 * @version 1.0
 * @see Student.h
 * 
 */

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include "Affiliate.h"
//creates student class
class Student{
public:
    Student();
    Student(int id, string name, string year, string major, double gpa, int advisor);
    ~Student();
    int getId();
    string getName();
    string getYear();
    string getMajor();
    double getGpa();
    int getAdvisor();
    string toString();
    void setAdvisor(int adv);
    bool operator<(const Student &s); 
    bool operator>(const Student &s);
    bool operator==(const Student &s);
    bool operator!=(const Student &s);

private:
    int id;
    string name;
    string year;
    string major;
    double gpa;
    int advisor;
};

//Default constructor
Student::Student(){
    id = 0;
    name = " ";
    year = " ";
    major = " ";
    gpa = 0;
    advisor = 0;
}

//Constructor
Student::Student(int id_, string name_, string year_, string major_, double gpa_, int advisor_){
    id = id_;
    name = name_;
    year = year_;
    major = major_;
    gpa = gpa_;
    advisor = advisor_;
}

//Destructor
Student::~Student(){
}
//Returns ID of student
int Student::getId(){
    return id;
}

//Returns Name of student
string Student::getName(){
    return name;
}

//Returns year of student
string Student::getYear(){
    return year;
}

//Returns major of student
string Student::getMajor(){
    return major;
}

//Returns GPA of student
double Student::getGpa(){
    return gpa;
}

//Returns Advisor of student
int Student::getAdvisor(){
    return advisor;
}

//Sets advisor of student
void Student::setAdvisor(int adv){
    this->advisor = adv;
}

//Creates a string displaying students info
string Student::toString(){
    return "ID: " + to_string(id) + ", Name: " + name + ", Year: " + year + ", Major: " + major + ", GPA: " + to_string(gpa) + ", Advisor: " + to_string(advisor);
}

//Boolean that compares the values id to sort BST
bool Student::operator<(const Student &s){
    return ((this->id < s.id) ? true : false);
}
bool Student::operator>(const Student &s){
    return ((this->id > s.id) ? true : false);
}
bool Student::operator==(const Student &s){
    return ((this->id == s.id) ? true : false);
}
bool Student::operator!=(const Student &s){
    return ((this->id != s.id) ? true : false);
}


#endif