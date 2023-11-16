#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
bool h[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        int s=0;
        for(int i=1;i<=n;++i)
        {
            int k;
            scanf("%d",&k);
            for(int j=1;j<=20;++j) h[j]=false;
            for(int j=1;j<=k;++j)
            {
                int x;
                scanf("%d",&x);
                h[x]=true;
            }
            int z=-1;
            for(int j=20;j>=0;--j)
            {
                if(h[j]) continue;
                if(z!=-1)
                {
                    s^=(z-j-1);
                    z=-1;
                }
                else z=j;
            }
        }
        if(s) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}