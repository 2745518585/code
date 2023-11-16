#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,q,w,p=1,t[N],b[N],c[N],d[N],l[N];
bool h[N];
struct road
{
    int m,q;
}a[N];
struct str
{
    int x,y;
}e[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x)
{
    for(int i=t[x];i!=0;i=a[i].q)
    {
        t[x]=a[i].q;
        if(h[i]) continue;
        h[i]=h[i^1]=true;
        dfs(a[i].m);
    }
    d[++w]=x;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        m=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
            c[++q]=b[i]-i;
            c[++q]=b[i]+i;
        }
        sort(c+1,c+q+1);
        q=unique(c+1,c+q+1)-c-1;
        p=1;
        for(int i=1;i<=n+q;++i) t[i]=l[i]=0;
        for(int i=1;i<=n;++i)
        {
            int z1=lower_bound(c+1,c+q+1,b[i]-i)-c,z2=lower_bound(c+1,c+q+1,b[i]+i)-c;
            ++l[i],++l[n+z1];
            road(i,n+z1);
            road(n+z1,i);
            ++l[i],++l[n+z2];
            road(i,n+z2);
            road(n+z2,i);
        }
        for(int i=1;i<=n+q;++i)
        {
            w=0;
            dfs(i);
            int x=0;
            for(int j=1;j<=w;++j)
            {
                if(c[d[j]]<=n)
                if(x==0) x=c[d[j]];
                else
                {
                    e[++m]=(str){x,c[d[j]]};
                    x=0;
                }
            }
            if(x!=0)
            {
                m=-1;
                break;
            }
        }
        if(m==-1)
        {
            printf("No\n");
            continue;
        }
        printf("Yes\n");
        for(int i=1;i<=m;++i)
        {
            printf("%d %d\n",e[i].x,e[i].y);
        }
    }
    return 0;
}