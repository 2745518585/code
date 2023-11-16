#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=100001;
int n,m,q,a[N],b[N];
ll s,c[N][2];
struct str
{
    int l,r,k;
}d[N];
bool cmp(str a,str b)
{
    if((a.l-1)/q!=(b.l-1)/q) return a.l<b.l;
    return a.r<b.r;
}
void add(int x)
{
    s+=2*b[x]+1;
    ++b[x];
}
void del(int x)
{
    s+=-2*b[x]+1;
    --b[x];
}
void print(ll x,ll y)
{
    if(x==0)
    {
        printf("0/1\n");
        return;
    }
    if(y%x==0)
    {
        printf("1/%lld\n",y/x);
        return;
    }
    for(int i=2;i<=sqrt(x);++i)
    {
        if(x%i==0&&y%(x/i)==0) y/=(x/i),x=i;
        while(x%i==0&&y%i==0) x/=i,y/=i;
    }
    printf("%lld/%lld\n",x,y);
}
int main()
{
    scanf("%d%d",&n,&m);
    q=sqrt(n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&d[i].l,&d[i].r);
        d[i].k=i;
    }
    sort(d+1,d+m+1,cmp);
    int l=1,r=0;
    for(int i=1;i<=m;++i)
    {
        while(d[i].l<l) add(a[--l]);
        while(d[i].r>r) add(a[++r]);
        while(d[i].l>l) del(a[l++]);
        while(d[i].r<r) del(a[r--]);
        c[d[i].k][0]=s-(d[i].r-d[i].l+1);
        c[d[i].k][1]=(ll)(d[i].r-d[i].l+1)*(d[i].r-d[i].l);
    }
    for(int i=1;i<=m;++i)
    {
        print(c[i][0],c[i][1]);
    }
    return 0;
}