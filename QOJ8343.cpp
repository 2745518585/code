#include<cstdio>
#include<algorithm>
#include<vector>
namespace Solve
{
    using namespace std;
    typedef long long ll;
    const int N=1000001;
    int n;
    bool h[N];
    void init(int _n)
    {
        n=_n;
    }
    int sum(ll x)
    {
        return (x%(n*2+1)+(n*2+1))%(n*2+1);
    }
    pair<int,int> encode(vector<int> a)
    {
        for(int i=0;i<=n*2;++i) h[i]=false;
        int s=0;
        for(auto i:a) s=sum(s+i);
        for(auto i:a) h[sum(i-s)]=true;
        auto mp=[&](int x,int y)
        {
            return make_pair(sum(x+s),sum(y+s));
        };
        for(pair<int,int> i:vector<pair<int,int>>{{0,1},{0,n*2},{n,2},{n,n*2-1},{4,n+1},{n*2-3,n+1}})
        {
            if(h[i.first]&&h[i.second]) return mp(i.first,i.second);
        }
        for(int i=1;i<=n-1;++i)
        {
            if(h[i]&&h[(n*2+1)-i])
            {
                if(n%2==0) return mp((n*2+1)-i,i);
                else return mp(i,(n*2+1)-i);
            }
        }
    }
    int decode(pair<int,int> a,pair<int,int> b)
    {
        auto solve=[&](int x1,int x2)
        {
            for(pair<int,int> i:vector<pair<int,int>>{{0,1},{0,n*2},{n,2},{n,n*2-1},{4,n+1},{n*2-3,n+1}})
            {
                if(sum(i.second-i.first)==sum(x2-x1))
                {
                    return sum((ll)((x1+x2)-(i.first+i.second))*(n+1));
                }
            }
            return sum((ll)(x1+x2)*(n+1));
        };
        int s1=solve(a.first,a.second),s2=solve(b.first,b.second);
        return sum(-s1-s2);
    }
}
void init(int n)
{
    return Solve::init(n);
}
std::pair<int, int> encode(std::vector<int> a)
{
    return Solve::encode(a);
}
int decode(std::pair<int, int> a, std::pair<int, int> b)
{
    return Solve::decode(a,b);
}