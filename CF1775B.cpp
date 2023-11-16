#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=300001;
int n,h[N],b[N];
vector<int> a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            a[i].clear();
            a[i].push_back(0);
            scanf("%d",&b[i]);
            for(int j=1;j<=b[i];++j) 
            {
                int x;
                scanf("%d",&x);
                a[i].push_back(x);
                ++h[x];
            }
        }
        bool u=false;
        for(int i=1;i<=n;++i)
        {
            int w=0;
            for(int j=1;j<=b[i];++j)
            {
                if(h[a[i][j]]>1) ++w;
            }
            if(w==b[i])
            {
                u=true;
                break;
            }
        }
        if(u) printf("Yes\n");
        else printf("No\n");
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=b[i];++j) h[a[i][j]]=0;
        }
    }
    return 0;
}