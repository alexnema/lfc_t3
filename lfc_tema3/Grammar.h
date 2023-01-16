#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <regex>
#include <random>
#include <ctime>
#include <cstdlib>

class Grammar {
public:
    explicit Grammar(std::vector<char> Vn, std::vector<char> Vt, char S, std::vector<std::pair<std::string, std::string>> P);
    Grammar() = default;
    Grammar(const Grammar& g);
    bool VerifyGrammar();
    std::string GenerateWord();
    void PrintGrammar();
    void ReadGrammar();
    friend std::ostream& operator<<(std::ostream& out, const Grammar& g);
    friend std::istream& operator>>(std::istream& in, Grammar& g);
    bool isContextFree() const;
    void simplifyCFG();
    bool verifyChomsky(std::pair<std::string, std::string> production);
    void convertToNFC();

private:
    bool containsStartSymbolAlone() const;
    bool containsOneNonTerminal(const std::string& s) const;
    bool checkNonTerminals() const;
    std::vector<unsigned int> getIndexOfProductions(const std::string& currentWord) const;
    std::string applyProduction(const std::string& currentWord, const std::pair<std::string, std::string>& prod) const;
    static bool isVoidIntersection(const std::vector<char>& v1, const std::vector<char>& v2);
    bool verifyProduction(unsigned int index) const;
    void removeSymbolsThatDontGenerateTerminals();
    void removeUnreachableSymbols();
    void removeUnitProductions();

private:
    std::vector<char> nonTerminal, terminal;
    char startSymbol{};
    std::vector<std::pair<std::string, std::string>> productions;
};