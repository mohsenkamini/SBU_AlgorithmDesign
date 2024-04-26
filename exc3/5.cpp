#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
void printVector(const vector<T>& vec) {
    // Print vector elements separated by space
    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";
    cout << endl;
}
int isPathValid(const vector<int>& oddPath,const vector<int>& evenPath) {
    /* return meaning:
        -1: neither is fine
         0: only even is fine
         1: only odd is fine
         2: both is fine
    */
    bool resultOdd=0,resultEven=0;
    int pointer=0;
    for (int i=0,pointer=0 ; i<oddPath.size() ; i++) {
        if (i%2==0)
            pointer=evenPath[pointer];
        else 
            pointer=oddPath[pointer];
        //if (pointer>oddPath.size()-1)
        //    cout << "some " << pointer << " " << oddPath.size();
        if (pointer==oddPath.size()-1) {
            resultEven=1;
            break;
        }
        if (pointer == 0) {
            resultEven=0;
            break;
        }
    }
    for (int i=0, pointer=0 ; i<oddPath.size() ; i++) {
        if (i%2==1)
            pointer=evenPath[pointer];
        else 
            pointer=oddPath[pointer];
        if (pointer==oddPath.size()-1) {
            resultOdd=1;
            break;
        }
        if (pointer == 0) {
            resultOdd=0;
            break;
        }
    }
    if (resultEven && resultOdd)
        return 2;
    else if (!resultEven && resultOdd)
        return 1;
    else if (resultEven && !resultOdd)
        return 0;
    else return -1;
}

int main() {
    int n;
    cin >> n;

    vector<int> jumps(n), even(n,n), odd(n,n);
    vector<bool>          evenValid(n,false), oddValid(n,false);
    vector<int>            evenPath(n,0), oddPath(n,0);
    for (int i=0; i < n ; i++) {
        cin >> jumps[i];
    }
    //construct the dp
    even[n-1]=0;
    odd[n-1]=0;
    evenValid[n-1]=true;
    oddValid[n-1]=true;
    for (int i=n-2; i>=0 ; i--) {
        //cout << "i: "<< i << " jumps[i]: " << jumps[i] <<endl;
        if (jumps[i]==0){
            oddValid[i]=false;
            evenValid[i]=false;
        } else for (int j=1 ; j<=jumps[i]; j++) {
            if (j%2==1) {
                if (evenValid[i+j] && odd[i]>even[i+j]+1 && i+j <n) {
                    odd[i]=even[i+j]+1;
                    oddValid[i]=true;
                    oddPath[i]=i+j;
                }
            } else {
                if (oddValid[i+j] && even[i]>odd[i+j]+1 && i+j <n) {
                    even[i]=odd[i+j]+1;
                    evenValid[i]=true;
                    evenPath[i]=i+j;
                }
            }

        }
    }
    /*
    cout << "jumps:     ";
    printVector(jumps);
    cout << "even:      ";
    printVector(even);
    cout << "odd:       ";
    printVector(odd);
/*    cout << "evenValid: ";
    printVector(evenValid);
    cout << "oddValid:  ";
    printVector(oddValid);
    cout << "evenPath:  ";
    printVector(evenPath);
    cout << "oddPath:   ";
    printVector(oddPath);
*/
    switch (isPathValid(oddPath,evenPath)) {
        case -1:
            cout << -1;
            break;
        case 0:
            cout << even[0];
            break;
        case 1:
            cout << odd[0];
            break;
        case 2:
            cout << min(odd[0],even[0]);
            break;
        default:
            cout <<"unexpected";
            break;
    }

}