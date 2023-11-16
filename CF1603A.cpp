#include<cstdio>
#include<algorithm>
using namespace std;
bool check(int x,int k)
{
    for(int i=2;i<=min(k,30);++i)
    {
        if(x%i!=0) return true;
    }
    return false;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        bool u=true;
        for(int i=1;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            if(!check(x,i+1)) u=false;
        }
        if(u) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}