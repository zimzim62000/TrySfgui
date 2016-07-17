#include "entity_sfgui.h"

EntitySfgui::EntitySfgui() : Button::Button()
{
	Button::SetLabel("Euhh i am a label button");
}

void EntitySfgui::OnButtonClick()
{
	Button::SetLabel("New Label record you know !");
}
