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

struct User{
    char[20] name; //name is always unique
    char[3] age;
    char[30] occupation;
};

class ProfileData{
    //add to a file

    //grab a user based on a ptr (index)

    //support PrintAll
}

//printAll with accompany with list of friends from friendship graph

#endif