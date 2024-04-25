#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip> // Include the <iomanip> header for setw
using namespace std;

int calculateCost(const string& word, const vector<int>& cost) {
    int totalCost = 0;
    for (char c : word) {
        totalCost += cost[c - 'a'];
    }
    return totalCost;
}


string longestCommonSubsequence(const string& str1, const string& str2, vector<vector<int>>& dp, const vector<int>& cost) {
    int m = str1.length();
    int n = str2.length();

    // Build the dynamic programming table
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 2*cost[str1[i - 1] - 'a'];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Construct the lcs
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) { //m-1 is the last char of str1, not m
            lcs.push_back(str1[i - 1]);
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(lcs.begin(), lcs.end());

    return lcs;
}

void printMatrix(const vector<vector<int>>& matrix, const string& str1, const string& str2) {
    int m = matrix.size() - 1;
    int n = matrix[0].size() - 1;

    cout << setw(8) << " ";
    for (int j = 0; j < n; j++) {
        cout << setw(4) << str2[j];
    }
    cout << endl;

    for (int i = 0; i <= m; i++) {
        if (i > 0) {
            cout << setw(4) << str1[i - 1];
        } else {
            cout << setw(4) << " ";
        }

        for (int j = 0; j <= n; j++) {
            cout << setw(4) << matrix[i][j];
        }

        cout << endl;
    }
}

int main() {
    int number, result = 0;
    string resultStr = "";
    cin >> number;

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

    for (int i = 0; i < number; i++) {

        string str1, str2;

        cin >> str1;
        cin >> str2;
        int cost1 = calculateCost(str1, cost);
        int cost2 = calculateCost(str2, cost);

        //cout << "Word 1: " << str1 << ", Cost: " << cost1 << endl;
        //cout << "Word 2: " << str2 << ", Cost: " << cost2 << endl;

        int m = str1.length();
        int n = str2.length();

        // Create the DP matrix
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        string lcs = longestCommonSubsequence(str1, str2, dp, cost);

        //cout << "Longest Common Subsequence: " << lcs << endl;

        //cout << "DP Matrix:" << endl;
        //printMatrix(dp, str1, str2);
        //cout << cost1+cost2-dp[m][n] <<endl;
        result+=cost1+cost2-dp[m][n];
        resultStr+=' '+lcs;
    }
    cout << result << resultStr;
    return 0;
}