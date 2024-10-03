#pragma once
#include <iostream>

class StateMachine
{
	public:
		enum State {
			MainMenu,
			Game,
			Options,
			Quit
		};

		StateMachine();
		void ChangeState(State newState);
		State getState() { return state; }
		bool isState(State stateToCompare) { return state == stateToCompare; }
	
	private:
		State state;
};

