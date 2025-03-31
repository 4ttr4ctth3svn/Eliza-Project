#include "AiModel.hpp"

ELIZA::AiModel::AiModel(const std::string& filename, const std::string& keywordFileName) {
    std::ifstream file(filename);
    std::string line;
    try {
        while (getline(file, line)) {
            size_t separatorPos = line.find("=>");
            if (separatorPos != std::string::npos) {
                std::string pattern = line.substr(0, separatorPos);
                std::string message = line.substr(separatorPos + 2);
                rules.push_back({ std::regex(pattern), message });
            }
        }
    } catch (const std::regex_error& e) {
        std::cerr << "Eroare la citirea expresiilor regulate: " << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
    std::ifstream keywordFile(keywordFileName);
    initMap(keywordFile);
}

std::string ELIZA::AiModel::raspuns(const std::string& input) {
    ELIZA::Rank inputRank = rankInput(input);
    if(inputRank == ELIZA::Rank::question) {
        std::vector<std::string> messageParts = {"Tu ce crezi?", "Tie ce iti sugereaza?", "Tie ce ti se pare?"};
        return randomAnswer(messageParts);
    }
    else if(inputRank == ELIZA::Rank::general_affirmation) {
        std::vector<std::string> messageParts = {"Poti sa imi dai un exemplu?", "Exemplifica, te rog.", "Ofera un exemplu."};
        return randomAnswer(messageParts);
    }
    else if(inputRank == ELIZA::Rank::aggreement) {
        std::vector<std::string> messageParts = {"Am inteles.", "E clar.", "Ok."};
        return randomAnswer(messageParts);
    }
    else {
        for (auto it = rules.begin(); it != rules.end(); ++it) {
            if (std::regex_search(input, it->rule)) {

                std::stringstream ss(it->message);
                std::vector<std::string> messageParts;
                std::string part;
                while (getline(ss, part, '|')) {
                    messageParts.push_back(part);
                }
                return randomAnswer(messageParts);
            }
        }
        if(inputRank == ELIZA::Rank::negation)
            return "De ce nu?";
        std::vector<std::string> messageParts = {"Poti sa dezvolti?", "Elaboreaza te rog."};
        return randomAnswer(messageParts);
    }
}

ELIZA::Rank ELIZA::AiModel::rankInput(std::string input) {
    std::string token;
    std::stringstream stream(input);
    std::vector<std::string> tokens;

    while(getline(stream, token, ' '))
        tokens.push_back(token);

    ELIZA::Rank minRank = ELIZA::Rank::none;
    for(auto it = tokens.begin(); it != tokens.end(); it++)
        if(keywordRankMap.find(*it) != NULL)
            minRank = std::min(minRank, keywordRankMap[*it]);

    return minRank;
}

std::string ELIZA::AiModel::randomAnswer(std::vector<std::string> messageParts) {
    srand(time(0));
    int randomIndex = rand() % (messageParts.size());
    return messageParts[randomIndex];
}

void ELIZA::AiModel::initMap(std::ifstream& file) {
    std::string line;
    while (getline(file, line)) {
        size_t separatorPos = line.find("=>");
        if (separatorPos != std::string::npos) {
            std::string keyword = line.substr(0, separatorPos);
            std::string rankString = line.substr(separatorPos + 2);
            ELIZA::Rank rank;
                
            if(rankString == "intrebare")
                rank = ELIZA::Rank::question;
            else if(rankString == "generalizare")
                rank = ELIZA::Rank::general_affirmation;
            else if(rankString == "negatie")
                rank = ELIZA::Rank::negation;
            else if(rankString == "acord")
                rank = ELIZA::Rank::aggreement;
            else
                rank = ELIZA::Rank::none;

            keywordRankMap.insert({keyword, rank});
        }
    }
}