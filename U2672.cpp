#include<bits/stdc++.h>
using namespace std;
const int N=500001,M=51;
int n,m,q,b[N][M],b2[N][M],pow2[N];
struct str
{
    int l,r;
}a[N];
bool cmp(str a,str b)
{
    return a.l<b.l;
}
int solve(int x,int y,int k)
{
    int s=0;
    while(x<y)
    {
        for(int i=30;i>=1;--i)
        {
            if(b[x][i]!=0&&b[x][i]<y&&(b[x][i]<a[k].l||x>a[k].r))
            {
                s+=pow2[i];
                x=b[x][i];
            }
            if(b2[x][i]!=0&&b2[x][i]<y&&(x>a[k].l&&b2[x][i]<a[k].r))
            {
                s+=pow2[i];
                x=b2[x][i];
            }
        }
        int z=(x>=a[k].l&&b[x][0]==a[k].r)?b2[x][0]:b[x][0];
        if(z<=x) return -1;
        else x=z,++s;
    }
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&a[i].l,&a[i].r);
    }
    for(int i=1;i<=m;++i)
    {
        if(a[i].r>b[a[i].l][0])
        {
            b2[a[i].l][0]=b[a[i].l][0];
            b[a[i].l][0]=a[i].r;
        }
        else if(a[i].r>b2[a[i].l][0])
        {
            b2[a[i].l][0]=a[i].r;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(b[i-1][0]>b[i][0])
        {
            b2[i][0]=b[i][0];
            b[i][0]=b[i-1][0];
        }
        else if(b[i-1][0]>b2[i][0])
        {
            b2[i][0]=b[i-1][0];
        }
        if(b2[i-1][0]>b2[i][0]) b2[i][0]=b2[i-1][0];
    }
    pow2[0]=1;
    for(int i=1;i<=30;++i) pow2[i]=pow2[i-1]*2;
    for(int i=1;i<=30;++i)
    {
        for(int j=1;j<=n;++j)
        {
            b[j][i]=b[b[j][i-1]][i-1];
            b2[j][i]=b2[b2[j][i-1]][i-1];
        }
    }
    scanf("%d",&q);
    for(int i=1;i<=q;++i)
    {
        int k,x,y;
        scanf("%d%d%d",&k,&x,&y);
        if(x>=y) printf("0\n");
        else printf("%d\n",solve(x,y,k));
    }
    return 0;
}