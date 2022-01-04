#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <iostream>
#include <unordered_set>
#include <numeric>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#define ll long long
using namespace std;

void Solve(const vector<int>& A, const vector<int>& B, int st_a, int en_a, int st_b, int en_b, vector<int>& pos) {

    if (st_b > en_b) return;
    int mid = (st_b+en_b)/2;
    ll num_less = 0;
    for(int j=st_a;j<=en_a;j++) {
        num_less += (A[j]<B[mid]);
    }
    ll min_inv = -1;
    ll num_greater = 0;
    for(int j=st_a;j<=en_a;j++) {
        ll num_inv = num_less + num_greater;
        if (min_inv == -1 || num_inv < min_inv) {
            min_inv = num_inv;
            pos[mid] = j;
        }
        if (j == en_a) break;
        num_greater += (A[j]>B[mid]);
        num_less -= (A[j]<B[mid]);
    }
    Solve(A, B, st_a, pos[mid], st_b, mid-1, pos);
    Solve(A, B, pos[mid], en_a, mid+1, en_b, pos);
}

int read(int idx, const vector<int>& tree) {
    int ret = 0;
    while(idx) {
        ret += tree[idx];
        idx -= (idx&-idx);
    }
    return ret;
}

void update(int idx, vector<int>& tree) {
    while(idx < tree.size()) {
        tree[idx]++;
        idx += (idx&-idx);
    }
}

ll GetInversions(const vector<int>& C) {
    int n=C.size();
    vector<int> tree(n+1, 0);
    vector<pair<int,int>> val_pos;
    for(int i=0;i<n;i++) {
        val_pos.push_back({C[i],i+1});
    }
    sort(val_pos.begin(),val_pos.end(),greater<pair<int,int>>());
     
    ll ret = 0;
    for(int i=0;i<val_pos.size();) {
        int j = i;
        while(j+1<val_pos.size() && val_pos[j+1].first == val_pos[i].first) {
            j++;
        }
        // i to j.
        for(int k=i;k<=j;k++) {
            ret += read(val_pos[k].second, tree);
        }
        for(int k=i;k<=j;k++) {
            update(val_pos[k].second, tree);
        }
        i = j+1;
    }
    return ret;
    
}

int main() {
    int T;
    scanf("%d",&T);
    for(int t=1;t<=T;t++) {
        int n,m;
        scanf("%d",&n);
        scanf("%d",&m);
        vector<int> A(n);
        vector<int> B(m);
        for(int i=0;i<n;i++) {
            scanf("%d",&A[i]);
        }
        for(int j=0;j<m;j++) {
            scanf("%d",&B[j]);
        }
        sort(B.begin(),B.end());
        
        vector<int> pos(m, -1);
        Solve(A, B, 0, n, 0, m-1, pos);
        vector<int> C;
        int id = 0;
        for(int i=0;i<=n;i++) {
            while (id < m && pos[id] == i) {
                C.push_back(B[id]);
                id++;
            }
            if (i == n) break;
            C.push_back(A[i]);
        }
        
        cout << GetInversions(C) << endl;
        
    }
}
