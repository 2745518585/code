#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001;
int m,n,q,a[N],b[N],c[N],d[N],f[N][N];
struct str
{
    int x,y;
    friend str max(str a,str b)
    {
        if(f[a.x][a.y]>f[b.x][b.y]) return a;
        return b;
    }
}T[N][N],g[N][N];
void add(str T[],int x,str k)
{
    while(x<=n)
    {
        T[x]=max(T[x],k);
        x+=(x&-x);
    }
}
str sum(str T[],int x)
{
    str s=(str){0,0};
    while(x>=1)
    {
        s=max(s,T[x]);
        x-=(x&-x);
    }
    return s;
}
int main()
{
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&a[i]);
        c[i]=a[i];
    }
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        c[m+i]=b[i];
    }
    sort(c+1,c+m+n+1);
    q=unique(c+1,c+m+n+1)-c-1;
    for(int i=1;i<=m;++i)
    {
        a[i]=lower_bound(c+1,c+q+1,a[i])-c;
    }
    for(int i=1;i<=n;++i)
    {
        b[i]=lower_bound(c+1,c+q+1,b[i])-c;
    }
    str s=(str){0,0};
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(a[i]!=b[j]) continue;
            f[i][j]=1;
            for(int k=1;k<=a[i]-1;++k)
            {
                str z=sum(T[k],j-1);
                if(f[z.x][z.y]+1>f[i][j])
                {
                    f[i][j]=f[z.x][z.y]+1;
                    g[i][j]=z;
                }
            }
            s=max(s,(str){i,j});
            add(T[a[i]],j,(str){i,j});
        }
    }
    printf("%d\n",f[s.x][s.y]);
    str x=s;
    int z=0;
    while(x.x!=0||x.y!=0)
    {
        d[++z]=a[x.x];
        x=g[x.x][x.y];
    }
    for(int i=z;i>=1;--i)
    {
        printf("%d ",c[d[i]]);
    }
    return 0;
}