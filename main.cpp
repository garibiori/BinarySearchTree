/**
 * Main file that runs simulation
 * 
 * @author Devin Keller and Ori G
 * @version 1.0
 * @see main.h 
 * 
 */
#include <iostream>
//Allows us to refrence classes in RunCommands.h file
#include "RunCommands.h"

using namespace std;

int main (int argc, char **argv){

    RunCommands *test = new RunCommands();
    //run takeCommands from the RunCommands File
    test->takeCommands();
    return 0;
}
