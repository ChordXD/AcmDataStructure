#include<iostream>
#include<vector>
#include<queue>
#include<cstdio>
#include<cstring>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

const int maxn = 1e6 + 10;

int n, m;
int a[maxn];

struct Node{
    int l, r, val;
}hjt[maxn*40];

int cnt, root[maxn];

void build(int l, int r, int &now){
    now = ++cnt;
    if(l == r){
        hjt[now].val = a[l];
        return;
    }
    int m = (l+r)>>1;
    build(l, m, hjt[now].l);
    build(m+1, r, hjt[now].r);
}

void modify(int l, int r, int verison, int &now, int &pos, int &num){
    now = ++cnt;
    hjt[now] = hjt[verison];
    if(l == r){
        hjt[now].val = num;
        return;
    }
    int m = (l+r)>>1;
    if(pos <= m){
        modify(l, m, hjt[verison].l, hjt[now].l, pos, num);
    }else{
        modify(m+1, r, hjt[verison].r, hjt[now].r, pos, num);
    }
}

int query(int l, int r, int now, int &pos){
    if(l == r){
        return hjt[now].val;
    }
    int m = (l+r)>>1;
    if(pos <= m){
        return query(l, m, hjt[now].l, pos);
    }else{
        return query(m+1, r, hjt[now].r, pos);
    }
}

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    build(1, n, root[0]);
    
    
    int verison, op;
    for(int i = 1; i <= m; i++){
        cin >> verison >> op;
        if(op == 1){
            int x, y;
            scanf("%d%d", &x, &y);
            modify(1, n, root[verison], root[i], x, y);
        }
        if(op == 2){
            int x;
            scanf("%d", &x);
            printf("%d\n", query(1, n, root[verison], x));
            root[i] = root[verison];
        }
    }
}


