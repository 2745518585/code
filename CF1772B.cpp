#include<cstdio>
#include<algorithm>
using namespace std;
int a[11][11];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d",&a[0][0],&a[0][1],&a[1][0],&a[1][1]);
        int s1=min(min(a[0][0],a[0][1]),min(a[1][0],a[1][1])),s2=max(max(a[0][0],a[0][1]),max(a[1][0],a[1][1]));
        bool u=false;
        for(int i=0;i<=1;++i)
        {
            for(int j=0;j<=1;++j)
            {
                if(a[i][j]==s1&&a[i^1][j^1]==s2)
                {
                    u=true;
                    break;
                }
            }
        }
        if(u) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}