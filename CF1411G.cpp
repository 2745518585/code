#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001,M=512;
const ll P=998244353;
int n,m,p=1,t[N],t2[N],l[N],f[N],g[N],h[N];
ll b[M+1][M+1],c[M+1];
struct road
{
    int m,q;
}a[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void road2(int x,int y)
{
    a[++p].m=y;
    a[p].q=t2[x];
    t2[x]=p;
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0) x=1,y=0;
    else exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a)
{
    a=(a%P+P)%P;
    ll x,y;
    exgcd(a,P,x,y);
    return (x%P+P)%P;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(y,x);
        road2(x,y);
        ++l[x];
    }
    queue<int> Q;
    for(int i=1;i<=n;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t2[k];i!=0;i=a[i].q) h[f[a[i].m]]=k;
        f[k]=0;
        while(h[f[k]]==k) ++f[k];
        for(int i=t[k];i!=0;i=a[i].q)
        {
            --l[a[i].m];
            if(l[a[i].m]==0) Q.push(a[i].m);
        }
    }
    for(int i=1;i<=n;++i) ++g[f[i]];
    for(int i=1;i<=M-1;++i)
    {
        for(int j=1;j<=M;++j)
        {
            b[i][j]=inv(n+1)*g[i^(j-1)]%P;
        }
        b[i][i+1]=(b[i][i+1]-1+P)%P;
        c[i]=0;
    }
    for(int i=1;i<=M;++i) b[M][i]=1;
    c[M]=1;
    for(int i=1;i<=M;++i)
    {
        int k=i;
        for(int j=i+1;j<=M;++j)
        {
            if(abs(b[j][i])>abs(b[k][i])) k=j;
        }
        for(int j=1;j<=M;++j) swap(b[i][j],b[k][j]);
        swap(c[i],c[k]);
        for(int j=1;j<=M;++j)
        {
            if(i==j) continue;
            ll z=b[j][i]*inv(b[i][i])%P;
            c[j]=(c[j]-c[i]*z)%P;
            for(int l=1;l<=M;++l) b[j][l]=(b[j][l]-b[i][l]*z)%P;
        }
    }
    printf("%lld",(1-c[1]*inv(b[1][1])%P+P)%P);
    return 0;
}