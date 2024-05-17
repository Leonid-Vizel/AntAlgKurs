#include "AntSystem.h"
#include <vector>
#include <random>
#include <sstream>
#include <string>

Ant::Ant(AntSystem* system, bool elite = false)
{
	System = system;
	Elite = elite;
}

void Ant::Iterate() {
	Reset(System->GetStartingNode());
	while (Visited.size() != System->Nodes.size() + 1) {
		const auto edge = ChooseNextEdge();
		Follow(edge);
	}
}

AntPathEdge* Ant::ChooseNextEdge() {
	if (Elite && System->BestEdges.size() > 0)
	{
		return ChooseNextEdgeElite();
	}
	const auto remaining = GetAllowedEdges();
	std::vector<double> desires;
	double sum = 0;
	for (const auto edge : remaining)
	{
		double amount = edge->CalculateDesire();
		sum += amount;
		desires.push_back(amount);
	}

	std::uniform_real_distribution<double> dis(0, 1);
	double randomize = dis(System->RandomGenerator);
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
	return remaining[remaining.size() - 1];
}

AntPathEdge* Ant::ChooseNextEdgeElite() {
	auto lastEdge = GetLastEdge();
	bool found = (lastEdge == NULL);
	for (const auto bestEdge : System->BestEdges) {
		if (found)
		{
			return bestEdge;
		}
		found = (lastEdge == bestEdge);
	}
}

std::vector<AntPathEdge*> Ant::GetAllowedEdges() {
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
	if (remainingNodes.size() == 0)
	{
		auto edge = System->Manager->GetEdge(last, System->GetStartingNode());
		remainingNodes.push_back(edge);
		return remainingNodes;
	}
	return remainingNodes;
}

AntPathNode* Ant::GetLastNode() {
	return Visited[Visited.size() - 1];
}

AntPathEdge* Ant::GetLastEdge() {
	if (History.size() == 0)
	{
		return NULL;
	}
	return History[History.size() - 1];
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

std::string Ant::GetPathString() {
	std::string separator = "-";
	std::ostringstream result;

	for (const auto node : Visited) {
		result << node->Index << separator;
	}
	return result.str();
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