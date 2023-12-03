#include "AntPathNode.h"

class AntPathEdge final
{
public:
	AntSystem* System;
	AntPathNode* Start;
	AntPathNode* End;
	double Length;
	double Pheromone;
	AntPathEdge(AntSystem* system, AntPathNode* start, AntPathNode* end);
	void EvaporatePheromone();
	double CalculateDesire();
};