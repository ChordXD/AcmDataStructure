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
int x, y, k;
int root[maxn];
int a[maxn];

vector<int> v;

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


int query(int l, int r, int x, int y, int k){
    if(l == r) return l;
    int mid = (l+r)>>1;
    int sum = hjt[hjt[y].l].sum - hjt[hjt[x].l].sum;
    if(sum >= k){
        return query(l, mid, hjt[x].l, hjt[y].l, k);
    }else{
        return query(mid+1, r, hjt[x].r, hjt[y].r, k-sum);
    }
}


int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    
    for(int i = 1; i <= n; i++){
        update(1, n, root[i], root[i-1], getid(a[i]));
    }
    
    for(int i = 1; i <= m; i++){
        scanf("%d%d%d",&x, &y, &k);
        printf("%d\n",v[query(1, n, root[x-1], root[y], k)-1]);
    }
}

