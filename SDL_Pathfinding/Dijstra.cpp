#include "Dijkstra.h"

Dijkstra::Dijkstra(Grid* g, Vector2D c, Vector2D p)
{
	maze = g;
	coin = c;
	initPos = p;
}

Dijkstra::~Dijkstra()
{
	delete maze;
}

std::vector<Vector2D> Dijkstra::CalculatePath()
{
	bool reachedCoin = false;

	Node* best = new Node(nullptr, initPos);
	best->costSF = 0;
	frontier.push_back(best);


	while (!reachedCoin)
	{
		best = frontier[bestNode()];

		if (maze->pix2cell(best->pos) == coin)
		{
			reachedCoin = true;
			break;
		}

		//UP
		Node* nextNode = new Node(best, Vector2D(best->pos.x, best->pos.y - CELL_SIZE));
		nextNode->costSF = best->costSF + 1;
		if (validPathNode(nextNode))
			nextFrontier.push_back(nextNode);

		//DOWN
		nextNode = new Node(best, Vector2D(best->pos.x, best->pos.y + CELL_SIZE));
		nextNode->costSF = best->costSF + 1;
		if (validPathNode(nextNode))
			nextFrontier.push_back(nextNode);

		//LEFT
		nextNode = new Node(best, Vector2D(best->pos.x - CELL_SIZE, best->pos.y));
		nextNode->costSF = best->costSF + 1;
		if (validPathNode(nextNode))
			nextFrontier.push_back(nextNode);

		//RIGHT
		nextNode = new Node(best, Vector2D(best->pos.x + CELL_SIZE, best->pos.y));
		nextNode->costSF = best->costSF + 1;
		if (validPathNode(nextNode))
			nextFrontier.push_back(nextNode);

		visited.push_back(best);

		if (!reachedCoin)
		{
			frontier = nextFrontier;
			nextFrontier.clear();
		}

	}

	std::vector<Vector2D> finalPath;

	bool reachedFirstNode = false;

	Node* actualNode = best;

	while (!reachedFirstNode)
	{
		finalPath.insert(finalPath.begin(), actualNode->pos);

		if (actualNode->cameFrom == nullptr)
			reachedFirstNode = true;
		else
			actualNode = actualNode->cameFrom;
	}

	return finalPath;
}

bool Dijkstra::validPathNode(Node* n)
{
	if (!isInVisited(n->pos) && !isInNextFrontier(n->pos) && maze->isValidCell(maze->pix2cell(n->pos)))
		return true;

	return false;
}

bool Dijkstra::isInVisited(Vector2D v)
{
	for (int i = 0; i < visited.size(); i++)
	{
		if (visited[i]->pos == v)
			return true;
	}

	return false;
}

bool Dijkstra::isInNextFrontier(Vector2D v)
{
	for (int i = 0; i < nextFrontier.size(); i++)
	{
		if (nextFrontier[i]->pos == v)
			return true;
	}

	return false;
}

int Dijkstra::bestNode()
{
	int index = 0;
	int cost = frontier[0]->costSF;

	for (int i = 0; i < frontier.size(); i++)
	{
		if(frontier[i]->costSF < cost)
		{
			index = i;
			cost = frontier[i]->costSF;
		}
	}

	return index;
}
