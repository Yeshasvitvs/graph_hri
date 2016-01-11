#include "aograph.h"
#include "aonode.h"

//Default Constructor
aoGraph::aoGraph(vector<char>& input){

    std::cout << "Default Graph Constructor" << std::endl;
    std::cout << "Initializing graph..." << std::endl; //Debug Code
    //std::cout << "Enter the size of the Graph : ";

    if(!input.empty()){

        int data = input.front()-48;
        size = data;
        input.erase(input.begin());

    }

    //std::cin >> size; //Initial size of the graph. i.e., No of Nodes
    std::cout << "Size of the Graph : " << size << std::endl; //Debug Code
    if(size!=0){
        build = true;
    }
    else{
        build = false;
    }

}


//Default Destructor
aoGraph::~aoGraph(){

    //std::cout << "Graph Destructor Called..." << std::endl; //Debug Code
    delete node; //NOTE Double free error becuase node contains pointers to pointers
}

void aoGraph::buildGraph(vector<aoNode*> &nodePointer,vector<char> &input){


    std::cout << "Creating " << size << " Nodes for the graph..." << std::endl;
    for(int i = 1; i <= size ; i++){

        node = new aoNode(input);
        nodePointer.push_back(node);

    }

}



