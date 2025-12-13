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



double jaccardSimilarity(vector<string> &listA, vector<string> &listB){

    set<string> A;
    set<string> B;
    A.insert(listA.begin(), listA.end());
    B.insert(listB.begin(), listB.end());
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
    string inputA ="The quick brown fox jumps over the lazy dog";   
    string inputB="The quick brown fox jumps over the sleeping cat";
    stringProcess(inputA, inputB);
    stringstream ssA(inputA);
    stringstream ssB(inputB);

    vector<string> listB;
    vector<string> listA;
    string wordB;
    string wordA;
    while(ssB >> wordB){
        //cout << "Word in sentence: " <<wordB<<endl;
        listB.push_back(wordB);

    }   
    while(ssA>> wordA){
        //cout << "Word in sentence: " <<wordA<<endl;
        listA.push_back(wordA);

    }   
    
    for(auto &word:listB){
        cout << word << endl;
    }
    cout <<endl;
    for(auto &word:listA){
        cout << word << endl;
    }


    double result = jaccardSimilarity(listA, listB);
    cout <<"The similarity between 2 strings is: " << result <<"%"<< endl;
   
    
    return 0;
}