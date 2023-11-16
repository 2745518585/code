#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
typedef long long ll;
const int N=500001,M=26;
int n,m,l[N],p1[N],p2[N];
char a[N],*b[N],c[N<<5],f1[M][N],f2[N],h[N];
ll ls,rs,f[N][M];
vector<int> g[N],g2[N];
void print(int x,int z,ll ls,ll rs)
{
    if(x==n+1)
    {
        g[x].push_back(m);
        g2[x].push_back(z);
        ++m;
        return;
    }
    if(z!=a[x]-'a')
    {
        print(x+1,z,ls,rs);
        return;
    }
    if(ls==-1&&rs==-1)
    {
        g[x].push_back(m);
        g2[x].push_back(z);
        m+=f[x-1][z];
    }
    else if(ls==-1)
    {
        ll w=0;
        for(int i=1;i<=p2[x]-1;++i) print(x+1,b[x][i]-'a',-1,-1),w+=f[x][b[x][i]-'a'];
        print(x+1,b[x][p2[x]]-'a',-1,rs-w);
    }
    else if(rs==-1)
    {
        print(x+1,b[x][p1[x]]-'a',ls,-1);
        for(int i=p1[x]+1;i<=l[x];++i) print(x+1,b[x][i]-'a',-1,-1);
    }
    else
    {
        if(p1[x]==p2[x])
        {
            ll w=0;
            for(int i=1;i<=p1[x]-1;++i) w+=f[x][b[x][i]-'a'];
            print(x+1,b[x][p1[x]]-'a',ls-w,rs-w);
        }
        else
        {
            ll w=0;
            for(int i=1;i<=p1[x]-1;++i) w+=f[x][b[x][i]-'a'];
            print(x+1,b[x][p1[x]]-'a',ls-w,-1);
            for(int i=p1[x]+1;i<=p2[x]-1;++i) print(x+1,b[x][i]-'a',-1,-1),w+=f[x][b[x][i]-'a'];
            print(x+1,b[x][p2[x]]-'a',-1,rs-w);
        }
    }
}
int main()
{
    scanf("%lld%lld%d",&ls,&rs,&n);
    b[0]=c;
    for(int i=1;i<=n;++i)
    {
        b[i]=b[i-1]+l[i-1]+1;
        scanf("%s%s",&a[i],b[i]+1);
        l[i]=strlen(b[i]+1);
    }
    for(int i=0;i<=25;++i) f[n][i]=1;
    for(int i=n-1;i>=0;--i)
    {
        for(int j=0;j<=25;++j)
        {
            if(j==a[i+1]-'a')
            {
                for(int k=1;k<=l[i+1];++k) 
                {
                    f[i][j]+=f[i+1][b[i+1][k]-'a'];
                    if(f[i][j]>1e18) f[i][j]=1e18;
                }
            }
            else f[i][j]=f[i+1][j];
        }
    }
    int z=0;
    ll x=ls;
    for(int i=1;i<=n;++i)
    {
        if(z==a[i]-'a')
        {
            for(int j=1;j<=l[i];++j)
            {
                if(f[i][b[i][j]-'a']<x) x-=f[i][b[i][j]-'a'];
                else
                {
                    p1[i]=j;
                    z=b[i][j]-'a';
                    break;
                }
            }
        }
        else p1[i]=-1;
    }
    z=0,x=rs;
    for(int i=1;i<=n;++i)
    {
        if(z==a[i]-'a')
        {
            for(int j=1;j<=l[i];++j)
            {
                if(f[i][b[i][j]-'a']<x) x-=f[i][b[i][j]-'a'];
                else
                {
                    p2[i]=j;
                    z=b[i][j]-'a';
                    break;
                }
            }
        }
        else p2[i]=-1;
    }
    print(1,0,ls,rs);
    for(int i=0;i<=25;++i) f1[i][1]=i+'a';
    for(int i=n+1;i>=1;--i)
    {
        for(int j=0;j<g[i].size();++j)
        {
            for(int k=1;k<=f[i-1][g2[i][j]];++k) h[g[i][j]+k]=f1[g2[i][j]][k];
        }
        if(i>1)
        {
            if(f[i-2][a[i-1]-'a']>rs-ls+1) continue;
            int z=0;
            for(int j=1;j<=l[i-1];++j)
            {
                for(int k=1;k<=f[i-1][b[i-1][j]-'a'];++k)
                {
                    f2[++z]=f1[b[i-1][j]-'a'][k];
                }
            }
            swap(f1[a[i-1]-'a'],f2);
        }
    }
    for(int i=1;i<=m;++i)
    {
        putchar(h[i]);
    }
    return 0;
}