#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001,M=20001;
int n,d[N];
ll a[N],b[N],f[N];
vector<int> Q[M];
double abc(int x,int y)
{
    return (double)((f[x]+a[x+1]*(b[x+1]-1)*(b[x+1]-1))-(f[y]+a[y+1]*(b[y+1]-1)*(b[y+1]-1)))/((b[x+1]-1)-(b[y+1]-1));
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
        b[i]=b[d[a[i]]]+1;
        d[a[i]]=i;
    }
    Q[a[1]].push_back(0);
    for(int i=1;i<=n;++i)
    {
        #define Q2 Q[a[i]]
        int l=0,r=Q2.size()-1;
        while(l<r)
        {
            int z=l+r>>1;
            if(abc(Q2[z],Q2[z+1])<=2*a[i]*b[i]) r=z;
            else l=z+1;
        }
        f[i]=f[Q2[l]]+a[i]*(b[i]-b[Q2[l]+1]+1)*(b[i]-b[Q2[l]+1]+1);
        f[i]=max(f[i],f[i-1]);
        #undef Q2
        #define Q2 Q[a[i+1]]
        while(Q2.size()>1&&abc(Q2[Q2.size()-2],Q2[Q2.size()-1])<=abc(Q2[Q2.size()-1],i)) Q2.pop_back();
        if(a[i+1]!=0) Q2.push_back(i);
        #undef Q2
    }
    printf("%lld",f[n]);
    return 0;
}