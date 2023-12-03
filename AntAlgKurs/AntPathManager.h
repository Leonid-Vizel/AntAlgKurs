#include "Ant.h"
#include <map>

class AntPathManager
{
public:
	AntSystem* System;
	std::map<std::pair<int, int>, AntPathEdge*> Edges{};
	AntPathManager(AntSystem* system);
	std::pair<int, int> GetKey(AntPathNode* node1, AntPathNode* node2);
	AntPathEdge* GetOrRegisterEdge(AntPathNode* node1, AntPathNode* node2);
	AntPathEdge* GetEdge(AntPathNode* node1, AntPathNode* node2);
	void EvaporatePheromones();
	void DrawEdges();
};