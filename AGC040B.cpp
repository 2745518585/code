#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q,b1[N],b2[N];
struct str
{
    int l,r;
    str(){}
    str(int l,int r):l(l),r(r){}
}a[N];
bool cmp(str a,str b)
{
    if(a.l!=b.l) return a.l<b.l;
    return a.r<b.r;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].l,&a[i].r);
    }
    sort(a+1,a+n+1,cmp);
    b1[0]=1e9;
    for(int i=1;i<=n;++i) b1[i]=min(b1[i-1],a[i].r);
    b2[n+1]=1e9;
    for(int i=n;i>=1;--i) b2[i]=min(b2[i+1],a[i].r);
    int s=0;
    for(int i=1;i<=n;++i)
    {
        s=max(s,(a[i].r-a[i].l+1)+max(min(b1[i-1],b2[i+1])-(i<n?a[n].l:a[n-1].l)+1,0));
    }
    int w=1e9;
    for(int i=1;i<=n-1;++i)
    {
        w=min(w,a[i].r);
        s=max(s,max(w-a[i].l+1,0)+max(b2[i+1]-a[n].l+1,0));
    }
    printf("%d",s);
    return 0;
}