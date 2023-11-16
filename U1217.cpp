#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,p=1,q,s1,s2,t[N],t0[N];
ll v,f[N];
bool h[N];
struct road
{
    int m,q;
    ll r,w;
}a[N];
struct str
{
    int x1,y1,x2,y2;
}b[N];
void road(int x,int y,ll r,ll w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
    a[p].w=w;
}
bool SPFA()
{
    queue<int> Q;
    Q.push(s1);
    for(int i=1;i<=s2;++i)
    {
        f[i]=1e18;
        h[i]=false;
    }
    f[s1]=0;
    h[s1]=true;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(a[i].r>0&&f[k]+a[i].w<f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                Q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    return f[s2]!=1e18;
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
                v+=z*a[i].w;
            }
            else f[a[i].m]=0;
            if(r==0) return s;
        }
    }
    return s;
}
bool check(int t1,int t2,int t3,int t4,int x1,int y1,int x2,int y2)
{
    return b[t1].y1<=y1&&b[t1].y2>=y2&&b[t3].y1<=y1&&b[t3].y2>=y2&&b[t2].x1<=x1&&b[t2].x2>=x2&&b[t4].x1<=x1&&b[t4].x2>=x2;
}
bool check2(int x1,int y1,int x2,int y2)
{
    for(int i=1;i<=n;++i)
    {
        if(((b[i].x1>x1&&b[i].x1<x2)||(b[i].x2>x1&&b[i].x2<x2))&&(!(b[i].y2<y1||b[i].y1>y2))) return false;
        if(((b[i].y1>y1&&b[i].y1<y2)||(b[i].y2>y1&&b[i].y2<y2))&&(!(b[i].x2<x1||b[i].x1>x2))) return false;
    }
    return true;
}
bool check3(int x1,int y1,int x2,int y2,int x)
{
    return x1>=b[x].x1&&x2<=b[x].x2&&y1>=b[x].y1&&y2<=b[x].y2;
}
void solve(int x1,int y1,int x2,int y2)
{
    if(!check2(x1,y1,x2,y2)) return;
    ++q;
    for(int j=1;j<=n;++j)
    {
        if(check3(x1,y1,x2,y2,j))
        {
            road(q,j,1,(ll)(x2-x1)*(y2-y1));
            road(j,q,0,-(ll)(x2-x1)*(y2-y1));
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i].x1);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i].y1);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i].x2);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i].y2);
    }
    for(int i=1;i<=n;++i)
    {
        if(b[i].x1>b[i].x2) swap(b[i].x1,b[i].x2);
        if(b[i].y1>b[i].y2) swap(b[i].y1,b[i].y2);
        if(b[i].x1==b[i].x2||b[i].y1==b[i].y2)
        {
            printf("-1");
            return 0;
        }
    }
    q=n;
    for(int i1=1;i1<=n*2;++i1)
    {
        int t1=(i1-1)%n+1,x1;
        if(i1<=n) x1=b[t1].x1;
        else x1=b[t1].x2;
        for(int i2=1;i2<=n*2;++i2)
        {
            int t2=(i2-1)%n+1,y1;
            if(i2<=n) y1=b[t2].y1;
            else y1=b[t2].y2;
            for(int i3=1;i3<=n*2;++i3)
            {
                int t3=(i3-1)%n+1,x2;
                if(i3<=n) x2=b[t3].x1;
                else x2=b[t3].x2;
                for(int i4=1;i4<=n*2;++i4)
                {
                    int t4=(i4-1)%n+1,y2;
                    if(i4<=n) y2=b[t4].y1;
                    else y2=b[t4].y2;
                    if(x1<x2&&y1<y2&&check(t1,t2,t3,t4,x1,y1,x2,y2)) solve(x1,y1,x2,y2);
                }
            }
        }
    }
    s1=q+1,s2=q+2;
    for(int i=1;i<=n;++i)
    {
        road(i,s2,1,0);
        road(s2,i,0,0);
    }
    for(int i=n+1;i<=q;++i)
    {
        road(s1,i,1,0);
        road(i,s1,0,0);
    }
    ll r=0;
    while(SPFA())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i],h[i]=false;
        r+=dfs(s1,1e18);
    }
    if(r<n) printf("-1");
    else printf("%lld",v);
    return 0;
}