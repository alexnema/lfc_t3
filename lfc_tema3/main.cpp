#include <iostream>
#include <vector>
#include <string>
#include "Grammar.h"
int main()
{
	//Grammar g({ 'S','A' }, { 'a','b' }, 'S', { {"S","abS"},{"S","aSAb"},{"S","aA"}, {"A","aAb"},{"A","a"}});
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
	//g.reduceCFG();
	std::cout << g;
	

}