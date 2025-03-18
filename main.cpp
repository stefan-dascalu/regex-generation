#include <bits/stdc++.h>
using namespace std;

// checks if the pattern matches the word, treating '.' as a wildcard
bool pattern_match(const string &pattern, const string &word) {
    if (pattern.length() != word.length()) {
        return false;
    }
    
    for (size_t i = 0; i < pattern.length(); i++) {
        if (pattern[i] != '.' && pattern[i] != word[i]) {
            return false;
        }
    }
    return true;
}

// checks if the pattern conflicts with any word in the failed list
bool has_pattern_conflict(const string &pattern, const vector<string> &failed_words) {
    for (const auto &failed : failed_words) {
        if (pattern_match(pattern, failed)) {
            return true;
        }
    }
    return false;
}

// merges two patterns by replacing characters that differ with '.'
string merge_patterns(const string &pattern1, const string &pattern2) {
    string merged = pattern1;
    for (size_t i = 0; i < merged.size(); i++) {
        if (merged[i] != pattern2[i]) {
            merged[i] = '.';
        }
    }
    return merged;
}

// checks that the pattern still matches all words in the group, including the new word
bool maintains_coverage(const string &pattern, const vector<string> &group_words, const string &new_word) {
    if (!pattern_match(pattern, new_word)) {
        return false;
    }
    
    for (const auto &word : group_words) {
        if (!pattern_match(pattern, word)) {
            return false;
        }
    }
    return true;
}

// tries to extend an existing pattern with a new word
// returns an empty string if the extension isn't possible
string try_extend_pattern(const string &existing_pattern, const vector<string> &group_words, const string &new_word, const vector<string> &failed_words) {
    string candidate = merge_patterns(existing_pattern, new_word);
    
    if (has_pattern_conflict(candidate, failed_words) || !maintains_coverage(candidate, group_words, new_word)) {
        return "";
    }
    return candidate;
}

// structure that holds a pattern along with the words it covers
struct PatternGroup {
    string pattern;
    vector<string> covered_words;
};

int main()
{
    // file handling
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    if (!input_file || !output_file) {
        return 1;
    }
    
    // input reading
    int accepted_count, failed_count, word_length;
    input_file >> accepted_count >> failed_count >> word_length;
    vector<string> accepted_words(accepted_count), failed_words(failed_count);
    for (auto &word : accepted_words) {
        input_file >> word;
    }
    for (auto &word : failed_words) {
        input_file >> word;
    }

    output_file << "regex\n";

    // handle special cases
    if (accepted_count == 0) {
        output_file << "xyzabc\n";
        return 0;
    }
    if (accepted_count == 1) {
        output_file << accepted_words[0] << "\n";
        return 0;
    }

    // initalize pattern groups
    vector<PatternGroup> pattern_groups;
    for (const auto &word : accepted_words) {
        bool merged = false;
        for (auto &group : pattern_groups) {
            string extended_pattern = try_extend_pattern(group.pattern, group.covered_words, word, failed_words);
            if (!extended_pattern.empty()) {
                group.pattern = extended_pattern;
                group.covered_words.push_back(word);
                merged = true;
                break;
            }
        }
        if (!merged) {
            pattern_groups.push_back({ word, { word } });
        }
    }

    // extract patterns for further merging
    vector<string> current_patterns;
    for (const auto &group : pattern_groups) {
        current_patterns.push_back(group.pattern);
    }

    vector<string> final_patterns = current_patterns;

    // build the final regex by joining patterns with '|'
    string final_regex;
    for (size_t i = 0; i < final_patterns.size(); i++) {
        if (i > 0) {
            final_regex += "|";
        }
        final_regex += final_patterns[i];
    }

    output_file << final_regex << "\n";
    return 0;
}

