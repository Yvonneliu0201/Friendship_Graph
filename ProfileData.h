// has name, age, occupation
//stored in a file on disk
#ifndef PROFILEDATA_H
#define PROFILEDATA_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

struct User {
    char[20] name; //name is always unique
    char[3] age;
    char[30] occupation;
};

class ProfileData{
    //add to a file
    public:
        //constructor
        ProfileData(string file); //file is file to write to
        //add user to file 
        void addUser(string name, string age, string occupation);

        //grab a user based on a ptr (index)
        User getUser(int index) const;
        string getName(int index) const;
        string getAge(int index) const;
        string getOccupation(int index) const;
        
        //support PrintAll
        string printAll();
    
    private:
        //filename?
        string filename;
        //size
        int totalSize;
}

//printAll with accompany with list of friends from friendship graph

#endif