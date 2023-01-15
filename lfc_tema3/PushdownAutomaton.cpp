#include "PushDownAutomaton.h"

bool PushDownAutomaton::CheckWord(std::string word)
{
	std::stack<char> m_stack;
	m_stack.push(m_stareaInitiala);
	bool ok = false;
	checkword2(0, word, m_stack, ok);
	if (ok == false)
		return false;
	else
		return true;
}


void PushDownAutomaton::checkword2(int index, std::string word, std::stack<char> m_stack, bool& ok)
{
	if (m_stack.empty() && index == word.size())
	{
		ok = true;
		return;
	}
	if (index >= word.size())
		return;
	std::vector<std::pair<char, std::string>> vector_tranz = m_tranzactii[{'0', word[index], m_stack.top()}];
	m_stack.pop();
	for (auto it = vector_tranz.begin(); it != vector_tranz.end(); it++)
	{
		int n = it->second.size();
		for (int i = 0; i < n; i++)
		{
			if (it->second[i] == '-')
				continue;
			m_stack.push(it->second[i]);
		}
		checkword2(index + 1, word, m_stack, ok);
		if (ok == true)
			return;
		for (int i = n - 1; i >= 0; i--)
		{
			if (it->second[i] == '-')
				continue;
			m_stack.pop();
		}
	}
}

bool PushDownAutomaton::IsDeterminist()
{
	for (auto it = m_tranzactii.begin(); it != m_tranzactii.end(); it++)
	{
		if (it->second.size() > 1)
			return false;
	}
	return true;
}
std::string PushDownAutomaton::GetStari() const
{
	return m_stari;
}
std::string PushDownAutomaton::GetAlfabet() const
{
	return m_alfabrt;
}
std::string PushDownAutomaton::GetStackAlfabet() const
{
	return m_stackAlfabet;
}
std::map<std::tuple<char, char, char>, std::vector<std::pair<char, std::string>>>PushDownAutomaton::GetTranzitii()
{
	return m_tranzactii;
}
char PushDownAutomaton::GetStareInitiala() const
{
	return m_stareaInitiala;
}
char PushDownAutomaton::GetPrimulStackChar() const
{
	return m_primulStackChar;
}

void PushDownAutomaton::SetStari(const std::string& stari)
{
	this->m_stari = stari;
}

void PushDownAutomaton::SetAlfabet(const std::string& alfabet)
{
	this->m_alfabrt = alfabet;
}

void PushDownAutomaton::SetStackAlfabet(const std::string& stack_alfabet)
{
	this->m_stackAlfabet = stack_alfabet;
}

void PushDownAutomaton::SetStareInitiala(const char& stare_initiala)
{
	this->m_stareaInitiala = stare_initiala;
}

void PushDownAutomaton::SetPrimulStachChar(const char& primul_stack_char)
{
	this->m_primulStackChar = primul_stack_char;
}


void PushDownAutomaton::AddTranzitii(const std::tuple<char, char, char>& trans, const std::pair<char, std::string>& result)
{
	std::vector<std::pair<char, std::string>>curentTrans = m_tranzactii[trans];
	curentTrans.push_back(result);
	m_tranzactii[trans] = curentTrans;
}

PushDownAutomaton::~PushDownAutomaton()
{
	//gol
}

std::ostream& operator<<(std::ostream& out, PushDownAutomaton pd)
{
	out << "M=({";
	out << pd.GetStari();
	out << "},{";
	out << pd.GetAlfabet();
	out << "},{";
	out << pd.GetStackAlfabet();
	out << "}, " << (char)235 << ", " << pd.GetStareInitiala() << "," << pd.GetPrimulStackChar() << "}";
	return out;
}