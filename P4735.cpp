#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,tot=0,a[N<<4][2],b[N],g[N<<4],h[N<<4],rt[N];
void add(int x,int k,int k2,int t)
{
    for(int i=30;i>=0;--i)
    {
        int z=(x&(1<<i))!=0;
        if(k2!=0) a[k][z^1]=a[k2][z^1];
        a[k][z]=++tot;
        k=a[k][z];
        g[k]=max(g[k],t);
        if(k2!=0&&a[k2][z]) k2=a[k2][z];
        else k2=0;
    }
    h[k]=x;
}
int find(int x,int k,int t)
{
    if(k==0) return 0;
    for(int i=30;i>=0;--i)
    {
        int z=(x&(1<<i))==0;
        if(a[k][z]!=0&&g[a[k][z]]>=t) k=a[k][z];
        else k=a[k][z^1];
    }
    return h[k];
}
int main()
{
    scanf("%d%d",&n,&m);
    rt[0]=++tot;
    add(0,rt[0],0,0);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        b[i]^=b[i-1];
        rt[i]=++tot;
        add(b[i],rt[i],rt[i-1],i);
    }
    for(int i=1;i<=m;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='A')
        {
            ++n;
            scanf("%d",&b[n]);
            b[n]^=b[n-1];
            rt[n]=++tot;
            add(b[n],rt[n],rt[n-1],n);
        }
        else if(z[0]=='Q')
        {
            int x,l,r;
            scanf("%d%d%d",&l,&r,&x);
            x^=b[n];
            printf("%d\n",find(x,rt[r-1],l-1)^x);
        }
    }
    return 0;
}