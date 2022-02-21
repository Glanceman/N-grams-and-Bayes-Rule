// N-grams and Bayes' Rule.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<unordered_map>
#include<unordered_set>

using namespace std;
void readFile(string path, vector<string>& text);

class NGramPredictor {
public:
    NGramPredictor(int windowSize) {
        nVal=windowSize+1;
    }

    void registerSequence(const string& actions) {
        if (actions.length() > nVal) { 
            cout << "cant reg due to size" << endl;
            return; }
        string key = actions.substr(0, nVal);
        uniqueAct.insert(key.back());
        if (frequency.find(key) == frequency.end()) { //not exist 
            frequency[key] = 0;
        }
        else { // exist
            frequency[key] = frequency[key] + 1;
        }
    }

    char getMostLikely(const string& actions) {
        string partialKey = actions;
        int highestScore = -1;
        char bestAct = ' ';
        for (unordered_set<char>::iterator it = uniqueAct.begin(); it != uniqueAct.end(); it++) {
            string completeKey = partialKey + *it;
            if (frequency.find(completeKey) != frequency.end()) {
                if (frequency[completeKey] >= highestScore) {
                    highestScore = frequency[completeKey];
                    bestAct = *it;
                }
            }
        }
        return bestAct;
    }
private:
    unordered_set<char> uniqueAct;
    unordered_map<string, int> frequency;
    int nVal = 0;

};

void main()
{
    vector<string> text;
    readFile("../string.txt", text);
    /* test
    NGramPredictor predictor(3);
    string str = "LRRLRLLLLRRLRLRR";
    for (int i = str.length(); i > 2; i--) {
        string action = str.substr(i - 3, 3);
        predictor.registerSequence(action);
    }
    cout << predictor.getMostLikely("RR") << endl;
    */
    NGramPredictor predictor1(1);
    for (int i = text[0].length(); i > 0; i--) {
        string action = text[0].substr(i - 1, 1);
        predictor1.registerSequence(action);
    }


    NGramPredictor predictor2(2);
    for (int i = text[0].length(); i > 1; i--) {
        string action = text[0].substr(i - 2, 2);
        predictor2.registerSequence(action);
    }
    cout << predictor2.getMostLikely(text[0].substr(text[0].length() - 1)) << endl;


    NGramPredictor predictor3(3);
    for (int i = text[0].length(); i > 2; i--) {
        string action = text[0].substr(i - 3, 3);
        predictor3.registerSequence(action);
    }
    cout << predictor3.getMostLikely(text[0].substr(text[0].length()-2)) << endl;
}

void readFile(string path, vector<string>& text) {
    ifstream file;
    file.open(path);
    if (file.is_open() == true) {
        string s;
        while (getline(file, s)) {
            text.push_back(s);
        }
    }else {
        cout << false << endl;
    }
    file.close();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
