#include "AntPathEdge.h"
#include<vector>

class Ant final
{
public:
	AntSystem* System;
	std::vector<AntPathNode*> Visited{};
	std::vector<AntPathEdge*> History{};

	Ant(AntSystem* system);
	void Visit(AntPathNode* node);
	void Follow(AntPathEdge* edge);
	AntPathNode* GetLastNode();
	void Reset(AntPathNode* node);
	AntPathEdge* ChooseNextEdge();
	std::vector<AntPathEdge*> GetAllowedEdges();
	void EmitPheromones();
	std::string GetPathString();
	double GetLength();
	void Iterate();
};