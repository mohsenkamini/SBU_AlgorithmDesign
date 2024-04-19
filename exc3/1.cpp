#include <iostream>
#include <string>
#include <vector>

using namespace std;
void printVector(const vector<int>& vec) {
    // Print vector elements separated by space
    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";
    cout << endl;
}
bool validateNumber (int n) {
    int highLimit = 26,
        lowLimit = 1 ;
    if (n <= highLimit && n >= lowLimit)
        return true;
    return false;
}
bool handleDigit(int index, const vector<int>& numbers, vector<int>& state) { // returns true if dead
    if (index == 0) {
        if (!validateNumber(numbers[index])) {
            state[index]=0;
            return true;
        } else {
            state[index]=1;
            return false;
        }
    } else {
        if (!validateNumber(numbers[index])) {
            if (!validateNumber(numbers[index-1]*10+numbers[index])) {
                state[index]=0;
                return true;
            } else {
                state[index]=1;
                state[index-1]=1;
                return false;
            }
        }

        if (validateNumber(numbers[index])) {
            if (numbers[index-1] == 0) {
                state[index]=1;
                return false;
            } else if(validateNumber(numbers[index-1]*10+numbers[index])) {
                switch (state[index-1]) {
                    case 0: 
                        return true;
                        break;
                    case 1:
                        state[index]=2;
                        return false;
                        break;
                    case 2:
                        state[index]=3;
                        return false;
                        break;
                    default:
                        state[index]=state[index-1]+state[index-2];
                        return false;
                        break;
                }
            } else {
                state[index]=1;
                return false;
            }
        }
    }
    cout << "unexpected";
    return false;
}

int main() {
    int n; 
    long result=1;
    cin >> n;
    bool deadFlag=false,mask=false;
    for (int i = 0; i < n; ++i) {
        string input;
        cin >> input;
        vector<int> numbers;

        for (int j = 0; j < input.length(); ++j) {
            int digit = input[j] - '0';
            numbers.push_back(digit);
        }

        vector<int> state(numbers.size());
        
        for (int j = 0; j < state.size(); ++j) {
            if (deadFlag=handleDigit(j, numbers, state)) {
                //cout << j <<"dead number";
                break;
            }
        }
        if (!deadFlag) {
            for (int j=state.size()-1 ; j >= 0 ; j--) {
                if (state[j] > 1 && mask==false) {
                    mask=true;
                    //if (state[j]==0)
                    //    cout << "Debug j: " << j << "State: " << state[j];
                    //cout << result << endl;
                    result = state[j] *result % 1000000007;

                } else if (mask==true && state[j] == 1)
                    mask=false;
            }
        }
        //printVector(state);
    }
        cout << result % 1000000007;

    return 0;
}