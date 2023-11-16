#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<utility>
using namespace std;
typedef unsigned long long ull;
const int N=1000001;
int n,m,l[N],a[N][2],b[N];
ull powb[N],f[N];
bool h[N];
int main()
{
    int T;
    scanf("%d",&T);
    powb[0]=1;
    for(int i=1;i<=1000000;++i) powb[i]=powb[i-1]*10007;
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) h[i]=f[i]=l[i]=0;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[i][0]=x,a[i][1]=y;
            ++l[x],++l[y];
            f[x]+=powb[y];
            f[y]+=powb[x];
        }
        for(int i=1;i<=n;++i) b[i]=i;
        sort(b+1,b+n+1,[](int x,int y){return f[x]<f[y];});
        for(int i=1;i<=n;++i)
        {
            if(f[b[i]]==f[b[i-1]]) h[b[i]]=h[b[i-1]]=true;
        }
        for(int i=1;i<=m;++i)
        {
            int x=a[i][0],y=a[i][1];
            if(f[x]+powb[x]==f[y]+powb[y]) h[x]=h[y]=true;
            if(l[x]==1||l[y]==1) h[x]=h[y]=true;
        }
        int s=0;
        for(int i=1;i<=n;++i) s+=h[i];
        printf("%d\n",s);
        for(int i=1;i<=n;++i) if(h[i]) printf("%d ",i);
        printf("\n");
    }
    return 0;
}