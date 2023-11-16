#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        int s=0;
        for(int i=30;i>=0;--i)
        {
            if(n>=(1<<i)) s+=((1<<i)-1),n-=(1<<i);
        }
        printf("%d\n",s);
    }
    return 0;
}