#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,tot,b[N][26],f[N],l[N],g[N],h[N];
char a[N];
int find(int x,int k)
{
    while(x!=0&&(k-l[x]-1<=0||a[k-l[x]-1]!=a[k])) x=f[x];
    return x;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s",&n,a+1);
        tot=1;
        for(int i=0;i<=25;++i) b[0][i]=1,b[1][i]=0;
        int x=0;
        for(int i=1;i<=n;++i)
        {
            x=find(x,i);
            if(b[x][a[i]-'a']==0)
            {
                b[x][a[i]-'a']=++tot;
                for(int j=0;j<=25;++j) b[tot][j]=0;
                f[tot]=b[find(f[x],i)][a[i]-'a'];
                l[tot]=l[x]+2;
                if(f[tot]!=1) h[tot]=h[f[tot]];
                else h[tot]=l[tot];
            }
            x=b[x][a[i]-'a'];
            if(h[x]!=0) g[i]=g[i-h[x]]+1;
            else g[i]=0;
        }
        ll s=0;
        for(int i=1;i<=n;++i) s+=g[i];
        printf("%lld\n",s);
    }
    return 0;
}