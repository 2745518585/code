#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll inf=1e18;
int n,m,q,b[N<<1];
ll f[N];
struct str
{
    int x,y;
}a[N];
bool cmp(str a,str b)
{
    if(a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        a[i].y+=a[i].x;
        b[i*2-1]=a[i].x;
        b[i*2]=a[i].y;
    }
    b[m*2+1]=1;
    sort(b+1,b+m*2+2);
    q=unique(b,b+m*2+2)-(b+1);
    b[q+1]=n+1;
    for(int i=1;i<=m;++i)
    {
    	a[i].x=lower_bound(b+1,b+q+1,a[i].x)-b;
    	a[i].y=lower_bound(b+1,b+q+1,a[i].y)-b;
	}
    sort(a+1,a+m+1,cmp);
    int t=0;
    for(int i=2;i<=q+1;++i) f[i]=-inf;
    for(int i=1;i<=q;++i)
    {
        if(a[t+1].x==i)
        {
            while(a[t+1].x==i)
            {
                ++t;
                f[a[t].y]=max(f[a[t].y],f[i]);
            }
        }
        else f[i+1]=max(f[i+1],f[i]+b[i+1]-b[i]);
    }
    printf("%lld",f[q+1]);
    return 0;
}
