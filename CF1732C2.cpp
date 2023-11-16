#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200001,M=32;
int n,m,a[N],b[N][M][2],c[N][M];
struct str
{
    int l,r;
}d[M][2];
int check(int x)
{
    int s=x;
    for(int i=0;i<=30;++i)
    {
        if(d[i][0].l==-1) continue;
        if(d[i][0].l>=x) s=max(s,d[i][0].r);
        else if(d[i][1].l>=x) s=max(s,d[i][1].r);
        else return 1e9;
    }
    return s;
}
void abc()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        for(int j=0;j<=30;++j)
        {
            c[i][j]=c[i-1][j]+((a[i]&(1<<j))!=0);
        }
    }
    for(int i=0;i<=n+1;++i)
    {
        for(int j=0;j<=30;++j) b[i][j][0]=b[i][j][1]=0;
    }
    for(int i=n;i>=1;--i)
    {
        for(int j=0;j<=30;++j)
        {
            if((a[i]&(1<<j))!=0) b[i][j][0]=i;
            else b[i][j][0]=b[i+1][j][0];
        }
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=30;++j)
        {
            if((a[i]&(1<<j))!=0) b[i][j][1]=i;
            else b[i][j][1]=b[i-1][j][1];
        }
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        for(int j=0;j<=30;++j)
        {
            if(c[y][j]-c[x-1][j]<=1)
            {
                d[j][0]=d[j][1]=(str){-1,-1};
                continue;
            }
            if((c[y][j]-c[x-1][j])%2!=0)
            {
                d[j][0]=(str){b[x][j][0],b[b[y][j][1]-1][j][1]};
                d[j][1]=(str){b[b[x][j][0]+1][j][0],b[y][j][1]};
            }
            else
            {
                d[j][0]=d[j][1]=(str){b[x][j][0],b[y][j][1]};
            }
        }
        int s=check(x)-x+1,q=x;
        for(int j=0;j<=30;++j)
        {
            if(d[j][0].l==-1) continue;
            int z=check(d[j][0].l)-d[j][0].l+1;
            if(z<s) s=z,q=d[j][0].l;
            z=check(d[j][1].l)-d[j][1].l+1;
            if(z<s) s=z,q=d[j][1].l;
        }
        printf("%d %d\n",q,q+s-1);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}