#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <unordered_map>

namespace ELIZA
{
    struct RuleMessagePair {
        std::regex rule;
        std::string message;
    };

    enum Rank {
        question,
        general_affirmation,
        negation,
        aggreement,
        none
    };

    class AiModel
    {
        private:
            std::vector<RuleMessagePair> rules;
            std::unordered_map<std::string, Rank> keywordRankMap;
            Rank rankInput(std::string input);
            std::string randomAnswer(std::vector<std::string> messageParts);
            void initMap(std::ifstream& file);
        public:
            AiModel(const std::string& filename, const std::string& keywordFileName);
            std::string raspuns(const std::string& input);
    };
}