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
    // 4. Friendship queries: goes to submenu List FriendsInfo of user1: list name,age,occupation of all friends, assumming user1 exists
    // 5. List all users ranging user1 to user2 inclusive: name, age, occupation, friendlist
    // 6. Get User Info, given index, print name, age, occupation, friendlist
    // 7. Get User Info, given name, print name, age, occupation, friendlist
    // 8. Exit

    int menuNum = 0;
    string menu = "Welcome to Friendship!\n Menu Items:\n 1. Insert New User\n 2. Add Friendship between Two Users\n 3. Print All\n 4. Friendship Queries\n 5. Range Queries\n 6. Get User Info Given Index\n 7. Get User Info Given Name\n 8. Exit\n Enter a Number: ";
    string friendshipQueryMenu = "Friendship Queries:\n Menu Items:\n 1. Print All Friends Info + Their Friendship List\n 2. Print All Friends Info\n 3. Print All Friends Name\n 4. Print All Friends Age\n 5. Print All Friends Occupation\n 6. Go Back to Main Page\n Enter a Number: ";
    string rangeQueryMenu = "Range Queries:\n Menu Items:\n 1. Print All Users Between A and B (exclusive)\n 2. Print All Users Between A and B (any)\n 3. Go Back to Main Page\n Enter A Number: ";

    while(menuNum != 8){
        system("clear");
        cout << menu;
        cin >> menuNum;

        //insert new user
        if(menuNum == 1){ // addUser
            system("clear");

            cout << "1. Insert New User" << endl;
            string nameInput = "";
            string ageInput = "";
            string occupationInput = "";
            string friendsInput = "";
            //prompt name, age, and occupation
            while(nameInput == ""){
                cout << "Insert a Name: ";
                cin.ignore(1,'\n');
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
            cout << "Insert a Friend List: (eg. friend,friend,friend,) or empty" << endl;
            getline(cin,friendsInput);

            //input
            int result = hub.addUser(nameInput,ageInput,occupationInput,friendsInput);

            if(result == 0){
                cout << "-------User Added!-------" << endl;
            }
            else if(result == 1){
                cout << "-----User Already Exists!-----" << endl;
            }
            else if(result == 2){
                cout << "---One of your inputs was too long!---" << endl;
            }
            else if(result == 3){
                cout << "---One of your friends does not exist!---" << endl;
            }
            else if(result == 4){
                cout << "---Bad Formatting in Friends---" << endl;
            }
            
            cout << "Press Enter to Return to Menu" << endl;
            cin.ignore();
            menuNum = 0;

        }// end addUser
        else if(menuNum == 2){ // addFriendship
            system("clear");
            cout << "2. Add Friendship between Two Users" << endl;
            //adds friendship between two users
            string name1 = "";
            string name2 = "";

            //get inputs
            while(name1 == ""){
                cout << "Enter First Name: ";
                cin.ignore(1,'\n');
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
            else if(result == 3){
                cout <<"----Self Inserts Are Not Allowed!----" << endl;
            }

            cout << "Press Enter to Return to Menu" << endl;
            cin.ignore();
            menuNum = 0;

        }// end addFriendship
        else if(menuNum == 3){ // printAll
            system("clear");
            cout << "3. Print All" << endl;
            //Print All, name, age, occupation, friend1, friend2, friend3, ...,
            cout << "---------start of PrintAll---------" << endl;
            cout << hub.printAll(); //printAll includes enl

            //once done
            cout << "----------end of PrintAll----------" << endl;

            cout << "Press Enter to Return to Menu" << endl;
            cin.ignore();
            cin.ignore();
            menuNum = 0;
            
        }// end PrintAll
        else if(menuNum == 4){ // friendship query menu
            //4. Go to submenu for friendship queries
            int fQuery = 0;
            while(fQuery != 6){
                system("clear");
                cout << friendshipQueryMenu;
                cin >> fQuery;

                // 1. Print all Friends Info and List
                if(fQuery == 1){
                    system("clear");
                    string name1 = "";

                    //ask for inputs
                    while(name1 == ""){
                        cout << "Enter name: ";
                        cin.ignore(1,'\n');
                        getline(cin,name1);
                    }

                    cout << "-------------Start of listFriendsAllInfo-------------" << endl;
                    cout << hub.listFriendsAllInfo(name1);
                    cout << "--------------End of listFriendsAllInfo--------------" << endl;
                    cout << "Press Enter to Return to Friendship Query Menu" << endl;
                    cin.ignore();
                    fQuery = 0;
                    
                }
                // 2. Print all Friends Info
                else if(fQuery == 2){
                    system("clear");
                    string name1 = "";

                    //ask for inputs
                    while(name1 == ""){
                        cout << "Enter name: ";
                        cin.ignore(1,'\n');
                        getline(cin,name1);
                    }

                    cout << "-------------Start of listFriendsInfo-------------" << endl;
                    cout << hub.listFriendsInfo(name1);
                    cout << "--------------End of listFriendsInfo--------------" << endl;
                    cout << "Press Enter to Return to Friendship Query Menu" << endl;
                    cin.ignore();
                    fQuery = 0;
                    
                }
                // 3. Print all Friends Name
                else if(fQuery == 3){
                    system("clear");
                    string name1 = "";

                    //ask for inputs
                    while(name1 == ""){
                        cout << "Enter name: ";
                        cin.ignore(1,'\n');
                        getline(cin,name1);
                    }

                    cout << "-------------Start of listFriendsName-------------" << endl;
                    cout << hub.listFriendsName(name1);
                    cout << "--------------End of listFriendsName--------------" << endl;
                    cout << "Press Enter to Return to Friendship Query Menu" << endl;
                    cin.ignore();
                    fQuery = 0;
                    
                }
                else if(fQuery == 4){
                    system("clear");
                    string name1 = "";

                    //ask for inputs
                    while(name1 == ""){
                        cout << "Enter name: ";
                        cin.ignore(1,'\n');
                        getline(cin,name1);
                    }

                    cout << "-------------Start of listFriendsAge-------------" << endl;
                    cout << hub.listFriendsAge(name1);
                    cout << "--------------End of listFriendsAge--------------" << endl;
                    cout << "Press Enter to Return to Friendship Query Menu" << endl;
                    cin.ignore();
                    fQuery = 0;
                    
                }
                else if(fQuery == 5){
                    system("clear");
                    string name1 = "";

                    //ask for inputs
                    while(name1 == ""){
                        cout << "Enter name: ";
                        cin.ignore(1,'\n');
                        getline(cin,name1);
                    }

                    cout << "-------------Start of listFriendsOccu-------------" << endl;
                    cout << hub.listFriendsOccu(name1);
                    cout << "--------------End of listFriendsOccu--------------" << endl;
                    cout << "Press Enter to Return to Friendship Query Menu" << endl;
                    cin.ignore();
                    fQuery = 0;
                    
                }
                else if(fQuery == 6){
                    fQuery = 6;
                }
                else{
                    cin.clear(); //clear bad input flag
                    cin.ignore();
                    cout << "INVALID ENTRY, TRY AGAIN" << endl;
                    cout << "Press Enter to Return to Friendship Query Menu" << endl;
                    cin.clear();
                    cin.ignore();
                    fQuery = 0;
                } 
            }

            menuNum = 0;
        }// end listFriendsAllInfo(name)
        else if(menuNum == 5){ // range query menu
            //5. Go to submenu for range queries
            int rQuery = 0;
            while(rQuery != 3){
                system("clear");
                cout << rangeQueryMenu;
                cin >> rQuery;

                // 1. Print all Friends Info and List
                if(rQuery == 1){
                    system("clear");
                    cout << "1. Print all Users Btwn A and B (exclusive)" << endl;
                    // 5. List all users ranging user1 to user2 inclusive: name, age, occupation, friendlist
                    string name1 = "";
                    string name2 = "";

                    //get inputs
                    while(name1 == ""){
                        cin.ignore(1,'\n');
                        cout << "Enter Lower Bound name: ";
                        getline(cin,name1);
                    }
                    while(name2 == ""){
                        cout << "Enter Upper Bound name: ";
                        getline(cin,name2);
                    }

                    if(hub.userExists(name1) && hub.userExists(name2)){
                        cout << "--------Start of PrintRangeExclusive--------" << endl;
                    }
                    cout << hub.printBtwnExclusive(name1,name2);
                    if(hub.userExists(name1) && hub.userExists(name2)){
                        cout << "---------End of PrintRangeExclusive---------" << endl;
                    }
                    cout << "Press Enter to Return to Range Query Menu" << endl;
                    cin.ignore();
                    rQuery = 0;
                    
                }
                // 2. Print all Friends Info
                else if(rQuery == 2){
                    system("clear");
                    cout << "2. Print all Users Btwn A and B (any)" << endl;
                    // 5. List all users ranging user1 to user2 inclusive: name, age, occupation, friendlist
                    string name1 = "";
                    string name2 = "";

                    //get inputs
                    while(name1 == ""){
                        cin.ignore(1,'\n');
                        cout << "Enter Lower Bound name: ";
                        getline(cin,name1);
                    }
                    while(name2 == ""){
                        cout << "Enter Upper Bound name: ";
                        getline(cin,name2);
                    }
                    
                    cout << "-------------Start of PrintRange------------" << endl;
                    cout << hub.printBtwn(name1,name2);
                    cout << "-------------End of PrintRange--------------" << endl;
                    cout << "Press Enter to Return to Range Query Menu" << endl;
                    cin.ignore();
                    rQuery = 0;
                    
                }
                // 3. Print all Friends Name
                else if(rQuery == 3){
                   rQuery = 3;
                    
                }
                else{
                    cin.clear(); //clear bad input flag
                    cin.ignore();
                    cout << "INVALID ENTRY, TRY AGAIN" << endl;
                    cout << "Press Enter to Return to Range Query Menu" << endl;
                    cin.clear();
                    cin.ignore();
                    rQuery = 0;
                } 
            }

            menuNum = 0;

        }// end ListInfo(Lower,Upper)
        else if(menuNum == 6){ // printUser(int index)
            system("clear");
            
            cout << "6. Get User Info Given Index" << endl;
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

            cout << "---------Start of Print User---------" << endl;
            cout << hub.printUser(index) << endl;

            cout << "----------End of Print User----------" << endl;
            cout << "Press Enter to Return to Menu" << endl;
            cin.ignore();
            cin.ignore();
            menuNum = 0;
    
        }
        else if(menuNum == 7){ // printUser(string name)
            system("clear");
            cout << "7. Get User Info Given Name" << endl;
            //find user info by traversing rbtree
            string userInput = "";
            while(userInput == ""){
                cout << "Enter a Name: ";
                cin.ignore(1,'\n');
                getline(cin,userInput);
            }

            if(hub.userExists(userInput)){ //if user exist, then there is an end
                cout << "---------Start of Print User---------" << endl;
            }
            cout << hub.printUser(userInput) << endl;

            if(hub.userExists(userInput)){ //if user exist, then there is an end
                cout << "----------End of Print User----------" << endl;
            }
            cout << "Press Enter to Return to Menu" << endl;
            cin.ignore();

            menuNum = 0;
            
        }
        else if(menuNum == 8){ // exit
            // 8. Exit
            menuNum = 8;
        }
        else{ // invalid entry
            cin.clear(); //clear bad input flag
            cin.ignore(); //discard input
            cout << "INVALID ENTRY, TRY AGAIN" << endl;
            cin.clear();
            cin.ignore();
            menuNum = 0;
        } 
    }
}