#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=201,M=11;
const short dx[4]={-1,0,1,0},dy[4]={0,1,0,-1},dn[4]={2,3,0,1};
int m,n,k,ex,ey,f[N][N][10],h1[N],h2[N];
ll f1[N],f2[N],g1[N][10],g2[N][10],b[N],s=9223372036854775807;
char a[N][N];
bool check(int x,int y)
{
    return x>=1&&x<=m&&y>=1&&y<=n;
}
void solve(int k)
{
    int x,y,d;
    char z[10];
    scanf("%d%d%s",&x,&y,z);
    if(z[0]=='U') d=0;
    else if(z[0]=='R') d=1;
    else if(z[0]=='D') d=2;
    else if(z[0]=='L') d=3;
    for(int i=1;i<=m;++i)
    {
        scanf("%s",a[i]+1);
    }
    for(int i=0;i<=m+1;++i)
    {
        for(int j=0;j<=n+1;++j)
        {
            f[i][j][0]=f[i][j][1]=f[i][j][2]=f[i][j][3]=-1;
        }
    }
    ll s1=0,s2=0,t=0;
    while(true)
    {
        d=(d+a[x][y]-'0')%4;
        if(!check(x+dx[d],y+dy[d])) d=dn[d];
        if(f[x][y][d]!=-1)
        {
            s1=f[x][y][d]-1,s2=t;
            break;
        }
        f[x][y][d]=++t;
        x+=dx[d],y+=dy[d];
    }
    f1[k]=s1;
    f2[k]=s2-s1;
    for(int i=0;i<4;++i)
    {
        if(f[ex][ey][i]!=-1)
        {
            if(f[ex][ey][i]<=s1) g1[k][++h1[k]]=f[ex][ey][i];
            else g2[k][++h2[k]]=f[ex][ey][i];
        }
    }
}
bool check1(ll x)
{
    for(int i=1;i<=k;++i)
    {
        bool u=false;
        for(int j=1;j<=h1[i];++j)
        {
            if(g1[i][j]==x) u=true;
        }
        for(int j=1;j<=h2[i];++j)
        {
            if(x>f1[i]&&(x-f1[i])%f2[i]==(g2[i][j]-f1[i])%f2[i]) u=true;
        }
        if(u==false) return false;
    }
    return true;
}
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll solve(ll x1,ll y1,ll x2,ll y2)
{
    ll p=(x2-x1%y2+y2)%y2,k1,k2,z=gcd(y1,y2);
    if(p%z!=0) return -1e18;
    exgcd(y1,y2,k1,k2);
    k1=k1*(p/z)%(y2/z);
    return (x1+y1*k1)%(y1/z*y2);
}
void dfs(int x,ll x1,ll y1)
{
    if(x==k+1)
    {
        for(int i=1;i<=k;++i)
        {
            if(x1<b[i])
            {
                x1+=((b[i]-x1-1)/y1+1)*y1;
            }
        }
        s=min(s,x1);
        return;
    }
    if(x1>s) return;
    for(int i=1;i<=h2[x];++i)
    {   
        ll x2=g2[x][i],y2=f2[x],z=solve(x1,y1,x2,y2);
        if(z==-1e18) continue;
        b[x]=g2[x][i];
        dfs(x+1,z,y1/gcd(y1,y2)*y2);
    }
}
int main()
{
    // freopen("bakterije.in","r",stdin);
    // freopen("bakterije.out","w",stdout);
    scanf("%d%d%d%d%d",&m,&n,&k,&ex,&ey);
    for(int i=1;i<=k;++i) solve(i);
    for(int i=1;i<=k;++i)
    {
        for(int j=1;j<=h1[i];++j)
        {
            if(check1(g1[i][j])) s=min(s,g1[i][j]);
        }
    }
    // for(int i=1;i<=k;++i)
    // {
    //     for(int j=1;j<=h2[i];++j)
    //     {
    //         printf("%d %d\n",g2[i][j],f2[i]);
    //     }
    // }
    dfs(1,0,1);
    if(s==9223372036854775807) printf("-1");
    else printf("%lld",s);
    return 0;
}