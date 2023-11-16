#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10001;
int n,m,a[N];
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        m=0;
        for(int i=1;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            m=gcd(m,x);
        }
        if(m==1)
        {
            printf("0\n");
            continue;
        }
        if(gcd(m,n)==1)
        {
            printf("1\n");
            continue;
        }
        if(gcd(m,n-1)==1)
        {
            printf("2\n");
            continue;
        }
        printf("3\n");
    }
    return 0;
}