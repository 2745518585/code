#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2000001;
int n,m,a[N],S[N],T;
bool h[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x;
        scanf("%d",&x);
        h[x]=true;
    }
    for(int i=n;i>=1;--i)
    {
        if(h[i]==true) S[++T]=a[i];
        else
        {
            if(S[T]==a[i]) --T;
            else h[i]=true,S[++T]=a[i];
        }
    }
    if(T>0)
    {
        printf("NO");
        return 0;
    }
    printf("YES\n");
    for(int i=1;i<=n;++i)
    {
        if(h[i]) printf("%d ",-a[i]);
        else printf("%d ",a[i]);
    }
}