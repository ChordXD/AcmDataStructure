#include <iostream>
#include <cmath>
using namespace std;

const int maxnode = 1<<19;
const int maxn = 2e6+10;

struct Node{
    int l, r;
    int value;
}node[maxnode];

int father[maxn];
void buildTree(int i, int l, int r){
    node[i].l = l;
    node[i].r = r;
    node[i].value = 0;
    if(l == r){
        father[l] = i;
        return;
    }
    buildTree(i<<1, l, (int)(floor(l+r)/2.0));
    buildTree((i<<1)+1, (int)(floor(l+r)/2.0)+1, r);
}

void updateTree(int ri){
    if(ri == 1){
        return;
    }
    int fi = ri / 2;
    int a = node[fi<<1].value;
    int b = node[(fi<<1)+1].value;
    node[fi].value = max(a, b);
    updateTree(ri/2);
}

int Maxx;

void query(int i, int l, int r){
    if(node[i].l == l && node[i].r == r){
        Maxx = max(Maxx, node[i].value);
        return;
    }
    i = i<<1;
    if(l <= node[i].r){
        if(r <= node[i].r){
            query(i, l, r);
        }else{
            query(i, l, node[i].r);
        }
    }
    i++;
    if(r >= node[i].l){
        if(l >= node[i].l){
            query(i, l, r);
        }else{
            query(i, node[i].l, r);
        }
    }
}

int main(){
    int n, m, ss;
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        buildTree(1, 1, n);
        for(int i = 1; i <= n; i++){
            cin >> ss;
            node[father[i]].value = ss;
            updateTree(father[i]);
        }
        char op;
        int a, b;
        while (m--) {
            cin >> op >> a >> b;
            if(op == 'Q'){
                Maxx = 0;
                query(1, a, b);
                cout << Maxx << endl;
            }else{
                node[father[a]].value = b;
                updateTree(father[a]);
            }
        }
    }
    return 0;
}

