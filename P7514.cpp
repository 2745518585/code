#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,q,b1[N],b2[N],c1[N],c2[N],d[N];
struct str
{
    int a,b;
}a[N];
bool cmp(str a,str b)
{
    return a.a<b.a;
}
bool check(int k)
{
    int x=1,y=0;
    for(int i=1;i<=q;++i)
    {
        while(x<=n&&a[x].a<d[i]) ++x;
        while(y+1<=n&&a[y+1].a<=d[i]+k) ++y;
        if((x-1)+(n-y)<=m&&min(b1[x-1],b2[y+1])>=d[i]&&max(c1[x-1],c2[y+1])<=d[i]+k) return true;
    }
    return false;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i].a);
        d[++q]=a[i].a;
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i].b);
        d[++q]=a[i].b;
    }
    sort(d+1,d+q+1);
    q=unique(d+1,d+q+1)-d-1;
    sort(a+1,a+n+1,cmp);
    b1[0]=1e9,c1[0]=0;
    for(int i=1;i<=n;++i)
    {
        b1[i]=min(b1[i-1],a[i].b);
        c1[i]=max(c1[i-1],a[i].b);
    }
    b2[n+1]=1e9,c2[n+1]=0;
    for(int i=n;i>=1;--i)
    {
        b2[i]=min(b2[i+1],a[i].b);
        c2[i]=max(c2[i+1],a[i].b);
    }
    int l=0,r=1e9;
    while(l<r)
    {
        int z=l+r>>1;
        if(check(z)) r=z;
        else l=z+1;
    }
    printf("%d",l);
    return 0;
}