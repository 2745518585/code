#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2000001;
int n,m,a[N],b[N],c[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;++i) b[i]=c[i]=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            ++b[a[i]];
        }
        for(int i=1;i<=m;++i) c[i]=c[i-1]+b[i];
        sort(a+1,a+n+1);
        bool u=true;
        for(int i=1;i<=m;++i)
        {
            if(b[i]!=0) continue;
            for(int j=1;j<=m/i;++j)
            {
                if(b[j]&&c[min(j*(i+1)-1,m)]-c[j*i-1]>0)
                {
                    u=false;
                    break;
                }
            }
            if(!u) break;
        }
        if(u) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}