#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<=n;++i) a[i]=0;
        for(int i=1;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            ++a[x];
        }
        if(a[0]==0)
        {
            printf("0\n");
            continue;
        }
        int x=0;
        while(a[x]>=2) ++x;
        if(a[x]>0)
        {
            ++x;
            while(a[x]>=2) ++x;
        }
        printf("%d\n",x);
    }
    return 0;
}