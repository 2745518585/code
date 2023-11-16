#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,T[N];
struct str
{
    int x,y;
}a[N];
bool cmp(str a,str b)
{
    return a.x<b.x;
}
void add(int x,int k)
{
    while(x<=n) T[x]=max(T[x],k),x+=x&-x;
}
int sum(int x)
{
    int s=0;
    while(x>=1) s=max(s,T[x]),x-=x&-x;
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i].x);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i].y);
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;++i)
    {
        add(a[i].y,sum(a[i].y)+1);
    }
    printf("%d\n",sum(n)+n);
    return 0;
}