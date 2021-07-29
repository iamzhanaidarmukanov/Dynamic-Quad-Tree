////
////  Created by Zhanaidar Mukanov
////  Copyright © 2021 Zhanaidar Mukanov. All rights reserved.
////

#include <iostream>
using namespace std;

char matrix[1025][1025];
int k, n;

struct Node
{
    int answer;
    int sum;
    int level;
    Node *ul, *ur, *dl, *dr;
    Node()
    {
        answer = sum = level = 0;
        ul = ur = dl = dr = NULL;
    }
};

Node *build(int l, int r, int u, int d, int lvl)
{
    Node *answer = new Node();

    answer->answer = 1;
    answer->level = lvl;

    if (l == r)
    {
        answer->sum = matrix[u][r] - '0';
    }
    else
    {
        int m1 = (l + r) / 2;
        int m2 = (u + d) / 2;
        answer->ul = build(l, m1, u, m2, lvl - 1);
        answer->ur = build(m1 + 1, r, u, m2, lvl - 1);
        answer->dl = build(l, m1, m2 + 1, d, lvl - 1);
        answer->dr = build(m1 + 1, r, m2 + 1, d, lvl - 1);

        answer->sum += answer->ul->sum;
        answer->sum += answer->ur->sum;
        answer->sum += answer->dl->sum;
        answer->sum += answer->dr->sum;

        if (answer->sum == 0 || answer->sum == (1 << answer->level) * (1 << answer->level)) {
            answer->answer = 1;
        } else {
            answer->answer = 1;
            answer->answer += answer->ul->answer;
            answer->answer += answer->ur->answer;
            answer->answer += answer->dl->answer;
            answer->answer += answer->dr->answer;
        }
    }
    return answer;
}

void update(Node *answer, int x, int y, int l, int r, int u, int d) {
    answer->answer = 1;
    if (l == r) {
        answer->sum ^= 1;
    } else {
        int m1 = (l + r) / 2;
        int m2 = (u + d) / 2;

        if (x <= m1 && y <= m2)
            update(answer->ul, x, y, l, m1, u, m2);
        else if (x <= m1 && y > m2)
            update(answer->ur, x, y, m1 + 1, r, u, m2);
        else if (x > m1 && y <= m2)
            update(answer->dl, x, y, l, m1, m2 + 1, d);
        else if (x > m1 && y > m2)
            update(answer->dr, x, y, m1 + 1, r, m2 + 1, d);

        answer->sum = 0;
        answer->sum += answer->ul->sum;
        answer->sum += answer->ur->sum;
        answer->sum += answer->dl->sum;
        answer->sum += answer->dr->sum;

        if (answer->sum == 0 || answer->sum == (1 << answer->level) * (1 << answer->level)) {
            answer->answer = 1;
        }
        else {
            answer->answer = 1;
            answer->answer += answer->ul->answer;
            answer->answer += answer->ur->answer;
            answer->answer += answer->dl->answer;
            answer->answer += answer->dr->answer;
        }
    }
}

void clean(Node *ptr) {
    if (ptr == NULL)
        return;

    clean(ptr->ul);
    clean(ptr->ur);
    clean(ptr->dl);
    clean(ptr->dr);
    delete ptr;
}

int main() {

    int T;
    cin >> T;

    while (T--) {
        cin >> k;
        int n = 1;
        for (int i = 0; i < k; i++) {
            n *= 2;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
            {
                cin >> matrix[i][j];
            }
        }

        auto root = build(1, n, 1, n, k);

        int q;
        cin >> q;
        for (int it = 0, r, c; it < q; it++) {
            cin >> r >> c;
            update(root, c, r, 1, n, 1, n);
            cout << root->answer << endl;
        }
        clean(root);
    }
    return 0;
}