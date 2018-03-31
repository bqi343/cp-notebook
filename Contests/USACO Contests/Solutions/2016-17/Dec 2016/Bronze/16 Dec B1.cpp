#include <bits/stdc++.h>

using namespace std;
 
typedef pair <int, int> pi;

#define f first
#define s second

int main() {
    // freopen("square.in","r",stdin);
    // freopen("square.out","w",stdout);
    
    pi a,b,c,d; cin >> a.f >> a.s >> b.f >> b.s >> c.f >> c.s >> d.f >> d.s;
    int ans = max(max(a.f,b.f),max(c.f,d.f))-min(min(a.f,b.f),min(c.f,d.f));
    ans = max(ans,max(max(a.s,b.s),max(c.s,d.s))-min(min(a.s,b.s),min(c.s,d.s)));
    cout << ans*ans;
}
