#include "StateMachine.h"

StateMachine::StateMachine()
{
	state = State::MainMenu;
}

void StateMachine::ChangeState(State newState)
{
	state = newState;
	std::cout << "State changed to " << state << std::endl;
}
