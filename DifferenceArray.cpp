/*
 * @Author: Cyan
 * @Date: 2021-07-06 19:53:31
 * @LastEditors: Cyan
 * @LastEditTime: 2021-07-06 20:03:18
 * @Description: Difference array
 * Enter a sequence of integers of length n.
    Next, enter m operations, each of which contains three integers L, R, and C, to add c to each number between [L, R] in the sequence.
    Please print out the sequence after you have done all the operations.
 */

#include<iostream>

using namespace std;

const int N = 1e5 + 10;
int a[N],b[N];
int n,m;

void insert(int l, int r, int c){
    b[l] +=c;
    b[r+1] -=c;
}


int main(){
    cin >> n >> m;
    for(int i = 1; i <=n; i++){
        scanf("%d",&a[i]);
        b[i] = a[i] - a[i-1];
    }
        
    while(m--){
        int l, r ,c;
        cin >> l >> r >> c;
        insert(l,r,c);
    }
    
    for(int i = 1; i<=n; i++){
        b[i] += b[i-1];
        printf("%d ",b[i]);
    }
        
    return 0;
    
}