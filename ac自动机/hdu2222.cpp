#include<stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int maxn = 5e5+10;

struct Node {
    int cnt;
    Node *fail;
    Node *next[26];
}*que[maxn];
char s[1000010];
char keyword[55];
int head, tail;
Node *root;

void init_node(Node *root){
    root->cnt = 0;
    root->fail = nullptr;
    for(int i = 0; i < 26; i++){
        root->next[i] = nullptr;
    }
}

void build_trie(char *keyword){
    Node *p, *q;
    int i, v;
    int len = strlen(keyword);
    for(i = 0, p = root; i < len; i++){
        v = keyword[i] - 'a';
        if(p->next[v] == nullptr){
            q = (struct Node*)malloc(sizeof(Node));
            init_node(q);
            p->next[v] = q;
        }
        p = p->next[v];
    }
    p->cnt++;
}

void build_ac(Node *root){
    head = 0;
    tail = 0;
    que[head++] = root;
    while (head != tail) {
        Node *p = nullptr;
        Node *temp = que[tail++];
        for(int i = 0; i < 26; i++){
            if(temp->next[i] != nullptr){
                if(temp == root){
                    temp->next[i]->fail = root;
                }else{
                    p = temp->fail;
                    while (p != nullptr) {
                        if(p->next[i] != nullptr){
                            temp->next[i]->fail = p->next[i];
                            break;
                        }
                        p = p->fail;
                    }
                    if(p == nullptr){
                        temp->next[i]->fail = root;
                    }
                }
                que[head++] = temp->next[i];
            }
            
        }
    }
}


int query(Node *root){
    int v, res = 0;
    Node *p = root;
    int len = strlen(s);
    for(int i = 0; i < len; i++){
        v = s[i] - 'a';
        while (p->next[v] == nullptr && p != root) {
            p = p->fail;
        }
        p = p->next[v];
        if(p == nullptr) p = root;
        Node *temp = p;
        while (temp != root) {
            if(temp->cnt >= 0){
                res += temp->cnt;
                temp->cnt = -1;
            }else{
                break;
            }
            temp = temp->fail;
        }
    }
    return res;
}



int main(){
    int t, n;
    scanf("%d", &t);
    while (t--) {
        root = (struct Node*)malloc(sizeof(Node));
        init_node(root);
        scanf("%d", &n);
        for(int i = 0; i < n; i++){
            scanf("%s", keyword);
            build_trie(keyword);
        }
        build_ac(root);
        scanf("%s", s);
        printf("%d\n", query(root));
    }
    return 0;
}
