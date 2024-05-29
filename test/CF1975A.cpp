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
        int x=1;
        while(x+1<=n&&a[x]<=a[x+1]) ++x;
        bool u=true;
        for(int i=x+1;i<=n;++i)
        {
            if(i+1<=n&&a[i]>a[i+1]) u=false;
            if(a[i]>a[1]) u=false;
        }
        if(u) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}