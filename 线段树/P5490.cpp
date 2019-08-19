#include <iostream>
#include<cstdio>
#include <cstdlib>
#include <algorithm>

#define ll long long
#define ull unsigned long long
using namespace std;
const int maxn = 2e5 + 10;

struct L {
    int x, y1, y2, state;

    bool operator<(const L &oth) const { return x < oth.x; }
} line[maxn];

struct Node {
    int l, r, cover;
    ll len;
} sgt[maxn << 3];

int v[maxn];

inline int ls(int k) { return k << 1; }

inline int rs(int k) { return k << 1 | 1; }


void pushup(int k) {
    if (sgt[k].cover) {
        sgt[k].len = sgt[k].r - sgt[k].l;
    } else {
        sgt[k].len = sgt[ls(k)].len + sgt[rs(k)].len;
    }
}

void buildtree(int l, int r, int k = 1) {
    sgt[k].l = v[l];
    sgt[k].r = v[r];
    if (r - l <= 1) return;
    int m = (l + r) >> 1;
    buildtree(l, m, ls(k));
    buildtree(m, r, rs(k));
}

void modify(int x, int y, int z, int k = 1) {
    int l = sgt[k].l;
    int r = sgt[k].r;
    if (x <= l && y >= r) {
        sgt[k].cover += z;
        pushup(k);
        return;
    }
    if (x < sgt[ls(k)].r) modify(x, y, z, ls(k));
    if (y > sgt[rs(k)].l) modify(x, y, z, rs(k));
    pushup(k);
}

int main() {
    int n;
    scanf("%d", &n);
    int a, b, c, d;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        v[i] = b, v[n + i] = d;
        line[i] = (L) {a, b, d, 1};
        line[n + i] = (L) {c, b, d, -1};
    }
    sort(v + 1, v + 1 + (n << 1));
    sort(line + 1, line + 1 + (n << 1));
    buildtree(1, n << 1);
    ull res = 0;
    for (int i = 1; i <= (n << 1); i++) {
        res += sgt[1].len * (line[i].x - line[i - 1].x);
        modify(line[i].y1, line[i].y2, line[i].state);
    }
    cout << res << endl;
}


