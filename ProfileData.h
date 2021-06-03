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
    char name[20]; //name is always unique
    char age[3];
    char occupation[30];
};

class ProfileData{
    //add to a file
    public:
        //add user to file 
        void addUser();

        //grab a user based on a ptr (index)
        User getUser(int index);

        //support PrintAll
        string printAll();
}

//printAll with accompany with list of friends from friendship graph

#endif