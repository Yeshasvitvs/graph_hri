
/**
 *
 */



#include "aograph.h"
#include "aonode.h"
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>


#include <ogdf/basic/Graph.h>
#include <ogdf/tree/TreeLayout.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/basic/graph_generators.h>


#include <ogdf/layered/SugiyamaLayout.h>
#include <ogdf/layered/OptimalRanking.h>
#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/OptimalHierarchyLayout.h>

//#include <tulip/Algorithm.h>
#include <tulip/TlpTools.h>
#include <tulip/Graph.h>

#define inf INFINITY;


using namespace std;
using namespace ogdf;
using namespace tlp;

vector<aoNode*> nodePointer; //Vector of Pointers to Nodes in the Graph
vector<aoNode*>::iterator nodePointer_it;
vector<aoNode*> changePointer; //Vector of pointers to changed nodes
vector<aoNode*>::iterator changedPointer_it;
int nValue, hValue; //values for Node and HyperArc linear Indexing
vector<int> node_list;
vector<int> hArc_list;
vector<int> open_list;
vector<int> close_list;
vector<aoNode> nList; //Vector of Nodes to be stored during graph search
int futility=inf; //TODO need to discuss this variable more

vector<int> nodeIndex;
vector<int> hyperArcIndex;
ifstream infile;
vector<char> input; // Data Read from input file
vector<char>::iterator input_it;
void init();
void clear();
void searchGraph(vector<aoNode*> &);
bool display(); //For displaying Graph using OGDF
void dfs( GraphAttributes *GA, ogdf::Graph *G , Array<int> *state , ogdf::node *current );

//Displaying the Graph
/*bool display(){

    ogdf::Graph G;
    randomSimpleGraph(G,10,10); // Random DAG using random_heirarchy graph generator with 10 nodes, 10 edges
    GraphAttributes GA( G, GraphAttributes::nodeGraphics |
           GraphAttributes::edgeGraphics |
           GraphAttributes::nodeLabel |
           GraphAttributes::nodeStyle |
           GraphAttributes::edgeType |
           GraphAttributes::edgeArrow |
           GraphAttributes::edgeStyle |
           GraphAttributes::edgeLabel); // Create graph attributes for this graph
       GA.setDirected(false); // set to undirected


       //Setting similar style for all nodes
       ogdf::node v;
       forall_nodes( v, G ){   // iterate through all  the node in the graph
           GA.fillColor( v ) = Color( "#FFFF00" ); // set node color to yellow
           GA.height( v ) = 40.0;  // set the height to 20.0
           GA.width( v ) = 40.0;   // set the width to 40.0
           GA.shape(v ) = shEllipse;

           string s = to_string(v->index()); //Using the index for node labelling
           char const *pchar = s.c_str();  //use char const* as target type

           GA.label( v ) = pchar;

       }

       //Setting similar style for all edges
       ogdf::edge e;
       forall_edges(e ,G)  // set default edge color and type
       {
           GA.bends(e);
           GA.arrowType(e) =  ogdf::EdgeArrow::eaNone;
           GA.strokeColor(e) = Color("#0000FF");

           string ss = to_string(e->index()); //Using the index for edge labelling
           char const *echar = ss.c_str();

           GA.label(e) = echar;
       }

       Array<int> state(G.numberOfNodes()); // create state array to store the current states of the nodes

       for(int i=0;i<state.size();i++)
       {
           state[i] = -1;  // init the state vaiables

       }

       v = G.chooseNode();  // select random nodes for source
       state[ v->index() ]=0; //Assigning index 0 to random node

       dfs( &GA, &G ,&state, &v); // start recursion parameters are GraphAttributes, Graph, state and current node passed by reference

       //ogdf::TreeLayout TL;
       //TL.levelDistance(30);
       //TL.siblingDistance(10);
       //TL.RootSelectionType(rootIsSource);
       //TL.call(GA);

       SugiyamaLayout SL;   //Compute a hierarchical drawing of G (using SugiyamaLayout). This can be modified for AND-OR Graphs
       SL.setRanking( new OptimalRanking );
       SL.setCrossMin( new MedianHeuristic );

       OptimalHierarchyLayout *ohl = new OptimalHierarchyLayout;
       ohl->layerDistance( 30.0 );
       ohl->nodeDistance( 25.0 );
       ohl->weightBalancing( 0.8 );
       SL.setLayout( ohl );
       SL.call( GA );

       GraphIO::drawSVG( GA, "dfs.svg" ); //This is the final way to save the Graph. Look for alternatives for display
       GraphIO::writeTLP(GA, "g.tlp");

       return true;
}

void dfs( GraphAttributes *GA, ogdf::Graph *G , Array<int> *state , ogdf::node *current )//Passed by reference
{
    ogdf::edge e;
    forall_edges( e, *G ){  // iterate through all the node in the graph

        ogdf::node u = e->target();
        if( e->source()->index() == (*current)->index() && (*state)[ u->index() ]==-1 )  //
        {
            (*state)[ u->index() ]=0;     // set states

            GA->bends( e );
            GA->arrowType( e ) =  ogdf::EdgeArrow::eaLast;    // add red colure and arrow type
            GA->strokeColor( e ) = Color( "#FF0000" );

            dfs( GA, G, state, &u );
        }

        u = e->source();
        if( e->target()->index() == (*current)->index() && (*state)[ u->index() ]==-1)   //
        {
            (*state)[ u->index() ]=0;     // set states

            GA->bends( e );
            GA->arrowType( e ) =  ogdf::EdgeArrow::eaFirst;
            GA->strokeColor( e ) = Color( "#FF0000" );

            dfs( GA, G, state, &u ); //This is a recursive function
        }
    }
}*/

void init(){

    //initialize the Tulip lib
    initTulipLib();

    //create an empty graph
    tlp::Graph *t_graph = newGraph();

    //Loading graph from a .tlp file
    t_graph = tlp::loadGraph("/home/yeshi/qt/build-graph_hri/g.tlp");
    //cout<< t_graph << flush;

    //GUI Visualization



    std::cout<<"Initialization Routine..." << std::endl;
    infile.open("/home/yeshi/qt/graph_hri/input_file.txt"); //TODO  can put extra options for the file read

    if(infile.is_open()){
        std::cout << "Reading from the input file..." << std::endl;
        while(!infile.eof()){
            char data;
            infile.get(data);
            if(data!='\n'){
                //std::cout << data << std::endl;
                input.push_back(data);
            }

        }

    }else std::cout << "Unable to read from the input file!!!" << std::endl;

    /*while(!input.empty()){

        int data = input.front()-48;
        std::cout << data << std::endl;
        input.erase(input.begin());

    }*/

    /*for(input_it = input.begin() ; input_it != input.end() ; input_it++){

        int data = *input_it - 48;

        std::cout << data << std::endl;

    }*/

}



int main(int argc, char **argv)
{

   init();
  //display();
  aoGraph aograph(input);
  if(aograph.build==1){
      aograph.buildGraph(nodePointer, input);
  }

  std::cout << "Graph Size : "<< nodePointer.size() << std::endl; //Debug Code
  for(nodePointer_it = nodePointer.begin() ; nodePointer_it != nodePointer.end() ; ++nodePointer_it ){

      //std::cout << "Node Index : " << (*nodePointer_it)->nIndex << std::endl; //Debug Code
      //std::cout << "Node Index : " << nodeIndex.at(1) << std::endl;
      if((*nodePointer_it)->nComplete!=true){

          std::cout << "Node " << (*nodePointer_it)->nIndex << " is Not Complete..." << std::endl; //Debug Code
          for(int h = 0; h < (*nodePointer_it)->nHyperArcs ; h++){

              std::cout << "Completing Node Hyperarcs..." << std::endl; //Debug Code
              //std::cout << "Updating the HyperArc Weight..." << std::endl;
              //(*nodePointer_it)->hArcs[h].hCost = 0;
              //std::cout << "Enter the HyperArc Index : ";
              //std::cin >> (*nodePointer_it)->hArcs[h].hIndex;

              //std::cout << "is the HyperArc " << (*nodePointer_it)->hArcs[h].hIndex << " AND type ? Enter 1 if YES : ";
              //std::cin >> (*nodePointer_it)->hArcs[h].hType;
              //std::cout << "Enter the Number of Child Nodes for HyperArc " << (*nodePointer_it)->hArcs[h].hIndex << " : ";
              //std::cin >> (*nodePointer_it)->hArcs[h].nChild;

              if(!input.empty()){

                  int data = input.front()-48;
                  (*nodePointer_it)->hArcs[h].hIndex = data;
                  std::cout << "HyperArc Index : " << (*nodePointer_it)->hArcs[h].hIndex << std::endl;
                  input.erase(input.begin());

                  data = input.front()-48;
                  (*nodePointer_it)->hArcs[h].hType = data;
                  std::cout << "is the HyperArc " << (*nodePointer_it)->hArcs[h].hIndex << " AND type ? : " << (*nodePointer_it)->hArcs[h].hType << std::endl;
                  input.erase(input.begin());

                  data = input.front()-48;
                  (*nodePointer_it)->hArcs[h].nChild = data;
                  std::cout << "Number of Child Nodes for HyperArc " << (*nodePointer_it)->hArcs[h].hIndex << " : " << (*nodePointer_it)->hArcs[h].nChild << std::endl;
                  input.erase(input.begin());


              }

              //std::cout << "Updating the HyperArc Weight..." << std::endl;
              //(*nodePointer_it)->hArcs[h].hCost = (*nodePointer_it)->hArcs[h].hCost + (*nodePointer_it)->hArcs[h].nChild ;
              for(int c = 1 ; c <= (*nodePointer_it)->hArcs[h].nChild ; c++){

                  int childIndex; //Temp Variable
                  //std::cout << "Enter the Index of the Child Node : ";
                  //std::cin >> childIndex;
                  if(!input.empty()){

                      int data = input.front()-48;
                      childIndex = data;
                      std::cout << "Index of the Child Node : " << childIndex << std::endl;
                      input.erase(input.begin());

                  }
                  if(nodePointer[childIndex-1]!=0){

                      std::cout << "Pointer to Child Node is good..." << std::endl; //Debug Code
                      (*nodePointer_it)->hArcs[h].childPointer.push_back(&nodePointer[childIndex-1]);

                  }

                  std::cout << "One child node added..." <<  std::endl; //Debug Code
              }

              //vector<aoNode**>::iterator it = (*nodePointer_it)->hArcs[h].childPointer.begin(); //Temp Variable NOTE: Pointer to Pointer Iterator
              //std::cout << "HyperArc " << (*nodePointer_it)->hArcs[h].hIndex  << " Weight is : "<< (*nodePointer_it)->hArcs[h].hCost << std::endl;
              //std::cout << "Updating the HyperArc Weight..." << std::endl;
              //for(vector<aoNode**>::iterator it = (*nodePointer_it)->hArcs[h].childPointer.begin(); it != (*nodePointer_it)->hArcs[h].childPointer.end() ; it++){

                  //std::cout << "Child Node cost is : " << (**it)->nCost << std::endl;
                  //(*nodePointer_it)->hArcs[h].hCost = (*nodePointer_it)->hArcs[h].hCost + (**it)->nCost;

              //}
              //std::cout << "HyperArc " << (*nodePointer_it)->hArcs[h].hIndex  << " Weight is : "<< (*nodePointer_it)->hArcs[h].hCost << std::endl;


              std::cout << "All child Nodes added to HyperArc " << (*nodePointer_it)->hArcs[h].hIndex << std::endl; //Debug Code

          }

          std::cout << "Updating parent pointer vector..." << std::endl;
          int nParents;
          if(!input.empty()){

              int data = input.front()-48;
              nParents = data;
              std::cout << "Number of Parent Nodes : " << nParents << std::endl;
              input.erase(input.begin());

          }

          if(nParents != 0){

              for(int p = 0 ; p < nParents ; p++){

                  int pIndex;
                  if(!input.empty()){

                      int data = input.front()-48;
                      pIndex = data;
                      std::cout << "Index of the Parent Node : " << pIndex << std::endl;
                      input.erase(input.begin());

                  }
                  if(pIndex != 0){

                      (*nodePointer_it)->parentIndex.push_back(pIndex);

                  }

              }

          }
          else{
              std::cout << "This node does not have parents..." << std::endl;
          }


          (*nodePointer_it)->nComplete = true;
          std::cout << "Node " << (*nodePointer_it)->nIndex << " Complete..." << std::endl;
      }
  }

  infile.close(); //Closing the input text file
  std::cout << "Graph Building Done..." << std::endl; //Debug Code

  searchGraph(nodePointer);
  clear();

  return 0;
}

void searchGraph(vector<aoNode*> &nodePointer){

    std::cout << "Searching graph..." << std::endl;

    nodePointer_it = nodePointer.begin(); //Pointing to the start/head node in he graph

    aoNode head_node, current_node, next_node;

    head_node = **nodePointer.begin(); //Assigining nodes form the pointers of pointers to nodes
    current_node = head_node; //Assigning the head node as current node

    //std::cout << "Graph Start Node Index : " << (*nodePointer_it)->nIndex << std::endl; //Debug Code
    //std::cout << "Head Node Index : " << head_node.nIndex << std::endl; //Debug Code

    while(current_node.nSolved!=true){

        current_node = head_node; //Assigning the head node as current node

        //std::cout << "Head Node is Not Solved " << std::endl;

        node_list.push_back(current_node.nIndex); //Pushing the index of the node

        //forward phase

        int hCost= inf; //Local Variable
        std::cout << "Number of hyperArcs : " << current_node.nHyperArcs << std::endl; //Debug Code
        for(int h=0 ; h < current_node.nHyperArcs ; h++){ //Loop to decide which hArc is of Low Cost

            int cost=0;//Local Variable

            if(current_node.hArcs[h].hType == 1){ //if this is AND hyperArc

                std::cout << "Numer of child Nodes of AND hyperArc " << current_node.hArcs[h].hIndex << " : " << head_node.hArcs->nChild << std::endl;//Debug Code

                bool solved = 1; //Temp Variable
                aoNode child_node; //Local Variable
                for(int c=0; c < current_node.hArcs[h].nChild ; c++){

                    child_node = **(current_node.hArcs[h].childPointer.at(c));
                    cost = cost + child_node.nCost;
                    std::cout << "Child Node Index : " << child_node.nIndex << std::endl;//Debug code

                    solved = solved * child_node.nSolved;

//                    if(child_node.nSolved == 1){//if the child node is not solved(in another sense not terminal)

//                        current_node.nSolved = 1; //TODO check how this works on large graphs
//                    }
//                    else{
//                        current_node.nSolved = 0;
//                    }


                }

                current_node.nSolved = solved;
                std::cout << "Is the Current Node Solved ? " << current_node.nSolved << std::endl;//Debug Code

                std::cout << "hArc cost : " << cost << std::endl; //Debug Code

                if(cost < hCost){

                    hCost = cost;
                    std::cout << "hCost : " << hCost <<std::endl;//Debug Code

                    if(hArc_list.size() >= node_list.size() ){
                        hArc_list.pop_back();

                    }

                    hArc_list.push_back(current_node.hArcs[h].hIndex); //This is the marked path from a node
                    //std::cout << "Node list Size : " << node_list.size() << std::endl;//Debug Code
                    //std::cout << "Node list front : " << node_list.front() << std::endl;//Debug Code
                    //std::cout << "Node list back : " << node_list.back() << std::endl;//Debug Code

                    //std::cout << "hArc list Size : " << hArc_list.size() << std::endl;//Debug Code
                    //std::cout << "hArc list front : " << hArc_list.front() << std::endl;//Debug Code
                    //std::cout << "hArc list back : " << hArc_list.back() << std::endl;//Debug Code

                }

            }
            else{//if this is OR hyperArc

            }

            //std::cout << "hArc list : " << hArc_list.front() << std::endl;//Debug Code

        }

        //Backward Cost Propogation
        aoNode cNode;
        changePointer.push_back((*nodePointer_it));
        while(!changePointer.empty()){//If any node is changed back propagate the cost

        }
        aoNode node = current_node; //Dummy Variable
        node.nCost = hCost;
        std::cout << "Node Index : " << node.nIndex << " with updated cost : " << node.nCost << std::endl;//Debug Code
        nList.push_back(node); //Pushing the nodes with updated costs in a new vector


        //std::cout << "Back in hArc List : " << hArc_list.back() << std::endl;//Debug Code

        if(current_node.nSolved != 1){ //if the current node is not solved expand it to find the next node

            int child_cost = 0; //Local Variable
            int value = hArc_list.back()-1; //Indexes are from 1 so need to use -1 for referencing vectors

            //std::cout << "Child value :" << current_node.hArcs[hArc_list.back()-1].nChild << std::endl;//Debug Code
            int cost = 0;//Local Variable
            aoNode child_node; //Local Variable
            for(int c=0; c < current_node.hArcs[value].nChild; c++){ //Note that the Indexes are from 1 not 0


                //std::cout << "C value : " << c << std::endl;
                child_node = **(current_node.hArcs[value].childPointer.at(c));
                std::cout << "Child Index : " << child_node.nIndex << std::endl;//Debug Code
                cost = child_node.nCost;
                std::cout << "Child Cost : " << cost << std::endl;//Debug Code

                if(cost > child_cost){

                    child_cost = cost; //Assigning the cost of the node with high cost in the hArc of the current node
                    head_node = child_node;

                }


            }

            std::cout << "Current Node Index : " << head_node.nIndex << std::endl;//Debug Code

        }



    }//Main while loop



}

void clear(){


}
