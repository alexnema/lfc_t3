#include <iostream>
#include <vector>
#include <string>
#include "Grammar.h"
#include "PushdownAutomaton.h"


int main()
{
	//Grammar grammar({ 'S','A' }, { 'a','b' }, 'S', { {"S","abS"},{"S","aSAb"},{"S","aA"}, {"A","aAb"},{"A","a"}});
	Grammar grammar({ 'S','A','B','C','D' }, { 'a','b' }, { 'S' }, { { "S","A" }, { "S","B" }, { "A","aB" }, { "A","bS" }, { "A","b" }, { "B","BD" }, { "B","Ba" }, { "C","AS" }, { "C","b" }, { "D","bD" }, { "D","b" } });
	//Grammar grammar({ 'S','L','T' }, { 'a','b','+','*','[',']' }, 'S', { {"S","T+S"},{"S","T"},{"T","L*T"},{"T","L"},{"L","[S]"},{"L","a"},{"L","b"} });
	//Grammar grammar({ 'S','A','B','C','E' }, { 'a','c','e' }, { 'S' }, { {"S","AC"},{"S","B"},{"A","a"},{"C","c"},{"C","BC"},{"E","aE"},{"E","e"} });
	std::map<std::tuple<char, char, char>, std::vector<std::pair<char, std::string>>> tranzitii;
	tranzitii[{'0', 'a', 'Z'}] = { {'1', "AZ"}};
	tranzitii[{'1', 'a', 'A'}] = { {'2', "AA"} };
	tranzitii[{'2', 'a', 'A'}] = { {'2', "AA"} };

	PushDownAutomaton pd("0,1,2", "a,b", "Z0,A", tranzitii, '0');
	int options = 0;
	do
	{
		std::cout << "1) afisarea gramaticii G \n  2)generarea unui cuvânt în gramatica.\n 3)afisarea rezultatului gramaticii simplificate.\n 4)afisarea gramaticii in FNG.\n 5)generarea unui cuvânt în G si verificarea daca e acceptat de automat.\n 6)verificarea daca un cuvânt citit de la tastatur  e acceptat de automat.\n0) EXIT\n";
		std::cout << "Alegeti optiunea: ";
		std::cin >> options;
		std::string word;
		switch (options)
		{
		case 1:
			std::cout << grammar << '\n';
			std::cout << '\n';
			break;
		case 2:
			std::cout << "Cuvantul generat este: ";
			std::cout << grammar.GenerateWord() << '\n';
			std::cout << '\n';
			break;
		case 3:
			grammar.simplifyCFG();
			std::cout << grammar << '\n';
			std::cout << '\n';
			break;

		case 4:
			break;
		case 5:
			break;
		case 6:
			std::cout << "Cititi un cuvant: ";
			std::cin >> word;
			if (!pd.CheckWord(word))
				std::cout << "Cuvantul este acceptat de automatul obtinut.\n";
			else
				std::cout << "Cuvantul NU este acceptat de automatul obtinut.\n";
			std::cout << '\n';
			break;
		case 0:
			return 0;
		default:
			break;
		}
	} while (options != 0);
	

	return 0;
}