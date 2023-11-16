#include<bits/stdc++.h>
using namespace std;
const int N=1000001,M=1000001,inf=1e9;
int n,m,f[N],h[N];
struct str
{
    int x,y;
}a[M];
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
    }
    sort(a+1,a+m+1,cmp);
    int t=0;
    for(int i=2;i<=n+1;++i) f[i]=-inf;
    for(int i=1;i<=n;++i)
    {
        if(a[t+1].x==i)
        {
            while(a[t+1].x==i)
            {
                ++t;
                f[a[t].y]=max(f[a[t].y],f[i]);
            }
        }
        else f[i+1]=max(f[i+1],f[i]+1);
    }
    printf("%d",f[n+1]);
    return 0;
}
