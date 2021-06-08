#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include "Hub.h"

using namespace std;

int main(int argc, char** argv){
    // init our hub
    Hub hub(argv[1]);

    //menu
    //features: 
    // 1. insert new user
    // 2. Add friendship between user1 and user2, assuming user1 and user2 exist
    // 3. Print All, name, age, occupation, friend1, friend2, friend3, ...,
    // 4. List FriendsInfo of user1: list name,age,occupation of all friends, assumming user1 exists
    // 5. List all users ranging user1 to user2 inclusive: name, age, occupation, friendlist
    // 6. Get User Info, given index, print name, age, occupation, friendlist
    // 7. Get User Info, given name, print name, age, occupation, friendlist
    // 8. Exit

    int menuNum = 0;
    string menu = "Welcome to Friendship!\n Menu Items:\n 1. Insert New User\n 2. Add Friendship between Two Users\n 3. Print All\n 4. List Friends Info of a User\n 5. List All Users from User1 to User2\n 6. Get User Info Given Index\n 7. Get User Info Given Name\n 8. Exit\n Enter a Number: ";

    while(menuNum != 8){
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
            
            int result = hub.addUser(nameInput,ageInput,occupationInput);

            if(result == 0){
                cout << "-------User Added!-------" << endl;
            }
            else if(result == 1){
                cout << "-----User Already Exists!-----" << endl;
            }
            else if(result == 2){
                cout << "---One of your inputs was too long!---" << endl;
            }
            
            cout << "Press Enter to Return to Menu" << endl;
            cin.ignore();
            menuNum = 0;

        }// end addUser
        else if(menuNum == 2){
            //adds friendship between two users
            string name1 = "";
            string name2 = "";

            //get inputs
            while(name1 == ""){
                cout << "Enter First Name: ";
                getline(cin,name1);
            }
            while(name2 == ""){
                cout << "Enter Second Name: ";
                getline(cin,name2);
            }

            int result = hub.addFriendship(name1,name2);
            if(result == 0){
                cout << "-----Friendship Added!-----" << endl;
            }
            else if(result == 1){
                cout << "----Friendship Already Exists!----" << endl;
            }
            else if(result == 2){
                cout << "---One of the Users Does Not Exist!---" << endl;
            }

            cout << "Press Enter to Return to Menu" << endl;
            cin.ignore();
            menuNum = 0;

        }// end addFriendship
        else if(menuNum == 3){
            //Print All, name, age, occupation, friend1, friend2, friend3, ...,

            cout << hub.printAll(); //printAll includes enl

            //once done
            cout << "----------end of PrintAll----------" << endl;

            cout << "Press Enter to Return to Menu" << endl;
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
            
            cout << hub.listFriendsInfo(name1);

            cout << "------End of listFriendInfo------" << endl;
            cout << "Press Enter to Return to Menu" << endl;
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

            cout << hub.printBtwn(name1,name2);

            cout << "-------End of PrintRange-------" << endl;
            cout << "Press Enter to Return to Menu" << endl;
            cin.ignore();
            cin.ignore();
            menuNum = 0;

        }// end ListInfo(Lower,Upper)
        else if(menuNum == 6){
            // 6. Get User Info given index, print name, age, occupation, friendlist
            int index = -1;
            while(index < 0 || index >= hub.getSize()){
                //get input 
                cout << "Enter index of User: ";
                cin >> index;
                if(index >= hub.getSize()){
                    cout << "Out of Range!" << endl;
                }
            }

            cout << hub.printUser(index) << endl;

            cout << "----------End of Print User----------" << endl;
            cout << "Press Enter to Return to Menu" << endl;
            cin.ignore();
            cin.ignore();
            menuNum = 0;
    
        }
        else if(menuNum == 7){
            //find user info by traversing rbtree
            string userInput = "";
            while(userInput == ""){
                cout << "Enter a Name: ";
                getline(cin,userInput);
            }

            cout << hub.printUser(userInput) << endl;

            if(hub.userExists(userInput)){ //if user exist, then there is an end
                cout << "----------End of Print User----------" << endl;
            }
            cout << "Press Enter to Return to Menu" << endl;
            cin.ignore();

            menuNum = 0;
            
        }
        else if(menuNum == 8){
            // 7. Exit
            menuNum = 8;
        }
        else{
            cin.clear(); //clear bad input flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
            cout << "INVALID ENTRY, TRY AGAIN\n";
            menuNum = 0;
        } 
    }
}