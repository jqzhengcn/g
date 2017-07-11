#include <iostream>
#include <queue>
using namespace std;

int a[102400], b[102400];
int n, e;

int main() {
    int as;
    cin >> as;
    while(as--) {
        cin >> n;
        for (int i = 0; i < n-1; ++i) {
            cin >> a[i];
        }
        long ret = 1;
        long x = 1;
        for (int i = 0; i < n - 1; ++i) {
            x *= a[i];
            ret += x;
        }
        cout << ret <<endl;
    }
    return 0;
}