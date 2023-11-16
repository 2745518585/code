#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
#define int long long
const int N=1000001;
int n,q,a[N];
struct str
{
    int x,y;
}b[N];
signed main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        q=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        a[n+1]=a[n+2]=0;
        bool u=true;
        for(int i=2;i<=n;++i)
        {
            if(a[i]!=a[i-1]) u=false;
        }
        if(u)
        {
            printf("0\n");
            continue;
        }
        u=false;
        for(int i=1;i<=n;++i)
        {
            if(a[i]==1)
            {
                u=true;
                break;
            }
        }
        if(u)
        {
            printf("-1\n");
            continue;
        }
        a[0]=1e18;
        while(true)
        {
            int x1=0,x2=0;
            for(int j=1;j<=n;++j)
            {
                if(a[j]<a[x1]) x2=x1,x1=j;
                else if(a[j]<a[x2]&&a[j]!=a[x1]) x2=j;
            }
            if(a[x1]==2) break;
            if(x1==0||x2==0) break;
            b[++q]=(str){x2,x1};
            a[x2]=(int)(ceil((double)a[x2]/a[x1]));
        }
        u=false;
        for(int i=2;i<=n;++i)
        {
            if(a[i]!=a[i-1])
            {
                u=true;
                break;
            }
        }
        if(!u)
        {
            printf("%d\n",q);
            for(int i=1;i<=q;++i)
            {
                printf("%d %d\n",b[i].x,b[i].y);
            }
            continue;
        }
        int x=0;
        for(int i=1;i<=n;++i)
        {
            if(a[i]==2)
            {
                x=i;
                break;
            }
        }
        for(int i=1;i<=n;++i)
        {
            while(a[i]>2)
            {
                b[++q]=(str){i,x};
                a[i]=(int)(ceil((double)a[i]/2));
            }
        }
        printf("%d\n",q);
        for(int i=1;i<=q;++i)
        {
            printf("%d %d\n",b[i].x,b[i].y);
        }
    }
    return 0;
}