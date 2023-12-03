#include "AntPathManager.h"
#include <SFML/Graphics.hpp>
#include <vector>

class AntSystem final
{
public:
	int CurrentIteration = 0; //������� ��������
	double MinLenth = 9999999999;
	const int MaxIterations = 1000; // ������������ ���������� ��������
	const int DelayMs = 100; // �������� ����� ������ �������� � ��
	const double EvaporationRate = 0.1; // ����������� ��������� ���������
	const double MinPheromone = 0.05; // ����������� ���������� ��������
	const double MaxPheromone = 0.9; // ������������ ���������� ��������
	const double Alpha = 2; // ��� ��������
	const double Beta = 2; // ��� ������������� ����������
	const double Q = 40.0; // ��� ������������� ����������
	const int Height = 900; // ������ ���� � ������������ Y ����
	const int Width = 1800; // ������ ���� � ������������ X ����
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