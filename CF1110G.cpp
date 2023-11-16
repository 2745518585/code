#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2000001;
int n,m,p=1,t[N],l[N],f[N];
char b[N];
struct road
{
    int m,q;
}a[N<<1];
void road(int x,int y)
{
    ++l[x],++l[y];
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[++p].m=x;
    a[p].q=t[y];
    t[y]=p;
}
void dfs(int x,int fa)
{
    f[x]=f[fa]+1;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        dfs(a[i].m,x);
    }
}
bool check()
{
    for(int i=1;i<=n;++i)
    {
        if(l[i]>=4) return true;
    }
    for(int i=1;i<=n;++i)
    {
        if(l[i]<3) continue;
        int v=0;
        for(int j=t[i];j!=0;j=a[j].q)
        {
            if(l[a[j].m]>1) ++v;
        }
        if(v>=2) return true;
    }
    int x1=0,x2=0,x3=0;
    for(int i=1;i<=n;++i)
    {
        if(l[i]>=3)
        {
            if(x1==0) x1=i;
            else if(x2==0) x2=i;
            else if(x3==0) x3=i;
        }
    }
    if(x1!=0)
    {
        dfs(x1,0);
        if((x2!=0&&f[x2]%2==1)||(x3!=0&&f[x3]%2==1)) return true;
    }
    if(x2!=0)
    {
        dfs(x2,0);
        if(x3!=0&&f[x3]%2==1) return true;
    }
    return false;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        p=1;
        for(int i=1;i<=n;++i) t[i]=l[i]=0;
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            road(x,y);
        }
        scanf("%s",b+1);
        int m=n;
        for(int i=1;i<=m;++i)
        {
            if(b[i]=='N') continue;
            t[n+1]=t[n+2]=t[n+3]=l[n+1]=l[n+2]=l[n+3]=0;
            road(i,n+1);
            road(n+1,n+2);
            road(n+1,n+3);
            n+=3;
        }
        if(check()) printf("White\n");
        else printf("Draw\n");
    }
    return 0;
}