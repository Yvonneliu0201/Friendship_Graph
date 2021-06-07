#include "ProfileData.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//constructor
ProfileData::ProfileData(string file){
    filename = file;
    totalSize = 0; // initial size is 0
}

// getters
User ProfileData::getUser(int index) const{
    //open file and go to line index
    User getInfo;

    char* nameBuffer = new char[20];
    char* ageBuffer = new char[3];
    char* occupationBuffer = new char[30];

    ifstream myfile(filename,ios::binary);
    myfile.seekg(53*index, ios::beg);
    myfile.read(nameBuffer,20);
    myfile.read(nameBuffer)



}  

string ProfileData::getName(int index) const{

}