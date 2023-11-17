#include "BFS.h"

BFS::BFS(Grid* g, Vector2D c, Vector2D p)
{
	maze = g;
	coin = c;
	initPos = p;
}

BFS::~BFS()
{
	delete maze;
}

std::vector<Vector2D> BFS::CalculatePath()
{
	bool reachedCoin = false;

	Node* initialNode = new Node(nullptr, initPos);
	frontier.push_back(initialNode);
	int reachedNode;

	while (!reachedCoin)
	{
		for (int i = 0; i < frontier.size(); i++)
		{
			if (maze->pix2cell(frontier[i]->pos) == coin)
			{
				reachedCoin = true;
				reachedNode = i;
				break;
			}
				
			//UP
			Node* nextNode = new Node(frontier[i], Vector2D(frontier[i]->pos.x, frontier[i]->pos.y-CELL_SIZE));
			if (validPathNode(nextNode))
				frontier.push_back(nextNode);

			//DOWN
			nextNode = new Node(frontier[i], Vector2D(frontier[i]->pos.x, frontier[i]->pos.y+ CELL_SIZE));
			if (validPathNode(nextNode))
				frontier.push_back(nextNode);

			//LEFT
			nextNode = new Node(frontier[i], Vector2D(frontier[i]->pos.x- CELL_SIZE, frontier[i]->pos.y));
			if (validPathNode(nextNode))
				frontier.push_back(nextNode);

			//RIGHT
			nextNode = new Node(frontier[i], Vector2D(frontier[i]->pos.x+CELL_SIZE, frontier[i]->pos.y));
			if (validPathNode(nextNode))
				frontier.push_back(nextNode);

			visited.push_back(frontier[i]);
			frontier.erase(frontier.begin()+i);

		}
	}

	std::vector<Vector2D> finalPath;

	bool reachedFirstNode = false;

	Node* actualNode = frontier[reachedNode];

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

bool BFS::validPathNode(Node* n)
{
	if (!isInVisited(n->pos) && maze->isValidCell(maze->pix2cell(n->pos)))
		return true;

	return false;
}

bool BFS::isInVisited(Vector2D v)
{
	for (int i = 0; i < visited.size(); i++)
	{
		if (visited[i]->pos == v)
			return true;
	}

	return false;
}
