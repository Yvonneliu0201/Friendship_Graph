#include "RBTree.h"
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

//constructor
RBTree::RBTree(){
    //set root to null
    root = NULL;
}

//deconstructor
RBTree::~RBTree(){
    //deletes everything from tree until root is null
    deleteAll(root);
}

//deletes recursively everything from the tree, for the deconstructor
void RBTree::deleteAll(RBNode* selNode){
    //recursive, deletes right and left if exists
    if(selNode == NULL){
        //nothing then return nothing
        return;
    }
    else{
        //deleteAll Left and right, then del selNode
        deleteAll(selNode->right);
        deleteAll(selNode->left);
        delete selNode;
    }
}

// return Root
RBNode* RBTree::getRoot(){
    return root;
}

// gets node's uncle
RBNode* RBTree::getUncle(RBNode* node){
    //uncle is node's parent's parent's other kid
    //check if node's parent or grandparent exists, if not return null
    if(node->parent == NULL || node->parent->parent == NULL){
        return NULL;
    }
    else if(node->parent == node->parent->parent->right){
        //checks if node's parent is on the right, if so uncle is left
        return node->parent->parent->left;
    }
    else{ 
        //since node's parent is not on right, then uncle is right
        return node->parent->parent->right; 
    }
    //idk if something goes wrong
    return NULL;

}

//return Index given name, if not found return -1
int RBTree::getIndex(string name){
    RBNode* searchedNode = search(name);

    if(searchedNode != NULL){
        //return the index
        return searchedNode->index;
    }
    else{
        return -1;
    }
}

//rotate right given root and node
void RBTree::rotateRight(RBNode* rt, RBNode* node){
    //swap L and R children
    RBNode* nodeL = node->left;
    node->left = nodeL->right;

    if(node->left != NULL){
        node->left->parent = node;
    }
    nodeL->parent = node->parent;

    if(node->parent == NULL){
        rt = nodeL;
    }
    else if(node == node->parent->left){
        node->parent->left = nodeL;
    }
    else{
        node->parent->right = nodeL;
    }

    nodeL->right = node;
    node->parent = nodeL;
}

//rotate Left given root and node
void RBTree::rotateLeft(RBNode* rt, RBNode* node){
    RBNode* nodeR = node->right;
    node->right = nodeR->left;

    if(node->right != NULL){
        node->right->parent = node;
    }

    nodeR->parent = node->parent;

    if(node->parent == NULL){
        rt = nodeR;
    }
    else if(node == node->parent->left){
        node->parent->left = nodeR;
    }
    else{
        node->parent->right = nodeR;
    }

    nodeR->left = node;
    node->parent = nodeR;
}

//inserts using BST and returns new root
RBNode* RBTree::insert(RBNode* rt, RBNode* node){
    //bst recursion insert
    
    //if tree is empty, node is new root
    if(rt == NULL){
        return node;
    }
    //if root exists, inserted node name is less than rt node name, go to left
    if(node->name < rt->name){
        rt->left = insert(rt->left, node);
        rt->left->parent = rt;
    }
    //if root exists, inserted node name is greater than rt node name, go to right
    else if(node->name > rt->name){
        rt->right = insert(rt->right,node);
        rt->right->parent = rt;
    }
    return rt;
}

//searches for a node in RBTree with name 'name'
RBNode* RBTree::search(string name){
    //start at root, if name < root->name, go left, else go right, if null return null
    RBNode* temp = root;
    if(temp == NULL){
        //could not find a node with string name
        return NULL;
    }

    while(temp){
        //if find node with same string
        if(name == temp->name){
            //return int 
            return temp;
        }
        else if(name < temp->name){
            //if name not found, if name is less then temp->name go left
            temp = temp->left;
        }
        else if(name > temp->name){
            //if name is greater than temp->name go right
            temp = temp->right;
        }
    }
    //if not found, return -1 to indicate not found
    return NULL;
}

//fixes all the colors and ordering after insert
void RBTree::sort(RBNode* rt, RBNode* node){
    RBNode* nodeParent = NULL;
    RBNode* nodeGrandParent = NULL;
    RBNode* nodeUncle = NULL;

    while( (node != root) && (node->color != "black") && (node->parent->color == "red") ){
        nodeParent = node->parent;
        nodeGrandParent = node->parent->parent;

        //nodeParent is on the right
        if(nodeParent == nodeGrandParent->right){
            nodeUncle = nodeGrandParent->left;

            if(nodeUncle != NULL && nodeUncle->color == "red"){
                nodeGrandParent->color = "red";
                nodeParent->color = "black";
                nodeUncle->color = "black";
                node = nodeGrandParent;
            }
            else{
                //if ptr is left child of parent, right rotate
                if(node == nodeParent->left){
                    rotateRight(rt, nodeParent);
                    node = nodeParent;
                    nodeParent = node->parent;
                }
                //if ptr is right child of parent, left rotate
                else{
                    rotateLeft(rt,nodeGrandParent);
                    //swap colors bewteen parent and gp
                    string colorTemp = nodeParent->color;
                    nodeParent->color = nodeGrandParent->color;
                    nodeGrandParent->color = colorTemp;
                    node = nodeParent;
                }
            }// end else if nodeUncle->color == black or/and nodeUncle == NULL
        }
        else{ //nodeParent is on the left
            nodeUncle = nodeGrandParent->right;

            //uncle is red, then recolor
            if(nodeUncle != NULL && nodeUncle->color == "red"){
                nodeGrandParent->color = "red";
                nodeParent->color = "black";
                nodeUncle->color = "black";
                node = nodeGrandParent;
            }
            else{ //if uncle is black then check ptr position

                if(node == nodeParent->right){//node is on the right, then left rotate
                    rotateLeft(rt, nodeParent);
                    node = nodeParent;
                    nodeParent = node->parent;
                }
                else{ // node is left child, right rotate
                    rotateRight(rt,nodeGrandParent);
                    //swap colors bewteen parent and gp
                    string colorTemp = nodeParent->color;
                    nodeParent->color = nodeGrandParent->color;
                    nodeGrandParent->color = colorTemp;
                    node = nodeParent;

                }
            }

        }
    }// if node is root, then have to be black cuz its root
    rt->color = "black";
}

//adds user to tree and sorts
void RBTree::addUser(string name, int index){
    //make RBNode with default red color
    RBNode* temp = new RBNode;
    temp->color = "red";
    temp->name = name;
    temp->index = index;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;

    //add to tree using insert and set new root
    root = insert(root, temp);

    //if there is not tree yet, temp is root and has to be black
    if(root == NULL) {
        temp->color = "black";
        return;
    }

    //then sort
    sort(root, temp);
}

void RBTree::listInfo(vector<int> &v, RBNode* rt, string lowerName, string upperName){
    //base case
    if(rt == NULL){
        return;
    }

    //lower bound string is less than rt, the go left
    if(lowerName < rt->name){
        listInfo(v,rt->left,lowerName,upperName);
    }
    //if rt-> is in between lower and upper bound, push index to vector
    if(lowerName <= rt->name && upperName >= rt->name){
        v.push_back(rt->index);
    }
    // upper bound is greater than rt, than go right
    if(upperName > rt->name){
        listInfo(v,rt->right,lowerName,upperName);
    }
}

