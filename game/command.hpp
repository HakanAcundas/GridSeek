#pragma once
#include "error.hpp"
#include "entity.hpp"

class Command {
public:
    virtual ~Command() {}
    virtual DPErrorCode execute(Entity& e) = 0;
};

class MoveCommand : public Command {
public:
    MoveCommand(glm::vec2 direction) : direction(direction) {}
    ~MoveCommand() override {}
    DPErrorCode execute(Entity& e) override {
        e.move(direction);
        return DPErrorCode::SUCCESS;
    }

private:
    glm::vec2 direction;
};

class AttackCommand : public Command {
public:
    ~AttackCommand() override {}
    DPErrorCode execute(Entity& e) override {
        Player& p = dynamic_cast<Player&>(e);
        p.attack();
        return DPErrorCode::SUCCESS;
    }
};
