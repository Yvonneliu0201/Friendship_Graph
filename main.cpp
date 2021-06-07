#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include "ProfileData.h"
#include "RBTree.h"
#include "FriendshipGraph.h"

using namespace std;

int main(int argc, char** argv){
    ifstream input;
    string line;
    string subsitute;
    int fileIndex = 0;

    //initialize profileData, rbtree, adjacency list
    RBTree rbTree;
    ProfileData records("Profile_Data.csv");
    remove("Profile_Data.csv"); //check if output file exists

    //get the input .csv file
    input.open(argv[1], ios_base::in | ios_base::binary);

    //adds each line in input file to output file
     while(getline(input,line)) {
        vector<string> inputs;
        line.erase(remove(line.begin(),line.end(),'"'),line.end());
        stringstream ss(line);
        while(ss.good()) {
            getline(ss, subsitute, ',');
            inputs.push_back(subsitute);
        }  
        string name = inputs[0];
        string age = inputs[1];
        string occupation = inputs[2];
        inputs.erase(inputs.begin(), inputs.begin()+2);
        rbTree.addUser(name,fileIndex);
        // adjL.insert(name, inputs, fileIndex);
        records.addUser(name,age,occupation);
        fileIndex = records.getTotalSize();
    }
    input.close();

    //menu
    //features: 
    // 1. insert new user
    // 2. Add friendship between user1 and user2, assuming user1 and user2 exist
    // 3. Print All, name, age, occupation, friend1, friend2, friend3, ...,
    // 4. List FriendsInfo of user1: list name,age,occupation of all friends, assumming user1 exists
    // 5. List all users ranging user1 to user2 inclusive: name, age, occupation, friendlist
    // 6. Get User Info, given index, print name, age, occupation, friendlist
    // 7. Exit

    int menuNum = 0;
    string menu = "Welcome to Friendship!\n Menu Items:\n 1. Insert New User\n 2. Add Friendship between Two Users\n 3. Print All\n 4. List Friends Info of a User\n 5. List All Users from User1 to User2\n 6. Get User Info Given Index\n 7. Exit\n Enter a Number: ";

    while(menuNum != 7){
        cout << menu;
        cin >> menuNum;

        //insert new user
        if(menuNum == 1){
            string nameInput = "";
            string ageInput = "";
            string occupationInput = "";
            //prompt name, age, and occupation
            while(nameInput == ""){
                cout << "Insert a Name: ";
                getline(cin,nameInput);
            }
            while(ageInput == ""){
                cout << "Insert an Age: ";
                getline(cin,ageInput);
            }
            while(occupationInput == ""){
                cout << "Insert an Occupation: ";
                getline(cin,occupationInput);
            }
            

            //check if name exists in RB, if so, throw it
            

            //once got info then,
            // add to ProfileData, RBTree, Friendship Graph
           // output.open("Profile_Data.csv", ios_base::binary);
            records.addUser(nameInput,ageInput,occupationInput);
            //output.close();
            rbTree.addUser(nameInput,records.getTotalSize()-1);
            //add to friendship graph with empty ll

            //once done, set all inputs to "" and menuNum=0
            cout << "User Added! \n Press Enter to return to menu:\n" ;
            cin.ignore();             
            menuNum = 0;

        }// end addUser
        else if(menuNum == 2){
            //adds friendship between two users
            //temp incomplete so just return work in progress
            cout << "WORK IN PROGRESS \n Press Enter to return to menu:\n" ;
            cin.ignore();
            cin.ignore();               
            menuNum = 0;
            
        }// end addFriendship
        else if(menuNum == 3){
            //Print All, name, age, occupation, friend1, friend2, friend3, ...,

            //currently can only print name, age, occupation
            //iterate through 0-records.filesize-1 
            for(int i = 0; i < records.getTotalSize(); i++){
                string printUserAndFriends = "";

                //get string from profiledata and append
                printUserAndFriends = printUserAndFriends + records.printUser(i);
                //get list of friends from friendshipgraph and append
                printUserAndFriends = printUserAndFriends + ",Friend,List,Dummy";

                // cout printUserAndFriends
                cout << printUserAndFriends << endl;
            }

            //once done
            cout << "end of PrintAll... Press Enter to return to menu:\n" ;
            cin.ignore();
            cin.ignore();
            menuNum = 0;
        }// end PrintAll
        else if(menuNum == 4){
            //4. List FriendsInfo of user1: list name,age,occupation of all friends, assumming user1 exists
            string name1 = "";

            //ask for inputs
            while(name1 == ""){
                cout << "Enter name: ";
                getline(cin,name1);
            }

            //run function to list all friends info
            //TEMP DUMMY FILLER
            cout << "This is where I would print all the friends" << endl;
            cout << "Press Enter to return to menu:\n";
            cin.ignore();
            cin.ignore();
            menuNum = 0;    
        }// end listFriendsInfo(name)
        else if(menuNum == 5){
            // 5. List all users ranging user1 to user2 inclusive: name, age, occupation, friendlist
            string name1 = "";
            string name2 = "";

            //get inputs
            while(name1 == ""){
                cout << "Enter Lower Bound name: ";
                getline(cin,name1);
            }
            while(name2 == ""){
                cout << "Enter Upper Bound name: ";
                getline(cin,name2);
            }

            //do the function and print
            //TEMP FILLER 
            cout << "This is where I would print all the users ranging from name1 to name2" << endl;
            cout << "Press Enter to return to menu:\n";
            cin.ignore();
            menuNum = 0;   
        }// end ListInfo(Lower,Upper)
        else if(menuNum == 6){
            // 6. Get User Info given index, print name, age, occupation, friendlist
            int index = -1;
            while(index < 0 || index >= records.getTotalSize()){
                //get input 
                cout << "Enter index of User: ";
                cin >> index;
            }

            //once given index append and print
            string printUserAndFriends = "";

            //get string from profiledata and append
            printUserAndFriends = printUserAndFriends + records.printUser(index);
            //get list of friends from friendshipgraph and append
            //DUMMY, TEMP, FILLER
            printUserAndFriends = printUserAndFriends + ",Friend,List,Dummy";

            // cout printUserAndFriends
            cout << printUserAndFriends << endl;

            //once done
            cout << "end of PrintUser... Press Enter to return to menu:\n" ;
            cin.ignore();
            cin.ignore();
            menuNum = 0;
    
        }
        else if(menuNum == 7){
            // 7. Exit
            menuNum = 7;
        }
        else{
            cin.clear(); //clear bad input flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
            cout << "INVALID ENTRY, TRY AGAIN\n";
            menuNum = 0;
        } 
    }
}