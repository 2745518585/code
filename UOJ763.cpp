#include<cstdio>
#include<algorithm>
#include<vector>
#include<utility>
#include<set>
using namespace std;
typedef unsigned long long ull;
const int N=1000001;
int n;
ull P1,P2,P3,f1[N],f2[N],f3[N];
vector<int> a[N];
set<pair<pair<ull,ull>,ull>> Set;
void dfs(int x,int fa)
{
    f1[x]=1;
    f2[x]=1;
    f3[x]=1;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs(i,x);
        f1[x]=(f1[x]+f2[i]*(f3[i]+P2)%P1+P3)%P1;
        f2[x]=(f2[x]+f3[i]*(f1[i]+P3)%P2+P1)%P2;
        f3[x]=(f3[x]+f1[i]*(f2[i]+P1)%P3+P2)%P3;
    }
}
int main()
{
    scanf("%d",&n);
    srand(n);
    P1=(unsigned)rand()*rand()*rand();
    P2=(unsigned)rand()*rand()*rand();
    P3=(unsigned)rand()*rand()*rand();
    for(int i=1;i<=n-1;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs(1,0);
    for(int i=1;i<=n;++i) Set.insert(make_pair(make_pair(f1[i],f2[i]),f3[i]));
    printf("%lld",Set.size());
    return 0;
}