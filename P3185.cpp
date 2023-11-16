#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],f[N];
bool h[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        f[n]=0;
        for(int i=n-1;i>=1;--i)
        {
            for(int j=0;j<=n*2;++j) h[j]=false;
            for(int j=i+1;j<=n;++j)
            {
                for(int k=j;k<=n;++k) h[f[j]^f[k]]=true;
            }
            for(int j=0;j<=n*2;++j)
            {
                if(!h[j])
                {
                    f[i]=j;
                    break;
                }
            }
        }
        int s=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            if(a[i]&1) s^=f[i];
        }
        int x1=0,x2=0,x3=0,w=0;
        for(int i=1;i<=n;++i)
        {
            if(a[i]==0) continue;
            for(int j=i+1;j<=n;++j)
            {
                for(int k=j;k<=n;++k)
                {
                    if((s^f[i]^f[j]^f[k])==0)
                    {
                        if(x1==0) x1=i,x2=j,x3=k;
                        ++w;
                    }
                }
            }
        }
        printf("%d %d %d\n%d\n",x1-1,x2-1,x3-1,w);
    }
    return 0;
}