#include "AntSystem.h"
#include <SFML/Graphics.hpp>

using namespace std;

AntSystem System(8, 2, 10);

int main() {
	while (System.Window->isOpen())
	{
		sf::Event event;
		while (System.Window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				System.Window->close();
			}
		}
		System.PerformIteration();
		System.DrawIteration();
		System.PerformDelay();
		System.Window->display();
		System.Window->clear();
	}
	return 0;
}