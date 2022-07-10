#pragma once
/*
route_model.h and route_model.cpp
These files contain class stubs which will be used to extend the Model and Node data structures
from model.h and model.cpp using "class inheritance".

Remember that inheritance in this case will you
to use all of the PUBLIC methods and attributes of the Model and Node classes in the derived classes.
You will be filling out the classes in route_model.h and route_model.cpp over the course of your project.

*/
#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>

class RouteModel : public Model {

  public:
    class Node : public Model::Node {
      public:
        //Task3
          /*Add the following public variables to the RouteModel::Node class :
              A Node pointer parent, which is initialized to a nullptr.
              A float h_value, which is initialized to the maximum possible : std::numeric_limits<float>::max().
              A float g_value, which is initialized to 0.0.
              A bool visited, which is initialized to false.
              A vector of Node pointers named neighbors.*/
          Node* parent = nullptr;
          float h_value = std::numeric_limits<float>::max();
          float g_value = 0.0;
          bool visited = false;
         std::vector<Node *>neighbors;
         //task 5 
         /*
          Add a distance declaration to the RouteModel::Node class in route_model.h. 
          This method should take a Node object as the argument, and it should return a float. 
          The distance method shouldn't change the object being passed,
           so you can make it a const method (add const after the function name).
           Return the euclidean distance from the current node to the node passed in.
          Note that for points (x_1, y_1) and (x_2, y_2), 
          the euclidean distance is given by \sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}.
         */
         float distance( Node other) const
         {
             return std::sqrt( std::pow((x-other.x),2) + std::pow((y-other.y),2));
         }
        void FindNeighbors();
        Node(){}
        Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}
      
      private:
        int index;
        //This variable is important, as it allows each node to access data stored in the parent model that the node belongs to.
        RouteModel * parent_model = nullptr;
        //task 9
        Node* FindNeighbor(std::vector<int>node_indices);
    };
    
    // Add public RouteModel variables and methods here.
    RouteModel(const std::vector<std::byte> &xml);  
    std::vector<Node> path; // This variable will eventually store the path that is found by the A* search.
     //Task2:Add a public "getter" method SNodes. This method should return a reference to the vector of Nodes stored as m_Nodes.
    auto& SNodes() { return m_Nodes; }
    auto& GetNodeToRoadMap() { return node_to_road };
    Node &FindClosestNode(float x , float y);
  private:
      //Task 7 :Add a method declaration CreateNodeToRoadHashmap in the RouteModel class in route_model.h
      //. This method will operate only on the node_to_road variable declared above, 
      //and only within the RouteModel class, so it can be private, it needs no arguments, and can have void return type
     void CreateNodeToRoadHashmap();
    //Taks1:Add a private vector of Node objects named m_Nodes. This will store all of the nodes from the Open Street Map data.
     std::vector<Node> m_Nodes;
     //Task 6 :Add a private variable node_to_road in the RouteModel class in route_model.h
     //This variable should be an unordered_map with an int key type, 
     //and a vector of const Model::Road* as the value type
     std::unordered_map<int, std::vector<const Model::Road* >>node_to_road;
};
 