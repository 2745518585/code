#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1001;
const ll P=1e9+7;
int n,m,b[N],l[N],h[N][N];
bool g[N];
ll s,k;
struct road
{
    int x,y;
    ll w1,w2;
}a[N];
ll A(ll a,ll b)
{
    if(b>a) return 0;
    ll s=1;
    for(int i=a;i>=a-b+1;--i) s=(s*i)%P;
    return s;
}
void dfs(int x,int t)
{
    if(x==n+1)
    {
        ll w=A(k,t);
        for(int i=1;i<=m;++i)
        {
            if(g[a[i].x]||g[a[i].y]) continue;
            if(b[a[i].x]!=b[a[i].y]) w=(w*a[i].w1)%P;
            else w=(w*a[i].w2)%P;
        }
        s=(s+w)%P;
        return;
    }
    if(g[x])
    {
        dfs(x+1,t);
        return;
    }
    for(int i=1;i<=t;++i)
    {
        b[x]=i;
        dfs(x+1,t);
    }
    b[x]=t+1;
    dfs(x+1,t+1);
}
void abc()
{
    scanf("%d%d%lld",&n,&m,&k);
    for(int i=1;i<=n;++i) l[i]=0,g[i]=false;
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%lld%lld",&a[i].x,&a[i].y,&a[i].w1,&a[i].w2);
        h[a[i].x][++l[a[i].x]]=i;
        h[a[i].y][++l[a[i].y]]=i;
    }
    if(m==n-1)
    {
        s=k;
        for(int i=1;i<=m;++i)
        {
            s=((k-1)*s%P*a[i].w1%P+s*a[i].w2%P)%P;
        }
        printf("%lld\n",s);
        return;
    }
    s=0;
    ll w=1;
    for(int i=1;i<=n;++i)
    {
        if(l[i]==1)
        {
            w=w*((k-1)*a[h[i][1]].w1%P+a[h[i][1]].w2)%P;
            int x=a[h[i][1]].x+a[h[i][1]].y-i;
            for(int j=1;j<=l[x];++j)
            {
                if(h[x][j]==h[i][1])
                {
                    for(int k=j+1;k<=l[x];++k) h[x][k-1]=h[x][k];
                    break;
                }
            }
            --l[x];
            g[i]=true;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(l[i]==2)
        {
            int x=h[i][1],y=h[i][2];
            if(a[x].x+a[x].y==a[y].x+a[y].y) continue;
            ++m;
            a[m].x=a[x].x+a[x].y-i,a[m].y=a[y].x+a[y].y-i;
            a[m].w1=(a[x].w1*a[y].w2%P+a[x].w2*a[y].w1%P+a[x].w1*a[y].w1%P*(k-2)%P)%P;
            a[m].w2=(a[x].w2*a[y].w2%P+a[x].w1*a[y].w1%P*(k-1)%P)%P;
            g[i]=true;
            for(int j=1;j<=l[a[m].x];++j)
            {
                if(h[a[m].x][j]==x)
                {
                    h[a[m].x][j]=m;
                    break;
                }
            }
            for(int j=1;j<=l[a[m].y];++j)
            {
                if(h[a[m].y][j]==y)
                {
                    h[a[m].y][j]=m;
                    break;
                }
            }
        }
    }
    dfs(1,0);
    printf("%lld\n",s*w%P);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}