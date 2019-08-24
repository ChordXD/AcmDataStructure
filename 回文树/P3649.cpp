#include<stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#define ll long long
using namespace std;
const int N = 3e5+10;

struct PalidromicTree {
    int nxt[N][30], fail[N], cnt[N];
    int num[N], len[N], s[N];
    int last, n, p;
  
    int newnode(int l){
        memset(nxt[p], 0, sizeof(nxt[p]));
        cnt[p] = num[p] = 0;
        len[p] = l;
        return p++;
    }
    
    void init(){
        p = 0;
        newnode(-1);
        newnode(0);
        n = 0;
        last = 1;
        s[0] = -1;
        fail[1] = 0;
    }
    
    int getfail(int x){
        while (s[n - len[x] - 1] != s[n]) {
            x = fail[x];
        }
        return x;
    }
    
    void add(int c){
        c -= 'a';
        s[++n] = c;
        int cur = getfail(last);
        if(!nxt[cur][c]){
            int now = newnode(len[cur]+2);
            if(nxt[getfail(fail[cur])][c] != 0){
                fail[now] = nxt[getfail(fail[cur])][c];
            }else{
                fail[now] = 1;
            }
            nxt[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = nxt[cur][c];
        cnt[last]++;
    }
     
    ll count(){
        ll res = 0;
        for(int i = p-1; i >= 0; i--){
            cnt[fail[i]] += cnt[i];
        }
        for(int i = 0; i < p; i++){
            res = max(res, 1ll * cnt[i] * len[i]);
        }
        return res;
    }
}pam;

char str[N];

int main(){
    ios::sync_with_stdio(false);
    cin >> str;
    int len = strlen(str);
    pam.init();
    for(int i = 0; i < len; i++){
        pam.add(str[i]);
    }
    cout << pam.count() << endl;
    return 0;
}


