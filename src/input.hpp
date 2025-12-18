#pragma once
#include <iostream>
#include <unordered_map>
#include "command.hpp"

namespace input {

class Input {
public:
    static Input &get_instance()
    { 
        static Input instance;
        return instance;
    }

    Input(Input const&)             = delete;
    void operator=(Input const&)    = delete;

    void bind(char key, std::unique_ptr<Command> command)
    {
        bindings[key] = std::move(command);
    }
    
    Command* handle_input()
    {
        char key;
        std::cout << "Your turn! ";
        std::cin >> key;

        auto it = bindings.find(key);
        if (it != bindings.end())
            return it->second.get();
        return nullptr;
    }

private:
    std::unordered_map<char, std::unique_ptr<Command>> bindings;
    Input() {}
};
}