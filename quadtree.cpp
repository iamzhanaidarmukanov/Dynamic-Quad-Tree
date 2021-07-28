#include <iostream>
#include <stack>
using namespace std;

int main() {

    int T;
    cin >> T;

    while(T--) {

        int k;
        cin >> k;

        int n = 1;
        for (int i = 0; i <= k; ++i) {
            n *= 2;
        }
        
        int matrix[1025][1025];

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cin >> matrix[i][j];
            }
        }

        int m;
        cin >> m;
        
        for (int i = 0, r, c; i < m; ++i) {
            cin >> r >> c;
        }

    }

    return 0;
}