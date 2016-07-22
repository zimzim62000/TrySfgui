#ifndef TASK

#define TASK

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
/*
namespace sf {
	class Vector2f;
};
*/

class Task
{
public:
	Task();
	Task(const int idTask, const std::string name, const sf::Vector2f target);
	Task(const int idTask, const std::string name);
	int idTask;
	std::string name;
	sf::Vector2f target;
	bool done;
};

#endif TASK