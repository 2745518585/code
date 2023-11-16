#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,q1,q2;
bool h[N];
struct str
{
    ll x,y;
    str(){}
    str(ll x,ll y):x(x),y(y){}
}a[N];
map<ll,int> d1,d2;
vector<int> b1[N],b2[N];
bool check(ll x,ll y,int u)
{
    if(x==0||y==0) return true;
    if(u==0)
    {
        if(!d1.count(x)) return false;
        int t=d1[x];
        ll p=y;
        for(auto i:b1[t])
        {
            if(h[i]) continue;
            p-=a[i].y;
            h[i]=true;
        }
        if(p==y) return false;
        return check(x,p,1);
    }
    else
    {
        if(!d2.count(y)) return false;
        int t=d2[y];
        ll p=x;
        for(auto i:b2[t])
        {
            if(h[i]) continue;
            p-=a[i].x;
            h[i]=true;
        }
        if(p==x) return false;
        return check(p,y,0);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        ll x=0,y=0,s=0;
        q1=0,q2=0;
        d1.clear(),d2.clear();
        for(int i=1;i<=n;++i)
        {
            scanf("%lld%lld",&a[i].x,&a[i].y);
            x=max(x,a[i].x);
            y=max(y,a[i].y);
            s+=a[i].x*a[i].y;
            if(!d1.count(a[i].x)) d1[a[i].x]=++q1,b1[q1].clear();
            if(!d2.count(a[i].y)) d2[a[i].y]=++q2,b2[q2].clear();
            b1[d1[a[i].x]].push_back(i);
            b2[d2[a[i].y]].push_back(i);
        }
        int u1=0,u2=0;
        if(s%x==0)
        {
            for(int i=1;i<=n;++i) h[i]=false;
            if(check(x,s/x,0)) u1=1;
        }
        if(s%y==0)
        {
            for(int i=1;i<=n;++i) h[i]=false;
            if(check(s/y,y,1)) u2=1;
        }
        if(x==s/y) u2=0;
        printf("%d\n",u1+u2);
        if(u1) printf("%lld %lld\n",x,s/x);
        if(u2) printf("%lld %lld\n",s/y,y);
    }
    return 0;
}