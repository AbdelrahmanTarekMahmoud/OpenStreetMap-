#include "route_planner.h"
#include <algorithm>
#include<cmath>
#include<set>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) 
{
	//task 2 
	/*Within the body of the RoutePlanner constructor:

    Scale the floats to percentages by multiplying each float by 0.01 and storing the result in the float variable. For example: start_x *= 0.01;
    Use the m_Model.FindClosestNode method to find the closest nodes to (start_x, start_y) and (end_x, end_y). Store pointers to these nodes in the start_node and end_node class variables*/
	start_x *= 0.01; // scaling to precentage
	start_y *= 0.01;
	end_x *= 0.01;
	end_y *= 0.01;
	start_node=&m_Model.FindClosestNode(start_x, start_y);
	end_node=&m_Model.FindClosestNode(end_x, end_y);
}
//task 3
/*n route_planner.cpp define the ConstructFinalPath method. The method should do the following:

    Initialize an empty vector path_found of RouteModel::Node objects and set the class variable distance to 0.
    Iterate through the node parents until a node with parent equal to nullptr is reached - this will be the start node, which has no parent. Each node in the iteration should be pushed to the path_found vector.
    To keep track of the total path distance, in each step of the iteration, add the distance between a node and its parent to the class distance variable.
    Before the method returns, scale the distance by multiplying by the model's scale: m_Model.MetricScale(). This is done since node coordinates are scaled down when they are stored in the model. They must be rescaled to get an accurate distance.
    Return the path_found.*/
std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node* current_node)
{
	std::vector<RouteModel::Node>path_found;
	distance = 0.0;
	RouteModel::Node parent;
	while(current_node->parent != nullptr) // itertaing untill we fing star_node which is the only one that has nullptr
	{
		
			path_found.push_back(*current_node);
			parent = *(current_node->parent);
			distance += current_node->distance(parent);
			current_node = current_node->parent;
    } 
	path_found.push_back(*current_node);
	distance *= m_Model.MetricScale();
	return path_found;
}
//task 7
/*


	Set start_node->visited to be true.

	Push start_node to the back of open_list.

	Create a pointer RouteModel::Node *current_node and initialize the pointer to nullptr.

	while the open_list size is greater than 0:
		Set the current_node pointer to the results of calling NextNode.
		if the distance from current_node to the end_node is 0:
		Call ConstructFinalPath using current_node and set m_Model.path with the results.
		Return to exit the A* search.
		else call AddNeighbors with the current_node.
*/
void RoutePlanner::AStarSearch()
{
	start_node->visited = true;
	open_list.push_back(start_node);
	RouteModel::Node* current_node = nullptr;
	while (open_list.size() > 0)
	{
		current_node=NextNode();
		if (current_node->distance(*end_node) == 0)
		{
			m_Model.path=ConstructFinalPath(current_node);
			return;
		}
		else
		{
			AddNeighbors(current_node);
		}
	}


}
//task 4
/*
In route_planner.cpp define the CalculateHValue method.
The method should return the distance from the passed argument to the end_node.*/
float RoutePlanner::CalculateHValue(RouteModel::Node* node)
{
	return node->distance(*end_node);
}
//task 5 
/*
In route_planner.cpp define the NextNode method. This method should:

	Sort the open_list according to the f-value, which is the sum of a node's h-value and g-value.
	Create a copy of the pointer to the node with the lowest f-value.
	Erase that node pointer from open_list.
	Return the pointer copy.
*/
RouteModel::Node* RoutePlanner::NextNode()
{
	std::sort(open_list.begin(), open_list.end(), [](const auto& _1st, const auto& _2nd)
	{
			return _1st->h_value + _1st->g_value < _2nd->h_value + _2nd->g_value;
	});

	RouteModel::Node *lowest_node = open_list.front();
	open_list.erase(open_list.begin());
	return lowest_node;
}
//task6
/*Set the neighbors parent to the current_node.

    Set the neighbor's g_value to the sum of the current_node's g_value plus the distance from the curent_node to the neighbor.
    Set the neighbor's h_value using CalculateHValue
    Push the neighbor to the back of the open_list.
    Mark the neighbor as visited.*/
void RoutePlanner::AddNeighbors(RouteModel::Node* current_node)
{
	current_node->FindNeighbors();
	for (auto neighbor : current_node->neighbors)
	{
		neighbor->parent = current_node;
		neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
		neighbor->h_value = CalculateHValue(neighbor);

		open_list.push_back(neighbor);
		neighbor->visited = true;
	}
}
