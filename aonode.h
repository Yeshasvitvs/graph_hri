#ifndef AONODE_H
#define AONODE_H

#include <iostream>
#include <vector>

using namespace std;

// Definition Node Class
class aoNode{



public:

    int nCost; //The initial node cost is same for all the nodes
    int nIndex; //Node Index
    int nHyperArcs; //Each node has fixed number of hyperarcs in the global graph
    bool nComplete; //A node is complete if all its Hyperarcs direct to child nodes
    bool nSolved; //Is the node solved
    vector<int> parentIndex; //Can put under protected

    struct hyperArcs{

        int hIndex;
        bool hType; //hyperArcs Type AND(1) or OR
        int nChild; //Number of child
        int hCost; //HyperArc Cost: Sum of child node costs + number of child nodes
        //TODO Pointers from One Node Hyperarcs to child nodes

        vector<aoNode**> childPointer; //This doesnt have to be a vector as hyperarc child nodes are only two

    };

    hyperArcs *hArcs;

    aoNode(vector<char> &); //Default Constructor
    aoNode();//Default Copy Constructor
    virtual ~aoNode(); //Default Destructor
    bool isTerminal(vector<char> &);
    void completeNode(); //This is the routine for completing node with all the hyperArcs directed to Child Node


    //        void addSuccessor(Node<N>*);
//        Node<N>* deleteSuccessor();
//        Node<N>* getNext();
//        void setCost();
//        void iterateCost();
//        void isComplete(); //Check if the node is completed with all the hyperarcs
//        bool isSolved(); // Also can be used for terminal node
//        bool isTerminal();

};
#endif
