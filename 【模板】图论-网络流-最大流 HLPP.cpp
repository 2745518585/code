#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001,M=10000001;
int n,m,p=1,t[N],t0[N],s1,s2,f[N],g[N];
ll q[N];
bool h[N];
struct cmp
{
    bool operator ()(int a,int b)const
    {
        return f[a]<f[b];
    }
};
priority_queue<int,vector<int>,cmp> Q;
struct road
{
    int m,q;
    ll r;
}a[M];
void road(int x,int y,ll r)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].r=r;
}
bool bfs()
{
    queue<int> Q;
    Q.push(s2);
    for(int i=1;i<=n;++i) f[i]=1e9;
    f[s2]=0;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[k]+1<f[a[i].m]&&a[i^1].r!=0)
            {
                f[a[i].m]=f[k]+1;
                Q.push(a[i].m);
            }
        }
    }
    return f[s1]!=1e9;
}
void push(int x)
{
    for(int i=t0[x];i!=0;i=a[i].q)
    {
        t0[x]=i;
        if(f[x]==f[a[i].m]+1&&a[i].r>0)
        {
            ll z=min(a[i].r,q[x]);
            a[i].r-=z;
            a[i^1].r+=z;
            q[x]-=z;
            q[a[i].m]+=z;
            if(a[i].m!=s1&&a[i].m!=s2&&h[a[i].m]==false)
            {
                Q.push(a[i].m);
                h[a[i].m]=true;
            }
            if(q[x]==0) return;
        }
    }
}
void move(int x)
{
    f[x]=1e9;
    t0[x]=t[x];
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].r!=0&&f[a[i].m]+1<f[x])
        {
            f[x]=f[a[i].m]+1;
        }
    }
}
ll HLPP()
{
    if(!bfs()) return 0;
    f[s1]=n;
    for(int i=1;i<=n;++i) if(f[i]<=n) ++g[f[i]];
    for(int i=1;i<=n;++i) t0[i]=t[i];
    for(int i=t[s1];i!=0;i=a[i].q)
    {
        if(a[i].r>0)
        {
            ll z=a[i].r;
            a[i].r-=z;
            a[i^1].r+=z;
            q[s1]-=z;
            q[a[i].m]+=z;
            if(a[i].m!=s1&&a[i].m!=s2&&h[a[i].m]==false)
            {
                Q.push(a[i].m);
                h[a[i].m]=true;
            }
        }
    }
    int s=0;
    while(!Q.empty())
    {
        int k=Q.top();
        Q.pop();
        h[k]=false;
        if(f[k]>n) continue;
        push(k);
        if(q[k]!=0)
        {
            --g[f[k]];
            if(g[f[k]]==0)
            {
                for(int i=1;i<=n;++i)
                {
                    if(i!=s1&&i!=s2&&f[i]>f[k]&&f[i]<=n)
                    {
                        --g[f[i]];
                        f[i]=n+1;
                    }
                }
            }
            ++s;
            move(k);
            if(f[k]<=n)
            {
                ++g[f[k]];
                Q.push(k);
                h[k]=true;
            }
            if(s%(n*4)==0)
            {
                for(int i=0;i<=n;++i) g[i]=0;
                if(bfs()) return q[s2];
                for(int i=1;i<=n;++i)
                {
                    if(f[i]<=n+1) ++g[f[i]];
                    t0[i]=t[i];
                }
            }
        }
    }
    return q[s2];
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&s1,&s2);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        ll r;
        scanf("%d%d%lld",&x,&y,&r);
        road(x,y,r);
        road(y,x,0);
    }
    printf("%lld",HLPP());;
    return 0;
}