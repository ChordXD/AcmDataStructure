
const int maxn = 2e5+10;

struct Node{
    int l, r, val;
}hjt[maxn*40*2];

int cnt, n, m, tot;
int rootfa[maxn], rootdep[maxn];

void build(int l, int r, int &now){
    now = ++cnt;
    if(l == r){
        hjt[now].val = ++tot;
        return;
    }
    int m = (l+r)>>1;
    build(l, m, hjt[now].l);
    build(m+1, r, hjt[now].r);
}
void modify(int l, int r, int ver, int &now, int pos, int val){
    hjt[now=++cnt] = hjt[ver];
    if(l == r){
        hjt[now].val = val;
        return;
    }
    int m = (l+r)>>1;
    if(pos <= m){
        modify(l, m, hjt[ver].l, hjt[now].l, pos, val);
    }else{
        modify(m+1, r, hjt[ver].r, hjt[now].r, pos, val);
    }
}
int query(int l, int r, int now, int pos){
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
int find(int ver, int x){
    int fx = query(1, n, rootfa[ver], x);
    return fx==x?fx:find(ver, fx);
}
void merge(int ver, int x, int y){
    x = find(ver-1, x);
    y = find(ver-1, y);
    if(x == y){
        rootfa[ver] = rootfa[ver-1];
        rootdep[ver] = rootdep[ver-1];
    }else{
        int depx = query(1, n, rootdep[ver-1], x);
        int depy = query(1, n, rootdep[ver-1], y);

        if(depx < depy){
            modify(1, n, rootfa[ver-1], rootfa[ver], x, y);
            rootdep[ver] = rootdep[ver-1];
        }else if(depx > depy){
            modify(1, n, rootfa[ver-1], rootfa[ver], y, x);
            rootdep[ver] = rootdep[ver-1];
        }else{
            modify(1, n, rootfa[ver-1], rootfa[ver], x, y);
            modify(1, n, rootdep[ver-1], rootdep[ver], y, depy+1);
        }
    }
}

int main(){
    scanf("%d%d", &n, &m);
    build(1, n, rootfa[0]);
    for(int ver = 1; ver <= m; ver++){
        int opt, x, y;
        scanf("%d", &opt);
        if(opt == 1){
            scanf("%d%d", &x, &y);
            merge(ver, x, y);
        }else if(opt == 2){
            scanf("%d", &x);
            rootfa[ver] = rootfa[x];
            rootdep[ver] = rootdep[x];
        }else{
            scanf("%d%d", &x, &y);
            rootfa[ver] = rootfa[ver-1];
            rootdep[ver] = rootdep[ver-1];
            int fx = find(ver, x);
            int fy = find(ver, y);
            printf("%d", fx==fy?1:0);
        }
    }
    return 0;
}
