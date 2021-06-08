#ifndef RBTREE_H
#define RBTREE_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

struct RBNode{
    string color; // 'red' or 'black'
    string name;
    int index; // index in Profile Data file
    //Friend* head; // head of linkedlist of friends
    RBNode* left;
    RBNode* right;
    RBNode* parent; 
};

class RBTree{
    public:
        //constructor and deconstructor
        RBTree();
        ~RBTree();
        void deleteAll(RBNode* selNode); //helper for ~RBTree

        //getters and setters
        RBNode* getRoot();
        int getIndex(string name); 

        //functions
        void addUser(string name, int index);
        RBNode* insert(RBNode* rt, RBNode* node); //BST insert
        RBNode* search(string name);
        //void addFriend(string user1, string user2);

        //sort and rotation functions* 
        void sort(RBNode* &rt, RBNode* &node); //fixes RB Tress
        void rotateRight(RBNode* &rt, RBNode* &node);
        void rotateLeft(RBNode* &rt, RBNode* &node);

        //range query, should output a int vector of indexes in the order of the range
        void listInfo(vector<int> &v, RBNode* rt,string lowerName, string upperName);
    private:
        RBNode* root;
};
#endif