#ifndef FRIENDSHIPGRAPH_H
#define FRIENDSHIPGRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include "ProfileData.h"

using namespace std;

struct GraphNode{
    string name;
    int index;
    

};

class FriendList{
    public:
        string getFriend();
    private:
        GraphNode* head;
};


#endif