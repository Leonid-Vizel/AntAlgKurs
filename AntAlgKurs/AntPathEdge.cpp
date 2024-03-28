#include "AntSystem.h"
#include <cmath>

AntPathEdge::AntPathEdge(AntSystem* system, AntPathNode* start, AntPathNode* end)
{
	System = system;
	Start = start;
	End = end;
	Length = sqrt(pow((end->Position->x - start->Position->x), 2) + pow((end->Position->y - start->Position->y), 2));
	Pheromone = system->MaxPheromone;
}

void AntPathEdge::EvaporatePheromone() {
	Pheromone -= Pheromone * System->EvaporationRate;
	if (Pheromone < System->MinPheromone)
	{
		Pheromone = System->MinPheromone;
	}
}

double AntPathEdge::CalculateDesire() {
	return std::pow(Pheromone, System->Alpha) * std::pow(Length, System->Beta);
}