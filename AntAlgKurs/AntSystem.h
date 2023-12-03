#include "AntPathManager.h"
#include <SFML/Graphics.hpp>
#include <vector>

class AntSystem final
{
public:
	int CurrentIteration = 0; //Текущая итерация
	double MinLenth = 9999999999;
	const int MaxIterations = 1000; // Максимальное количество итераций
	const int DelayMs = 100; // Задержка поска каждой итерации в мс
	const double EvaporationRate = 0.1; // Коэффициент испарения феромонов
	const double MinPheromone = 0.05; // Минимальное количество феромона
	const double MaxPheromone = 0.9; // Максимальное количество феромона
	const double Alpha = 2; // Вес феромона
	const double Beta = 2; // Вес эвристической информации
	const double Q = 40.0; // Вес эвристической информации
	const int Height = 900; // Высота окна и максимальный Y узла
	const int Width = 1800; // Ширина окна и максимальный X узла
	const float nodeRadius = 10.0f; // 
	const std::string fontPath = "C:\\Windows\\Fonts\\arial.ttf";
	sf::RenderWindow* Window;
	sf::Font Font;
	AntPathManager* Manager;
	std::vector<AntPathNode*> Nodes{};
	std::vector<Ant*> Ants{};

	void PerformIteration();
	void PerformDelay();
	void DrawIteration();
	void DrawNodes();
	void DrawEdges();
	void DrawCounter();
	AntSystem(int ants = 10, int nodes = 10);
};