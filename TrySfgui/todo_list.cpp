#include "todo_list.h"
#include "task.h"

TodoList::TodoList()
{

}

bool TodoList::AddTask(std::shared_ptr<Task> task)
{
	this->todoList.push_back(task);
	return true;
}

std::list<std::shared_ptr<Task>> TodoList::GetTodoList()
{
	return this->todoList;
}

void TodoList::DeleteTask()
{
	this->todoList.pop_front();
}

int TodoList::Size() const
{
	return this->todoList.size();
}

std::shared_ptr<Task> TodoList::GetTask() const
{
	return this->todoList.front();
}

void TodoList::CancelAllTask()
{
	this->todoList.clear();
}