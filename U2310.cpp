#include<bits/stdc++.h>
using namespace std;
const int N=201;
int n,m1,m2,g[N][N],f[N][N],Q[N],T,R;
bool h[N][N];
int main()
{
    scanf("%d%d%d",&n,&m1,&m2);
    for(int i=1;i<=n;++i)
    {
        int w1,w2,s,a;
        scanf("%d%d%d%d",&w1,&w2,&s,&a);
        if(s==0)
        {
            for(int j=w1;j<=m1;++j)
            {
                for(int k=w2;k<=m2;++k)
                {
                    f[j][k]=max(f[j][k],f[j-w1][k-w2]+a);
                }
            }
            continue;
        }
        for(int j=0;j<=m1;++j)
        {
            for(int k=0;k<=m2;++k)
            {
                g[j][k]=f[j][k];
                h[j][k]=false;
            }
        }
        for(int j=0;j<=m1;++j)
        {
            for(int k=0;k<=m2;++k)
            {
                if(h[j][k]==true) continue;
                T=0,R=-1;
                for(int l=0;j+l*w1<=m1&&k+l*w2<=m2;++l)
                {
                    h[j+l*w1][k+l*w2]=true;
                    while(T<=R&&l-Q[T]>s) ++T;
                    while(T<=R&&g[j+Q[R]*w1][k+Q[R]*w2]-a*Q[R]<=g[j+l*w1][k+l*w2]-a*l) --R;
                    Q[++R]=l;
                    f[j+l*w1][k+l*w2]=g[j+Q[T]*w1][k+Q[T]*w2]+a*(l-Q[T]);
                }
            }
        }
    }
    printf("%d",f[m1][m2]);
    return 0;
}