#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#define ll long long
using namespace std;
inline int read() {
    char ch = getchar(); int x = 0, f = 1;
    while(ch < '0' || ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    } while('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    } return x * f;
}
const int maxn = 1e5+10;
int n, m, r, mod;
int tot, head[maxn];
int fa[maxn], dep[maxn], siz[maxn], son[maxn], w[maxn];

//segment tree
struct Node{
    int l, r, f, val;
}sgt[maxn*4];
int ls(int k){return k<<1;}
int rs(int k){return k<<1|1;}
inline void pushup(int k){
    sgt[k].val = (sgt[ls(k)].val + sgt[rs(k)].val) % mod;
}
inline void pushdown(int k){
    sgt[ls(k)].f += sgt[k].f;
    sgt[rs(k)].f += sgt[k].f;
    sgt[ls(k)].val += (sgt[ls(k)].r - sgt[ls(k)].l + 1) * sgt[k].f % mod;
    sgt[rs(k)].val += (sgt[rs(k)].r - sgt[rs(k)].l + 1) * sgt[k].f % mod;
    sgt[k].f = 0;
}
void build(int l, int r, int k = 1){
    sgt[k].l = l, sgt[k].r = r;
    if (l == r){
        sgt[k].val = w[l] % mod;
        return;
    }
    int m = (l + r) >> 1;
    build(l, m, ls(k));
    build(m + 1, r, rs(k));
    pushup(k);
}
void modify(int x, int y, int z, int k = 1){
    int l = sgt[k].l, r = sgt[k].r;
    if (x <= l && y >= r){
        sgt[k].f += z;
        sgt[k].val += (r - l + 1) * z;
        sgt[k].val %= mod;
        return;
    }
    if (sgt[k].f)
        pushdown(k);
    int m = (l + r) >> 1;
    if (x <= m)
        modify(x, y, z, ls(k));
    if (y > m)
        modify(x, y, z, rs(k));
    pushup(k);
}
int query(int x, int y, int k = 1){
    int l = sgt[k].l, r = sgt[k].r;
    if (x <= l && y >= r)
        return sgt[k].val;
    if (sgt[k].f)
        pushdown(k);
    int sum = 0, m = (l + r) >> 1;
    if (x <= m)
        sum += query(x, y, ls(k));
    if (y > m)
        sum += query(x, y, rs(k));
    return sum % mod;
}

int main(){
    int x, y, z, opt;
    memset(head, -1, sizeof head);
    n=read(); m=read(); mod=read();
    for(int i = 1; i <= n; i++){
        w[i]=read();
    }
    build(1, n);
    while (m--) {
        opt=read();
        if(opt == 1){
            x=read(); y=read(); z=read();
            modify(x, y, z);
        }
        if(opt == 2){
            x=read(); y=read();
            printf("%d\n", query(x, y));
        }
    }
}
