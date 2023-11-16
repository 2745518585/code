#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int P=1e9+7;
int n,m,p,a1[101],a2[101];
ll f[101][2][2][2][2];
ll dfs(int x,bool u1,bool u2,bool u3,bool v)
{
	if(x==0) return v;
    ll &f0=f[x][u1][u2][u3][v];
    if(f0!=-1) return f0;
    f0=0;
    int t1=u1?a1[x]:p-1,t2=u2?a2[x]:p-1;
    for(int i=0;i<=t1;++i)
    {
        for(int j=0;j<=min(u3?i:p-1,t2);++j)
        {
            f0=(f0+dfs(x-1,u1&&i==t1,u2&&j==t2,u3&&j==i,v||i<j)%P)%P;
        }
    }
	return f0%P;
}
int main()
{
    int T;
    scanf("%d%d",&T,&p);
    while(T--)
    {
        ll x,y;
        scanf("%lld%lld",&x,&y);
        memset(f,-1,sizeof(f));
        n=0;
        while(x!=0)
        {
            a1[++n]=x%p;
            x/=p;
        }
        for(int i=1;i<=n;++i) a2[i]=0;
        m=0;
        while(y!=0)
        {
            a2[++m]=y%p;
            y/=p;
        }
        printf("%lld\n",dfs(n,true,true,true,false)%P);
    }
	return 0;
}