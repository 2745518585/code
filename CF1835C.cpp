#include<cstdio>
#include<algorithm>
#include<map>
#include<random>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,b[5];
ll a[N];
int rnd(int x1,int x2)
{
    static random_device seed;
    static mt19937 rnd(seed());
    return (std::uniform_int_distribution<int>(x1,x2))(rnd);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        n=(1<<(n+1));
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
            a[i]^=a[i-1];
        }
        map<ll,int> Map;
        bool u=false;
        Map[0]=0;
        for(int i=1;i<=n;++i)
        {
            if(!Map.count(a[i])) Map[a[i]]=i;
            else
            {
                int z=Map[a[i]];
                if(z<i-1)
                {
                    printf("%d %d %d %d\n",z+1,z+1,z+2,i);
                    u=true;
                    break;
                }
            }
        }
        if(u) continue;
        while(true)
        {
            ll s=0;
            for(int i=1;i<=3;++i) b[i]=rnd(0,n),s^=a[b[i]];
            if(!Map.count(s)) continue;
            b[4]=Map[s];
            sort(b+1,b+5);
            if(b[1]!=b[2]&&b[2]!=b[3]&&b[3]!=b[4])
            {
                printf("%d %d %d %d\n",b[1]+1,b[2],b[3]+1,b[4]);
                break;
            }
        }
    }
    return 0;
}