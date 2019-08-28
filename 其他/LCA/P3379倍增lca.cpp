#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#define ll long long
const int maxn = 5e5 + 10;
const int maxbit = 30;
int n, m, s;
vector<int> G[maxn];
int deep[maxn];
int lg[maxn];
int father[maxn][maxbit];

void dfs(int nowp, int fa){
    deep[nowp] = deep[fa] + 1;
    father[nowp][0] = fa;
    for(int j = 1; j <= lg[deep[nowp]]+1; j++){
        father[nowp][j] = father[father[nowp][j-1]][j-1];
    }
    
    for(int i = 0; i < G[nowp].size(); i++){
        if(G[nowp][i] != fa){
            dfs(G[nowp][i], nowp);
        }
    }
}

int LCA(int u, int v){
    if(deep[u] < deep[v]){
        swap(u, v);
    }
    
    while (deep[u] != deep[v]) {
        u = father[u][lg[deep[u] - deep[v]]];
    }
    
    if(u == v){
        return u;
    }
    
    for(int i = lg[deep[u]]; i >= 0; i--){
        if(father[u][i] != father[v][i]){
            u = father[u][i];
            v = father[v][i];
        }
    }
    return father[u][0];
}

int main(){
    
    lg[0] = -1;
    for(int i = 1; i <= maxn; i++){
        lg[i] = lg[i>>1] + 1;
    }
    
    cin >> n >> m >> s;
    int x, y;
    for(int i = 1; i <= n - 1; i++){
        scanf("%d%d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(s, 0);
    while (m--) {
        scanf("%d%d", &x, &y);
        printf("%d\n", LCA(x, y));
    }
    return 0;
}

