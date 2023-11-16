#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001;
int n,c[N];
bool h[N];
struct str
{
    int x,s;
}a[N],b[N];
bool cmp(str a,str b)
{
    return a.s>b.s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i].s);
        a[i].x=i;
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i].s);
        b[i].x=i;
    }
    sort(a+1,a+n+1,cmp);
    sort(b+1,b+n+1,cmp);
    for(int i=1;i<=n;++i)
    {
        c[a[i].x]=b[i].x;
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=n;j>=i+1;--j)
        {
            if(c[j-1]>c[j])
            {
                swap(c[j],c[j-1]);
                ++s;
            }
        }
    }
    printf("%d",s);
    return 0;
}
