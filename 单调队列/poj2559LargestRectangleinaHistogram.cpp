#include <iostream>
#include <cstdio>
using namespace std;
#define ll long long
const int maxn = 1e5+10;

struct Rec {
    int height;
    int cnt;
};

Rec stk[maxn];

int main(){
    int n;
    while(cin >> n && n){
        ll res = 0, top = 0, tot = 0, temp = 0;
        for(int i = 0; i < n; i++){
            int h;
            cin >> h;
            temp = 0;

            while(top > 0 && stk[top-1].height >= h){
            	tot = stk[top-1].height * (stk[top-1].cnt + temp);
            	if(tot > res){
            		res = tot;
            	}
            	temp += stk[top-1].cnt;
            	--top;
            }
            stk[top].height = h;
            stk[top].cnt = temp + 1;
            top++;
        }
        temp = 0;
        while(top > 0){
        	tot = stk[top-1].height * (stk[top-1].cnt + temp);
            	if(tot > res){
            		res = tot;
            	}
            	temp += stk[top-1].cnt;
            	--top;
        }
        cout << res << endl;
    }
}