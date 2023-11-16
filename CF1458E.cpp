#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,q,b[N],c[N],T[N];
bool h[N];
struct str
{
    int x,y,t;
}a[N];
bool cmp(str a,str b)
{
    if(a.x!=b.x) return a.x<b.x;
    if(a.y!=b.y) return a.y<b.y;
    return a.t<b.t;
}
void add(int x,int k)
{
    while(x<=q) T[x]+=k,x+=x&-x;
}
int sum(int x)
{
    int s=0;
    while(x>=1) s+=T[x],x-=x&-x;
    return s;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        b[++q]=a[i].y;
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&a[n+i].x,&a[n+i].y);
        a[n+i].t=i;
    }
    sort(a+1,a+n+m+1,cmp);
    sort(b+1,b+q+1);
    q=unique(b+1,b+q+1)-b-1;
    int s=0,p=-1;
    for(int i=1;i<=n+m;++i)
    {
        if(a[i].t)
        {
            int z=upper_bound(b+1,b+q+1,a[i].y)-b-1;
            if(!a[i-1].t&&a[i-1].x==a[i].x&&a[i-1].y==a[i].y)
            {
                c[a[i].t]=0;
                continue;
            }
            if(a[i].x!=p&&(a[i].y!=b[z]||!h[z])&&a[i].x-s==a[i].y-sum(z)) c[a[i].t]=0;
            else c[a[i].t]=1;
        }
        else
        {
            int z=lower_bound(b+1,b+q+1,a[i].y)-b;
            if(a[i].x-s<a[i].y-sum(z))
            {
                if(!h[z]) h[z]=true,add(z,1);
            }
            else if(a[i].x-s>a[i].y-sum(z))
            {
                if(p!=a[i].x) p=a[i].x,++s;
            }
        }
    }
    for(int i=1;i<=m;++i)
    {
        if(c[i]) printf("WIN\n");
        else printf("LOSE\n");
    }
    return 0;
}