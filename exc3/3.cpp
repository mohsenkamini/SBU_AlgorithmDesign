#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void calculateIndexValues(char c, int word1InputIndex, int word2Index, int totalCost, const vector<int>& cost,
                            vector<int>& remainingCost, vector<int>& word1CorrespondingIndex, vector<int>& word2PrvIndex) {
                             
    for (int i=0 ; i<word2Index; i++) { //iterate over vectors and for the before word2index
        if (word1CorrespondingIndex[i] < word1InputIndex && word1CorrespondingIndex[i] != -1 ) {
            //cout << word1CorrespondingIndex[i]  << "left: " << remainingCost[word2Index] - 2*cost[c - 'a'] << " rem[i]: " << remainingCost[i]  << endl;
          if (remainingCost[i] - 2*cost[c - 'a'] < remainingCost[word2Index]) {
            remainingCost[word2Index] = remainingCost[i] - 2*cost[c - 'a'];
            word2PrvIndex[word2Index] = i; 
            word1CorrespondingIndex[word2Index]= word1InputIndex;
          }
        } //else if (word1CorrespondingIndex[i] == word1InputIndex)
    }
}

vector<int> findIndicesInWord1(const string& word1, char c) {
    vector<int> indices;
    for (int i = 0; i < word1.length(); i++) {
        if (word1[i] == c) {
            indices.push_back(i);
        }
    }
    return indices;
}


void processWord2Characters(const string& word1, const string& word2, const vector<int>& cost,
                            vector<int>& remainingCost, vector<int>& word1CorrespondingIndex, vector<int>& word2PrvIndex, int totalCost) {

    for (int word2Index=0; word2Index<word2.length() ; word2Index++) {
        char c=word2[word2Index];
        vector<int> indices = findIndicesInWord1(word1, c);
        
        if (indices.empty()) {
            //remainingCost[index] = totalCost;
            word1CorrespondingIndex[word2Index] = -1;
            word2PrvIndex[word2Index] = -1;
        } else {
            remainingCost[word2Index] -= 2*cost[c - 'a'];
            word1CorrespondingIndex[word2Index] = indices[0];
            word2PrvIndex[word2Index] = -1;
            // Call a function to calculate the values for remainingCost,
            // word1CorrespondingIndex, and word2PrvIndex based on the indices
            for (int word1Index : indices) {
                //cout << "processing: " << word1Index << endl;
                calculateIndexValues(c, word1Index, word2Index, totalCost, cost,
                            remainingCost, word1CorrespondingIndex, word2PrvIndex);
            }
        }
    }
}

int calculateCost(const string& word, const vector<int>& cost) {
    int totalCost = 0;
    for (char c : word) {
        totalCost += cost[c - 'a'];
    }
    return totalCost;
}

void orderWords(string& word1, string& word2) {
    if (word2.length() > word1.length()) {
        swap(word1, word2);
    }
}

void printResult(int minIndex, const string& word2, const vector<int>& word2PrvIndex, string& resultStr) {
    if (word2PrvIndex[minIndex] != -1)
        printResult(word2PrvIndex[minIndex], word2, word2PrvIndex, resultStr);
    resultStr += word2[minIndex];
}

int main() {
    int n,result=0;
    string resultStr="";
    cin >> n;

    vector<int> cost(26);
    for (int i = 0; i < 26; i++) {
        string costStr;
        cin >> costStr;
        int figureSum = 0;
        for (char c : costStr) {
            figureSum += c - '0';
        }
        cost[i] = (i + 1) * figureSum;
    }

    cin.ignore(); // Ignore the newline character after reading n

    for (int i = 0; i < n; i++) {
        string word1, word2;
        getline(cin, word1, ' ');
        getline(cin, word2);

        orderWords(word1, word2);
        
        int totalCost = calculateCost(word2, cost) + calculateCost(word1, cost);

        vector<int> remainingCost(word2.length(), totalCost);
        vector<int> word1CorrespondingIndex(word2.length());
        vector<int> word2PrvIndex(word2.length());

        int cost1 = calculateCost(word1, cost);
        int cost2 = calculateCost(word2, cost);

        //cout << "Word 1: " << word1 << ", Cost: " << cost1 << endl;
        //cout << "Word 2: " << word2 << ", Cost: " << cost2 << endl;

        processWord2Characters(word1, word2, cost,
                            remainingCost, word1CorrespondingIndex, word2PrvIndex, totalCost);
        int minIndex=0;
        int minValue=totalCost;
        cout << endl << i << ": " << endl;
        for (int i=0 ; i<word2.length() ; i++) {
            cout << word2[i] << " ";
        }
        cout << endl;
        for (int i=0 ; i<word2.length() ; i++) {
            //cout << remainingCost[i] << " ";
            if (remainingCost[i]< minValue)
            {
                minValue=remainingCost[i];
                minIndex=i;
            }
        }
        cout << endl;
        for (int i=0 ; i<word2.length() ; i++) {
            cout << word1CorrespondingIndex[i] << " ";
        }
        cout << endl;
        for (int i=0 ; i<word2.length() ; i++) {
            cout << word2PrvIndex[i] << " ";
        }
        cout << endl << minValue << endl;
        result += minValue;
        printResult(minIndex, word2, word2PrvIndex, resultStr);
        resultStr += ' ';
        cout << endl;
    }
    cout << result << ' ' << resultStr.substr(0, resultStr.length()-1);
    return 0;
}