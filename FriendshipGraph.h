#ifndef FRIENDSHIPGRAPH_H
#define FRIENDSHIPGRAPH_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node{
    string name;
    int index;
    Node* next;
};

struct GraphNode{
    string name; //user
    Node* head; //friend list    
};

class FriendList{
    public:
        FriendList();
        ~FriendList();

        string getFriendList(int index); //outputs string in form ,friend1,friend2,friend3,... or nothing if empty
        void getFriendIndex(vector<int> &v, int index); //sets v to indexes of all friends of index user

        bool areFriends(int index1, int index2);   
        void addUser(string name);
        void addFriend(int index1, int index2); //adds corresponding friend to each user given index


    private:
        vector<GraphNode> graph; //graph vector with graphNode, vector index is relative to pd index
        int vectorSize;
};


#endif