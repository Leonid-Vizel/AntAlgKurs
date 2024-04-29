#include "AntPathManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class AntSystem final
{
public:
	int CurrentIteration = 0; //Текущая итерация
	double MinLenth = 9999999999;
	std::string MinLengthPath = "";
	double CurrentLength = 0;
	std::string CurrentPath = "";

	const int MaxIterations = 1000; // Максимальное количество итераций
	const int DelayMs = 100; // Задержка поска каждой итерации в мс
	const double EvaporationRate = 0.05; // Коэффициент испарения феромонов
	const double MinPheromone = 0.01; // Минимальное количество феромона
	const double MaxPheromone = 0.9; // Максимальное количество феромона
	const double Alpha = 2; // Вес феромона
	const double Beta = 1; // Вес эвристической информации
	const double Q = 105.0; // Выледяемое количество феромона
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