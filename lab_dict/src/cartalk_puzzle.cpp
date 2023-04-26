/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iterator>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d, const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    /* Your code goes here! */
    map<string, unsigned int> words;
    ifstream wordsFile(word_list_fname);
    string word;

    auto removeCharAt = [](const string& str, size_t index) {
        string result = str;
        result.erase(result.begin() + index);
        return result;
    };

    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            words[word] = word.size();
        }
    }

    for (const auto& [word, word_length] : words) {
        if (word_length != 5) {
            continue;
        }

        string word2 = removeCharAt(word, 0);
        string word3 = removeCharAt(word, 1);

        if ((words.find(word2) != words.end()) && (words.find(word3) != words.end())) {
            if ((d.homophones(word, word2)) && (d.homophones(word, word3))) {
                ret.push_back(std::tuple<std::string, std::string, std::string>(word, word2, word3));
            }
        }
    }

    return ret;
}
