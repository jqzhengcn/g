#include <iostream>
#include <queue>
using namespace std;

int a[102400], b[102400];
int n, e;

int main() {
    int as;
    cin >> as;
    while(as--) {
        cin >> n >> e;
        memset(a, 0, sizeof(a));
        int t = 1;
        for (int i =0; i < e; ++i) {
            cin >> b[i];
            a[b[i]] = t++;
        }
        int ret = -1;
        for (int i = n; i >= 1 && ret == -1; --i) {
            if (a[i] == 0) {
                ret = i;
            }
        }
        if (ret != -1) {
            cout << ret << endl;
            continue;
        }
        int reti = 1;
        for (int i = 1; i <= n; ++i) {
            //cout << a[i] << " ";
            if (a[i] < a[reti]) reti = i;
        }
        cout << reti << endl;
    }
    return 0;
}