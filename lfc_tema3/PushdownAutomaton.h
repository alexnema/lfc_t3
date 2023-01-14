#ifndef PUSHDOWN_AUTOMATON_H
#define PUSHDOWN_AUTOMATON_H

#include <stack>
#include <unordered_map>
#include <vector>
#include <string>

#define epsilon 'ε'

class PushdownAutomaton {
public:
    struct Transition {
        int from_state;
        char input_symbol;
        char stack_symbol;
        int to_state;
        std::string push_symbols;
    };

    PushdownAutomaton(std::vector<int> states, std::vector<char> input_symbols,
        std::vector<char> stack_symbols, int start_state,
        std::vector<int> accept_states, std::vector<Transition> transitions);
    //bool process_input(std::string input);

private:
    std::vector<int> states_;
    std::unordered_map<int, std::unordered_map<char, std::vector<Transition>>> transitions_;
    std::stack<char> stack_;
    int current_state_;
    std::vector<int> accept_states_;
};

#endif
