//-------------------------------------------------
// Author: Aiden Koknat
// Date: 4/16/21
// Description: CS 316 Project 4
//-------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

// 489 is the magic number of words you want!
// delete it after you figure out how to access stuff properly!

struct value {
    string word;
    int frequency;

    value() { // constructor
        word = "";
        frequency = 0;
    }
};

void mergeFrequency(vector<value> &v, int start, int middle, int end) {
    int i = start;
    int j = middle + 1;
    vector<value> tempVec;
    while (i <= middle && j <= end) {
        if (v[i].frequency <= v[j].frequency) {
            tempVec.push_back(v[i]);
            i++;
        }
        else {
            tempVec.push_back(v[j]);
            j++;
        }
    }
    while (i <= middle) {
        tempVec.push_back(v[i]);
        i++;
    }
    while (j <= end) {
        tempVec.push_back(v[j]);
        j++;
    }
    for (int k = start; k <= end; k++) {
        v[k] = tempVec[k - start];
    }
}

void mergeWord(vector<value> &v, int start, int middle, int end) {
    int i = start;
    int j = middle + 1;
    vector<value> tempVec;
    while (i <= middle && j <= end) {
        if (v[i].word <= v[j].word) {
            tempVec.push_back(v[i]);
            i++;
        }
        else {
            tempVec.push_back(v[j]);
            j++;
        }
    }
    while (i <= middle) {
        tempVec.push_back(v[i]);
        i++;
    }
    while (j <= end) {
        tempVec.push_back(v[j]);
        j++;
    }
    for (int k = start; k <= end; k++) {
        v[k] = tempVec[k - start];
    }
}

void sortWord(vector<value> &v, int start, int end) {
    if (start < end) {
        int middle = (start + end) / 2;
        sortWord(v, start, middle);
        sortWord(v, middle + 1, end);
        mergeWord(v, start, middle, end);
    }
}

void sortFrequency(vector<value> &v, int start, int end) {
    if (start < end) {
        int middle = (start + end) / 2;
        sortFrequency(v, start, middle);
        sortFrequency(v, middle + 1, end);
        mergeFrequency(v, start, middle, end);
    }
}

vector<value> storage; // Just for getting in info (words)
int hashDivider = 73; // What youre dividing by for the hash 

// make a hash function idiot
int hashTime(string word) {
    int sum = 0;
    for (long unsigned int i = 0; i < word.length(); i++) {
        sum = sum + ((word[i])^(i));
    }
    return sum % hashDivider;
}

int main() {

    vector<vector<value>> hashTable;
    stringstream stream; // for sanitized stream
    string temp;

    while(cin.good()) {
        cin >> temp; // get single word from text
        for (long unsigned int i = 0; i < temp.length(); i++) {
            char character = temp[i];
            if (!((character >= 65 && character <= 90) || (character >= 97 && character <= 122) || (character == 95))) { // Checks for invalid characters and sanitizes
                temp[i] = ' ';
            }
        }
        stream << temp << ' '; // creates sanitized stream
    }

    value tempValue;
    while (stream.good()) { // Put stream into storage
        stream >> temp;
        tempValue.word = temp;
        tempValue.frequency = 1;
        if (temp != "") {
            storage.push_back(tempValue);
        }
    }
    // for (int i = 0; i < storage.size(); i++) {
    //     cout << storage[i].word << " ";
    // }
    hashTable.resize(hashDivider);

    // Organizing the words into hash
    
    for (long unsigned int i = 0; i < storage.size(); i++) {
        int match = 0;
        string tempWord = storage[i].word;
        int index = hashTime(tempWord);
        for (long unsigned int j = 0; j < hashTable[index].size(); j++) {
            if (hashTable[index][j].word == tempWord) {
                hashTable[index][j].frequency++;
                match = 1;
            }
        }
        if (!match) {
            value *tempPointer = new value;
            tempPointer->word = tempWord;
            tempPointer->frequency = 1;
            hashTable[index].push_back(*tempPointer);
        }
    }


    // list of sorted words
    vector<value> sorted;

    for (int i = 0; i < hashDivider; i++) {
        vector<value> tempVec = hashTable[i];
        for (int j = 0; j < tempVec.size(); j++) {
            sorted.push_back(tempVec[j]);
        }
    }
    
    vector<value> countSort = sorted;
    sortFrequency(countSort, 0, countSort.size() - 1);

    vector<value> wordSort = sorted;
    sortWord(wordSort, 0, wordSort.size() - 1);


    // printing the words ! wowie god has abandoned me
    for (int i = 0; i < wordSort.size(); i++) {
        cout << wordSort[i].word << " " << wordSort[i].frequency << endl;
    }
    cout << endl;
    for (int i = countSort.size() - 1; i >= 0; i--) {
        cout << countSort[i].word << " " << countSort[i].frequency << endl;
    }
    return 0;
}