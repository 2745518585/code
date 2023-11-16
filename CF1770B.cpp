#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
int n,m;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        int x=0,y=n+1;
        for(int i=1;i<=n;++i)
        {
            if(i%2==0) printf("%d ",++x);
            else printf("%d ",--y);
        }
        printf("\n");
    }
    return 0;
}