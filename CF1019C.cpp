#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m;
bool h[N];
vector<int> a[N];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
    }
    for(int i=1;i<=n;++i)
    {
        if(h[i]) continue;
        for(auto j:a[i])
        {
            if(j>i) h[j]=true;
        }
    }
    for(int i=n;i>=1;--i)
    {
        if(h[i]) continue;
        for(auto j:a[i])
        {
            if(j<i) h[j]=true;
        }
    }
    int s=0;
    for(int i=1;i<=n;++i) s+=!h[i];
    printf("%d\n",s);
    for(int i=1;i<=n;++i)
    {
        if(!h[i]) printf("%d ",i);
    }
    return 0;
}