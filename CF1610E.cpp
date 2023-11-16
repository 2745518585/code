#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N];
int check(int x)
{
    int y=x+1,s=0;
    while(y<=n)
    {
        ++s;
        y=lower_bound(a+1,a+n+1,a[y]*2-a[x])-a;
    }
    return s;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        int s=0;
        for(int i=1;i<=n;++i)
        {
            int j=i;
            while(j+1<=n&&a[j+1]==a[i]) ++j;
            s=max(s,(j-i+1)+check(j));
            i=j;
        }
        printf("%d\n",n-s);
    }
    return 0;
}