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
#include <cassert>
using namespace std;

int b[10000000];
int bn;
int used[10];

void gowith(int x, int t, int m) {
    if (x == t) {
        if (m) {
            b[bn++] = m;
        }
    }
    for (int i = 0; i <= 9; ++i) {
        if (x==0 && i ==0) continue;
        if (x==0 && t == 10 && i>1) continue;
        if (!used[i]) {
            used[i] = 1;
            gowith(x + 1, t, m * 10 + i);
            used[i] = 0;
        }
    }
}
void init() {
    bn = 0;
    for (int i = 1; i <= 10; ++i) {
        //cout << i << " " << bn << " go" << endl; int xx = bn;
        memset(used, 0, sizeof(used));
        gowith(0, i, 0);
        //for (int j = xx; j < xx+100 && j < bn; ++j) cout << b[j] << " "; cout << endl;
    }
}

int r[10000];
int rn;
set<int> a;
void done(int w) {
    rn = 0;
    while(w) {
        //cout << w << " | ";
        int* k = lower_bound(b, b + bn, w);
        int j = k - b;
        if (b[j] > w) j--;
        r[rn++] = b[j];
        w -= b[j];
    }
    cout << rn;
    for (int i = 0; i < rn; ++i) {
        cout << " " << r[i];
    }
    cout << endl;
}
void done2(int w) {
    if (a.find(w) != a.end()) {
        cout << 1 << " " << w << endl;
        return;
    }
    int* k = lower_bound(b, b + bn, w);
    int j = k - b;
    if (b[j] > w) j--;
    for (int i = j; i >=0; --i) {
        if (a.find(w-b[i]) != a.end()) {
            cout << 2 << " " << b[i] << " " << w-b[i] << endl;
            return;
        }
    }
    assert(false);
}
int main() {
    init();
    //cout << bn;for (int i = 0; i < 100; ++i) cout << b[i] << " "; cout << endl;
    //for (int i =0; i < 30; ++i) {cout << b[bn*i/30] << " ";} cout << endl;
    for (int i = 0; i < bn; ++i) a.insert(b[i]);
    int cases;
    cin >> cases;
    while(cases--) {
        int n;
        cin >> n;
        done2(n);
    }
    return 0;
}