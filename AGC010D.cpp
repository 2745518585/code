#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
bool solve()
{
    int s1=0,s2=0;
    bool u=false;
    for(int i=1;i<=n;++i)
    {
        if(a[i]%2==1) ++s1;
        else ++s2;
        if(a[i]==1) u=true;
    }
    if(u) return s2%2==1;
    if(s2%2==1) return true;
    if(s1>1) return false;
    for(int i=1;i<=n;++i)
    {
        if(a[i]%2==1)
        {
            --a[i];
            break;
        }
    }
    int z=0;
    for(int i=1;i<=n;++i) z=gcd(z,a[i]);
    for(int i=1;i<=n;++i) a[i]/=z;
    return solve()^1;
}
int main()
{
    scanf("%d",&n);
    int z=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        z=gcd(z,a[i]);
    }
    for(int i=1;i<=n;++i) a[i]/=z;
    if(solve()) printf("First");
    else printf("Second");
    return 0;
}