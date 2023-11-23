#include "Greedy.h"

Greedy::Greedy(Grid* g, Vector2D c, Vector2D p)
{
	maze = g;
	coin = c;
	initPos = p;
}

Greedy::~Greedy()
{
	delete maze;
}

std::vector<Vector2D> Greedy::CalculatePath()
{
	bool reachedCoin = false;

	Node* lowestHeuristicNode = new Node(nullptr, initPos);
	lowestHeuristicNode->heuristic = 0;
	frontier.push_back(lowestHeuristicNode);


	while (!reachedCoin)
	{
		int index = lowestHeuristicIndex();
		lowestHeuristicNode = frontier[index];
		frontier.erase(frontier.begin() + index);

		if (maze->pix2cell(lowestHeuristicNode->pos) == coin)
		{
			reachedCoin = true;
			break;
		}

		//UP
		Node* nextNode = new Node(lowestHeuristicNode, Vector2D(lowestHeuristicNode->pos.x, lowestHeuristicNode->pos.y - CELL_SIZE));
		nextNode->heuristic = mapWeight(nextNode->pos);
		if (validPathNode(nextNode))
			frontier.push_back(nextNode);

		//DOWN
		nextNode = new Node(lowestHeuristicNode, Vector2D(lowestHeuristicNode->pos.x, lowestHeuristicNode->pos.y + CELL_SIZE));
		nextNode->heuristic = mapWeight(nextNode->pos);
		if (validPathNode(nextNode))
			frontier.push_back(nextNode);

		//LEFT
		nextNode = new Node(lowestHeuristicNode, Vector2D(lowestHeuristicNode->pos.x - CELL_SIZE, lowestHeuristicNode->pos.y));
		nextNode->heuristic = mapWeight(nextNode->pos);
		if (validPathNode(nextNode))
			frontier.push_back(nextNode);

		//RIGHT
		nextNode = new Node(lowestHeuristicNode, Vector2D(lowestHeuristicNode->pos.x + CELL_SIZE, lowestHeuristicNode->pos.y));
		nextNode->heuristic = mapWeight(nextNode->pos);
		if (validPathNode(nextNode))
			frontier.push_back(nextNode);

		visited.push_back(lowestHeuristicNode);
	}

	std::vector<Vector2D> finalPath;

	bool reachedFirstNode = false;

	Node* actualNode = lowestHeuristicNode;

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

bool Greedy::validPathNode(Node* n)
{
	if (!isInVisited(n->pos) && !isInFrontier(n->pos) && maze->isValidCell(maze->pix2cell(n->pos)))
		return true;

	return false;
}

bool Greedy::isInVisited(Vector2D v)
{
	for (int i = 0; i < visited.size(); i++)
	{
		if (visited[i]->pos == v)
			return true;
	}

	return false;
}

bool Greedy::isInFrontier(Vector2D v)
{
	for (int i = 0; i < frontier.size(); i++)
	{
		if (frontier[i]->pos == v)
			return true;
	}

	return false;
}

int Greedy::mapWeight(Vector2D v)
{
	Vector2D cell = maze->pix2cell(v);

	if (cell.x > 4 && cell.x < 10 && cell.y > 8 && cell.y < 16 ||
		cell.x > 29 && cell.x < 34 && cell.y > 8 && cell.y < 16)
		return 10;
	else if (cell.x > 15 && cell.x < 23 && cell.y > 7 && cell.y < 16)
		return 0;

	return 1;
}

int Greedy::lowestHeuristicIndex()
{
	int index = 0;
	int costHeuristic = frontier[0]->heuristic;

	for (int i = 0; i < frontier.size(); i++)
	{
		if (frontier[i]->heuristic < costHeuristic)
		{
			index = i;
			costHeuristic = frontier[i]->heuristic;
		}
	}

	return index;
}
