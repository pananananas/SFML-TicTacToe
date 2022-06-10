#pragma once
#include <memory>
#include <stack>
#include "State.hpp"

namespace Game {

typedef std::unique_ptr<State> StateRef; // Top state is an actual one, rest are the state history

class StateMachine {
    
    std::stack<StateRef> _states;
    StateRef _newState;
    bool     _isReplacing;
    bool     _isRemoving;
    bool     _isAdding;
    
public:
    
    StateMachine()  {};
    ~StateMachine() {};
    
    void AddState(StateRef NewState, bool isReplacing = true);
    void RemoveState();
    void ProcessStateChanges();
    
    StateRef &GetActiveState();
};
}
