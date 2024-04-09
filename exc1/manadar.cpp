#include <iostream>
#include <vector>
#include <bits/stdc++.h> 
#include<unistd.h>               
using namespace std;

int binarySearch(vector<long>& array, int low, int high, int n, vector<bool>* flag) {
    while (low <= high ) {
        int mid = low + (high - low) / 2;
        if (n == array[mid]){
            if ((*flag)[mid]==false) {
                (*flag)[mid]=true;
                return mid;
            } else {
                int tempMid=mid;
                while (n == array[--tempMid]) {
                    if ((*flag)[tempMid]==false) {
                        (*flag)[tempMid]=true;
                        return tempMid;
                    }
                }
                while (n == array[++mid]) {
                    if ((*flag)[mid]==false) {
                        (*flag)[mid]=true;
                        return mid;
                    }
                }
                return -1;
            }
        }
        if (n > array[mid]){
            low = mid + 1;
        }
        if (n < array[mid]){
            high = mid - 1;
        }
        //cout << n << " " << low << " " << mid << " " << high << endl;
        //sleep( 1 ); 
    }
  return -1;
}

long elementExists(long x,vector<long>* array, vector<bool>* flag, long n) {
    for (int i=0 ; i < n ; i++) {
        if (x==(*array)[i] && (*flag)[i]==false)
        {
            (*flag)[i]=true;
            return i;
        }
    }
    return -1;
}

long calculateCost(vector<long> array1, vector<long> array2,long n, long m) {
    long result=0,index=-1;
    vector<bool> flag(m);
    
    for (int i=0 ; i < n ; i++) {
        //if (elementExists(array1[i],&array2,&flag,m)!=-1)

        if (binarySearch(array2,0,m,array1[i],&flag)!=-1)
            continue;
        else
            result+=array1[i];
    }
    //for (long i = 0; i < m; ++i) {
    //    std::cout << flag[i] << " ";
    //}
    //std::cout << std::endl;
    for (int i=0 ; i < m ; i++) {
        if (flag[i]==true)
            continue;
        else
            result+=array2[i];
    }
    return result;
}

int main() {
    int n, m;
    cin >> n;
    cin >> m;

    // Get the element values for the first array from stdin
    vector<long> array1(n);
    for (int i = 0; i < n; ++i) {
        cin >> array1[i];
    }
    vector<long> array2(m);
    for (int i = 0; i < m; ++i) {
        cin >> array2[i];
    }

    sort(array1.begin(), array1.end());
    sort(array2.begin(), array2.end());
    /*cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << array1[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < m; ++i) {
        cout << array2[i] << " ";
    }
    cout << endl;*/
    cout <<  calculateCost(array1, array2, n, m);

    return 0;
}