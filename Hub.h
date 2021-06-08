#ifndef HUB_H
#define HUB_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "FriendshipGraph.h"
#include "RBTree.h"
#include "ProfileData.h"

//this is the hub for all actions including queries

class Hub{
    public:
        //constructor
        Hub(string inputFile);
        Hub();

        //getters
        int getSize(){return size;}
        //insert a user
        int addUser(string user, string age, string occupation,string friends);

        //adds a friendship between user
        int addFriendship(string user1, string user2);

        //prints user with friends
        string printUser(string name);
        string printUser(int index);

        //print user w/o friends
        string printUserSimple(int index);

        //returns a string with all info
        string printAll();
        string listFriendsAllInfo(string name);
        string listFriendsInfo(string name);
        string listFriendsName(string name);
        string listFriendsAge(string name);
        string listFriendsOccu(string name);

        string printBtwnExclusive(string user1, string user2); //only allows users that exist
        string printBtwn(string user1, string user2); //any name can work

        //user exists?
        bool userExists(string name);
        bool userExists(int index);

    private:
        RBTree rbTree;
        FriendList adjL;
        ProfileData records = ProfileData("Profile_Data.csv");
        vector<int> nameLen;
        vector<int> ageLen;
        vector<int> occuLen;
        int size = 0;

};

#endif