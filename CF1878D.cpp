#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,q,b[N],f[N],l[N],r[N];
char a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%s",&n,&m,a+1);
        for(int i=1;i<=n;++i) f[i]=0;
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&l[i]);
        }
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&r[i]);
        }
        for(int i=1;i<=m;++i)
        {
            for(int j=l[i];j<=r[i];++j) b[j]=i;
        }
        scanf("%d",&q);
        for(int i=1;i<=q;++i)
        {
            int x;
            scanf("%d",&x);
            int x1=x,x2=l[b[x]]+r[b[x]]-x;
            if(x1>x2) swap(x1,x2);
            f[x1]^=1;
            if(x2+1<=r[b[x]]) f[x2+1]^=1;
        }
        for(int i=1;i<=m;++i)
        {
            int u=0;
            for(int j=l[i];j<=r[i];++j)
            {
                u^=f[j];
                if(u==0) printf("%c",a[j]);
                else printf("%c",a[l[i]+r[i]-j]);
            }
        }
        printf("\n");
    }
    return 0;
}