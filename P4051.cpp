#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=200001,M=128;
int n,m,h[N],x1[N],x2[N],sa[101][N],rk[101][N],he[N];
char a[N];
struct str
{
    int a[101],x;
}b[N];
bool cmp(str a,str b)
{
    for(int i=20;i>=0;--i)
    {
        if(a.a[i]!=b.a[i]) return a.a[i]<b.a[i];
    }
    return false;
}
void init()
{
    for(int i=1;i<=n;++i)
    {
        ++h[a[i]];
        x1[i]=a[i];
    }
    for(int i=1;i<=m;++i) h[i]+=h[i-1];
    for(int i=n;i>=1;--i) sa[0][h[x1[i]]--]=i;
    for(int i=1;i<=n;++i) rk[0][sa[0][i]]=i;
    for(int r=0;(1<<r)<=n;++r)
    {
        int p=0;
        for(int i=n-(1<<r)+1;i<=n;++i) x2[++p]=i;
        for(int i=1;i<=n;++i) if(sa[r][i]>(1<<r)) x2[++p]=sa[r][i]-(1<<r);
        for(int i=1;i<=m;++i) h[i]=0;
        for(int i=1;i<=n;++i) ++h[x1[i]];
        for(int i=1;i<=m;++i) h[i]+=h[i-1];
        for(int i=n;i>=1;--i) sa[r+1][h[x1[x2[i]]]--]=x2[i],x2[i]=0;
        swap(x1,x2);
        p=0;
        x1[sa[r+1][1]]=++p;
        for(int i=2;i<=n;++i)
        {
            if(x2[sa[r+1][i]]==x2[sa[r+1][i-1]]&&x2[sa[r+1][i]+(1<<r)]==x2[sa[r+1][i-1]+(1<<r)]) x1[sa[r+1][i]]=p;
            else x1[sa[r+1][i]]=++p;
        }
    	for(int i=1;i<=n;++i) rk[r+1][sa[r+1][i]]=i;
        if(p==n) break;
        m=p;
    }
}
int main()
{
    scanf("%s",a+1);
    n=strlen(a+1),m=M;
    for(int i=1;i<=n;++i) a[i+n]=a[i];
    n*=2;
    init();
    n/=2;
    for(int i=1;i<=n;++i)
    {
        int k=i;
        b[i].x=i;
        for(int j=20;j>=0;--j)
        {
            if((n&(1<<j))!=0)
            {
                b[i].a[j]=rk[j][k];
                k+=(1<<j);
            }
            else b[i].a[j]=0;
        }
    }
    sort(b+1,b+n+1,cmp);
    for(int i=1;i<=n;++i)
    {
    	putchar(a[b[i].x+n-1]);
    }
    return 0;
}