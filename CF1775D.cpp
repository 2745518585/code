#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=2000001;
int n,m,tot,p=1,t[N],s1,s2,b[N],f[N],g[N],h[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
int main()
{
    scanf("%d",&n);
    tot=n;
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        b[i]=x;
        for(int j=2;j*j<=b[i];++j)
        {
            if(x%j==0)
            {
                if(h[j]==0) h[j]=++tot;
                road(i,h[j]);
                road(h[j],i);
            }
            while(x%j==0) x/=j;
        }
        if(x!=1)
        {
            if(h[x]==0) h[x]=++tot;
            road(i,h[x]);
            road(h[x],i);
        }
    }
    scanf("%d%d",&s1,&s2);
    for(int i=1;i<=tot;++i) f[i]=-1;
    f[s2]=0;
    queue<int> Q;
    Q.push(s2);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[a[i].m]==-1)
            {
                f[a[i].m]=f[k]+1;
                g[a[i].m]=k;
                Q.push(a[i].m);
            }
        }
    }
    if(f[s1]==-1)
    {
        printf("-1");
        return 0;
    }
    int x=s1,s=1;
    while(x!=s2)
    {
        if(x<=n) ++s;
        x=g[x];
    }
    printf("%d\n",s);
    x=s1;
    while(x!=s2)
    {
        if(x<=n) printf("%d ",x);
        x=g[x];
    }
    printf("%d ",s2);
    return 0;
}