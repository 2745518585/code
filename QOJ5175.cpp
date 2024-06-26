#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=201,M=8;
int n,m,q,b[N],f[1<<M][N][N];
vector<pair<int,pair<int,int>>> a[N];
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=q;++i)
    {
        scanf("%d",&b[i]);
    }
    for(int i=1;i<=m;++i)
    {
        int x,y,w1,w2;
        scanf("%d%d%d%d",&x,&y,&w1,&w2);
        a[x].push_back(make_pair(y,make_pair(w1,w2)));
    }
    for(int i=1;i<=(1<<q)-1;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=0;k<=m;++k) f[i][j][k]=1e9;
        }
    }
    for(int i=1;i<=q;++i)
    {
        for(int j=0;j<=m;++j) f[1<<(i-1)][b[i]][j]=0;
    }
    for(int i=0;i<=(1<<q)-1;++i)
    {
        for(int j=1;j<=n;++j)
        {
            for(int k=i;k;k=(k-1)&i)
            {
                int p=0;
                for(int l=0;l<=m;++l)
                {
                    while(p<=m&&f[i^k][j][p]>f[k][j][l]) ++p;
                    f[i][j][l+p]=min(f[i][j][l+p],f[k][j][l]);
                }
            }
            for(int k=1;k<=m;++k) f[i][j][k]=min(f[i][j][k],f[i][j][k-1]);
        }
        for(int p=1;p<=m;++p)
        {
            for(int j=1;j<=n;++j)
            {
                for(auto k:a[j])
                {
                    for(int l=0;l<=m;++l)
                    {
                        f[i][j][l]=min(f[i][j][l],f[i][k.first][l]+k.second.first);
                        if(l>0) f[i][j][l]=min(f[i][j][l],f[i][k.first][l-1]+k.second.second);
                    }
                }
            }
        }
    }
    for(int i=0;i<=m;++i)
    {
        printf("%d ",f[(1<<q)-1][1][i]);
    }
    return 0;
}