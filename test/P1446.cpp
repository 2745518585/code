#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=101;
int n,m,s1,s2,s3,a[N];
bool h[N];
ll P,f[N][N][N];
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
    x=(x%P+P)%P;
    return x;
}
int dfs(int x)
{
    if(h[x]) return 0;
    h[x]=true;
    return dfs(a[x])+1;
}
int main()
{
    scanf("%d%d%d%d%lld",&s1,&s2,&s3,&m,&P);
    n=s1+s2+s3;
    ll s=0;
    for(int i=0;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i==0) a[j]=j;
            else scanf("%d",&a[j]);
            h[j]=false;
        }
        for(int p1=0;p1<=s1;++p1) for(int p2=0;p2<=s2;++p2) for(int p3=0;p3<=s3;++p3) f[p1][p2][p3]=0;
        f[0][0][0]=1;
        for(int j=1;j<=n;++j)
        {
            if(h[j]) continue;
            int w=dfs(j);
            for(int p1=s1;p1>=0;--p1) for(int p2=s2;p2>=0;--p2) for(int p3=s3;p3>=0;--p3)
            {
                if(w<=p1) f[p1][p2][p3]=(f[p1][p2][p3]+f[p1-w][p2][p3])%P;
                if(w<=p2) f[p1][p2][p3]=(f[p1][p2][p3]+f[p1][p2-w][p3])%P;
                if(w<=p3) f[p1][p2][p3]=(f[p1][p2][p3]+f[p1][p2][p3-w])%P;
            }
        }
        s+=f[s1][s2][s3];
    }
    printf("%lld\n",s*inv(m+1)%P);
    return 0;
}