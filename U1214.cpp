#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
typedef long long ll;
const int N=2000001,M=2000001;
struct cost
{
    double w1;
    ll w2;
    cost(){}
    cost(double p1,ll p2):w1(p1),w2(p2){}
    inline friend cost operator +(cost a,cost b)
    {
        return cost(a.w1+b.w1,a.w2+b.w2);
    }
    inline friend cost operator -(cost a,cost b)
    {
        return cost(a.w1-b.w1,a.w2-b.w2);
    }
    inline friend cost operator -(cost a)
    {
        return cost(-a.w1,-a.w2);
    }
    inline friend cost operator *(cost a,int b)
    {
        return cost(a.w1*b,a.w2*b);
    }
    inline friend cost operator *(int b,cost a)
    {
        return cost(a.w1*b,a.w2*b);
    }
    inline friend bool operator >(cost a,cost b)
    {
        return a.w1!=b.w1?a.w1<b.w1:a.w2>b.w2;
    }
    inline friend bool operator <(cost a,cost b)
    {
        return a.w1!=b.w1?a.w1>b.w1:a.w2<b.w2;
    }
    inline friend bool operator ==(cost a,cost b)
    {
        return a.w1-b.w1<=1e-8&&a.w1-b.w1>=-1e-8&&a.w2==b.w2;
    }
    inline friend bool operator !=(cost a,cost b)
    {
        return a.w1-b.w1>1e-8||a.w1-b.w1<-1e-8||a.w2!=b.w2;
    }
};
int n,m,d,p=1,s1,s2,t[N],t0[N],g[N];
ll b[N];
double c[N];
cost v,f[N];
bool h[N];
struct road
{
    int m,q;
    ll r;
    cost w;
}a[M];
void road(int x,int y,ll r,cost w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[p].w=w;
}
inline bool SPFA()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=d;++i)
    {
        f[g[i]]=cost(1e9,-1e18);
        h[g[i]]=false;
    }
    f[s1]=cost(0,0);
    h[s1]=true;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(a[i].r>0&&f[k]+a[i].w>f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                Q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    return f[s2]!=cost(1e9,-1e18);
}
ll dfs(int x,ll r)
{
    if(x==s2) return r;
    ll s=0;
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(h[a[i].m]==false&&a[i].r>0&&f[a[i].m]==f[x]+a[i].w)
        {
            h[a[i].m]=true;
            ll z=dfs(a[i].m,min(r,a[i].r));
            h[a[i].m]=false;
            if(z!=0)
            {
                a[i].r-=z;
                a[i^1].r+=z;
                r-=z;
                s+=z;
                v=v+z*a[i].w;
            }
            else f[a[i].m]=cost(0,0);
            if(r==0) return s;
        }
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    s1=n+m+1,s2=n+m+2;
    for(int i=1;i<=m;++i)
    {
        scanf("%lld",&b[i]);
    }
    for(int i=1;i<=n;++i)
    {
        register int t[101]={0};
        c[0]=1e9;
        for(int j=1;j<=m;++j)
        {
            double w;
            scanf("%lf",&w);
            w=log2(1/w);
            c[j]=w;
            t[n+1]=j;
            for(int k=n;k>=1;--k)
            {
                if(c[t[k+1]]<c[t[k]]) t[k+1]^=t[k],t[k]^=t[k+1],t[k+1]^=t[k];
                else break;
            }
        }
        for(int j=1;j<=n;++j)
        {
            road(i,n+t[j],1,cost(c[t[j]],b[t[j]]));
            road(n+t[j],i,0,-cost(c[t[j]],b[t[j]]));
            if(h[t[j]]==false)
            {
                h[t[j]]=true;
                g[++d]=n+t[j];
            }
        }
    }
    g[++d]=s1,g[++d]=s2;
    for(int i=1;i<=n;++i)
    {
        g[++d]=i;
        road(s1,i,1,cost(0,0));
        road(i,s1,0,cost(0,0));
    }
    for(int i=1;i<=m;++i)
    {
        if(h[i]==false) continue;
        road(n+i,s2,1,cost(0,0));
        road(s2,n+i,0,cost(0,0));
    }
    while(SPFA())
    {
        for(int i=1;i<=d;++i)
        {
            t0[g[i]]=t[g[i]];
            h[g[i]]=false;
        }
        dfs(s1,1e18);
    }
    printf("%.12lf\n%lld",1/pow(2,v.w1),v.w2);
    return 0;
}