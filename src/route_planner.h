#pragma once
/*
These files contain a class stub for a RoutePlanner class which accepts a RouteModel along with start and end coordinates.
The RouteModel data, along with the start and end points will be used for A* search,
which will be implemented in these files. Have a look a the video below for a brief overview of the contents.
*/
#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
  public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    // Add public variables or methods declarations here.
    //task 1 
    /*
    Add the following private variables to the RoutePlanner class in route_planer.h:
       -RouteModel::Node pointers start_node and end_node. These will point to the nodes in the model which are closest to our starting and ending points.
       -A float distance. This variable will hold the total distance for the route that A* search finds from start_node to end_node.
    Add the following public method to the RoutePlanner class in route_planner.h:
       -A GetDistance() method. This is a public getter method for the distance variable, and should just return distance. This method will later be used to print out the total distance from main.cpp.
*/
    float GetDistance() const { return distance; }
    void AStarSearch();
  private:
    // Add private variables or methods declarations here.
    RouteModel::Node* start_node;
    RouteModel::Node* end_node;
    //task 5 
    std::vector<RouteModel::Node*>open_list;
    float distance;
    RouteModel &m_Model;
    //task 3
    /*Add a ConstructFinalPath declaration to the RoutePlanner class in route_planner.h. 
    This method will only be called from the A* search within the RoutePlanner class,
    so it can be a private method. ConstructFinalPath should accept the pointer
    RouteModel::Node *current_node as the argument, and it should return a vector of RouteModel::Node objects.*/
    std::vector<RouteModel::Node>ConstructFinalPath(RouteModel::Node* current_node);
    //task 4 
    //Add a CalculateHValue declaration to the RoutePlanner class in route_planner.h.
    //This method will only be used in the RoutePlanner class, so it can be a private method.
    //CalculateHValue should accept a const pointer to a RouteModel::Node object, and it should return a float.
    float CalculateHValue(RouteModel::Node* node);
    //task 5
   RouteModel::Node* NextNode();
   //task 6
   void AddNeighbors(RouteModel::Node* node);
};
