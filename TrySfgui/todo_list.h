#ifndef TODOLIST

#define TODOLIST

#pragma once

class Task;
#include <vector>
#include <queue>
#include <memory>

class TodoList
{
public:
	TodoList();
	bool addTask(std::shared_ptr<Task> task);
	std::queue<std::shared_ptr<Task>> getTodoList();
	void deleteFirstTask();
	int countTodoList() const;
	std::shared_ptr<Task> getFisrtTask() const;

private:
	std::queue<std::shared_ptr<Task>> todoList;
};

#endif TODOLIST