#include<vector>
#include<SFML/Graphics.hpp>
class AntSystem;
class AntPathEdge;

class AntPathNode final
{
public:
	int Index;
	AntSystem* System;
	sf::Vector2f* Position;
	std::vector<AntPathEdge*> Edges;
	AntPathNode(AntSystem* system, int index, int x, int y);
};