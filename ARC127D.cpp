#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
typedef long long ll;
int n,a[N],b[N];
ll s;
void sum(int t,const vector<int> &x1,const vector<int> &x2,int *p)
{
    for(int i=0;i<=20;++i)
    {
        ll w[2]={0,0};
        for(auto j:x1) ++w[p[j]>>i&1];
        for(auto j:x2) s+=w[(p[j]>>i&1)^1]<<i;
    }
}
void solve(int t,const vector<int> &x)
{
    if(t==-1)
    {
        for(int i=0;i<=20;++i)
        {
            ll w[2]={0,0};
            for(auto j:x)
            {
                s+=w[(a[j]>>i&1)^1]<<i;
                ++w[a[j]>>i&1];
            }
        }
        return;
    }
    vector<int> d[2][2];
    for(auto i:x)
    {
        d[a[i]>>t&1][b[i]>>t&1].push_back(i);
    }
    sum(t,d[0][0],d[0][1],a);
    sum(t,d[0][0],d[1][0],b);
    sum(t,d[1][1],d[0][1],b);
    sum(t,d[1][1],d[1][0],a);
    vector<int> u1,u2;
    for(auto i:d[0][0]) u1.push_back(i);
    for(auto i:d[1][1]) u1.push_back(i);
    for(auto i:d[0][1]) u2.push_back(i);
    for(auto i:d[1][0]) u2.push_back(i);
    solve(t-1,u1);
    solve(t-1,u2);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    vector<int> u;
    for(int i=1;i<=n;++i) u.push_back(i);
    solve(20,u);
    printf("%lld",s);
    return 0;
}