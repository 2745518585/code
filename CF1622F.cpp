#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<random>
using namespace std;
typedef unsigned long long ull;
const int N=2000001;
mt19937 rnd(random_device{}());
int n,g[N];
ull b[N];
bool h[N];
map<ull,int> Map;
vector<int> c[N];
int main()
{
    scanf("%d",&n);
    for(int i=2;i<=n;++i)
    {
        if(h[i]) continue;
        b[i]=(uniform_int_distribution<ull>(0,-1))(rnd);
        int w=1;
        while(w<=n/i)
        {
            w*=i;
            for(int j=1;w*j<=n;++j) c[w*j].push_back(i),h[w*j]=true;
        }
    }
    ull x=0;
    for(int i=1;i<=n;++i)
    {
        for(auto j:c[i])
        {
            if(g[j]==0) x+=b[j];
            else x-=b[j];
            g[j]^=1;
        }
        Map[x]=i;
    }
    for(int i=1;i<=n;++i) g[i]=0;
    for(int i=1;i<=n;++i)
    {
        if((n-i+1)%2==0) continue;
        for(auto j:c[i]) g[j]^=1;
    }
    x=0;
    for(int i=1;i<=n;++i) if(g[i]) x+=b[i];
    if(x==0)
    {
        printf("%d\n",n);
        for(int i=1;i<=n;++i) printf("%d ",i);
        return 0;
    }
    if(Map.count(x))
    {
        int z=Map[x];
        printf("%d\n",n-1);
        for(int i=1;i<=n;++i) if(i!=z) printf("%d ",i);
        return 0;
    }
    if(n%4==0)
    {
        printf("%d\n",n-1);
        for(int i=1;i<=n;++i) if(i!=n/2) printf("%d ",i);
        return 0;
    }
    for(int i=1;i<=n;++i)
    {
        for(auto j:c[i])
        {
            if(g[j]==0) x+=b[j];
            else x-=b[j];
            g[j]^=1;
        }
        if(Map.count(x))
        {
            int x1=Map[x],x2=i;
            printf("%d\n",n-2);
            for(int i=1;i<=n;++i) if(i!=x1&&i!=x2) printf("%d ",i);
            return 0;
        }
    }
    if(n%4==2)
    {
        printf("%d\n",n-2);
        for(int i=1;i<=n;++i) if(i!=2&&i!=n/2) printf("%d ",i);
        return 0;
    }
    if((n/2)%2==0)
    {
        printf("%d\n",n-2);
        for(int i=1;i<=n-1;++i) if(i!=(n-1)/2) printf("%d ",i);
        return 0;
    }
    printf("%d\n",n-3);
    for(int i=1;i<=n-1;++i) if(i!=2&&i!=(n-1)/2) printf("%d ",i);
    return 0;
}