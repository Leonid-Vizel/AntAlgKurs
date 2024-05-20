#include "AntPathManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class AntSystem final
{
public:
	int CurrentIteration = 0; //Текущая итерация
	double MinLenth = INT_MAX;
	std::string MinLengthPath = "";
	double CurrentLength = 0;
	std::string CurrentPath = "";
	std::vector<AntPathEdge*> BestEdges;
	int EliteAntsCount;
	int StandartAntsCount;

	const bool FixedStartIndex = true; // Фиксированная стартовая позиция муравья
	int IterationStartIndex = 0; // Стартовая позиция муравья на итерации
	const int DelayMs = 100; // Задержка поска каждой итерации в мс
	const double EvaporationRate = 0.1; // Коэффициент испарения феромонов
	const double MinPheromone = 0.01; // Минимальное количество феромона
	const double MaxPheromone = 0.9; // Максимальное количество феромона
	const double Alpha = 1; // Вес феромона
	const double Beta = 2; // Вес эвристической информации
	const double Q = 1; // Выледяемое количество феромона
	const int Height = 900; // Высота окна и максимальный Y узла
	const int Width = 1800; // Ширина окна и максимальный X узла
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