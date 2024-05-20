#include "AntPathManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class AntSystem final
{
public:
	int CurrentIteration = 0; //������� ��������
	double MinLenth = INT_MAX;
	std::string MinLengthPath = "";
	double CurrentLength = 0;
	std::string CurrentPath = "";
	std::vector<AntPathEdge*> BestEdges;
	int EliteAntsCount;
	int StandartAntsCount;

	const bool FixedStartIndex = true; // ������������� ��������� ������� �������
	int IterationStartIndex = 0; // ��������� ������� ������� �� ��������
	const int DelayMs = 100; // �������� ����� ������ �������� � ��
	const double EvaporationRate = 0.1; // ����������� ��������� ���������
	const double MinPheromone = 0.01; // ����������� ���������� ��������
	const double MaxPheromone = 0.9; // ������������ ���������� ��������
	const double Alpha = 1; // ��� ��������
	const double Beta = 2; // ��� ������������� ����������
	const double Q = 1; // ���������� ���������� ��������
	const int Height = 900; // ������ ���� � ������������ Y ����
	const int Width = 1800; // ������ ���� � ������������ X ����
	const float nodeRadius = 10.0f; // 
	const std::string fontPath = "C:\\Windows\\Fonts\\arial.ttf";
	sf::RenderWindow* Window;
	sf::Font Font;
	AntPathManager* Manager;
	std::vector<AntPathNode*> Nodes{};
	std::vector<Ant*> Ants{};

	std::random_device RandomDevice;
	std::mt19937 RandomGenerator = AntSystem::GetRandomEngine();

	std::mt19937& GetRandomEngine();
	AntPathNode* GetStartingNode();
	void PerformIteration();
	void PerformDelay();
	void DrawIteration();
	void GenerateRandomNodes(int nodes);
	void ReadPreDescripedNodes(std::vector<std::pair<int, int>> positions);
	void ReadPreDescripedEdges(std::vector<std::vector<double>> lengths);
	void DrawNodes();
	void DrawEdges();
	void DrawCounter();
	AntSystem(int standartAnts, int eliteAnts, int nodes);
};