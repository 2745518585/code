#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=201;
int m,n,x0,y0,k,Q[N],T=0,R=-1,f[N][N],g[N][N];
char a[N][N];
int main()
{
    scanf("%d%d%d%d%d",&m,&n,&x0,&y0,&k);
    for(int i=1;i<=m;++i)
    {
        scanf("%s",a[i]+1);
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            f[i][j]=-1e9;
        }
    }
    f[x0][y0]=0;
    while(k--)
    {
        int t0,t,d;
        scanf("%d%d%d",&t0,&t,&d);
        t-=t0-1;
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j)
            {
                g[i][j]=f[i][j];
            }
        }
        if(d==1)
        {
            for(int i=1;i<=n;++i)
            {
                T=0,R=-1;
                for(int j=m;j>=1;--j)
                {
                    if(a[j][i]=='x')
                    {
                        T=0,R=-1;
                        continue;
                    }
                    while(T<=R&&Q[T]-j>t) ++T;
                    while(T<=R&&g[Q[R]][i]+Q[R]<=g[j][i]+j) --R;
                    Q[++R]=j;
                    f[j][i]=g[Q[T]][i]+Q[T]-j;
                }
            }
        }
        else if(d==2)
        {
            for(int i=1;i<=n;++i)
            {
                T=0,R=-1;
                for(int j=1;j<=m;++j)
                {
                    if(a[j][i]=='x')
                    {
                        T=0,R=-1;
                        continue;
                    }
                    while(T<=R&&j-Q[T]>t) ++T;
                    while(T<=R&&g[Q[R]][i]-Q[R]<=g[j][i]-j) --R;
                    Q[++R]=j;
                    f[j][i]=g[Q[T]][i]+j-Q[T];
                }
            }
        }
        else if(d==3)
        {
            for(int i=1;i<=m;++i)
            {
                T=0,R=-1;
                for(int j=n;j>=1;--j)
                {
                    if(a[i][j]=='x')
                    {
                        T=0,R=-1;
                        continue;
                    }
                    while(T<=R&&Q[T]-j>t) ++T;
                    while(T<=R&&g[i][Q[R]]+Q[R]<=g[i][j]+j) --R;
                    Q[++R]=j;
                    f[i][j]=g[i][Q[T]]+Q[T]-j;
                }
            }
        }
        else if(d==4)
        {
            for(int i=1;i<=m;++i)
            {
                T=0,R=-1;
                for(int j=1;j<=n;++j)
                {
                    if(a[i][j]=='x')
                    {
                        T=0,R=-1;
                        continue;
                    }
                    while(T<=R&&j-Q[T]>t) ++T;
                    while(T<=R&&g[i][Q[R]]-Q[R]<=g[i][j]-j) --R;
                    Q[++R]=j;
                    f[i][j]=g[i][Q[T]]+j-Q[T];
                }
            }
        }
    }
    int s=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(a[i][j]=='.')
            {
                s=max(s,f[i][j]);
            }
        }
    }
    printf("%d",s);
    return 0;
}