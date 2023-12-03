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
	std::vector<AntPathEdge*> GetRemainingEdges();
	void EmitPheromones();
	double GetLength();
	void Iterate();
};