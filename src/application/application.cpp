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
	input.bind('d', std::make_unique<CommandChangeAlgorithmToDijkstra>(ph));
	input.bind('r', std::make_unique<CommandNewGrid>(grid));

	return DPErrorCode::SUCCESS;
}

void Application::run()
{
	Input& input = Input::get_instance();
	print_menu();
	while (grid.is_running())
	{
		std::vector<glm::ivec2> targets = grid.get_targets();
		std::string alg = to_string(ph.get_current_algorithm());;
		std::cout << "Current Algorithm is: " << alg << "\n";
		int cost = ph.find_shortest_path(glm::ivec2(0, 0), targets);
		grid.print_map();
		std::cout << "PathCost is: " << cost << "\n";
		Command* command = Input::get_instance().handle_input();
		if (command)
			command->execute();
	}
}

void Application::print_menu()
{
	std::string menu =
		"Avaible path finding algorithms are : \n"
		"1) Dijkstra\n"
		"2) A*\n"
		"Yes we have wide algorithm options :)\n\n\n";

	std::cout << menu;
}
