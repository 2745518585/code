#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=6000001;
const ll P=998244353;
int n,S[N],g[N][5],h[N][2];
ll f[N];
bool d[N][2];
char a[N];
int check(int x,int v)
{
    int T=0;
    for(int i=x;i<=n;++i)
    {
        S[++T]=(a[i]-'0')^v;
        if(T>=3&&S[T-1]==1&&S[T]==0) T-=2;
        if(T>=3&&S[T-2]==1&&S[T-1]==1&&S[T]==1) T-=2;
        if(T==2&&S[T]==0) return i;
    }
    return n+1;
}
void solve(int v)
{
    int T=0;
    for(int i=n;i>=1;--i)
    {
        S[++T]=(a[i]-'0')^v;
        if(T>=2&&S[T-1]==1&&S[T]==0) T-=2;
        if(T>=3&&S[T-2]==1&&S[T-1]==1&&S[T]==1) T-=2;
        d[i][v]=(T&1)&&(T-(T&&S[T]==1)-(T>1&&S[T-1]==1)>(T&&S[T]==1)+(T>1&&S[T-1]==1));
    }
    g[n+1][0]=g[n+1][1]=g[n+1][2]=g[n+1][3]=g[n+1][4]=n+1;
    for(int i=n;i>=1;--i)
    {
        if((a[i]-'0')^v)
        {
            g[i][0]=g[i][4]=g[i+1][2];
            g[i][1]=g[i+1][3];
            g[i][2]=g[i+1][4];
            g[i][3]=g[i+1][1];
        }
        else
        {
            g[i][0]=g[i][1]=i;
            g[i][2]=g[i+1][0];
            g[i][3]=g[i+1][1];
            g[i][4]=g[i+1][2];
        }
        h[i][v]=g[i][(a[i-1]-'0')^v];
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",a+1);
        n=strlen(a+1);
        for(int i=0;i<=n;++i) f[i]=0;
        int s=0;
        f[0]=1;
        a[0]='0'+'1'-a[1];
        solve(0);
        solve(1);
        for(int i=1;i<=n;++i)
        {
            f[h[i][0]]=(f[h[i][0]]+f[i-1])%P;
            f[h[i][1]]=(f[h[i][1]]+f[i-1])%P;
            if(d[i][a[i]-'0']) s=(s+f[i])%P;
        }
        printf("%d\n",s);
    }
    return 0;
}