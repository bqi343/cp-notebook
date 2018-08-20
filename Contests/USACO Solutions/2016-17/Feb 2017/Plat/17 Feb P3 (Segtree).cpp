#include<iostream>
#include<fstream>
 
using namespace std;
 
typedef pair<int,int> pi;
 
#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
 
#define f first
#define s second
 
int N,K,nex;
pi x[100001];
pair<int,pi> segbit[20000000];
long long ans = 0;
 
int getnode(int in, int b) {
    if (b == 0) {
        if (!segbit[in].s.f) segbit[in].s.f = nex++;
        return segbit[in].s.f;
    }
    if (!segbit[in].s.s) segbit[in].s.s = nex++;
    return segbit[in].s.s;
}
 
void update(int in, int left, int right, int ind) {
    segbit[in].f ++;
    if (left == ind && right == ind) return;
    int mid = (left+right)/2;
    if (mid >= ind) update(getnode(in,0),left,mid,ind);
    else update(getnode(in,1),mid+1,right,ind);
}
     
int query(int ind, int left, int right, int high) {
    if (right <= high) return segbit[ind].f;
    int mid = (left+right)/2, z = 0;
    if (segbit[ind].s.f) z += query(segbit[ind].s.f,left,mid,high);
    if (segbit[ind].s.s && mid+1 <= high) z += query(segbit[ind].s.s,mid+1,right,high);
    return z;
}
 
void updb (int num, int pos) {
    while (num <= N) {
        update(num, 1,N,pos);
        num += (num & -num);
    }
}
 
void queryb(int mnum, int mpo, int mult) {
    while (mnum) {
        ans += mult*query(mnum,1,N,mpo);
        mnum -= (mnum & -mnum);
    }
}
 
void init() {
    //ifstream cin ("friendcross.in");
    cin >> N >> K; nex = N+1;
    F0R(i,N) {
        int a; cin >> a;
        x[a].f = i+1;
    }
    F0R(i,N) {
        int b; cin >> b;
        x[b].s = i+1;
    }
}
 
int main() {
    //ofstream cout ("friendcross.out");
    init();
    for (int i = N; i > 0; --i) {
        int j = i+K+1;
        if (j > N) continue;
        updb(x[j].f,x[j].s);
        queryb(N,x[i].s,1);
        queryb(x[i].f,N,1);
        queryb(x[i].f,x[i].s,-2);
    }
    cout << ans;
}
