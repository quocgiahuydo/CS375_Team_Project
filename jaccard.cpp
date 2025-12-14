#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>
#include <string>
#include <cctype>
#include <sstream>
#include <map>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <unordered_set>

using namespace std;



double jaccardSimilarity(){
    set<string> A ={"The", "quick", "brown","fox", "jumps" ,"over" ,"the" ,"lazy" ,"dog"};
    set<string> B ={"The", "quick","brown", "fox", "jumps" ,"over" ,"the" ,"sleeping" ,"cat"};
    
    
   
    vector<string> setIntersection;
    vector<string> setUnion;
    set_intersection(A.begin(), A.end(), B.begin(), B.end(),back_inserter(setIntersection));
    set_union(A.begin(), A.end(), B.begin(), B.end(), back_inserter(setUnion));
    double result = double(setIntersection.size())/double(setUnion.size())*double(100);
    cout << result<<"%"<< endl;
    return result;
}



void removeMarkAndLowercase(string &inputString){
    for (char &c : inputString) {
        unsigned char uc = static_cast<unsigned char>(c);
        if (isspace(uc) || ispunct(uc)) {
            c = ' ';
        } else {
            c = static_cast<char>(tolower(uc));
        }
    }
}

void stringProcess(string &inputA, string &inputB){
    removeMarkAndLowercase(inputA);
    removeMarkAndLowercase(inputB);

}

static inline string ltrim_copy(const string &s){
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;
    return s.substr(start);
}


void readSampleAndExtract(const string &path, string &stringA, string &stringB){
    ifstream in(path);
    if(!in){
        cerr << "Could not open file: " << path << "\n";
        return;
    }

    const string markA = "paragraph a";
    const string markB = "paragraph b";
    bool waiting_for_content = false;

    enum class Mode { NONE, A, B };
    Mode mode = Mode::NONE;

    string line;
    while (std::getline(in, line)) {
        string lower = line;
        for (char &c: lower) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

        size_t posA = lower.find(markA);
        size_t posB = lower.find(markB);

        if (posA != string::npos) {
            mode = Mode::A;
            waiting_for_content = true;
            size_t start = posA + markA.size();
            string remainder = ltrim_copy(line.substr(start));
            while(!remainder.empty() && std::ispunct(static_cast<unsigned char>(remainder[0]))) remainder.erase(0,1);
            remainder = ltrim_copy(remainder);
            if (!remainder.empty()){
                if (!stringA.empty()) stringA += ' ';
                stringA += remainder;
                waiting_for_content = false;
            }
            continue;
        }

        if (posB != string::npos) {
            mode = Mode::B;
            waiting_for_content = true;
            size_t start = posB + markB.size();
            string remainder = ltrim_copy(line.substr(start));
            while(!remainder.empty() && std::ispunct(static_cast<unsigned char>(remainder[0]))) remainder.erase(0,1);
            remainder = ltrim_copy(remainder);
            if (!remainder.empty()){
                if (!stringB.empty()) stringB += ' ';
                stringB += remainder;
                waiting_for_content = false;
            }
            continue;
        }

        bool only_ws = true;
        for (char ch: line) if (!std::isspace(static_cast<unsigned char>(ch))) { only_ws = false; break; }

        if (mode == Mode::A) {
            if (waiting_for_content) {
                if (only_ws) continue;
                if (!stringA.empty()) stringA += ' ';
                stringA += ltrim_copy(line);
                waiting_for_content = false;
            } else {
                if (only_ws) {
                    mode = Mode::NONE;
                } else {
                    if (!stringA.empty()) stringA += ' ';
                    stringA += ltrim_copy(line);
                }
            }
        } else if (mode == Mode::B) {
            if (waiting_for_content) {
                if (only_ws) continue;
                if (!stringB.empty()) stringB += ' ';
                stringB += ltrim_copy(line);
                waiting_for_content = false;
            } else {
                if (only_ws) {
                    mode = Mode::NONE;
                } else {
                    if (!stringB.empty()) stringB += ' ';
                    stringB += ltrim_copy(line);
                }
            }
        }
    }
}


vector<string> tokenizeString(const string &input){
    string copy = input;
    removeMarkAndLowercase(copy);
    stringstream ss(copy);
    vector<string> tokens;
    string w;
    while(ss >> w) tokens.push_back(w);
    return tokens;
}

vector<vector<string>> chunkTokens(const vector<string> &tokens, size_t maxTokens){
    vector<vector<string>> chunks;
    if(maxTokens == 0) return chunks;
    size_t i = 0;
    while(i < tokens.size()){
        size_t end = std::min(tokens.size(), i + maxTokens);
        chunks.emplace_back(tokens.begin() + i, tokens.begin() + end);
        i = end;
    }
    return chunks;
}

double jaccardFromTokens(const vector<string> &aTokens, const vector<string> &bTokens){
    unordered_set<string> A(aTokens.begin(), aTokens.end());
    unordered_set<string> B(bTokens.begin(), bTokens.end());
    if(A.empty() && B.empty()) return 100.0;
    if(A.empty() || B.empty()) return 0.0;
    size_t inter = 0;
    for(const auto &t: A) if(B.count(t)) ++inter;
    size_t uni = A.size() + B.size() - inter;
    if(uni == 0) return 0.0;
    return static_cast<double>(inter) / static_cast<double>(uni) * 100.0;
}

int main(){
    const size_t MAX_TOKENS = 50; // adjust as needed

    // Fixed list of test files to process. Add or remove filenames as needed.
    vector<string> txtFiles = {
        "sample.txt",
        "sample_sent.txt",
        "testcase1.txt",
        "testcase2.txt",
        "testcase3.txt",
        "testcase4.txt",
        "testcase5.txt"
    };

    for (const auto &file : txtFiles){
        cout << "========================================\n";
        cout << "File: " << file << "\n";

        auto t0 = std::chrono::high_resolution_clock::now();
        string inputA, inputB;
        readSampleAndExtract(file, inputA, inputB);

        cout << "--- Extracted Paragraph A (raw) ---\n" << inputA << "\n";
        cout << "--- Extracted Paragraph B (raw) ---\n" << inputB << "\n";

        auto tokensA = tokenizeString(inputA);
        auto tokensB = tokenizeString(inputB);

        auto chunksA = chunkTokens(tokensA, MAX_TOKENS);
        auto chunksB = chunkTokens(tokensB, MAX_TOKENS);

        size_t maxChunks = std::max(chunksA.size(), chunksB.size());
        if(maxChunks == 0){
            cout << "No tokens found in either paragraph for this file.\n";
            continue;
        }

        for(size_t i = 0; i < maxChunks; ++i){
            const vector<string> emptyVec;
            const vector<string> &aChunk = (i < chunksA.size()) ? chunksA[i] : emptyVec;
            const vector<string> &bChunk = (i < chunksB.size()) ? chunksB[i] : emptyVec;
            double sim = jaccardFromTokens(aChunk, bChunk);
            cout << "Chunk "<< i << ": Jaccard = " << sim << "%\n";
        }

        double overall = jaccardFromTokens(tokensA, tokensB);
        cout << "Overall Jaccard = " << overall << "%\n";

        auto t1 = std::chrono::high_resolution_clock::now();
        double ms = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count() / 1000.0;
        cout << fixed << setprecision(3);
        cout << "Running time: " << ms << " ms\n";
    }

    return 0;
}