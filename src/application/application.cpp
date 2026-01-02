#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "application.hpp"

Application::Application() : grid(), ph(grid.get_map())
{
	init();
}

DPErrorCode Application::init()
{
	Input& input = Input::get_instance();
	input.bind('q', std::make_unique<CommandClose>(grid));
	input.bind('a', std::make_unique<CommandChangeAlgorithmToAStar>(ph));

	return DPErrorCode::SUCCESS;
}

void Application::run()
{
	Input& input = Input::get_instance();
	std::vector<glm::ivec2> targets = grid.get_targets();

	while (grid.is_running())
	{
		int cost = ph.find_shortest_path(glm::ivec2(0, 0), targets);
		grid.run();
		std::cout << "PathCost is: " << cost << "\n";
		Command* command = Input::get_instance().handle_input();
		if (command)
			command->execute();
	}
}
