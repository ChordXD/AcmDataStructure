#include <iostream>
#include <cmath>
#include <stack>
#include <queue>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
const int maxn = 1e6+10;
int n, m;
int a[maxn];

int main(){
    while(cin >> n >> m){
        deque<int> qmax, qmin;
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
        }
        for(int i = 1; i <= n; i++){
            if(qmin.empty()){
                qmin.push_back(i);
            }else{
                while (!qmin.empty() && i-qmin.front()+1>m) {
                    qmin.pop_front();
                }
                while (!qmin.empty() && a[qmin.back()] > a[i]) {
                     qmin.pop_back();
                }
                qmin.push_back(i);
            }
            if(i >= m){
                printf("%d ", a[qmin.front()]);
            }
        }
        printf("\n");
        for(int i = 1; i <= n; i++){
            if(qmax.empty()){
                qmax.push_back(i);
            }else{
                while (!qmax.empty() && i-qmax.front()+1>m) {
                    qmax.pop_front();
                }
                while (!qmax.empty() && a[qmax.back()] < a[i]) {
                    qmax.pop_back();
                }
                qmax.push_back(i);
            }
            if(i >= m){
                printf("%d ", a[qmax.front()]);
            }
        }
        printf("\n");
    }
}

/*

qmax:
1 3 -1 -3 5 3 6 7
 */

