#pragma once

#include "error.hpp"
#include "input.hpp"
#include "grid.hpp"
#include "path_handler/path_handler.hpp"

class Application
{
public:
	Application();
	~Application() = default;

	DPErrorCode init();
	void run();
	void print_menu();

private:
	Grid grid;
	PathHandler ph;
};