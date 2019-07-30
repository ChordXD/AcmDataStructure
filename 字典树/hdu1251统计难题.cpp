#include <iostream>
#include <cmath>
#include <stack>
#include <queue>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
const int maxn = 2e6 + 10;
char s[maxn];

int trie[maxn][30];
int total = 0;
int book[maxn] = {0};
int len;


void insert(){
    int root = 0;
    int id;
    for(int i = 0; i < len; i++){
        id = s[i] - 'a';
        if(trie[root][id] == 0){
            trie[root][id] = ++total;
        }
        root = trie[root][id];
        book[root]++;
    }
}

int find(){
    int root = 0;
    int id;
    for(int i = 0; i < len; i++){
        id = s[i] - 'a';
        if(trie[root][id] == 0){
            return 0;
        }
        root = trie[root][id];
    }
    return book[root];
}

int main(){
    while (gets(s)) {
        if(s[0] == NULL){
            break;
        }
        len = strlen(s);
        insert();
    }
    while (gets(s)) {
        len = strlen(s);
        cout << find() << endl;
    }
    return 0;
}

