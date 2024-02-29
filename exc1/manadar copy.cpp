#include <iostream>
#include <set>
#include <vector>
using namespace std;

int elementExists(int x, const multiset<long>& array, vector<bool>& flag, int m, long& existings) {
    for (auto it = array.lower_bound(x) ; *it == x && it != array.end() ; it++ ) {
        int index = distance(array.begin(), it);
        if (!flag[index]) {
            flag[index] = true;
            existings += x;
            return index;
        }
    }
    return -1;
}

long calculateCost(const multiset<long>& array1, const multiset<long>& array2, int n, int m, long sumM) {
    long result = 0;
    long existings = 0;
    vector<bool> flag(m, false);

    for (int x : array1) {
        if (elementExists(x, array2, flag, m, existings) != -1)
            continue;
        else
            result += x;
    }

    result += sumM - existings;
    return result;
}

int main() {
    int n, m;
    long sumM = 0;
    cin >> n;
    cin >> m;

    // Get the element values for the first array from stdin
    multiset<long> array1;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        array1.insert(num);
    }

    multiset<long> array2;
    for (int i = 0; i < m; ++i) {
        int num;
        cin >> num;
        array2.insert(num);
        sumM += num;
    }

    cout << calculateCost(array1, array2, n, m, sumM);

    return 0;
}