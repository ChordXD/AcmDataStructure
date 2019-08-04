#include <iostream>
using namespace std;

const int maxn = 1000;
int arr[maxn];
int tree[maxn];
int n;

void build_tree(int node, int start, int end){
    if(start == end){
        tree[node] = arr[start];
    } else {
        int left_node = 2 * node + 1;
        int right_node = 2 * node + 2;
        int mid = (start + end) / 2;
        build_tree(left_node, start, mid);
        build_tree(right_node, mid+1, end);
        
        tree[node] = tree[left_node] + tree[right_node];
    }
}

void update_tree(int node, int start, int end, int index, int value){
    if(start == end){
        arr[index] = value;
        tree[node] = value;
    } else {
        int mid = (start + end) / 2;
        int left_node = 2 * node + 1;
        int right_node = 2 * node + 2;
        
        if(index >= start && index <= mid){
            update_tree(left_node, start, mid, index, value);
        } else{
            update_tree(right_node, mid+1, end, index, value);
        }
        
        tree[node] = tree[left_node] + tree[right_node];
    }
}

int query_tree(int node, int start, int end, int L, int R){
    if(R < start || L > end){
        return 0;
    } else if(start == end){
        return tree[node];
    } else if(L <= start && R >= end){
        return tree[node];
     
    } else{
        int mid = (start + end) / 2;
        int left_node = 2 * node + 1;
        int right_node = 2 * node + 2;
        int left_sum = query_tree(left_node, start, mid, L, R);
        int right_sum = query_tree(right_node, mid+1, end, L, R);
        return left_sum + right_sum;
    }
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    memset(tree, 0, sizeof(tree));
    
    build_tree(0, 0, n-1);
    update_tree(0, 0, n-1, 1, 3);
    /*
     
    for(int i = 0; i <= 14; i++){
        cout << tree[i] << " ";
    }cout << endl;
    */
    
    cout << "*" << query_tree(0, 0, n-1, 0, 2) << endl;
}
/*
 *
 5
 1 2 3 4 5
 *7
 */

