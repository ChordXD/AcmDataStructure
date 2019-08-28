//请开o2优化
#include<cstdio>
#include<cstring>
#include <vector>
#include <algorithm>
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
const int maxbit = 20;
vector<int> G[maxn];
int deep[maxn<<1];
int order[maxn<<1];
int st[maxn<<1][maxbit];
int first_list[maxn];
int n, m, s;
int lg[maxn<<1];
int father[maxn][maxbit];

int cnt = 0;
void dfs(int nowp, int dep){
    ++cnt;
    first_list[nowp] = cnt;
    order[cnt] = nowp;
    deep[cnt] = dep+1;

    for(int i = 0; i < G[nowp].size(); i++){
        int to = G[nowp][i];
        if(first_list[to] == 0){
            dfs(to, dep+1);
            ++cnt;
            order[cnt] = nowp;
            deep[cnt] = dep + 1;
        }
    }
}

void st_init(){
    for(int i = 1; i <= cnt; i++){
        st[i][0] = i;
    }
    int a, b;
    for(int j = 1; j <= lg[cnt]; j++){
        for(int i = 1; i+(1<<j)-1 <= cnt; i++){
            a = st[i][j-1];
            b = st[i+(1<<j-1)][j-1];
            if(deep[a] < deep[b]){
                st[i][j] = a;
            }else{
                st[i][j] = b;
            }
        }
    }
}

int main(){
    lg[0] = -1;
    for(int i = 1; i <= maxn*2; i++){
        lg[i] = lg[i>>1] + 1;
    }
    n=read(); m=read(); s=read();
    int x, y;
    for(int i = 1; i <= n - 1; i++){
        x=read(); y=read();
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(s, 0);
    st_init();
    while (m--) {
        x=read(); y=read();
        x = first_list[x];
        y = first_list[y];
        if(x > y) swap(x, y);
        int k = lg[y-x];
        int a, b;
        a = st[x][k];
        b = st[y-(1<<k)+1][k];
        if(deep[a] < deep[b]){
            printf("%d\n",order[a]);
        }else{
            printf("%d\n",order[b]);
        }
    }
}
