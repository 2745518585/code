#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n;
int sum(int x)
{
    int s=0;
    while(x%2==1) x/=2,++s;
    return s;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int s=0;
        for(int i=1;i<=n/2;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            s^=sum((x-1)|(y-1));
        }
        if(s) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}