/**
 * Affiliate is the base class for Students and Faculty
 * 
 * @author Devin Keller and Ori G
 * @version 1.0
 * @see Affiliate.h
 * 
 */


#ifndef AFFILIATE_H
#define AFFILIATE_H
#include <iostream>
#include <string>
using namespace std;
//creates Affiliate Class
class Affiliate{
    public:
        Affiliate();
        Affiliate(int id, string name, string level);
        ~Affiliate();
        int getId();
        string getName();
        string getLevel();
        string toString();
        int id;
        string name;
        string level;
};
//Default Constructor
Affiliate::Affiliate(){
    id = 0;
    name = "";
    level = "";
}
//Affiliate Constructor
Affiliate::Affiliate(int id_, string name_, string level_){
    id = id_;
    name = name_;
    level = level_;
}

//Creates getId function that returns ID of Affiliate
int Affiliate::getId(){
    return id;
}

//Creates getId function that returns name of Affiliate
string Affiliate::getName(){
    return name;
}

//Creates getLevel function that returns level of Affiliate
string Affiliate::getLevel(){
    return level;
}

//Creates toString function that returns a string of affiliate
string Affiliate::toString(){
    return "ID: " + to_string(id) + ", Name: " + name + ", Level: " + level;
}

#endif



