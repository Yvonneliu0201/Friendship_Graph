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
        RBNode* getUncle(RBNode* node);

        //functions
        void addUser(string name, int index);
        RBNode* insert(RBNode* rt, RBNode* node); //BST insert
        RBNode* search(string name);
        //void addFriend(string user1, string user2);

        //sort and rotation functions* 
        void sort(RBNode* rt, RBNode* node); //fixes RB Tress
        void rotateRight(RBNode* rt, RBNode* node);
        void rotateLeft(RBNode* rt, RBNode* node);

        //range query
                /* The functions prints all the keys
        which in the given range [k1..k2].
            The function assumes than k1 < k2 */
        // void Print(RBNode* rt, string lowerName, string upperName)
        // {
        //     /* base case */
        //     if(rt == NULL){
        //         return;
        //     }
            
        //     /* Since the desired o/p is sorted,
        //         recurse for left subtree first
        //         If root->data is greater than k1,
        //         then only we can get o/p keys
        //         in left subtree */
        //     if ( lowerName < rt->name )
        //         Print(rt->left, lowerName, upperName);
            
        //     /* if rt's name lies in range,
        //     then prints rt's name */
        //     if ( lowerName <= rt->name && upperName >= rt->name )
        //         cout<<rt->name<<" ";
            
        //     /* If rt->name is smaller than upperName,
        //         then only we can get o/p keys
        //         in right subtree */
        //     if ( upperName > rt->name )
        //         Print(rt->right, lowerName, upperName);
        // }
    private:
        RBNode* root;
};
#endif