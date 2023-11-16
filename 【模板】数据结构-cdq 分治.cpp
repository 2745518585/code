#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,q,b[N],c[N],T[N],f[N],g[N],h[N];
struct str
{
    int a,b,c;
}a[N];
bool cmp(str a,str b)
{
    if(a.a!=b.a) return a.a<b.a;
    if(a.b!=b.b) return a.b<b.b;
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
void cdq(int b[],int n)
{
    if(n==1) return;
    int m=n>>1;
    cdq(b,m);
    cdq(b+m,n-m);
    for(int i=1;i<=n;++i) c[i]=b[i];
    int x=1,y=m+1;
    for(int i=1;i<=n;++i)
    {
        if(x<=m&&(y>n||a[c[x]].b<=a[c[y]].b))
        {
            b[i]=c[x];
            add(a[c[x]].c,h[c[x]]);
            ++x;
        }
        else
        {
            b[i]=c[y];
            g[c[y]]+=sum(a[c[y]].c);
            ++y;
        }
    }
    for(int i=1;i<=m;++i) add(a[c[i]].c,-h[c[i]]);
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
    for(int i=1;i<=q;++i) b[i]=i;
    cdq(b,q);
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