#include <iostream>
#include <bits/stdc++.h> 
#include <vector>
#include<unistd.h>  
#include <sys/time.h>
#include <chrono>
#include <ctime>             
using namespace std;
using std::cout;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;
using std::chrono::system_clock;
volatile int iterations=0;
volatile int iterations2=0,iterationsb1=0,iterationsb2=0;
void printVector (vector<int>& array) {
    for (int i=0; i < array.size() ; i++) {
        cout << array[i];
        //if (array[i]==-1)
        //    cout << " ";
    }
}
  auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  //cout << "milliseconds since epoch: " << millisec_since_epoch << endl;

int findClosestM(string str, int index, vector<int>& truthArray,int size) {
    //cout << index << endl;
    //sleep(1);
    for (int i=index ; i < size ; i++) {
        iterations++;
        //cout << "i: " << i << " stri: " << str[i] << endl;
        //millisec_since_epoch = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
        //    cout << "b iteration: " << iterations << " nanoseconds since epoch: " << millisec_since_epoch << endl;
        switch (str[i]) {
            case 'b':
                iterationsb2++;
                i=findClosestM(str,i+1,truthArray,size);
                if (i==-1) {
                    truthArray[index-1]=-1;
                    return -1;
                } else i--;
                break;
            case 'm':
                //for (int j=index-1 ; j <= i ; j++)
                //    truthArray[j]=1;
                    truthArray[i]=1;
                    truthArray[index-1]=1;
                //cout << "m: " << i << endl;
                return i+1;
                break;
            default:
                //cout << "hello! " << i << " " << str.length() << endl;
                break;
        }
    }
    //cout << "-1: " << index-1 << endl;
    truthArray[index-1]=-1;
    return -1;
}

int main() {


    string str;
    cin >> str;
    int size=str.size();
    vector<int> truthArray(size);
    for (int i=0 ; i < size && i>=0 ; i++) {
        iterations2++;
        switch(str[i]) {
            case 'b':
                iterationsb1++;
                i=findClosestM(str,i+1,truthArray,size);
                i--;
                break;
            case 'm':
                truthArray[i]=-1;
                break;
            default:
                break;
        }
    }
    //for (int i=0 ; i< str.length() ; i++)31696-
    //    cout << str << endl;
    //cout << endl;
    //printVector(truthArray);
    //cout << endl;
    int strike=0,max=0,zeroCount=0;
    bool flag=false;
    for (int i=0 ; i< size ; i++) {
        if (truthArray[i]==1) {
            strike++;
            flag=true;
            zeroCount=0;
        } else if (truthArray[i]==-1 || i == size-1 ){
            strike-=zeroCount;
            if (max<strike)
                max=strike;
            strike=0;
            flag=false;
        } else if (flag==true) {
            strike++;
            zeroCount++;
        }
        if (i == size-1 && max<strike) {
            max=strike;
        }
    }
    cout << max << endl << "str size: " << size << endl << "iterations: " << iterations << endl
        << "iterationsb1: " << iterationsb1 << endl 
        << "iterationsb2: " << iterationsb2 << endl 
        << "iterations2: " << iterations2 << endl ;

    return 0;
}