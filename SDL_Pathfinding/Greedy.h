#pragma once
#include <vector>
#include "Node.h"
#include "Grid.h"
#include "SDL_SimpleApp.h"


class Greedy
{
public:
	Vector2D coin;
	Vector2D initPos;

	Grid* maze;

	Greedy(Grid* g, Vector2D c, Vector2D p);
	~Greedy();

	std::vector<Vector2D> CalculatePath();

private:
	std::vector<Node*> frontier;
	std::vector<Node*> visited;


	bool validPathNode(Node* n);
	bool isInVisited(Vector2D v);
	bool isInFrontier(Vector2D v);

	int mapWeight(Vector2D v);

	int lowestHeuristicIndex();





};
