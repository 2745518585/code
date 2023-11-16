#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<bitset>
using namespace std;
const int N=501,M=5001,K=2500000;
int n,m,k,a[N];
bitset<N*M*2> b[N];
struct str
{
    int x,s;
    str(){}
    str(int x,int s):x(x),s(s){}
    friend bool operator<(str a,str b)
    {
        return a.s<b.s;
    }
};
void solve(vector<str> a)
{
    multiset<str> Set;
    int n=a.size(),m=0;
    for(auto i:a) m+=i.s,Set.insert(i);
    m/=k;
    while(m>=n)
    {
        printf("%d %d\n",(*prev(Set.end())).x,k);
        str p=(*prev(Set.end()));
        p.s-=k;
        Set.erase(prev(Set.end()));
        Set.insert(p);
        --m;
    }
    while(m>0)
    {
        int z=(*Set.begin()).s;
        printf("%d %d %d %d\n",(*Set.begin()).x,z,(*prev(Set.end())).x,k-z);
        Set.erase(Set.begin());
        str p=(*prev(Set.end()));
        p.s-=k-z;
        Set.erase(prev(Set.end()));
        if(p.s!=0) Set.insert(p);
        --m;
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        if(m>=n-1)
        {
            vector<str> a1;
            for(int i=1;i<=n;++i) a1.push_back(str(i,a[i]));
            solve(a1);
            continue;
        }
        for(int i=0;i<=n;++i) b[i]=0;
        b[0][K]=1;
        for(int i=1;i<=n;++i)
        {
            if(a[i]-k>=0) b[i]=b[i-1]|(b[i-1]<<(a[i]-k));
            else b[i]=b[i-1]|(b[i-1]>>(k-a[i]));
        }
        if(b[n][K-k]==0)
        {
            printf("-1\n");
            continue;
        }
        int x=K-k;
        vector<str> a1,a2;
        for(int i=n;i>=1;--i)
        {
            if(b[i-1][x]==1) a2.push_back(str(i,a[i]));
            else x-=(a[i]-k),a1.push_back(str(i,a[i]));
        }
        solve(a1);
        solve(a2);
    }
    return 0;
}