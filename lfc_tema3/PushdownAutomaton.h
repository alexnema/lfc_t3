#pragma once
#include <string>
#include <stack>
#include <map>
#include <iostream>
#include <vector>

class PushDownAutomaton
{
	std::string m_stari;
	std::string m_alfabrt;
	std::string m_stackAlfabet;
	std::map<std::tuple<char, char, char>, std::vector<std::pair<char, std::string>>> m_tranzactii;
	char m_stareaInitiala;
	char m_primulStackChar;
public:
	PushDownAutomaton();
	bool CheckWord(std::string word);
	void checkword2(int index, std::string word, std::stack<char> m_stack, bool& ok);
	bool IsDeterminist();

	void SetStari(const std::string& stari);
	void SetAlfabet(const std::string& alfabet);
	void SetStackAlfabet(const std::string& stack_alfabet);
	void SetStareInitiala(const char& stare_initiala);
	void SetPrimulStachChar(const char& primul_stack_char);
	std::string GetStari() const;
	std::string GetAlfabet() const;
	std::string GetStackAlfabet() const;
	char GetStareInitiala() const;
	char GetPrimulStackChar() const;
	std::map<std::tuple<char, char, char>, std::vector<std::pair<char, std::string>>>GetTranzitii();
	void AddTranzitii(const std::tuple<char, char, char>& trans, const std::pair<char, std::string>& result);
	friend std::ostream& operator<<(std::ofstream& out, PushDownAutomaton pd);
	~PushDownAutomaton();

};