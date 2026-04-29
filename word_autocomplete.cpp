#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <algorithm>

// 1. Базовий елемент дерева
struct Node {
    std::unordered_map<char, Node*> children;
    bool isEndOfWord;

    Node() : isEndOfWord(false) {}
};

// 2. Структура Trie
class Trie {
private:
    Node* root;

    // Рекурсивна допоміжна функція для збору всіх слів з заданого вузла
    void collectAllWords(Node* curr, std::string prefix, std::vector<std::string>& results) {
        if (curr->isEndOfWord) {
            results.push_back(prefix);
        }

        for (auto const& [ch, childNode] : curr->children) {
            collectAllWords(childNode, prefix + ch, results);
        }
    }

public:
    Trie() {
        root = new Node();
    }

    // Додавання нового слова
    void insert(const std::string& word) {
        Node* curr = root;
        for (char ch : word) {
            if (curr->children.find(ch) == curr->children.end()) {
                curr->children[ch] = new Node();
            }
            curr = curr->children[ch];
        }
        curr->isEndOfWord = true;
    }

    // Пошук слів за префіксом
    std::vector<std::string> findByPrefix(const std::string& prefix) {
        Node* curr = root;
        std::vector<std::string> results;

        // Переходимо до вузла, який відповідає кінцю префікса
        for (char ch : prefix) {
            if (curr->children.find(ch) == curr->children.end()) {
                return {}; // Префікс не знайдено
            }
            curr = curr->children[ch];
        }

        // Збираємо всі слова, що починаються з цього вузла
        collectAllWords(curr, prefix, results);
        return results;
    }
};

int main() {
    Trie trie;
    std::string filename = "words_alpha.txt";

    // 3. Зчитування з файлу
    std::cout << "Loading dictionary..." << std::endl;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        std::cerr << "Please ensure words_alpha.txt is in the same directory." << std::endl;
        return 1;
    }

    std::string word;
    int count = 0;
    while (file >> word) {
        trie.insert(word);
        count++;
    }
    file.close();
    std::cout << "Loaded " << count << " words." << std::endl;

    // 4. Тестування
    std::string input;
    while (true) {
        std::cout << "\nInput: > ";
        std::cin >> input;

        if (input == ":q") break; // Вихід з програми

        std::vector<std::string> matches = trie.findByPrefix(input);

        if (matches.empty()) {
            std::cout << "No matches found.";
        } else {
            std::cout << "Output: > ";
            // Обмежуємо вивід першими 10 результатами для зручності
            for (size_t i = 0; i < std::min(matches.size(), (size_t)10); ++i) {
                std::cout << matches[i] << (i == matches.size() - 1 || i == 9 ? "" : ", ");
            }
            if (matches.size() > 10) std::cout << "... (total " << matches.size() << ")";
        }
        std::cout << std::endl;
    }

    return 0;
}