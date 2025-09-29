#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N],f[N];
vector<int> b[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) f[i]=0,b[i].clear();
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            b[a[i]].push_back(i);
            f[i]=f[i-1];
            if(b[a[i]].size()>=a[i]) f[i]=max(f[i],f[b[a[i]][b[a[i]].size()-a[i]]-1]+a[i]);
        }
        printf("%d\n",f[n]);
    }
    return 0;
}