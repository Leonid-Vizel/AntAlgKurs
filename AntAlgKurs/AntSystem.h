#include "AntPathManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class AntSystem final
{
public:
	int CurrentIteration = 0; //������� ��������
	double MinLenth = 9999999999;
	std::string MinLengthPath = "";
	double CurrentLength = 0;
	std::string CurrentPath = "";

	const int MaxIterations = 1000; // ������������ ���������� ��������
	const int DelayMs = 100; // �������� ����� ������ �������� � ��
	const double EvaporationRate = 0.05; // ����������� ��������� ���������
	const double MinPheromone = 0.01; // ����������� ���������� ��������
	const double MaxPheromone = 0.9; // ������������ ���������� ��������
	const double Alpha = 2; // ��� ��������
	const double Beta = 1; // ��� ������������� ����������
	const double Q = 105.0; // ���������� ���������� ��������
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
	void PerformIteration();
	void PerformDelay();
	void DrawIteration();
	void GenerateRandomNodes(int nodes);
	void ReadPreDescripedNodes(std::vector<std::pair<int, int>> positions);
	void DrawNodes();
	void DrawEdges();
	void DrawCounter();
	AntSystem(int ants = 10, int nodes = 10);
};