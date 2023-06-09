/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename) {
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    string key;

    auto sortedWord = [](const string& word) {
        string sorted_word = word;
        std::sort(sorted_word.begin(), sorted_word.end());
        return sorted_word;
    };

    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            key = sortedWord(word);
            dict[key].push_back(word);
        }
    }
}


/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    string key;

    auto sortedWord = [](const string& word) {
        string sorted_word = word;
        std::sort(sorted_word.begin(), sorted_word.end());
        return sorted_word;
    };

    for (const auto& word : words) {
        key = sortedWord(word);
        dict[key].push_back(word);
    }
}
/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    auto sortedWord = [](const string& word) {
        string sorted_word = word;
        std::sort(sorted_word.begin(), sorted_word.end());
        return sorted_word;
    };

    string key = sortedWord(word);
    auto lookup = dict.find(key);

    if (lookup == dict.end() || lookup->second.size() < 2) {
        return vector<string>();
    }

    vector<string> v = lookup->second;

    auto it = std::find(v.begin(), v.end(), word);
    if (it != v.end()) {
        return v;
    } else {
        return vector<string>();
    }

}



/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> res;
    for (const auto& [key, anagrams] : dict) {
        if (anagrams.size() > 1) {
            res.push_back(anagrams);
        }
    }
    return res;
}
