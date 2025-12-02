#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>
#include <string>
#include <cctype>
#include <sstream>
#include <map>

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

int main(){
    string inputA ="Exercise improves mental health.";
    
    string inputB="Working out boosts a person's mental well-being.";
    cout << inputB<<endl;
    removeMarkAndLowercase(inputB);
    stringstream ss(inputB);
    
    vector<string> listB;
    string word;
    while(ss >> word){
        cout << "Word in sentence: " <<word<<endl;
        listB.push_back(word);

    }   

    for(auto &word:listB){
        cout << word << endl;
    }
    jaccardSimilarity();
   
    
    return 0;
}