#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,q,a[N],f[N];
int sum(int x)
{
    int s=0;
    while(x>0) s+=x&1,x>>=1;
    return s;
}
int lg(int x)
{
    int s=-1;
    while(x>0) ++s,x>>=1;
    return s;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        sort(a+1,a+n+1,[](int x,int y){return x>y;});
        int t=0;
        for(int i=1;i<=n;++i) t|=a[i];
        for(int i=1;i<=31;++i)
        {
            if(sum(t)<i)
            {
                for(int j=0;j<=30;++j)
                {
                    if((t&(1<<j))==0)
                    {
                        t|=(1<<j);
                        break;
                    }
                }
            }
            int p=t,s=0;
            priority_queue<int> Q;
            for(int j=1;j<=n;++j) Q.push(a[j]);
            while(!Q.empty()&&p>0)
            {
                int x=Q.top();
                Q.pop();
                int k=lg(p);
                if(x<(1<<k))
                {
                    s+=(1<<k)-x;
                    p^=(1<<k);
                }
                else
                {
                    if(x&(1<<k)) p^=(1<<k);
                    Q.push(x&((1<<(k+1))-1));
                }
            }
            s+=p;
            f[i]=s;
        }
        for(int i=1;i<=q;++i)
        {
            int x;
            scanf("%d",&x);
            for(int j=31;j>=0;--j)
            {
                if(f[j]<=x)
                {
                    printf("%d\n",j);
                    break;
                }
            }
        }
    }
    return 0;
}