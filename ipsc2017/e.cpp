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


int M = 1000000009;
int bn;
int b[5000100][2];
int ret;

map<int, int> h;
typedef  map<int,int>::iterator MI;

void get_lr(int pos, MI& itl, MI& itr) {
    itr = h.upper_bound(pos);
    itl = itr;
    itl--;
    assert(pos < itr->first);
    assert(pos >= itl->first);
}
int find_height(int pos) {
    MI itl, itr;
    get_lr(pos, itl, itr);
    if (itl->first == pos) {
        return itl->second;
    }
    if (itl->second == itr->second) {
        return itl->second;
    }
    assert(abs(itl->second - itr->second) == abs(itl->first - itr->first));
    if (itl->second > itr->second) {
        // left higher
        return itr->second + (itr->first - pos);
    } else {
        // right higher
        return itl->second + (pos - itl->first);
    }
    assert(false);
}
int goleft(int pos, int op, MI itl, MI itm, MI itr) {
    assert(itm->first == pos);
    int r = 0;
    if (itl->second == itm->second) {
        // case1
        h[pos-1] = itl->second;
        r += 1;
    } else if (itl->second < itm->second) {
        // case2
        if (op == 1) {
            // case 2.1
            int llh = find_height(itl->first - 1);
            h[itl->first - 1] = llh;
            itl->second = itl->second + op;
            r += (itm->first - itl->first) * 2 +1;
        } else {
            h[itm->first -1] = itm->second + op;
            r += 1;
        }
    } else if (itl->second > itm->second) {
        if (op == 1) {
            h[itm->first - 1] = itm->second + op;
            r += 1;
        } else {
            int llh = find_height(itl->first - 1);
            h[itl->first - 1] = llh;
            itl->second = itl->second + op;
            r += (itm->first - itl->first) * 2 +1;
        }
    }
    return r;
}
int goright(int pos, int op, MI itm, MI itr) {
    assert(itm->first == pos);
    int r = 0;
    if (itr->second == itm->second) {
        // case1
        h[pos+1] = itr->second;
        r += 1;
    } else if (itr->second > itm->second) {
        // case2
        if (op == 1) {
            // case 2.1
            h[itm->first +1] = itm->second + op;
            r += 1;
        } else {
            int rrh = find_height(itr->first + 1);
            h[itr->first + 1] = rrh;
            itr->second = itr->second + op;
            r += (itr->first - itm->first) * 2 +1;
        }
    } else if (itr->second < itm->second) {
        if (op == 1) {
            int rrh = find_height(itr->first + 1);
            h[itr->first + 1] = rrh;
            itr->second = itr->second + op;
            r += (itr->first - itm->first) * 2 +1;
        } else {
            h[itm->first +1] = itm->second + op;
            r += 1;
        }
    }
    return r;
}
void compute_change(int pos, int op, int round) {
    int r = 0;
    MI itl, itr, itm;

    get_lr(pos, itl, itr);
    itm = itl;
    itl--;
    r += goleft(pos, op, itl, itm, itr);

    get_lr(pos, itl, itr);
    itm = itl;
    itl--;
    r += goright(pos, op, itm, itr);


    get_lr(pos, itl, itr);
    itm = itl;
    h[pos] = itm->second + op;

    assert(r%2 == 0);
    ret = (ret + ((long)r/2 *round%M)) % M;
}
bool shrinkonce(int pos) {
    MI itl, itr;
    get_lr(pos, itl, itr);
    MI itx, ity;
    itx = itl; ity = itr;
    for (int i = 0;i < 30 && itx != h.begin(); i++) {itx--;}
    for (int i = 0;i < 30 && ity != h.end(); i++) {ity++;}
    for (MI it = itx; it != ity; ++it) {
        if (it == h.begin()) continue;
        MI it1, it2, it3;
        it1 = it;
        it2 = it;
        it3 = it;
        it1--;
        it3++;
        if (it3 == h.end()) continue;

        int h1 = it3->second - it1->second;
        int h2 = it2->second - it1->second;
        int p1 = it3->first - it1->first;
        int p2 = it2->first - it1->first;
        if ((long)p2 * h1 == (long)p1 * h2) {
            h.erase(it2);
            return true;
        }
    }
    return false;

}
void shrink(int pos) {
    while(shrinkonce(pos));
}
void done() {
    ret = 0;
    h.clear();
    h[-1100000000] = 0;
    h[1100000000] = 0;
    for (int i = 0; i < bn; ++i) {

        int pret = ret;
        int pos = b[i][0];
        int op = b[i][1]; // 1 / -1
        //if (i%1000==0) cout << "round " << i << " : " << pos << " " << op << endl;

        int pos_h = find_height(pos);
        h[pos] = pos_h;
        compute_change(pos, op, i+1);
        shrink(pos);

/*
        for (MI it= h.begin(); it!= h.end(); it++) {
            cout << it->first << " " << it->second << endl;
        }
        cout << "RET: " << ret << "  add: " << (ret - pret)/(i+1) << endl;
*/
    }
    cout << ret << endl;
}
int main() {
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        int n;
        scanf("%d", &n);
        bn = n;
        int x, y;
        for (int i =0; i < n; ++i) {
            scanf("%d %d", &x, &y);
            b[i][0] = x;
            b[i][1] = y;
            //c[i] = x;
        }
        done();
    }
    return 0;
}