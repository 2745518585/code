#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include"matrix.h"
#include"grader.cpp"
namespace Solve
{
    using namespace std;
    typedef long long ll;
    const int N=1000001;
    int n;
    ll k,p1[N],p2[N];
    map<pair<int,int>,ll> a;
    map<ll,int> b[N];
    ll query(int x,int y)
    {
        if(y<1) return -1;
        if(a.count(make_pair(x,y))) return a[make_pair(x,y)];
        b[x][a[make_pair(x,y)]=::query(x,y)]=y;
        return a[make_pair(x,y)];
    }
    ll check(ll t)
    {
        p1[n+1]=0,p2[0]=n+1;
        for(int i=n;i>=1;--i)
        {
            p1[i]=max(p1[i+1],(ll)prev(b[i].lower_bound(t))->second);
        }
        for(int i=1;i<=n;++i)
        {
            p2[i]=min(p2[i-1],(ll)b[i].lower_bound(t)->second-1);
        }
        for(int i=n;i>=1;--i) p1[i]+=p1[i+1],p2[i]+=p2[i+1];
        int x=n;
        ll s=0;
        for(int i=1;i<=n;++i)
        {
            while(query(i,x)>=t) --x;
            s+=x;
            if(s+p1[i+1]>=k) return false;
            if(s+(ll)x*(n-i)<k||s+p2[i+1]<k) return true;
        }
        return s<k;
    }
    ll main(int _n,ll _k)
    {
        n=_n,k=_k;
        for(int i=1;i<=n;++i) b[i][-1]=0,b[i][(ll)1e18+1]=n+1;
        ll l=0,r=1e18;
        while(l<r)
        {
            ll z=l+r+1>>1;
            if(check(z)) l=z;
            else r=z-1;
        }
        return l;
    }
}
long long solve(int N, long long k) {
	return Solve::main(N,k);
}