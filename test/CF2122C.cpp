#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N],b[N],c[N],d[N],f[N];
vector<int> h[4];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d",&a[i],&b[i]);
            c[i]=d[i]=i;
            f[i]=0;
        }
        sort(c+1,c+n+1,[](int x,int y){return a[x]<a[y];});
        sort(d+1,d+n+1,[](int x,int y){return b[x]<b[y];});
        for(int i=1;i<=n;++i)
        {
            if(i>n/2) f[c[i]]+=1,f[d[i]]+=2;
        }
        h[0].clear();
        h[1].clear();
        h[2].clear();
        h[3].clear();
        for(int i=1;i<=n;++i) h[f[i]].push_back(i);
        while(!h[0].empty())
        {
            printf("%d %d\n",h[0].back(),h[3].back());
            h[0].pop_back();
            h[3].pop_back();
        }
        while(!h[1].empty())
        {
            printf("%d %d\n",h[1].back(),h[2].back());
            h[1].pop_back();
            h[2].pop_back();
        }
    }
    return 0;
}