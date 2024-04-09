#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=6001;
int n,a[N][N],k,f[N][N],g[N],p[N];
struct str
{
    int t,w,p;
    str() {}
    str(int t,int w,int p):t(t),w(w),p(p) {}
    friend bool operator<(str a,str b)
    {
        return a.w<b.w;
    }
};
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;++i)
        {
            for(int j=i;j<=n;++j)
            {
                scanf("%d",&a[i][j]);
            }
        }
        f[0][1]=0;
        g[0]=1;
        for(int i=1;i<=n;++i)
        {
            priority_queue<str> Q;
            Q.push(str(0,a[1][i],0));
            for(int j=0;j<=i-2;++j)
            {
                if(j+2<=i) Q.push(str(j,f[j][1]+a[j+2][i],1));
            }
            g[i]=0;
            while(g[i]<k&&!Q.empty())
            {
                str x=Q.top();
                Q.pop();
                f[i][++g[i]]=x.w;
                if(x.t==0||x.p==g[x.t]) continue;
                ++x.p;
                x.w=f[x.t][x.p]+a[x.t+2][i];
                Q.push(x);
            }
            int p1=1,p2=1;
            for(int j=1;j<=k&&(p1<=g[i]||p2<=g[i-1]);++j)
            {
                if(p1<=g[i]&&(p2>g[i-1]||f[i][p1]>f[i-1][p2])) p[j]=f[i][p1],++p1;
                else p[j]=f[i-1][p2],++p2;
            }
            g[i]=min(g[i]+g[i-1],k);
            swap(p,f[i]);
        }
        for(int i=1;i<=k;++i)
        {
            printf("%d ",f[n][i]);
        }
        printf("\n");
    }
    return 0;
}