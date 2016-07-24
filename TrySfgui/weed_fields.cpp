#include "weed_fields.h"
#include "entity_tile.h"
#include "game_interface.h"
#include "map_game.h"
#include "map_tile.h"
#include "task.h"
#include "todo_list.h"
#include "game_speed.h"


WeedFields::WeedFields(const int stockMax, const int stockCounter, sf::Color color, std::shared_ptr<EntityTile> entityTile) : EntityFactory(stockMax, stockCounter, color, entityTile)
{
	this->todoList->AddTask(std::make_shared<Task>(0, 0, "Harvest Weed :)"));
}
