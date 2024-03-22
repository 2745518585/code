#pragma GCC optimize("O2")
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
inline char gc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T> inline void read(T &x)
{
    T u=1,t=0;char c=gc();
    while(c<'0'||c>'9') {if(c=='-') u=-1; c=gc();}
    while(c>='0'&&c<='9') t*=10,t+=c-'0',c=gc();
    x=u*t;return;
}
template<typename T,typename ...O> inline void read(T &x,O &...o) {read(x),read(o...);}
const int N=1000001,M=21;
int n,m,a[N],b1[2][N][M],b2[2][N][M],c[N],s=1e9;
vector<int> b[N];
int query1(int x,int u,int l)
{
    for(int t=20;t>=0;--t)
    {
        if(b1[u][x][t]>=l) x=b1[u][x][t];
    }
    return a[x];
}
int query2(int x,int u,int r)
{
    for(int t=20;t>=0;--t)
    {
        if(b2[u][x][t]<=r) x=b2[u][x][t],++t;
    }
    return a[x];
}
int solve1(int x,int y)
{
    int l=0,r=min(x,y);
    while(l<r)
    {
        int z=l+r+1>>1;
        if(query1(y,1,z)-query1(x,0,z)>=m) l=z;
        else r=z-1;
    }
    if(l==0) return -1e9;
    return l;
}
int solve2(int x,int y)
{
    int l=max(x,y),r=n+1;
    while(l<r)
    {
        int z=l+r>>1;
        if(query2(y,1,z)-query2(x,0,z)>=m) r=z;
        else l=z+1;
    }
    if(l==n+1) return 1e9;
    return l;
}
void solve(int x,int y)
{
    int u=solve1(x,x),v=solve2(y,y);
    s=min(s,solve2(x,y)-u);
    s=min(s,solve2(y,x)-u);
    s=min(s,v-solve1(x,y));
    s=min(s,v-solve1(y,x));
}
int main()
{
    read(n,m);
    if(m%2==1)
    {
        printf("-1");
        return 0;
    }
    m=(m-2)/2;
    for(int i=1;i<=n;++i)
    {
        read(a[i]);
        b[a[i]].push_back(i);
    }
    for(int i=1;i<=n;++i)
    {
        b1[0][i][0]=c[a[i]-1];
        b1[1][i][0]=c[a[i]+1];
        c[a[i]]=i;
    }
    for(int i=0;i<=n+1;++i) c[i]=n+1;
    b2[0][n+1][0]=b2[1][n+1][0]=n+1;
    for(int i=n;i>=1;--i)
    {
        b2[0][i][0]=c[a[i]-1];
        b2[1][i][0]=c[a[i]+1];
        c[a[i]]=i;
    }
    for(int i=1;i<=20;++i)
    {
        for(int j=0;j<=n+1;++j)
        {
            for(int k=0;k<=1;++k)
            {
                b1[k][j][i]=b1[k][b1[k][j][i-1]][i-1];
                b2[k][j][i]=b2[k][b2[k][j][i-1]][i-1];
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j+1<b[i].size();++j)
        {
            solve(b[i][j],b[i][j+1]);
        }
    }
    printf("%d",s>n?-1:s);
    return 0;
}