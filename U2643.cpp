#include<bits/stdc++.h>
using namespace std;
const int N=20001,M=2000001;
int n,m,d,k,s,t[N],p=1,b[N],l[N],f[N],g[N];
bool h[N];
struct road
{
    int m,q;
}a[M<<1];
bool cmp(int a,int b)
{
    if(l[a]!=l[b]) return l[a]<l[b];
    return f[a]<f[b];
}
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
bool check(int x)
{
    int s=0;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m]==true)
        {
            if(g[a[i].m]+1>=d) return false;
            ++s;
        }
    }
    if(s<d) return true;
    return false;
}
void add(int x)
{
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m]==true) ++g[a[i].m],++g[x];
    }
}
void del(int x)
{
    h[x]=true;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(h[a[i].m]==false) --l[a[i].m],--l[x];
    }
}
void abc()
{
    while(s<n)
    {
        for(int i=1;i<=k*n;++i) b[i]=i,f[i]=rand();
        sort(b+1,b+k*n+1);
        s=0;
        for(int i=1;i<=k*n&&s<n;++i)
        {
            if(check(b[i])) add(b[i]),++s;
        }
    }
    for(int i=1;i<=k*n;++i)
    {
        if(h[i]) printf("%d ",i);
    }
}
int main()
{
    scanf("%d%d%d%d",&k,&n,&d,&m);
    srand(time(NULL));
    int z=0;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
        ++l[x],++l[y];
        z=max(z,max(l[x],l[y]));
    }
    if(z<=k)
    {
        abc();
        return 0;
    }
    for(int i=1;i<=k*n-n;++i)
    {
        int x=0;
        for(int j=1;j<=k*n;++j)
        {
            if(l[j]>l[x]) x=j;
        }
        del(x);
    }
    for(int i=1;i<=k*n;++i)
    {
        if(h[i]==false) printf("%d ",i);
    }
    return 0;
}