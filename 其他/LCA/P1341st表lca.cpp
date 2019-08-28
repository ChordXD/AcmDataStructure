#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 100;
int n;
bool mapp[maxn][maxn];
int cnt[maxn];
bool vis[maxn][maxn];
stack<int> res;
int siz = 53;

int convert1(char c){
    if (c >= 'A' && c <= 'Z')
        return (int)c - 'A';
    return (int)c - 'a' + 26;
}
char convert2(int x){
    if (x >= 0 && x <= 25)
        return (char)x + 'A';
    return (char)(x - 26) + 'a';
}

void euler(int u){
    for(int v = 0; v < siz; v++){
        if(mapp[u][v] && !vis[u][v]){
            vis[u][v] = vis[v][u] = true;
            euler(v);
//            cout << "yes" << endl;
            res.push(v);
        }
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        char a, b;
        cin >> a >> b;
        int x = convert1(a), y = convert1(b);
        mapp[x][y] = mapp[y][x] = true;
        cnt[x]++;
        cnt[y]++;
    }
    int total = 0;//入度奇数节点
    int min1 = 1e6, min2 = 1e6;
    for(int i = 0; i < siz; i++){
        if(cnt[i]%2 == 1){
            total++;
            min1 = min(i, min1);
        }else if(cnt[i] > 0){
            min2 = min(i, min2);
        }
    }

    if(total!=2 && total!=0){
        printf("No Solution\n");
    }else{
        int fn;
        if(total==0){
            fn = min2;
        }else{
            fn = min1;
        }
        euler(fn);
        res.push(fn);
        while (!res.empty()) {
            int itop = res.top();
            res.pop();
            char cc = convert2(itop);
            printf("%c",cc);
        }
        printf("\n");
    }
    return 0;
}
