#include<cstdio>
#include<algorithm>
using namespace std;
int n,m;
bool check(int x)
{
    if(x==1) return false;
    for(int i=2;i*i<=x;++i)
    {
        if(x%i==0) return false;
    }
    return true;
}
int main()
{
    scanf("%d",&n);
    m=n*(n+1)/2;
    if(check(m))
    {
        for(int i=1;i<=n;++i) printf("1 ");
        return 0;
    }
    if(m%2==1)
    {
        if(check(m-2))
        {
            printf("1 2 ");
            for(int i=3;i<=n;++i) printf("1 ");
            return 0;
        }
        printf("1 1 ");
        m-=3;
        int x=0;
        for(int i=3;i<=n;++i)
        {
            if(check(i)&&check(m-i))
            {
                x=i;
                break;
            }
        }
        for(int i=3;i<=n;++i)
        {
            if(x==i) printf("3 ");
            else printf("2 ");
        }
    }
    else
    {
        int x=0;
        for(int i=1;i<=n;++i)
        {
            if(check(i)&&check(m-i))
            {
                x=i;
                break;
            }
        }
        for(int i=1;i<=n;++i)
        {
            if(x==i) printf("2 ");
            else printf("1 ");
        }
    }
    return 0;
}