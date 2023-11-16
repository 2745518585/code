#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=501,M=31;
int n,m,q,p,tot=1,c[N*N<<2][M],e[N*N<<2],f[N*N<<2],s;
char a[N],b[N<<2][N],d[N*N<<2];
bool g[N*N<<2],h[N][N];
struct str
{
    int x,y;
}a0[N*N<<2];
namespace maxflow
{
    const int N=1000001,M=10000001;
    int n,p=1,T,s1,s2,t1,t2,t[N],t0[N],f[N];
    ll b[N];
    struct str
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
        Q.push(s1);
        for(int i=1;i<=T;++i) f[i]=0;
        f[s1]=1;
        while(!Q.empty())
        {
            int k=Q.front();
            Q.pop();
            for(int i=t[k];i!=0;i=a[i].q)
            {
                if(f[a[i].m]==0&&a[i].r!=0)
                {
                    f[a[i].m]=f[k]+1;
                    Q.push(a[i].m);
                }
            }
        }
        return f[s2]!=0;
    }
    ll dfs(int x,ll r)
    {
        if(x==s2) return r;
        ll s=0;
        for(int i=t0[x];i!=0;i=a[i].q)
        {
            t0[x]=i;
            if(f[a[i].m]==f[x]+1&&a[i].r!=0)
            {
                int z=dfs(a[i].m,min(r,a[i].r));
                if(z!=0)
                {
                    a[i].r-=z;
                    a[i^1].r+=z;
                    r-=z;
                    s+=z;
                }
                else f[a[i].m]=0;
                if(r==0) return s; 
            }
        }
        return s;
    }
    int main()
    {
        n=::m;
        t1=n*2+1,t2=n*2+2,s1=n*2+3,s2=n*2+4,T=n*2+4;
        for(int i=1;i<=::p;++i)
        {
            road(n+a0[i].x,a0[i].y,1e18);
            road(a0[i].y,n+a0[i].x,0);
        }
        for(int i=1;i<=n;++i)
        {
            road(t1,i,1e18);
            road(i,t1,0);
            road(n+i,t2,1e18);
            road(t2,n+i,0);
            ++b[i];
            --b[n+i];
        }
        for(int i=1;i<=n*2;++i)
        {
            if(b[i]<0)
            {
                road(s1,i,-b[i]);
                road(i,s1,0);
            }
            else if(b[i]>0)
            {
                road(i,s2,b[i]);
                road(s2,i,0);
            }
        }
        road(t2,t1,1e18);
        road(t1,t2,0);
        while(bfs())
        {
            for(int i=1;i<=T;++i) t0[i]=t[i];
            dfs(s1,1e18);
        }
        s1=t2,s2=t1;
        ll r=0;
        for(int i=t[t2];i!=0;i=a[i].q)
        {
            if(a[i].m==t1)
            {
                r+=a[i^1].r;
                a[i].r=a[i^1].r=0;
            }
        }
        while(bfs())
        {
            for(int i=1;i<=T;++i) t0[i]=t[i];
            r-=dfs(s1,1e18);
        }
        printf("%lld",r);
        return 0;
    }
}
void add(int l,int r)
{
    int k=1;
    for(int i=l;i<=r;++i)
    {
        if(c[k][a[i]-'a']==0) c[k][a[i]-'a']=++tot;
        k=c[k][a[i]-'a'];
    }
    if(g[k]==false)
    {
        ++m;
        for(int i=l;i<=r;++i) b[m][i-l+1]=a[i];
    }
    g[k]=true;
}
void KMP(char a[],char b[],int x)
{
    f[1]=0;
    int n=strlen(b+1);
    for(int i=2,j=0;i<=n;++i)
    {
        while(j!=0&&b[i]!=b[j+1]) j=f[j];
        if(b[i]==b[j+1]) ++j;
        f[i]=j;
    }
    for(int i=1,j=0;i<=q;++i)
    {
        while(j!=0&&a[i]!=b[j+1]) j=f[j];
        if(a[i]==b[j+1]) ++j;
        if(j==n)
        {
            if(e[i]!=x&&h[x][e[i]]==false)
            {
                a0[++p]=(str){x,e[i]};
                h[x][e[i]]=true;
            }
        }
    }
}
int main()
{
    scanf("%s",a+1);
    n=strlen(a+1);
    for(int i=1;i<=n;++i)
    {
        for(int j=0;i-j>=1&&i+j<=n;++j)
        {
            if(a[i-j]!=a[i+j]) break;
            add(i-j,i+j);
        }
        for(int j=0;i-j>=1&&i+j+1<=n;++j)
        {
            if(a[i-j]!=a[i+j+1]) break;
            add(i-j,i+j+1);
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=strlen(b[i]+1);++j) d[++q]=b[i][j],e[q]=i;
        d[++q]='#';
    }
    for(int i=1;i<=m;++i) KMP(d,b[i],i);
    maxflow::main();
    return 0;
}