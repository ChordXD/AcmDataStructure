#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
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
const int maxn = 5e5 + 10;
const int maxbit = 30;
int n, m, s;
vector<int> G[maxn];
vector<int> Q[maxn];
bool vis[maxn];
int father[maxn];

struct qnode {
    int x, y;
    int lca;
}query[maxn];

int find(int x){
    if(father[x] == x){
        return x;
    }else{
        return father[x] = find(father[x]);
    }
}

void tarjan(int u){
    vis[u] = true;
    for(auto qid : Q[u]){
        if(query[qid].x == u){
            if(vis[query[qid].y]){
                query[qid].lca = find(query[qid].y);
            }
        }else{
            if(vis[query[qid].x]){
                query[qid].lca = find(query[qid].x);
            }
        }
    }
    for(auto v : G[u]){
        if(vis[v]){
            continue;
        }
        tarjan(v);
        father[v] = u;
    }
}

void init(){
    for(int i = 1; i <= n; i++){
        father[i] = i;
    }
}

int main(){
    n=read(); m=read(); s=read();
    init();
    int x, y;
    for(int i = 1; i <= n - 1; i++){
        x=read(); y=read();
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 1; i <= m; i++){
        query[i].x=read();
        query[i].y=read();
        Q[query[i].x].push_back(i);
        Q[query[i].y].push_back(i);
    }
    tarjan(s);
    for(int i = 1; i <= m; i++){
        printf("%d\n", query[i].lca);
    }
    return 0;
}

