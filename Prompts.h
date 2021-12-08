/**
 * Prompts.h creates the prompt that asks the user what commands they want to run
 * 
 * @author Devin Keller and Ori G
 * @version 1.0
 * @see Prompts.h
 * 
 */

#include <iostream>
#include <string>
using namespace std;
//Creates Prompts Class
class Prompts{
    public:
        Prompts();
        ~Prompts();
        int returnPrompts();
    private:
};

//Default Constructor
Prompts::Prompts(){

}

//Default Destructore
Prompts::~Prompts(){

}

//returnPrompts function creates the prompt that asks the user what commands they want to run
int Prompts::returnPrompts(){
    int num;
    cout<<"1. Print all Students\n2. Print all faculty\n3. Display a students info\n4. Display a faculty info\n5. Display a students advisor\n6. Display an advisors students\n7. Add a student\n8. Delete a student\n9. Add a faculty member\n10. Delete a faculty member\n11. Change a student's advisor\n12. Remove an advisee from a faculty member\n13. Rollback\n14. Exit"<<endl;
    cin>>num;
    return num;
}