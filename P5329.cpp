#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,b[N],f[N];
char a[N];
bool cmp(int x,int y)
{
    if(x<y) return f[x]>0||-f[x]>=y;
    else return !(f[y]>0||-f[y]>=x);
}
int main()
{
    scanf("%d%s",&n,a+1);
    f[n]=n;
    for(int i=n-1;i>=1;--i)
    {
        if(a[i+1]<a[i]) f[i]=i;
        else if(a[i+1]>a[i]) f[i]=-i;
        else f[i]=f[i+1];
    }
    for(int i=1;i<=n;++i) b[i]=i;
    sort(b+1,b+n+1,cmp);
    for(int i=1;i<=n;++i)
    {
        printf("%d ",b[i]);
    }
    return 0;
}