#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=2000001;
int n,m,tot=1,las=1,f[N],g[N];
char b[N];
struct sam
{
    int s[2],l,f;
}a[N<<1];
void add(int c)
{
    int x=las,nx=las=++tot;
    a[nx].l=a[x].l+1;
    while(x!=0&&a[x].s[c]==0)
    {
        a[x].s[c]=nx;
        x=a[x].f;
    }
    if(x==0) a[nx].f=1;
    else
    {
        int y=a[x].s[c];
        if(a[x].l+1==a[y].l) a[nx].f=y;
        else
        {
            int ny=++tot;
            a[ny]=a[y];
            a[ny].l=a[x].l+1;
            a[y].f=a[nx].f=ny;
            while(x!=0&&a[x].s[c]==y)
            {
                a[x].s[c]=ny;
                x=a[x].f;
            }
        }
    }
}
bool check(int n,int x)
{
    static int Q[N],T,R;
    T=1,R=0;
    for(int i=1;i<=n;++i)
    {
        if(i-x>=0)
        {
            while(T<=R&&f[Q[R]]-Q[R]<=f[i-x]-(i-x)) --R;
            Q[++R]=i-x;
        }
        while(T<=R&&Q[T]<i-g[i]) ++T;
        f[i]=f[i-1];
        if(T<=R) f[i]=max(f[i],f[Q[T]]+i-Q[T]);
    }
    if(f[n]>=n*0.9) return true;
    return false;
}
void solve()
{
    scanf("%s",b+1);
    int n=strlen(b+1),m=0,x=1;
    for(int i=1;i<=n;++i)
    {
        while(x!=0&&a[x].s[b[i]-'0']==0) x=a[x].f;
        if(x==0) x=1,g[i]=0;
        else
        {
            g[i]=min(g[i-1],a[x].l)+1;
            x=a[x].s[b[i]-'0'];
        }
        m=max(m,g[i]);
    }
    int l=0,r=m;
    while(l<r)
    {
        int z=l+r+1>>1;
        if(check(n,z)) l=z;
        else r=z-1;
    }
    printf("%d\n",l);
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%s",b+1);
        int k=strlen(b+1);
        for(int j=1;j<=k;++j) add(b[j]-'0');
        las=1;
    }
    for(int i=1;i<=m;++i) solve();
    return 0;
}