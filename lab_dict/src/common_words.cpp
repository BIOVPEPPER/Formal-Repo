/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        [](int c) {return std::ispunct(c);});
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */
        for (const auto& word : words) {
            file_word_maps[i].emplace(word, 0).first->second++;
        }
    }
}

void CommonWords::init_common()
{
    /* Your code goes here! */
    // for (const auto& word_map : file_word_maps) {
    //     for (const auto& [word, count] : word_map) {
    //         common.insert_or_assign(word, 0).first->second += count;
    //     }
    // }
    for (const auto& file_word_map : file_word_maps) {
        for (const auto& [key, value] : file_word_map) {
            auto lookup = common.find(key);
            if (lookup == common.end()) {
                common[key] = 1;
            } else {
                common[key]++;
            }
        }
    }

}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    unsigned numFile = file_word_maps.size();
    /* Your code goes here! */

    // create a temporary vector to hold the common words that occur in all files
    vector<string> common_words;
    for (const auto& [word, count] : common) {
        if (count == numFile) {
            common_words.push_back(word);
        }
    }

    // use std::copy_if to filter the common words based on the frequency of occurrence in each file
    std::copy_if(common_words.begin(), common_words.end(), std::back_inserter(out), [&](const string& word) {
        unsigned count = 0;
        for (const auto& file_map : file_word_maps) {
            auto lookup = file_map.find(word);
            if (lookup != file_map.end() && lookup->second >= n) {
                count++;
            }
        }
        return count == numFile;
    });

    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
