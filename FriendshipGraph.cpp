#include <iostream>
#include <string>
#include <vector>
#include "FriendshipGraph.h"

using namespace std;

//constructor
FriendList::FriendList(){
    //nothing lol, always start with zero
    vectorSize = 0;
}

//deconstructor, go through vector and remove all ll nodes
FriendList::~FriendList(){
    for(vector<GraphNode>::iterator it = begin(graph); it != end(graph); ++it){
        //go to curr, and delete
        Node* curr = it->head;
        while(curr != NULL){
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        it->head = NULL;
    }
}

//getFriendList return string ,friend,frefjdk,fdfddf,dfdf..
string FriendList::getFriendList(int index){
    string out = "";

    //goes to index index in vector,
    //grab the index
    //while head is not null, append name to out
    //head is null, return out
    Node* temp = graph[index].head;
    while(temp != NULL && index < vectorSize && index > -1){
        out =  out + "," + temp->name;
        temp = temp->next;
    }

    return out;
}

//getFriendIndex sets a given vector to a list of indexes of friends of index index
void FriendList::getFriendIndex(vector<int> &v, int index){
    //index is out of range
    if(index > vectorSize || index < 0){
        return;
    }

    //go to index in vector and
    //while head is not null, push back index to v
    Node* temp = graph[index].head;
    while(temp != NULL){
        v.push_back(temp->index);
        temp = temp->next;
    }

    return;

}

//check if they are friends, given index
bool FriendList::areFriends(int index1, int index2){
    //return false if out of range
    if(index1 > vectorSize || index1 < 0 || index2 > vectorSize || index2 < 0){
        return false;
    }

    //go to first index, traverse ll, if index2 found return true
    Node* temp = graph[index1].head;
    while(temp != NULL){
        //compare index
        if(temp->index == index2){
            //they are friends 
            return true;
        }
        temp = temp->next;
    }
    //went through entire list, not found
    return false;
}

//adds new user, init with no friends
void FriendList::addUser(string name){
    //check if user exists? i think thats already done on init
    
    //add name to end of vector and increase vectorSize
    GraphNode temp;
    temp.head = NULL;
    temp.name = name;

    graph.push_back(temp);
    vectorSize++;
}

//adds new friend to both users given index
void FriendList::addFriend(int index1,int index2){
    //return immed if either indexes is out of range
    if(index1 > vectorSize || index1 < 0 || index2 > vectorSize || index2 < 0){
        return;
    }
    //if already friends, immed return
    if(areFriends(index1,index2)){
        return;
    }

    cout << "adding a new friend" << endl;
    //else, go to both indexes in vector, append Node to list
    Node* user1 = new Node;
    user1->name = graph[index1].name;
    user1->index = index1;
    user1->next = NULL; //gonna be at end of ll
    Node* user2 = new Node;
    user2->name = graph[index2].name;
    user2->index = index2;
    user2->next = NULL; //gonna be at end of ll

    //go to first index, traverse to node with next == NULL
    Node* temp1 = graph[index1].head;
    while(temp1->next != NULL){
        temp1 = temp1->next;
    }
    //ends, then temp1 is last node
    //set temp1-> next to user2
    temp1->next = user2;

    //do same for second index
    Node* temp2 = graph[index2].head;
    while(temp2->next != NULL){
        temp2 = temp2->next;
    }
    //ends, then temp2 is last node
    //set temp2-> next to user1
    temp2->next = user1;
    cout << "done adding friend" << endl;
    return; //done
}


