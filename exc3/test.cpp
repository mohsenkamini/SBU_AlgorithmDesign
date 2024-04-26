#include <iostream>
#include <string>
using namespace std;
int main () {
    string n;
    getline(cin, n);
    int m=0;
    for (int i=0 ; i<n.size() ;i++ )
        if (n[i]==' ')
            m++;

    cout << m;
}