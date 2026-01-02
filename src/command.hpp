#pragma once

#include "error.hpp"
#include "../path_handler/path_handler.hpp"

class Command
{
public:
    virtual ~Command() {}
    virtual DPErrorCode execute() = 0;
};

class CommandClose : public Command
{
public:
    CommandClose(Grid& grid) : grid(grid) {}
    ~CommandClose() override {}
    DPErrorCode execute() override
    {
        grid.set_running();
        return DPErrorCode::SUCCESS;
    }
private:
    Grid& grid;
};

class CommandChangeAlgorithmToAStar : public Command
{
public:
    CommandChangeAlgorithmToAStar(PathHandler& ph) : ph(ph){}
    ~CommandChangeAlgorithmToAStar() override {}

    DPErrorCode execute() override
    {
        ph.switch_algorithm(Algorithm::ASTAR);
        return DPErrorCode::SUCCESS;
    }
private:
    PathHandler& ph;
};
