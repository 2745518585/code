#include<cstdio>
#include<algorithm>
#include<queue>
#include<set>
using namespace std;
typedef long long ll;
const int N=1000001;
int n;
ll m;
struct str
{
    ll x,y;
    str() {}
    str(ll x,ll y):x(x),y(y) {}
    friend bool operator<(str a,str b)
    {
        if(a.y!=b.y) return a.y>b.y;
        return a.x>b.x;
    }
};
int main()
{
    scanf("%d%lld",&n,&m);
    priority_queue<str> Q;
    ll q=0;
    for(int i=1;i<=n;++i)
    {
        ll x;
        scanf("%lld",&x);
        Q.push(str(x,x));
        q=max(q,x);
    }
    ll s=1e18;
    while(true)
    {
        auto k=Q.top();
        Q.pop();
        s=min(s,max(q-k.y,0ll));
        if(k.y*2+m>1e18) break;
        Q.push(str(k.x*2,k.y*2+m));
        q=max(q,k.x*2);
    }
    printf("%lld",s);
    return 0;
}