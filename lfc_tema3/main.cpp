#include <iostream>
#include <vector>
#include <string>
#include "Grammar.h"
#include "PushdownAutomaton.h"

#define epsilon 'ε'

int main()
{
	/*//Grammar g({ 'S','A' }, { 'a','b' }, 'S', { {"S","abS"},{"S","aSAb"},{"S","aA"}, {"A","aAb"},{"A","a"}});
	Grammar g({ 'S','A','B','C','D' }, { 'a','b' }, { 'S' }, { { "S","A" }, { "S","B" }, { "A","aB" }, { "A","bS" }, { "A","b" }, { "B","BD" }, { "B","Ba" }, { "C","AS" }, { "C","b" }, { "D","bD" }, { "D","b" } });
	//Grammar g({ 'S','L','T' }, { 'a','b','+','*','[',']' }, 'S', { {"S","T+S"},{"S","T"},{"T","L*T"},{"T","L"},{"L","[S]"},{"L","a"},{"L","b"} });
	if (g.isContextFree())
	{
		std::cout << "DA" << "\n";
	}
	else
	{
		std::cout << "NU" <<"\n";
	}
	std::cout << g;
	std::cout << "\n";
	//g.removeUnitProductions();
	//g.reduceCFG();*/

	std::vector<PushdownAutomaton::Transition> map;
	PushdownAutomaton::Transition trans;

	trans.from_state = 0;
	trans.to_state = 1;
	trans.input_symbol = epsilon;
	trans.push_symbols = "$";
	trans.stack_symbol = epsilon;

	map.emplace_back(trans);

	trans.from_state = 1;
	trans.to_state = 1;
	trans.input_symbol = 'a';
	trans.push_symbols = "A";
	trans.stack_symbol = epsilon;

	map.emplace_back(trans);

	trans.from_state = 1;
	trans.to_state = 2;
	trans.input_symbol = epsilon;
	trans.push_symbols = epsilon;
	trans.stack_symbol = epsilon;
	map.emplace_back(trans);

	trans.from_state = 2;
	trans.to_state = 2;
	trans.input_symbol = 'b';
	trans.push_symbols = epsilon;
	trans.stack_symbol = 'A';
	map.emplace_back(trans);

	trans.from_state = 2;
	trans.to_state = 3;
	trans.input_symbol = epsilon;
	trans.push_symbols = epsilon;
	trans.stack_symbol = '$';
	map.emplace_back(trans);


	PushdownAutomaton pda({ 0,1,2,3 }, { 'a', 'b',epsilon }, { 'A', '$', epsilon}, 0, {3}, map);

	//std::cout << pda.process_input("aaabbb");


	return 0;
}