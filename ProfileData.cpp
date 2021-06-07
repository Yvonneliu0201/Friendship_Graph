#include "ProfileData.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;


//constructor
ProfileData::ProfileData(string output){
    outputFile = output;
    totalSize = 0; // initial size is 0
}

// adds user to text file
void ProfileData::addUser(string name, string age, string occupation){
    ofstream output;
    output.open(outputFile, ios_base::binary | ofstream::app);
    output << left << setw(20) << name;
    output << left << setw(3) << age;
    output << left << setw(30) << occupation;
    output.close();
    totalSize++;
}

//prints user in name,age,occupation format
string ProfileData::printUser(int index){
    //saves each info separately
    char* userName = new char[20];
    char* userAge = new char[3];
    char* userOccupation = new char[30];

    //assign values
    ifstream myfile(outputFile, ios::binary);
    myfile.seekg(53*index);
    myfile.read(userName,20);
    myfile.read(userAge,3);
    myfile.read(userOccupation,30);
    myfile.close();

    //then cout it
   string out = string(userName,20) + "," + string(userAge,3) + "," + string(userOccupation,30);
   return out;

}
//returns name of index
string ProfileData::getName(int index) const{
    //using index and multiply by 53
    //open file and go to line index
    char* nameBuffer = new char[20];

    ifstream myfile(outputFile,ios::binary);
    myfile.seekg(53*index);
    myfile.read(nameBuffer,20);
    myfile.close();

    return nameBuffer;

}

//returns age of index
string ProfileData::getAge(int index) const{
    //using index and multiply by 53
    //open file and go to line index
    char* ageBuffer = new char[20];

    ifstream myfile(outputFile,ios::binary);
    myfile.seekg(53*index+20); //skip the age
    myfile.read(ageBuffer,3);
    myfile.close();

    return ageBuffer;
}

//returns occupation of index
string ProfileData::getOccupation(int index) const{
    //using index and multiply by 53
    //open file and go to line index
    char* occupationBuffer = new char[20];

    ifstream myfile(outputFile,ios::binary);
    myfile.seekg(53*index+23); //skip the name and age
    myfile.read(occupationBuffer,20);
    myfile.close();

    return occupationBuffer;
}

//return totalSize
int ProfileData::getTotalSize() const{
    return totalSize;
}
