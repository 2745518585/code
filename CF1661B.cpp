#include<cstdio>
#include<algorithm>
using namespace std;
int sum(int x)
{
    for(int i=0;i<=14;++i)
    {
        if(x&(1<<i)) return i;
    }
    return 15;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        int s=1e9;
        for(int i=0;i<=15;++i)
        {
            s=min(s,i+(15-sum(n+i)));
        }
        printf("%d ",s);
    }
    return 0;
}