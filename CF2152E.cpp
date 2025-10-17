#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=100001;
int n,f[N],g[N];
bool d[N];
vector<int> a1[N],a2[N];
vector<int> ask(vector<int> x)
{
    if(x.size()==0) return x;
    printf("? %d ",x.size());
    for(auto i:x) printf("%d ",i);
    printf("\n");
    fflush(stdout);
    int t;
    scanf("%d",&t);
    x.clear();
    for(int i=1;i<=t;++i)
    {
        int z;
        scanf("%d",&z);
        x.push_back(z);
    }
    return x;
}
void tpsort(vector<int> *a)
{
    for(int i=1;i<=n*n+2;++i) f[i]=1,g[i]=0;
    for(int i=1;i<=n*n+1;++i)
    {
        for(auto j:a[i])
        {
            if(f[i]+1>f[j])
            {
                f[j]=f[i]+1;
                g[j]=i;
            }
        }
    }
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n*n+1;++i)
        {
            a1[i].clear(),a2[i].clear();
            d[i]=false;
            a1[i].push_back(n*n+2);
            a2[i].push_back(n*n+2);
        }
        for(int i=1;i<=n;++i)
        {
            vector<int> p;
            for(int j=1;j<=n*n+1;++j)
            {
                if(!d[j]) p.push_back(j);
            }
            p=ask(p);
            auto k=p.begin();
            p.push_back(n*n+2);
            for(auto j=p.begin();next(j)!=p.end();++j)
            {
                d[*j]=true;
                if(*next(j)!=n*n+2) a1[*j].push_back(*next(j));
                for(int l=*j+1;l<=*next(j)-1;++l)
                {
                    if(!d[l]) a2[*j].push_back(l);
                }
            }
        }
        tpsort(a1);
        if(f[n*n+2]<n+2) tpsort(a2);
        vector<int> p;
        p.push_back(n*n+2);
        while(g[p.back()]!=0) p.push_back(g[p.back()]);
        // for(auto i:p) printf("%d ",i);printf("\n");
        reverse(p.begin(),p.end());
        printf("! ");
        for(int i=0;i<=n;++i) printf("%d ",p[i]);
        printf("\n");
        fflush(stdout);
    }
    return 0;
}