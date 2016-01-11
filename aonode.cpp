#include "aonode.h"

///***
//* While building the big graph, when a node is created,
//* Node characteristics are : Number of next nodes
//* Shold this relation be implied in the graph or node instance ?
//***/

//Default Copy Constructor
aoNode::aoNode(){

    //std::cout << "Node Copy Constructor..." << std::endl;

}

//Default Constructor
aoNode::aoNode(vector<char> &input){

    //std::cout << "Enter the Node Index : ";
    //std::cin >> nIndex;
    //std::cout << "Enter the Node Cost : ";
    //std::cin >> nCost;
    if(!input.empty()){

        int data = input.front()-48;
        nIndex = data;
        std::cout << "Node Index : " << nIndex << std::endl;
        input.erase(input.begin());

        data = input.front()-48;
        nCost = data;
        std::cout << "Node Cost : " << nCost << std::endl;
        input.erase(input.begin());


    }

    if(isTerminal(input)!=1){ //If the node is not terminal

        nComplete = false; //Bool For checking Node Complete
        //std::cout << "Enter the number of hyper arcs : ";
        //std::cin >> nHyperArcs;
        if(!input.empty()){

            int data = input.front()-48;
            nHyperArcs = data;
            std::cout << "Number of HyperArcs : " << nHyperArcs << std::endl;
            input.erase(input.begin());

        }
        std::cout << "Initializing HyperArc Structure of the Node..." << std::endl; //Debug Code
        hArcs = new hyperArcs[nHyperArcs]; //Creating array of structure instances

    }else{
        nComplete = true; //Terminal Nodes are complete
    }
    //nSolved = false; //By default the nodes are not solved
}

//Default Destructor
aoNode::~aoNode(){

    //std::cout << "Node Destructor Called..." << std::endl; //Debug Code
    //hArcs-> childPointer.clear();
    //delete [] hArcs;

}


// Checking for terminal node
bool aoNode::isTerminal(vector<char> &input){

    int value; //Local Variable
    //std::cout << "Is this node Terminal ? Enter 1 if YES : ";
    //std::cin >> value;
    if(!input.empty()){

        int data = input.front()-48;
        value = data;
        std::cout << "Node is Terminal ? : " << value << std::endl;
        input.erase(input.begin());

    }

    if(value ==1){

        nHyperArcs = 0;
        nSolved = 1;
        return 1;
    }else{return 0;}

}

void aoNode::completeNode(){


}






