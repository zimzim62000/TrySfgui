#include "engine.h"

int main()
{
	//reset random
	srand(time(NULL));

	std::shared_ptr<Engine> engine = std::make_shared<Engine>();

	engine->LoadingDefault();

	engine->Run();

	return 0;
}
