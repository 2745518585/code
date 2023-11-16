#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=100001,M=20;
int n,m,q,a[N],b1[N][M],b2[N][M],lg[N],pw[M];
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;++i)
    {
        a[i]=read();
        b1[i][0]=b2[i][0]=a[i];
        lg[i]=log2(i);
    }
    q=log2(n);
    pw[0]=1;
    for(int i=1;i<=q;++i) pw[i]=pw[i-1]*2;
    for(int i=1;i<=q;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(j+pw[i]-1<=n) b1[j][i]=min(b1[j][i-1],b1[j+pw[i-1]][i-1]);
            if(j-pw[i]+1>=1) b2[j][i]=min(b2[j][i-1],b2[j-pw[i-1]][i-1]);
        }
    }
    for(int i=1;i<=m;++i)
    {
        int x=read(),y=read();
        printf("%d ",min(b1[x][lg[y-x]],b2[y][lg[y-x]]));
    }
    return 0;
}