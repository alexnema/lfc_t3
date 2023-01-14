#include "PushdownAutomaton.h"
#include <iostream>
PushdownAutomaton::PushdownAutomaton(std::vector<int> states, std::vector<char> input_symbols,
    std::vector<char> stack_symbols, int start_state,
    std::vector<int> accept_states, std::vector<Transition> transitions)
    : states_(states),
    current_state_(start_state),
    accept_states_(accept_states) {
    for (const auto& transition : transitions) {
        transitions_[transition.from_state][transition.input_symbol].push_back(transition);
    }
}

/*bool PushdownAutomaton::process_input(std::string input) {
    for (const auto& c : input) {
        bool transition_applied = false;
        for (const auto& transition : transitions_[current_state_][c]) {
            std::cout << transition.stack_symbol << " ";
            if (transition.stack_symbol == stack_.top() || transition.stack_symbol == epsilon) {
                if(!stack_.empty())
                    stack_.pop();
                current_state_ = transition.to_state;
                for (auto it = transition.push_symbols.rbegin(); it != transition.push_symbols.rend(); ++it) {
                    stack_.push(*it);
                }
                transition_applied = true;
            }
        }
        if (!transition_applied) {
            return false;
        }
    }
    return std::find(accept_states_.begin(), accept_states_.end(), current_state_) != accept_states_.end() || stack_.empty();
}
*/