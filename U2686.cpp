#include<bits/stdc++.h>
using namespace std;
const int N=110001,M=18;
int n,m,q,a[N],pw[N],lg[N],b1[N][M+1][M+1],b2[N][M+1][M+1];
int sum1(int x,int y,int k)
{
    if(x>=y) return n+1;
    --y;
    return min(b1[x][lg[y-x]][k],b1[y-pw[lg[y-x]]+1][lg[y-x]][k]);
}
int sum2(int x,int y,int k)
{
    if(x>=y) return 0;
    --y;
    return max(b2[x][lg[y-x]][k],b2[y-pw[lg[y-x]]+1][lg[y-x]][k]);
}
void init()
{
    for(int i=1;i<=n-1;++i)
    {
        b1[i][0][0]=min(a[i],a[i+1]);
        b2[i][0][0]=max(a[i],a[i+1]);
        lg[i]=log2(i);
    }
    q=log2(n-1);
    pw[0]=1;
    for(int i=1;i<=q;++i) pw[i]=pw[i-1]*2;
    for(int r=0;r<=M;++r)
    {
        if(r!=0)
        {
            for(int i=1;i<=n-1;++i)
            {
                b1[i][0][r]=sum1(b1[i][0][r-1],b2[i][0][r-1],r-1);
                b2[i][0][r]=sum2(b1[i][0][r-1],b2[i][0][r-1],r-1);
            }
        }
        for(int i=1;i<=q;++i)
        {
            for(int j=1;j<=n-pw[i];++j)
            {
                b1[j][i][r]=min(b1[j][i-1][r],b1[j+pw[i-1]][i-1][r]);
                b2[j][i][r]=max(b2[j][i-1][r],b2[j+pw[i-1]][i-1][r]);
            }
        }
    }
}
int check(int x,int y)
{
    if(x==1&&y==n) return 0;
    if(sum1(x,y,M)!=1||sum2(x,y,M)!=n) return -1;
    int s=0;
    for(int i=M;i>=0;--i)
    {
        if(sum1(x,y,i)!=1||sum2(x,y,i)!=n)
        {
            s+=(1<<i);
            int x0=sum1(x,y,i),y0=sum2(x,y,i);
            x=x0,y=y0;
        }
    }
    return s+1;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    init();
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        int z=check(x,y);
        if(z==-1) printf("qwq\n");
        else printf("%d\n",z);
    }
    return 0;
}