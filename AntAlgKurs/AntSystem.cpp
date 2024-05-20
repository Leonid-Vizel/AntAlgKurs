#include "AntSystem.h"
#include <random>
#include <thread>
#include <vector>
#include <iostream>

AntSystem::AntSystem(int standartAnts = 8, int eliteAnts = 2, int nodes = 10)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	Font.loadFromFile(fontPath);
	Window = new sf::RenderWindow(sf::VideoMode(Width, Height), "Ant optimisation");
	EliteAntsCount = eliteAnts;
	StandartAntsCount = standartAnts;

	for (int i = 0; i < standartAnts; i++)
	{
		Ant* ant = new Ant(this, false);
		Ants.push_back(ant);
	}
	for (int i = 0; i < eliteAnts; i++)
	{
		Ant* ant = new Ant(this, true);
		Ants.push_back(ant);
	}

	GenerateRandomNodes(nodes);

	/*std::vector<std::pair<int, int>> posVec = {
		std::make_pair(50, 50),
		std::make_pair(100, 50),
		std::make_pair(150, 50),
		std::make_pair(1750, 50),
		std::make_pair(1750, 100),
		std::make_pair(1750, 150),
		std::make_pair(1750, 800),
		std::make_pair(1750, 850),
		std::make_pair(100, 850),
		std::make_pair(50, 850) };
	ReadPreDescripedNodes(posVec);*/

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

	std::vector<std::vector<double>> edges =
	{
		{0, 10, 12, 11, 14},
		{10, 0, 13, 15, 8},
		{12, 13, 0, 9, 14},
		{11, 15, 9, 0, 16},
		{14, 8, 14, 16, 0},
	};
	ReadPreDescripedEdges(edges);
}

std::mt19937& AntSystem::GetRandomEngine() {
	static std::mt19937 gen(RandomDevice());
	return gen;
}

void AntSystem::GenerateRandomNodes(int nodes) {
	std::uniform_int_distribution<int> uniX(0, Width);
	std::uniform_int_distribution<int> uniY(0, Height);
	for (int i = 0; i < nodes; i++)
	{
		AntPathNode* node = new AntPathNode(this, i, uniX(RandomGenerator), uniY(RandomGenerator));
		Nodes.push_back(node);
	}
}

void AntSystem::ReadPreDescripedNodes(std::vector<std::pair<int, int>> positions) {
	for (int i = 0; i < positions.size(); i++)
	{
		const auto position = positions[i];
		AntPathNode* node = new AntPathNode(this, i, position.first, position.second);
		Nodes.push_back(node);
	}
}

void AntSystem::ReadPreDescripedEdges(std::vector<std::vector<double>> lengths) {
	for (auto i = 0; i < lengths.size(); i++) {
		auto row = lengths[i];
		auto node1 = Nodes[i];
		for (auto j = 0; j < row.size(); j++) {
			if (i == j)
			{
				continue;
			}
			auto node2 = Nodes[j];
			Manager->GetEdge(node1, node2)->Length = row[j];
		}
	}
}

AntPathNode* AntSystem::GetStartingNode() {
	return Nodes[IterationStartIndex];
};

void AntSystem::PerformIteration()
{
	if (!FixedStartIndex)
	{
		std::uniform_int_distribution<int> dis(0, Nodes.size() - 1);
		IterationStartIndex = dis(RandomGenerator);
	}
	CurrentIteration++;
	for (const auto ant : Ants) {
		ant->Iterate();
		CurrentLength = ant->GetLength();
		CurrentPath = ant->GetPathString();
		if (MinLenth > CurrentLength)
		{
			MinLenth = CurrentLength;
			MinLengthPath = CurrentPath;
			if (EliteAntsCount > 0)
			{
				BestEdges.swap(ant->History);
			}
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

		sf::Text text(std::to_string(node->Index), Font, nodeRadius * 2);
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		text.setPosition(*node->Position);
		Window->draw(text);
	}
};

void AntSystem::DrawCounter() {
	sf::Text counter1;
	counter1.setString("I: " + std::to_string(CurrentIteration) + " M: (" + std::to_string(MinLenth) + " (" + MinLengthPath + ")" + ")");
	counter1.setCharacterSize(15);
	counter1.setFillColor(sf::Color::White);
	counter1.setOutlineColor(sf::Color::White);
	counter1.setFont(Font);
	Window->draw(counter1);

	if (EliteAntsCount == 0)
	{
		sf::Text counter2;
		counter2.setString("CURR: (" + std::to_string(CurrentLength) + " (" + CurrentPath + ")" + ")");
		counter2.setCharacterSize(15);
		counter2.setFillColor(sf::Color::White);
		counter2.setOutlineColor(sf::Color::White);
		counter2.setFont(Font);
		counter2.setPosition(0, 20);
		Window->draw(counter2);
	}
};