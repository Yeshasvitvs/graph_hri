#ifndef AOGRAPH_H
#define AOGRAPH_H

#include <iostream>
#include <vector>
#include "aonode.h"
using namespace std;

//Definition of Graph Class
class aoGraph{

public:

    int size; //Could be number of nodes ?
    int position;
    bool build;
    aoNode* node; //Node Pointer Variable

    aoGraph(vector<char> &); //Default Constructor
    virtual ~aoGraph(); //Default Destructor
    void buildGraph(vector<aoNode *> &, vector<char> &);


};

#endif
