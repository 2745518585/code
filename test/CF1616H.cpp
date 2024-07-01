#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5000001;
const ll P=998244353;
int n,k,tot=1,a[N][2],g[N];
ll pw[N];
void add(int x)
{
    int q=1;
    for(int i=30;i>=0;--i)
    {
        int z=(x&(1<<i))!=0;
        if(a[q][z]==0) a[q][z]=++tot;
        ++g[q];
        q=a[q][z];
    }
    ++g[q];
}
ll solve(int x,int y,int t)
{
    if(t==-1||x==0||y==0) return pw[g[x]]*pw[g[y]]%P;
    if((k&(1<<t))==0)
    {
        return (solve(a[x][0],a[y][0],t-1)+solve(a[x][1],a[y][1],t-1)-1+pw[g[x]]-pw[g[a[x][0]]]-pw[g[a[x][1]]]+1+pw[g[y]]-pw[g[a[y][0]]]-pw[g[a[y][1]]]+1)%P;
    }
    else
    {
        return solve(a[x][0],a[y][1],t-1)*solve(a[x][1],a[y][0],t-1)%P;
    }
}
ll solve(int x,int t)
{
    if(t==-1||x==0) return pw[g[x]];
    if((k&(1<<t))==0)
    {
        return (solve(a[x][0],t-1)+solve(a[x][1],t-1)-1)%P;
    }
    else
    {
        return solve(a[x][0],a[x][1],t-1);
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    pw[0]=1;
    for(int i=1;i<=n;++i) pw[i]=pw[i-1]*2%P;
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        add(x);
    }
    printf("%lld",((solve(1,30)-1)%P+P)%P);
    return 0;
}