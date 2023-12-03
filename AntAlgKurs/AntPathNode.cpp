#include "AntSystem.h"
#include<SFML/Graphics.hpp>

AntPathNode::AntPathNode(AntSystem* system, int index, int x, int y)
{
	System = system;
	Index = index;
	Position = new sf::Vector2f((float)x, (float)y);
}