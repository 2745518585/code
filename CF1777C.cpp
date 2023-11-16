#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=200001;
int n,m,s,a[N],f[N];
vector<int> b[N];
void add(int x)
{
    if(f[x]==0) ++s;
    ++f[x];
}
void del(int x)
{
    if(f[x]==1) --s;
    --f[x];
}
int main()
{
    for(int i=1;i<=100000;++i)
    {
        for(int j=1;i*j<=100000;++j) b[i*j].push_back(i);
    }
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        sort(a+1,a+n+1);
        for(int i=1;i<=m;++i) f[i]=0;
        s=0;
        int x=0,w=1e9;
        for(int i=1;i<=n;++i)
        {
            if(i>1)
            {
                for(int j=0;b[a[i-1]][j]<=m&&j<b[a[i-1]].size();++j) del(b[a[i-1]][j]);
            }
            while(x+1<=n&&s<m)
            {
                ++x;
                for(int j=0;b[a[x]][j]<=m&&j<b[a[x]].size();++j) add(b[a[x]][j]);
            }
            if(s==m) w=min(w,a[x]-a[i]);
        }
        printf("%d\n",w==1e9?-1:w);
    }
    return 0;
}