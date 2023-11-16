#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001,M=200000;
int n,a[N],b[N],f[N][2],g[N];
vector<int> c[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        ++b[a[i]];
    }
    for(int i=2;i<=M;++i)
    {
        for(int j=i*2;j<=M;j+=i) b[i]+=b[j];
    }
    for(int i=M;i>=2;--i)
    {
        for(int j=i;j<=M;j+=i) c[j].push_back(i);
    }
    for(int i=2;i<=M;++i)
    {
        for(auto j:c[i]) g[j]=b[j];
        for(auto j:c[i])
        {
            if(j!=i&&g[j]!=0)
            {
                f[i][0]|=(!f[j][1]);
                f[i][1]|=(!f[j][0]);
            }
            for(auto k:c[j]) if(k!=j) g[k]-=g[j];
        }
        if(f[i][0]==false&&f[i][1]==false) f[i][b[i]%2]=true;
    }
    for(int i=1;i<=n;++i)
    {
        if(f[a[i]][0]==true) printf("Aoki\n");
        else printf("Takahashi\n");
    }
    return 0;
}