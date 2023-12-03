#include "AntSystem.h"
#include <vector>

Ant::Ant(AntSystem* system)
{
	System = system;
}

void Ant::Iterate() {
	Reset(System->Nodes[0]);
	while (Visited.size() != System->Nodes.size()) {
		const auto edge = ChooseNextEdge();
		Follow(edge);
	}
}

AntPathEdge* Ant::ChooseNextEdge() {
	const auto remaining = GetRemainingEdges();
	std::vector<double> desires;
	double sum = 0;
	for (const auto edge : remaining)
	{
		double amount = edge->CalculateDesire();
		sum += amount;
		desires.push_back(amount);
	}
	double randomize = std::rand() / RAND_MAX;
	for (int i = 0; i < desires.size(); i++)
	{
		const auto desire = desires[i];
		double current = desire / sum;
		randomize -= current;
		if (randomize < 0)
		{
			return remaining[i];
		}
	}
	return remaining[remaining.size()-1];
}

std::vector<AntPathEdge*> Ant::GetRemainingEdges() {
	auto last = GetLastNode();
	std::vector<AntPathEdge*> remainingNodes;
	for (const auto systemNode : System->Nodes)
	{
		bool flag = true;
		for (const auto visitedNode : Visited)
		{
			flag &= systemNode != visitedNode;
		}
		if (flag)
		{
			auto edge = System->Manager->GetEdge(last, systemNode);
			remainingNodes.push_back(edge);
		}
	}
	return remainingNodes;
}

AntPathNode* Ant::GetLastNode() {
	return Visited[Visited.size() - 1];
}

void Ant::Visit(AntPathNode* node) {
	if (Visited.size() != 0)
	{
		auto last = GetLastNode();
		auto edge = System->Manager->GetEdge(last, node);
		Follow(edge);
	}
	else
	{
		Visited.push_back(node);
	}
}

void Ant::Follow(AntPathEdge* edge) {
	History.push_back(edge);
	Visited.push_back(edge->End);
}

void Ant::Reset(AntPathNode* node) {
	Visited.clear();
	History.clear();
	Visit(node);
}

double Ant::GetLength() {
	double sum = 0;
	for (const auto edge : History) {
		sum += edge->Length;
	}
	return sum;
}

void Ant::EmitPheromones() {
	double addValue = System->Q / GetLength();
	for (const auto edge : History) {
		edge->Pheromone += addValue;
		if (edge->Pheromone > System->MaxPheromone)
		{
			edge->Pheromone = System->MaxPheromone;
		}
	}
}