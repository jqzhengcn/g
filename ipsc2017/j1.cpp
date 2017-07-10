#include <cstdio>
#include <cstring>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include <random>
#include <algorithm>
#include <string>
#include <bitset>
#include <regex>
using namespace std;

int main() {
    int cases;
    cin >> cases;
    while(cases--) {
        int n;
        cin >> n;
        cout << n-1 <<endl;
        for (int i =0; i < n-1; ++i) {
            cout << 0 << " "<< i << endl;
        }
    }
    return 0;
}