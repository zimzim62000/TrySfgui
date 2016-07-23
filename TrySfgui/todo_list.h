#ifndef TODOLIST

#define TODOLIST

#pragma once

class Task;
#include <vector>
#include <list>
#include <memory>

class TodoList
{
public:
	TodoList();
	bool AddTask(std::shared_ptr<Task> task);
	std::shared_ptr<Task> GetTask() const;

	int Size() const;

	void DeleteTask();
	void TodoList::CancelAllTask();

	std::list<std::shared_ptr<Task>> GetTodoList();

private:
	std::list<std::shared_ptr<Task>> todoList;
};

#endif TODOLIST