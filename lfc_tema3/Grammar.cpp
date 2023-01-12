#include "Grammar.h"
#include <utility>
#include <set>

Grammar::Grammar(std::vector<char> Vn, std::vector<char> Vt, char S,
    std::vector<std::pair<std::string, std::string>> P)
    :nonTerminal(std::move(Vn)), terminal(std::move(Vt)), startSymbol(S), productions(std::move(P))
{}

bool Grammar::VerifyGrammar() {
    //check if something was provided
    if (nonTerminal.empty() || terminal.empty() || !startSymbol || productions.empty())
        return false;
    //check if terminals and nonTerminals itersected are void result
    if (!isVoidIntersection(nonTerminal, terminal))
        return false;
    //check if the start symbol is in nonTerminal values
    if (std::find(nonTerminal.begin(), nonTerminal.end(), startSymbol) == nonTerminal.end())
        return false;
    if (!checkNonTerminals())
        return false;
    //check id start symbol appears in one prod alone
    if (!containsStartSymbolAlone()) {
        return false;
    }
    return true;
}

bool Grammar::isVoidIntersection(const std::vector<char>& v1, const std::vector<char>& v2) {
    std::unordered_set<char> set(v1.begin(), v1.end());
    for (const auto& el : v2) {
        if (set.count(el))
            return false;
    }
    return true;
}

bool Grammar::checkNonTerminals() const {
    for (const auto& pair : productions) {
        if (!containsOneNonTerminal(pair.first))
            return false;
    }
    return true;
}

bool Grammar::containsOneNonTerminal(const std::string& s) const {
    for (const auto& chr : s) {
        if (std::count(nonTerminal.begin(), nonTerminal.end(), chr))
            return true;
    }
    return false;
}

std::vector<unsigned int> Grammar::getIndexOfProductions(const std::string& currentWord) const {
    std::vector<unsigned int> index;
    for (unsigned int i = 0; i < productions.size(); i++) {
        if (currentWord.find(productions[i].first) != std::string::npos) {
            index.emplace_back(i);
        }
    }
    return index;
}

std::string Grammar::applyProduction(const std::string& currentWord, const std::pair<std::string, std::string>& prod) const {
    std::string aux;
    aux += this->startSymbol;
    if (currentWord == aux) {
        return prod.second;
    }
    const unsigned int indexFound = currentWord.find(prod.first);
    return currentWord.substr(0, indexFound) + prod.second + currentWord.substr(indexFound + prod.first.size());
}

std::string Grammar::GenerateWord() {
    if (!VerifyGrammar())
        throw "NOT A GOOD GRAMMAR...";
    srand(time(NULL));
    std::string currentWord = "";
    currentWord += this->startSymbol;
    std::vector<unsigned int> index = getIndexOfProductions(currentWord);
    while (!index.empty()) {
        const unsigned int numOfProd = index.size();
        std::pair<std::string, std::string> production = this->productions[index[rand() % numOfProd]];
        std::cout << currentWord << " => ";
        currentWord = applyProduction(currentWord, production);
        index = getIndexOfProductions(currentWord);
    }
    return currentWord;
}

bool Grammar::containsStartSymbolAlone() const {
    for (const auto& prod : this->productions) {
        if (prod.first.size() == 1 && std::count(prod.first.begin(), prod.first.end(), this->startSymbol))
            return true;
    }
    return false;
}

bool Grammar::verifyProduction(unsigned int index) const 
{
    std::pair<std::string, std::string> currentProduction = productions[index];
    // left - one non-terminal symbol 
    if (currentProduction.first.size() > 1 || std::count(nonTerminal.begin(), nonTerminal.end(), currentProduction.first[0]) == 0)
    {
        return false;
    }
    //right - a combination of terminal and non - terminal symbols, possibly including the empty string.
    for (const auto& symbol : currentProduction.second)
    {
        if (currentProduction.second.empty());
        else
        {
            if (std::count(terminal.begin(), terminal.end(), symbol) == 0 && std::count(nonTerminal.begin(), nonTerminal.end(), symbol) == 0) {
                return false;
            }
        }
    }
    return true;
}

void Grammar::removeUnitProductions()
{
    bool stillUnitProduction = false;
    std::vector<std::pair<std::string, std::string>> newProductions;
    do
    {
        stillUnitProduction = false;
        newProductions.clear();
        for (auto production : productions)
        {
            //Production is not A->B
            if (production.second.size() != 1 || std::count(terminal.begin(), terminal.end(), production.second[0]) != 0)
            {
                newProductions.push_back(production);
            }
            else
            {
                // Replace the non-terminal with its corresponding rule
                for (const auto& newProduction : productions)
                {
                    if (newProduction.first == production.second)
                    {
                        newProductions.emplace_back(production.first, newProduction.second);
                    }
                }
            }
        }
        productions = newProductions;
        for (auto production : productions)
        {
            if (production.second.size() == 1 && std::count(nonTerminal.begin(), nonTerminal.end(), production.second[0]))
            {
                stillUnitProduction = true;
            }
        }
    }
    while (stillUnitProduction);
}


//void Grammar::reduceCFG()
//{
//    std::unordered_set<std::string> reachableSymbols;
//
//    // Find reachable symbols
//    reachableSymbols.insert("S"); // Start symbol is always reachable
//    bool changed = false;
//    do
//    {
//        changed = false;
//        for (const auto& production : productions)
//        {
//            if (reachableSymbols.count(production.first))
//            {
//                for (const auto& symbol : production.second)
//                {
//                    std::string symbolString = "";
//                    symbolString += symbol;
//                    if (reachableSymbols.count(symbolString) == 0)
//                    {
//                        reachableSymbols.insert(symbolString);
//                        changed = true;
//                    }
//                }
//            }
//        }
//    } while (changed);
//    std::cout << "SET: ";
//    for (auto it : reachableSymbols)
//        std::cout << it << " ";
//}


bool Grammar::isContextFree() const
{
    for (unsigned int i = 0; i < productions.size(); i++) {
        if (!verifyProduction(i)) {
            return false;
        }
    }
    return true;
}

void Grammar::PrintGrammar() {
    std::cout << *this;
}

void Grammar::ReadGrammar() {
    std::cin >> *this;
}


std::ostream& operator<<(std::ostream& out, const Grammar& g) {
    out << "The Grammar:\nNon-Terminals: ";
    for (const auto& nonTerminal : g.nonTerminal) {
        out << nonTerminal << ", ";
    }
    out << "\nTerminals: ";
    for (const auto& terminal : g.terminal) {
        out << terminal << ", ";
    }
    out << "\nStart Symbol: " << g.startSymbol << '\n';
    out << "Productions:\n";
    for (const auto& prod : g.productions) {
        out << prod.first << " -> " << prod.second << '\n';
    }
    if (g.isContextFree()) {
        out << "\nIs Context Free Grammar\n";
    }
    else {
        out << "\nIs not a Context Free Grammar\n\n";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Grammar& g) {
    g.terminal.clear();
    g.nonTerminal.clear();
    g.productions.clear();

    std::vector<char> nt, t;
    char start;
    std::vector<std::pair<std::string, std::string>> prod;

    char aux;
    unsigned int n;

    std::cout << "No. of Non-Terminals: ";
    in >> n;
    std::cout << "Non-terminals: ";
    for (unsigned int i = 0; i < n; i++) {
        in >> aux;
        g.nonTerminal.emplace_back(aux);
    }

    std::cout << "No. of Terminals: ";
    in >> n;
    std::cout << "Terminals: ";
    for (unsigned int i = 0; i < n; i++) {
        in >> aux;
        g.terminal.emplace_back(aux);
    }

    std::cout << "Start Symbol(Non terminal): ";
    in >> g.startSymbol;

    std::string p1, p2;
    std::cout << "No. of Productions: ";
    in >> n;
    std::cout << "Productions:\n";
    for (unsigned int i = 0; i < n; i++) {
        std::cout << "Go for prod " << i << " first: ";
        in >> p1;
        std::cout << "Go for prod " << i << " second: ";
        in >> p2;

        g.productions.emplace_back(std::make_pair(p1, p2));

        std::cout << '\n';

    }
    return in;
}

Grammar::Grammar(const Grammar& g) {
    *this = g;
}
