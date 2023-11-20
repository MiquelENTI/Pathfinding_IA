#pragma once
#include <vector>
#include "Node.h"
#include "Grid.h"
#include "SDL_SimpleApp.h"


class BFS
{
public:
	Vector2D coin;
	Vector2D initPos;

	Grid* maze;

	BFS(Grid* g, Vector2D c, Vector2D p);
	~BFS();

	std::vector<Vector2D> CalculatePath();

private:
	std::vector<Node*> frontier;
	std::vector<Node*> nextFrontier;
	std::vector<Node*> visited;


	bool validPathNode(Node* n);
	bool isInVisited(Vector2D v);
	bool isInNextFrontier(Vector2D v);





};