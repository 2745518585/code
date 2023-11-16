#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10001;
int m,n;
bool h[N];
struct str
{
    int a,b;
}a[N];
bool cmp(str a,str b)
{
    if(a.b!=b.b) return a.b>b.b;
    return a.a<b.a;
}
int main()
{
    int m,n;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;++i) scanf("%d",&a[i].a);
    for(int i=1;i<=n;++i) scanf("%d",&a[i].b);
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;++i)
    {
        m-=a[i].b;
        for(int j=a[i].a;j>=1;--j)
        {
            if(h[j]==false)
            {
                h[j]=true;
                m+=a[i].b;
                break;
            }
        }
    }
    printf("%d",m); 
    return 0;
}