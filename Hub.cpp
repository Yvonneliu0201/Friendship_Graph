#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include "Hub.h"

//init with a file
Hub::Hub(string inputFile){
    size = 0;
    ifstream input;
    string line;
    string subsitute;
    int fileIndex = 0;

    remove("Profile_Data.csv"); //check if output file exists

    //get the input .csv file
    input.open(inputFile, ios_base::in | ios_base::binary);

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
        nameLen.push_back(name.length());
        string age = inputs[1];
        ageLen.push_back(age.length());
        string occupation = inputs[2];
        occuLen.push_back(occupation.length());
        inputs.erase(inputs.begin(), inputs.begin()+3);
        allUserFriends.push_back(inputs); //add list of friends to vector, corresponding to user
        adjL.addUser(name); //adds all users to graph with no friends
        rbTree.addUser(name,fileIndex);
        records.addUser(name,age,occupation);
        fileIndex = records.getTotalSize();
        size++;
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
}

int Hub::addUser(string name, string age, string occupation){   
    // return int meanings
    // 0: success
    // 1: name exists
    // 2: length is wrong for either name, age, or occupation

    //check if name exists in RB, if so, throw it
    if(rbTree.getIndex(name) != -1){
        //user exists
        return 1;
    }
    if(name.length() > 20 || age.length() > 3 || occupation.length() > 30){
        return 2; //length is wrong
    }
    else{
        //save lengths to corresponding vectors
        nameLen.push_back(name.length());
        ageLen.push_back(age.length());
        occuLen.push_back(occupation.length());

        //once got info then,
        // add to ProfileData, RBTree, Friendship Graph
        // output.open("Profile_Data.csv", ios_base::binary);
        records.addUser(name,age,occupation);
        //output.close();
        rbTree.addUser(name,records.getTotalSize()-1);
        //add to friendship graph with empty ll
        adjL.addUser(name);
        size++;

        //done 
        return 0;
    }
}

//adds friendship between two users
int Hub::addFriendship(string name1, string name2){
     //return int 
     // 0: success
     // 1: they are already friends
     // 2: one of the users does not exist

    int index1 = rbTree.getIndex(name1);
    int index2 = rbTree.getIndex(name2);
    // cout << "index1: " << index1 << endl;
    // cout << "index2: " << index2 << endl;

    if(index1 != -1 && index2 != -1){ //indexes exist, users exist
        if(adjL.areFriends(index1,index2)){
            //if friendship already exists, return 1
            return 1;
        }
        else{
            //if friendship dne, then add friendships
            adjL.addFriend(index1,index2);
            //success!
            return 0;
        } 
    }  
    else{// user dne
        return 2;
    }
}

//print user given name, no \n at end
string Hub::printUser(string name){
    //get index from rbtree
    int index = rbTree.getIndex(name);
    if(index == -1){
        //user not found
        string err = "User Not Found";
        return err;
    }
    else{
        //get strings with correct lengths
        string name = records.getName(index).substr(0,nameLen[index]);
        string age = records.getAge(index).substr(0,ageLen[index]);
        string occupation = records.getOccupation(index).substr(0,occuLen[index]);

        string user = "";
        user = name + "," + age + "," + occupation;

        //add friends
        user = user + adjL.getFriendList(index);

        return user;
    }
}

//print user given index, no \n at end
string Hub::printUser(int index){

    if(index < 0 || index > records.getTotalSize()){ //index is out of bounds
        //user not found
        string err = "Index is Out of Bounds";
        return err;
    }
    else{
        //get strings with correct lengths
        string name = records.getName(index).substr(0,nameLen[index]);
        string age = records.getAge(index).substr(0,ageLen[index]);
        string occupation = records.getOccupation(index).substr(0,occuLen[index]);

        string user = "";
        user = name + "," + age + "," + occupation;

        //add friends
        user = user + adjL.getFriendList(index);

        return user;
    }
}

//Print All, name, age, occupation, friend1, friend2, friend3, ...,
string Hub::printAll(){
    //iterate through 0-records.filesize-1 
    string all = "";
    for(int i = 0; i < records.getTotalSize(); i++){
        all = all + printUser(i) + "\n";
    }

    //once done, return all
    return all;
}

//4. List FriendsInfo of user1: list name,age,occupation of all friends, assumming user1 exists
string Hub::listFriendsInfo(string name){

    int index = rbTree.getIndex(name);
    //check if user exists
    if(index == -1){
       string err = "User Does Not Exist!\n" ;
       return err;
    }
    else{
        //run function to list all friends info
        //get vector<int> of all friends of index
        vector<int> friendIndexList;
        adjL.getFriendIndex(friendIndexList, index);

        cout << name << "'s Friend List:" << endl;
        string friends = "";
        //iterate through friendIndexList
        for(vector<int>::iterator it = begin(friendIndexList); it != end(friendIndexList); ++it){
            friends = friends + printUser(*it) + "\n";
        }

        //once done, return friends
        return friends;
    }  
}

// 5. List all users ranging user1 to user2 inclusive: name, age, occupation, friendlist
string Hub::printBtwn(string user1, string user2){
    //do the function and print
    //check if name1 and name 2 are in the tree first
    if(rbTree.getIndex(user1) == -1 || rbTree.getIndex(user2) == -1){
        //one is not in tree, exit
        string err = "At least one of the users is not in the tree\n";
        return err;
    }
    else{
        //users are valid, then print
        vector<int> order;
        rbTree.listInfo(order, rbTree.getRoot(), user1, user2);

        string range = "";
        //order now has list in indexes, iterate through and print users inclusive
        for(vector<int>::iterator it = begin(order); it != end(order); ++it){
            
            range = range + printUser(*it) + "\n";
        }
        
        //once done, return range
        return range;  
    }
}

bool Hub::userExists(string name){
    if(rbTree.getIndex(name) == -1){
        return false;
    }
    else{
        return true;
    }
}

bool Hub::userExists(int index){
    if(index < 0 || index > records.getTotalSize()){
        return false;
    }
    else{
        return true;
    }
}
