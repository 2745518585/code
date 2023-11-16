#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],b[N],c[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i) c[i]=n+1;
    for(int i=n;i>=1;--i)
    {
        b[i]=c[a[i]];
        c[a[i]]=i;
    }
    b[0]=n+1;
    int x1=0,x2=0,s=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]==a[x1]) x1=i;
        else if(a[i]==a[x2]) x2=i;
        else
        {
            if(b[x1]>=b[x2]) x1=i;
            else x2=i;
            ++s;
        }
    }
    printf("%d",s);
    return 0;
}