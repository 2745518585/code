#include<cstdio>
#include<algorithm>
using namespace std;
const int N=101,M=25001;
int n,m,s,a[N];
bool f[M];
void abc()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    m=a[n];
    for(int i=1;i<=m;++i) f[i]=false;
    f[0]=true;
    s=0;
    for(int i=1;i<=n;++i)
    {
        if(f[a[i]]==true) continue;
        ++s;
        for(int j=a[i];j<=m;++j)
        {
            f[j]|=f[j-a[i]];
        }
    }
    printf("%d\n",s);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}
