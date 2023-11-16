#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,q1,t,w,fa[N];
struct road
{
    road(){}
    road(int x,int y):x(x),y(y){}
    int x,y;
}a[N];
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    scanf("%d%d%d",&n,&m,&q1);
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=q1;++i)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        ++x,++y;
        if(z==0) fa[find(x)]=find(y);
        else a[++t]=road(x,y);
    }
    for(int i=1;i<=n;++i)
    {
        if(find(i)==i) ++w;
    }
    for(int i=1;i<=t;++i)
    {
        if(find(a[i].x)==find(a[i].y))
        {
            printf("No");
            return 0;
        }
    }
    if(t==0)
    {
        if((m-n+w)>=w-1&&(m-n+w)<=(ll)w*(w-1)/2) printf("Yes");
        else printf("No");
        return 0;
    }
    if(w==2) printf("No");
    else if((m-n+w)>=w&&(m-n+w)<=(ll)w*(w-1)/2) printf("Yes");
    else printf("No");
    return 0;
}