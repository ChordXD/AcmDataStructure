// o2优化开
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
const int maxm = 1e5+10;
int n, m, r, mod;
int tot, head[maxn];
int v[maxn];
int fa[maxn], dep[maxn], siz[maxn], son[maxn];

//剖分
struct Edge{
    int to, next;
}edge[maxm];

void addEdge(int u, int v){
    edge[tot] = (Edge){v, head[u]};
    head[u] = tot++;
    edge[tot] = (Edge){u, head[v]};
    head[v] = tot++;
}
void dfs1(int u, int f){
    fa[u] = f;
    dep[u] = dep[f]+1;
    siz[u] = 1;
    int maxnsize = -1;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > maxnsize){
            maxnsize = siz[v];
            son[u] = v;
        }
    }
}
int tim, dfn[maxn], top[maxn], w[maxn];
void dfs2(int u, int t){
    dfn[u] = ++tim;
    top[u] = t;
    w[tim] = v[u];
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int i = head[u];  ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}
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

void modifyChain(int x, int y, int z){
    z %= mod;
    while (top[x] != top[y]){
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        modify(dfn[top[x]], dfn[x], z);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    modify(dfn[x], dfn[y], z);
}

int queryChain(int x, int y){
    int ret = 0;
    while (top[x] != top[y]){
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ret += query(dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    ret += query(dfn[x], dfn[y]);
    return ret % mod;
}

void modifySon(int x, int z){
    modify(dfn[x], dfn[x]+siz[x]-1, z);
}

int querySon(int x){
    return query(dfn[x], dfn[x]+siz[x]-1);
}

int main(){
    int x, y, z, opt;
    memset(head, -1, sizeof head);
    //1xyz 表示将树从x到y结点最短路径上所有节点的值都加上z
    //2xy  表示求树从x到y结点最短路径上所有节点的值之和
    //3xz  表示将以x为根节点的子树内所有节点值都加上z
    //4x   表示求以x为根节点的子树内所有节点值之和
    n=read(); m=read(); r=read(); mod=read();
    for(int i = 1; i <= n; i++){
        v[i]=read();
    }
    for(int i = 1; i <= n-1; i++){
        x=read(); y=read();
        addEdge(x, y);
    }
    dfs1(r, r);
    dfs2(r, r);
    build(1, n);
    while(m--){
        opt=read();
        if(opt == 1){
            x=read(); y=read(); z=read();
            modifyChain(x, y, z);
        }else if(opt == 2){
            x=read(); y=read();
            printf("%d\n", queryChain(x, y));
        }else if(opt == 3){
            x=read(); z=read();
            modifySon(x, z);
        }else{
            x=read();
            printf("%d\n", querySon(x));
        }
    }
}
