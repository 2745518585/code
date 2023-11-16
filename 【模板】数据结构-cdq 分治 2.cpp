#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,q,T[N],f[N],g[N],h[N];
struct str
{
    int a,b,c,t;
}a[N];
bool cmp(str a,str b)
{
    if(a.a!=b.a) return a.a<b.a;
    if(a.b!=b.b) return a.b<b.b;
    return a.c<b.c;
}
bool cmp2(str a,str b)
{
    if(a.b!=b.b) return a.b<b.b;
    if(a.a!=b.a) return a.a<b.a;
    return a.c<b.c;
}
void add(int x,int k)
{
    T[x]+=k;
    while(x<=m)
    {
        x+=(x&-x);
        T[x]+=k;
    }
}
int sum(int x)
{
    int s=T[x];
    while(x>=1)
    {
        x-=(x&-x);
        s+=T[x];
    }
    return s;
}
void cdq(int l,int r)
{
    if(l>=r) return;
    int z=l+r>>1;
    str p=a[z+1];
    cdq(l,z);
    sort(a+l,a+r+1,cmp2);
    for(int i=l;i<=r;++i)
    {
        if(cmp(a[i],p)) add(a[i].c,h[a[i].t]);
        else g[a[i].t]+=sum(a[i].c);
    }
    for(int i=l;i<=r;++i) if(cmp(a[i],p)) add(a[i].c,-h[a[i].t]);
    sort(a+l,a+r+1,cmp);
    cdq(z+1,r);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d%d",&a[i].a,&a[i].b,&a[i].c);
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;++i)
    {
        if(a[i].a!=a[q].a||a[i].b!=a[q].b||a[i].c!=a[q].c) a[++q]=a[i];
        ++h[q];
    }
    for(int i=1;i<=q;++i) a[i].t=i;
    cdq(1,q);
    for(int i=1;i<=q;++i)
    {
        f[g[i]+h[i]-1]+=h[i];
    }
    for(int i=0;i<=n-1;++i)
    {
        printf("%d\n",f[i]);
    }
    return 0;
}