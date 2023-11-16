#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001,M=1000001,K=1001;
int n,m,s1,s2,q,p=1,t[N],t0[N],f[N],b[K][K],d[N][2];
char c[K][K];
bool h[N];
struct road
{
    int m,q;
    ll r;
}a[M<<1];
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
    for(int i=1;i<=s2;++i) f[i]=0;
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
            ll z=dfs(a[i].m,min(r,a[i].r));
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
void dfs2(int x)
{
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m>q*2||a[i].r==0||h[a[i].m]) continue;
        dfs2(a[i].m);
    }
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        scanf("%s",c[i]+1);
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(c[i][j]=='1') b[i][j]=++q,d[q][0]=i,d[q][1]=j;
        }
    }
    s1=q*2+1,s2=q*2+2;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(c[i][j]=='0')
            {
                int k1=i,k2=j;
                while(c[k1][j]=='0') --k1;
                while(c[i][k2]=='0') --k2;
                road(b[k1][j],q+b[i][k2],1);
                road(q+b[i][k2],b[k1][j],0);
            }
        }
    }
    for(int i=1;i<=q;++i)
    {
        road(s1,i,1);
        road(i,s1,0);
        road(q+i,s2,1);
        road(s2,q+i,0);
    }
    ll r=0;
    while(bfs())
    {
        for(int i=1;i<=s2;++i) t0[i]=t[i];
        r+=dfs(s1,1e18);
    }
    printf("%d\n",r);
    for(int i=1;i<=s2;++i) h[i]=false;
    for(int i=t[s1];i!=0;i=a[i].q)
    {
        if(a[i].r>0) dfs2(a[i].m);
    }
    for(int i=1;i<=q;++i)
    {
        if(h[i]==false)
        {
            printf("%d %d DOLJE\n",d[i][0],d[i][1]);
        }
        if(h[q+i]==true)
        {
            printf("%d %d DESNO\n",d[i][0],d[i][1]);
        }
    }
    return 0;
}