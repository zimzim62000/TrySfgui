#include "todo_list.h"
#include "task.h"

TodoList::TodoList()
{

}

bool TodoList::addTask(std::shared_ptr<Task> task)
{
	this->todoList.push(task);
	return true;
}

std::queue<std::shared_ptr<Task>> TodoList::getTodoList()
{
	return this->todoList;
}

void TodoList::deleteFirstTask()
{
	this->todoList.pop();
}

int TodoList::countTodoList() const
{
	return this->todoList.size();
}

std::shared_ptr<Task> TodoList::getFisrtTask() const
{
	return this->todoList.front();
}