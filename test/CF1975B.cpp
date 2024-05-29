#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,a[N];
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        int x=1e9;
        for(int i=1;i<=n;++i)
        {
            x=min(x,a[i]);
        }
        int y=1e9;
        for(int i=1;i<=n;++i)
        {
            if(a[i]%x!=0) y=min(y,a[i]);
        }
        bool u=true;
        for(int i=1;i<=n;++i)
        {
            if(a[i]%x!=0&&a[i]%y!=0) u=false;
        }
        if(u) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}