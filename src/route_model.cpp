#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) 
{
	//task 4 
	/*
    In the RouteModel constructor in route_model.cpp, 
	write a for loop with a counter to loop over the vector of Model::Nodes given by this->Nodes().
    For each Model node in the loop, use the RouteModel::Node constructor to create a new node, 
	and push the new node to the back of m_Nodes.
    To do this, you should use the RouteModel::Node constructor that accepts three arguments:
*/
	int counter = 0;
	for (Model::Node node : this -> Nodes())
	{
		m_Nodes.push_back(Node(counter , this , node));
		counter++;
	}

}
//task 8 :
/*
 1-Add a private variable node_to_road in the RouteModel class in route_model.h.
 This variable should be an unordered_map with an int key type, 
 and a vector of const Model::Road* as the value type.
 2-Add a method declaration CreateNodeToRoadHashmap in the RouteModel class in route_model.h.
 This method will operate only on the node_to_road variable declared above, 
 and only within the RouteModel class, so it can be private, it needs no arguments, 
 and can have void return type.
 3-Add a method definition in route_model.cpp. In the body of the method, you will need to do the following:
       A-Write a loop that iterates through the vector given by calling Roads().
           -For each reference &road in the vector, check that the type is not a footway:
		   road.type != Model::Road::Type::Footway. If the road is not a footway:
           - Loop over each node_idx in the way that the road belongs to: Ways()[road.way].nodes.
           - If the node index is not in the node_to_road hashmap yet, 
		   set the value for the node_idx key to be an empty vector of const Model::Road* objects.
           - Push a pointer to the current road in the loop to the back of the vector given by 
		   the node_idx key in node_to_road.
       B-  Call CreateNodeToRoadHashmap() in the RouteModel constructor in route_model.cpp.
       C- Lastly, add a public getter function GetNodeToRoadMap() in the RouteModel class in route_model.h. 
	   This function should return a reference to the node_to_road variable, 
	   and it will be primarily used for testing.

*/
void RouteModel ::CreateNodeToRoadHashmap()
{
	for (const Model::Road& road : Roads())
	{
		if (road.type != Model::Road::Type::Footway)
		{
			for (int node_idx : Ways()[road.way].nodes)
			{
				if (node_to_road.find(node_idx) == node_to_road.end());
				{
					node_to_road[node.idx] = std::vector<const Model::Road*> ();
				}
				node_to_road[node_idx].push_back(&road);
			}
		}
	}

}
//Task 9
/*## To complete this exercise:

    Add a FindNeighbor declaration to the RouteModel::Node class in route_model.h.
	This method will only be used later in another RouteModel::Node method to
	find the closest node in each Road containing the current node,
	so FindNeighbor can be a private method. FindNeighbor should accept
	a vector<int> node_indices argument and return a pointer to a node: RouteModel::Node* type.

    In route_model.cpp define an empty FindNeighbor method. At this step, compile the code using make to check that your method declaration and empty method definiton have matching signatures.
    Within the FindNeighbor method, loop through the node_indices vector to find the closest unvisited node. To do this, start with a pointer Node *closest_node = nullptr, and then update closest_node as you find closer nodes in the loop. The following will be useful:
      -For each index in the loop, you can retrieve the Node object with parent_model->SNodes()[index].
       -For each retrieved Node in the loop, you should check that the node has not been visted (!node.visited) and that the distance to this is nonzero. In other words, you want the closest unvisted node that is not the current node.
       - The RouteModel::Node::distance method can be used to find the distance between two nodes.

## Pseudocode:

The FindNeighbor method, given a vector<int> node_indices:

    Create a pointer Node *closest_node = nullptr

    Declare a temporary Node variable node

    For each node_index in node_indices

        Set node equal to the parent_model->SNodes()[node_index]

        If the distance from this to node is nonzero, and the node has not been visited:

        If the closest_node equals nullptr, or the distance from this to node is less than the distance from this to *closest_node:
            Set closest_node to point to the address of parent_model->SNodes()[node_index].

    Finally, return the closest_node.
*/
RouteModel::Node* RouteModel::Node::FindNeighbor(std::vector<int>node_indices)
{
	Node* closest_node = nullptr;
	Node node;
	for (int node_index : node_indices)
	{
		node = parent_model->SNodes()[node_index];
		if (this->distance(node) != 0 && !node.visited)
		{
			if (closest_node == nullptr || this->distance(node) < this->distance(*closest_node))
			{
				closest_node = &parent_model->SNodes()[node_index];
			}
		}
	}
	return closet_node;
}
//task 10
/*
    Add a public FindNeighbors declaration to the RouteModel::Node class in route_model.h. 
	This method will be called from route_planner.cpp, so the method needs to be public.
	FindNeighbors should take no arguments and have void return type.
    In route_model.cpp define the FindNeighbors method.
    With the FindNeighbors method, for each road reference &road in 
	the vector parent_model->node_to_road[this->index],
	FindNeighbors should use the FindNeighbor method to create a pointer of RouteModel::Node* type.
    If that pointer is not a nullptr, push the pointer to the back of this->neighbors.
*/
void RouteModel::Node::FindNeighbors()
{
	for (auto& road : parent_model->node_to_road[this->index])
	{
		RouteModel::Node* new_neighbor = this->FindNeighbor(parent_model->Ways()[road.way].nodes);
		if (new_neighbor)
		{
			this->neighbors.emplace_back(new_neighbor);
		}
	}
}
//task 11
/*
   1 Add a public method declaration FindClosestNode in the RouteModel class in route_model.h. This method should accept two floats x and y as arguments, and should return a reference to a RouteModel::Node object.
   2 Add a method definition route_model.cpp
   3 In the body of the method, you will need to do the following:

       1 Create a temporary Node with x and y coordinates given by the method inputs.
            2Create a float min_dist = std::numeric_limits<float>::max() for the minum distance found in your search.
           3 Create an int variable closest_idx to store the index of the closest
           4 Write a loop that iterates through the vector given by calling Roads().
           5 For each reference &road in the vector, check that the type is not a footway: road.type != Model::Road::Type::Footway. If the road is not a footway:
                1Loop over each node index in the way that the road belongs to: Ways()[road.way].nodes.
                2Update closest_idx and min_dist, if needed.
            6 Return the node from the SNodes() vector using the found index.

*/
RouteModel::Node &RouteModel::FindClosestNode(float x, float y)
{
	Node input;
	input.x = x;
	input.y = y;
	float min_dist = std::numeric_limits<float>::max();
	float dist;
	int closest_idx;
	for (const Model::Road& road : Roads())
	{
		if (road.type != Model::Road::Type::Footway)
		{
			for (int node_idx : Ways()[road.way].nodes)
			{
				dist = input.distance(SNodes()[node_idx]);
				{
					if (dist < mid_dist)
					{
						closest_idx = node_idx;
						min_dist = dist;
					}
				}

			}
		}
	}
	return SNodes()[closest_idx];

}