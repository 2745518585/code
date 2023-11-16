#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,t[N],l[N];
bool h[N];
ll f[N];
struct road
{
    int x,y,m,q;
    ll w1,w2;
}a[N];
bool cmp(road a,road b)
{
    return a.w1>b.w1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%lld%lld",&a[i].x,&a[i].y,&a[i].w1,&a[i].w2);
        ++l[a[i].x];
    }
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=m;++i)
    {
        a[i].m=a[i].x;
        a[i].q=t[a[i].y];
        t[a[i].y]=i;
    }
    for(int i=1;i<=n;++i) f[i]=1e18;
    queue<int> Q;
    for(int i=1;i<=n;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        f[k]=-1;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(h[i]==true) continue;
            --l[a[i].m];
            h[i]=true;
            if(l[a[i].m]==0) Q.push(a[i].m);
        }
    }
    for(int i=1;i<=m;++i)
    {
        if(h[i]) continue;
        f[a[i].x]=min(f[a[i].x],a[i].w1);
        --l[a[i].x];
        h[i]=true;
        if(l[a[i].x]==0) Q.push(a[i].x);
        while(!Q.empty())
        {
            int k=Q.front();
            Q.pop();
            for(int i=t[k];i!=0;i=a[i].q)
            {
                if(h[i]==true) continue;
                f[a[i].m]=min(f[a[i].m],max(f[k]-a[i].w2,a[i].w1));
                --l[a[i].m];
                h[i]=true;
                if(l[a[i].m]==0) Q.push(a[i].m);
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        printf("%lld ",f[i]);
    }
    return 0;
}