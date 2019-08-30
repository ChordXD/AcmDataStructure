#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

const int maxn = 1e5+10;

struct Node{
    int l, r, sum;
}hjt[maxn*40];

int cnt, n, m;
int x, y, k, w;
int root[maxn];
int a[maxn];
vector<int> v;
int lg[maxn];

struct Edge {
    int to, w;
};
vector<Edge> G[maxn];
int deep[maxn];
int father[maxn][30];

int getid(int x){
    return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}


void update(int l, int r, int &cur, int pre, int pos){
    hjt[++cnt] = hjt[pre];
    hjt[cnt].sum++;
    cur = cnt;
    if(l == r) return;
    int mid = (l+r)>>1;
    if(mid >= pos){
        update(l, mid, hjt[cur].l, hjt[pre].l, pos);
    }else{
        update(mid+1, r, hjt[cur].r, hjt[pre].r, pos);
    }
}


//int query(int l, int r, int x, int y, int k){
//    if(l == r) return l;
//    int mid = (l+r)>>1;
//    int sum = hjt[hjt[y].l].sum - hjt[hjt[x].l].sum;
//    if(sum >= k){
//        return query(l, mid, hjt[x].l, hjt[y].l, k);
//    }else{
//        return query(mid+1, r, hjt[x].r, hjt[y].r, k-sum);
//    }
//}

int query(int l,int r,int x,int y,int k)
{
    if(r<=k) return hjt[y].sum-hjt[x].sum;
    int mid = (l+r)/2;
    if(k<=mid) return query(l,mid,hjt[x].l,hjt[y].l,k);
    else return hjt[hjt[y].l].sum-hjt[hjt[x].l].sum+query(mid+1,r,hjt[x].r,hjt[y].r,k);
}

void dfs(int nowp, int fa){
    deep[nowp] = deep[fa] + 1;
    father[nowp][0] = fa;
    for(int j = 1; j <= lg[deep[nowp]]+1; j++){
        father[nowp][j] = father[father[nowp][j-1]][j-1];
    }
    
    for(int i=0;i<G[nowp].size();i++){
        int t = G[nowp][i].to;
        if(t==fa) continue;
        update(1,n,root[t],root[nowp],getid(G[nowp][i].w));
        dfs(t,nowp);
    }
}
int lca(int u, int v){
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
    for(int i = 1; i <= maxn; i++) lg[i] = lg[i>>1] + 1;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n-1; i++){
        scanf("%d%d%d", &x, &y, &w);
        G[x].push_back({y,w});
        G[y].push_back({x,w});
        v.push_back(w);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    dfs(1,0);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&k);
        int h = upper_bound(v.begin(),v.end(),k)-v.begin();
        if(h) printf("%d\n",query(1,n,root[1],root[x],h)+query(1,n,root[1],root[y],h)-2*query(1,n,root[1],root[lca(x,y)],h));
        else printf("0\n");
    }
}

