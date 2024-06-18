#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <unordered_set>

// Daftar kata berdasarkan kategori
std::unordered_set<std::string> subjects = {"andi", "afra", "azam", "alwi", "arka"};
std::unordered_set<std::string> predicates = {"membawa", "mengajak", "mendorong", "menemani", "menarik"};
std::unordered_set<std::string> objects = {"rafa", "rika", "reza", "raka", "raju"};
std::unordered_set<std::string> descriptions = {"ketaman", "kehutan", "kerumah", "keteras", "kekamar"};

enum TokenType {
    SUBJECT,
    PREDICATE,
    OBJECT,
    DESCRIPTION,
    INVALID
};

// Fungsi untuk mengenali token
TokenType recognizeToken(const std::string& word) {
    if (subjects.find(word) != subjects.end()) {
        return SUBJECT;
    } else if (predicates.find(word) != predicates.end()) {
        return PREDICATE;
    } else if (objects.find(word) != objects.end()) {
        return OBJECT;
    } else if (descriptions.find(word) != descriptions.end()) {
        return DESCRIPTION;
    }
    return INVALID;
}

// Fungsi untuk memeriksa kevalidan struktur kalimat
std::string getSentenceStructure(const std::vector<TokenType>& tokens) {
    std::stack<int> stateStack;
    stateStack.push(0);  // Initial state

    for (TokenType token : tokens) {
        int currentState = stateStack.top();
        stateStack.pop();
        switch (currentState) {
            case 0: // Initial state
                if (token == SUBJECT) {
                    stateStack.push(1);
                } else {
                    return "Kalimat tidak valid.";
                }
                break;
            case 1: // After SUBJECT
                if (token == PREDICATE) {
                    stateStack.push(2);
                } else {
                    return "Kalimat tidak valid.";
                }
                break;
            case 2: // After PREDICATE
                if (token == OBJECT) {
                    stateStack.push(3);
                } else if (token == DESCRIPTION) {
                    stateStack.push(4);
                } else {
                    return "Kalimat tidak valid.";
                }
                break;
            case 3: // After OBJECT
                if (token == DESCRIPTION) {
                    stateStack.push(4);
                } else {
                    return "Kalimat tidak valid.";
                }
                break;
            case 4: // After DESCRIPTION
                return "Kalimat tidak valid."; // No valid transition after DESCRIPTION
            default:
                return "Kalimat tidak valid.";
        }
    }

    // Valid final states are 2, 3, and 4
    int finalState = stateStack.top();
    if (finalState == 2) {
        return "Kalimat valid dengan struktur S-P.";
    } else if (finalState == 3) {
        return "Kalimat valid dengan struktur S-P-O.";
    } else if (finalState == 4) {
        if (tokens.size() == 3) {
            return "Kalimat valid dengan struktur S-P-K.";
        } else if (tokens.size() == 4) {
            return "Kalimat valid dengan struktur S-P-O-K.";
        }
    }

    return "Kalimat tidak valid.";
}

int main() {
    std::string sentence;
    std::cout << "Masukkan kalimat: ";
    std::getline(std::cin, sentence);

    std::istringstream iss(sentence);
    std::vector<TokenType> tokens;
    std::string word;

    while (iss >> word) {
        TokenType token = recognizeToken(word);
        if (token == INVALID) {
            std::cout << "Kalimat tidak valid: kata '" << word << "' tidak dikenali." << std::endl;
            return 1;
        }
        tokens.push_back(token);
    }

    std::cout << getSentenceStructure(tokens) << std::endl;

    return 0;
}

