#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001,M=21;
const ll P=998244353;
int n,m,q,f[N][M];
struct str
{
    int l,r;
    str() {}
    str(int l,int r):l(l),r(r) {}
    friend bool operator<(str a,str b)
    {
        if(a.l!=b.l) return a.l<b.l;
        else return a.r>b.r;
    }
}a[N],b[N];
pair<int,int> find(int x,int r)
{
    int t=0,s=0;
    while(t>=0)
    {
        if(a[f[x][t]].r<=r) x=f[x][t],s+=(1<<t),++t;
        else --t;
    }
    return make_pair(x,s);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].l,&a[i].r);
    }
    sort(a+1,a+n+1);
    int p=2e9;
    for(int i=n;i>=1;--i)
    {
        if(a[i].r<p)
        {
            p=a[i].r;
            b[++q]=a[i];
        }
    }
    swap(a,b);
    n=q;
    sort(a+1,a+n+1);
    int x=1;
    for(int i=1;i<=n;++i)
    {
        while(x<=n&&a[x].r<a[i].l)
        {
            f[x][0]=i;
            ++x;
        }
    }
    for(int i=x;i<=n;++i) f[i][0]=n+1;
    f[n+1][0]=n+1;
    a[n+1].l=a[n+1].r=2e9;
    for(int i=1;i<=20;++i)
    {
        for(int j=1;j<=n+1;++j)
        {
            f[j][i]=f[f[j][i-1]][i-1];
        }
    }
    for(int i=1;i<=m;++i)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        int x=lower_bound(a+1,a+n+1,str(l,2e9))-a,y=lower_bound(a+1,a+n+1,str(l+1,2e9))-a;
        // printf("%d %d %d %d\n",a[x].l,a[x].r,a[y].l,a[y].r);
        if(a[x].l==l&&a[x].r==r)
        {
            printf("%lld\n",P-1);
            continue;
        }
        if(a[x].l!=l||a[y].r>r)
        {
            printf("0\n");
            continue;
        }
        auto [px,s1]=find(x,r);
        auto [py,s2]=find(y,r);
        if(px==py||(a[px].r!=r&&a[py].r!=r))
        {
            printf("0\n");
            continue;
        }
        if((s1+s2)%2==1) printf("%lld\n",P-1);
        else printf("%lld\n",1);
    }
    return 0;
}