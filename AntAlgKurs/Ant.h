#include "AntPathEdge.h"
#include<vector>

class Ant final
{
public:
	AntSystem* System;
	bool Elite;
	std::vector<AntPathNode*> Visited{};
	std::vector<AntPathEdge*> History{};

	Ant(AntSystem* system, bool elite);
	void Visit(AntPathNode* node);
	void Follow(AntPathEdge* edge);
	AntPathNode* GetLastNode();
	AntPathEdge* GetLastEdge();
	void Reset(AntPathNode* node);
	AntPathEdge* ChooseNextEdge();
	AntPathEdge* ChooseNextEdgeElite();
	std::vector<AntPathEdge*> GetAllowedEdges();
	void EmitPheromones();
	std::string GetPathString();
	double GetLength();
	void Iterate();
};