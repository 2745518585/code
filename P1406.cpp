#include<cstdio>
#include<algorithm>
using namespace std;
const int N=101;
int n,m,a[N],c[N][N],p1[N],p2[N],p3,p4;
bool b[N];
void dfs(int x,int y)
{
    if(x==n+1)
    {
        for(int i=1;i<=n;++i)
        {
            if(p1[i]!=m||p2[i]!=m) return;
        }
        if(p3!=m||p4!=m) return;
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n;++j)
            {
                printf("%d ",c[i][j]);
            }
            printf("\n");
        }
        exit(0);
    }
    int px=x,py=y+1;
    if(py>n) px=x+1,py=1;
    for(int i=1;i<=n*n;++i)
    {
        if(b[i]==true) continue;
        if((y==n&&p1[x]+a[i]!=m)||(x==n&&p2[y]+a[i]!=m)) continue;
        p1[x]+=a[i];
        p2[y]+=a[i];
        if(x==y) p3+=a[i];
        if(x+y==n+1) p4+=a[i];
        b[i]=true;
        c[x][y]=a[i];
        dfs(px,py);
        p1[x]-=a[i];
        p2[y]-=a[i];
        if(x==y) p3-=a[i];
        if(x+y==n+1) p4-=a[i];
        b[i]=false;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n*n;++i)
    {
        scanf("%d",&a[i]);
        m+=a[i];
    }
    m/=n;
    printf("%d\n",m);
    sort(a+1,a+n*n+1);
    dfs(1,1);
    return 0;
}