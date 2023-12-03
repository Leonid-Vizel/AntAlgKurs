#include "AntSystem.h"
#include <cmath>
#include <utility>

AntPathManager::AntPathManager(AntSystem* system) {
	System = system;
}

std::pair<int, int> AntPathManager::GetKey(AntPathNode* node1, AntPathNode* node2) {
	return std::make_pair(node1->Index, node2->Index);
}

AntPathEdge* AntPathManager::GetOrRegisterEdge(AntPathNode* node1, AntPathNode* node2) {
	const auto key = GetKey(node1, node2);
	if (!Edges.count(key)) {
		const auto edge = new AntPathEdge(System, node1, node2);
		Edges[key] = edge;
		return edge;
	}
	return Edges[key];
}

AntPathEdge* AntPathManager::GetEdge(AntPathNode* node1, AntPathNode* node2) {
	auto key = GetKey(node1, node2);
	if (!Edges.count(key)) {
		return NULL;
	}
	return Edges[key];
}

void AntPathManager::EvaporatePheromones() {
	for (const auto edgePair : Edges) {
		const auto edge = edgePair.second;
		edge->EvaporatePheromone();
	}
}

void AntPathManager::DrawEdges() {
	for (const auto& edgePair : Edges) {
		const auto edge = edgePair.second;
		sf::Color lineColor(0, 255, 0, (int)(edge->Pheromone / System->MaxPheromone * 255));
		sf::Vertex line[] = {
			sf::Vertex(*edge->Start->Position, lineColor),
			sf::Vertex(*edge->End->Position, lineColor)
		};
		System->Window->draw(line, 2, sf::LineStrip);
	}
};