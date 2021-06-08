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
    FriendList adjL;
    ProfileData records("Profile_Data.csv");
    remove("Profile_Data.csv"); //check if output file exists

    //get the input .csv file
    input.open(argv[1], ios_base::in | ios_base::binary);

    vector<vector<string>> allUserFriends;

    //skip the first line with default category names but just reading it
    getline(input,line);

    //adds each line in input file to output file
     while(getline(input,line)) {
        vector<string> inputs;     
        line.erase(remove(line.begin(),line.end(),'"'),line.end());
        stringstream ss(line);
        //cout << "new line: " << endl;
        while(ss.good()) {
            getline(ss, subsitute, ',');
            //cout << subsitute << endl;
            inputs.push_back(subsitute); //input is friend list
        }  
        //cout << endl;
        string name = inputs[0];
        string age = inputs[1];
        string occupation = inputs[2];
        inputs.erase(inputs.begin(), inputs.begin()+3);
        allUserFriends.push_back(inputs); //add list of friends to vector, corresponding to user
        adjL.addUser(name); //adds all users to graph with no friends
        rbTree.addUser(name,fileIndex);
        records.addUser(name,age,occupation);
        fileIndex = records.getTotalSize();
    }//end get lines

    //once done adding all users, then its time to add friends to graph
    //iterate allUserFriends
    //cout << "before adding friends" << endl;
    for (int i = 0; i < allUserFriends.size(); i++) { //index of user
        for (int j = 0; j < allUserFriends[i].size(); j++){ //friends in string
            //get index of friend being added
            int friendIndex = rbTree.getIndex(allUserFriends[i][j]);
            //cout << "user1 name: '" << records.getName(i) <<"'"<< endl;
            
            //cout << "friend to be added: '" << allUserFriends[i][j] << "': " << friendIndex << endl;
            //add friend
            //cout << "before .addFriend" << endl;
            adjL.addFriend(i,friendIndex);
            //cout << "after .addFriend" << endl;
        }
    }
    input.close();
    //cout << "after adding friends" << endl;

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
            

            //check if name exists in RB, if so, throw it
            if(rbTree.getIndex(nameInput) != -1){
                //user exists
                cout << "User Already Exists! \n Press Enter to return to menu:\n" ;
                cin.ignore();             
                menuNum = 0;
            }
            else{
                //once got info then,
                // add to ProfileData, RBTree, Friendship Graph
                // output.open("Profile_Data.csv", ios_base::binary);
                records.addUser(nameInput,ageInput,occupationInput);
                //output.close();
                rbTree.addUser(nameInput,records.getTotalSize()-1);
                //add to friendship graph with empty ll
                adjL.addUser(nameInput);

                //once done, set all inputs to "" and menuNum=0
                cout << "User Added! \n Press Enter to return to menu:\n" ;
                cin.ignore();             
                menuNum = 0;
            }

        }// end addUser
        else if(menuNum == 2){
            //adds friendship between two users
            //temp incomplete so just return work in progress
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

            int index1 = rbTree.getIndex(name1);
            int index2 = rbTree.getIndex(name2);
            if(index1 != -1 || index2 != -1){ //indexes exist, users exist
                //then add friendships
                adjL.addFriend(index1,index2);
                cout << "Friends Added!" << endl;
            }
            else{
                cout << "At least one of the users is not in the tree" << endl;
            }

            cout << "Press Enter to Return to Menu" << endl;
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
                printUserAndFriends = printUserAndFriends + adjL.getFriendList(i);

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
            
            int index = rbTree.getIndex(name1);
            //check if user exists
            if(index == -1){
                cout << "User Does Not Exist! \n Press Enter to return to menu:\n" ;
                cin.ignore();             
                menuNum = 0;
            }
            else{
                //run function to list all friends info
                //get vector<int> of all friends of index
                vector<int> friendIndexList;
                adjL.getFriendIndex(friendIndexList, index);

                cout << name1 << "'s Friend List:" << endl;
                //iterate through friendIndexList
                for(vector<int>::iterator it = begin(friendIndexList); it != end(friendIndexList); ++it){
                    string printUserAndFriends = "";

                    //get string from profiledata and append
                    printUserAndFriends = printUserAndFriends + records.printUser(*it);

                    // cout printUserAndFriends
                    cout << printUserAndFriends << endl;
                }

                cout << "Friend List Info Completed!" << endl;
                cout << "Press Enter to return to menu:" << endl;;
                cin.ignore();
                menuNum = 0;  
            }  
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
            //check if name1 and name 2 are in the tree first
            if(rbTree.getIndex(name1) == -1 || rbTree.getIndex(name2) == -1){
                //one is not in tree, exit
                cout << "At least one of the users is not in the tree\n";
                cout << "Press Enter to return to menu:\n";
                cin.ignore();
                menuNum = 0;
            }
            else{
                //users are valid, then print
                vector<int> order;
                rbTree.listInfo(order, rbTree.getRoot(), name1, name2);

                //order now has list in indexes, iterate through and print users inclusive
                for(vector<int>::iterator it = begin(order); it != end(order); ++it){
                    string printUserAndFriends = "";

                    //get string from profiledata and append
                    printUserAndFriends = printUserAndFriends + records.printUser(*it);
                    //get list of friends from friendshipgraph and append
                    printUserAndFriends = printUserAndFriends + adjL.getFriendList(*it);

                    // cout printUserAndFriends
                    cout << printUserAndFriends << endl;
                }
                
                //once done printing 
                cout << "Print ListInfo is Complete" << endl;
                cout << "Press Enter to return to menu:\n";
                cin.ignore();
                menuNum = 0;  
            }
             
        }// end ListInfo(Lower,Upper)
        else if(menuNum == 6){
            // 6. Get User Info given index, print name, age, occupation, friendlist
            int index = -1;
            while(index < 0 || index >= records.getTotalSize()){
                //get input 
                cout << "Enter index of User: ";
                cin >> index;
                if(index >= records.getTotalSize()){
                    cout << "Out of Range!" << endl;
                }
            }

            //once given index append and print
            string printUserAndFriends = "";

            //get string from profiledata and append
            printUserAndFriends = printUserAndFriends + records.printUser(index);
            //get list of friends from friendshipgraph and append
            printUserAndFriends = printUserAndFriends + adjL.getFriendList(index);

            // cout printUserAndFriends
            cout << printUserAndFriends << endl;

            //once done
            cout << "end of PrintUser... Press Enter to return to menu:\n" ;
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

            // after getting name, search in rbtree output index
            int index = rbTree.getIndex(userInput);
            if(index < 0){
                cout << "User Not Found" << endl;
            }
            else{
                cout << records.printUser(index) << adjL.getFriendList(index) << endl;
            }

            //once done
            cout << "end of PrintUser... \nPress Enter to return to menu" << endl ;
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