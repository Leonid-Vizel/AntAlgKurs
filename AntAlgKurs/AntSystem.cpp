#include "AntSystem.h"
#include <random>
#include <thread>
#include <iostream>

AntSystem::AntSystem(int ants, int nodes)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	Font.loadFromFile(fontPath);
	Window = new sf::RenderWindow(sf::VideoMode(Width, Height), "Ant optimisation");

	for (int i = 0; i < ants; i++)
	{
		Ant* ant = new Ant(this);
		Ants.push_back(ant);
	}

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uniX(0, Width);
	std::uniform_int_distribution<int> uniY(0, Height);
	for (int i = 0; i < nodes; i++)
	{
		AntPathNode* node = new AntPathNode(this, i, uniX(rng), uniY(rng));
		Nodes.push_back(node);
	}
	Manager = new AntPathManager(this);

	for (int i = 0; i < nodes; i++)
	{
		auto node1 = Nodes[i];
		for (int j = 0; j < nodes; j++)
		{
			if (i == j)
			{
				continue;
			}
			auto node2 = Nodes[j];
			auto edge = Manager->GetOrRegisterEdge(node1, node2);
			node1->Edges.push_back(edge);
		}
	}
}

void AntSystem::PerformIteration()
{
	CurrentIteration++;
	for (const auto ant : Ants) {
		ant->Iterate();
		const auto length = ant->GetLength();
		if (MinLenth > length)
		{
			MinLengthPath = 
			
			MinLenth = length;
		}
	}
	Manager->EvaporatePheromones();
	for (const auto ant : Ants) {
		ant->EmitPheromones();
	}
};

void AntSystem::PerformDelay()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(DelayMs));
};

void AntSystem::DrawIteration() {
	Manager->DrawEdges();
	DrawNodes();
	DrawCounter();
};

void AntSystem::DrawNodes() {

	for (const auto& node : Nodes) {
		sf::CircleShape circle(nodeRadius);
		circle.setFillColor(sf::Color::Blue);
		circle.setPosition(*node->Position);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		Window->draw(circle);
	}
};

void AntSystem::DrawCounter() {
	sf::Text counter;
	counter.setString("I: " + std::to_string(CurrentIteration) + " M: (" + std::to_string(MinLenth) + ")");
	counter.setCharacterSize(15);
	counter.setFillColor(sf::Color::White);
	counter.setOutlineColor(sf::Color::White);
	counter.setFont(Font);
	Window->draw(counter);
};