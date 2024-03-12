#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
const int N=1001;
int n,d[N];
set<int> a[N],b;
vector<int> ans;
int query(set<int> &x)
{
    printf("? ");
    for(auto i:x) printf("%d ",i);
    printf("\n");
    fflush(stdout);
    int z;
    scanf("%d",&z);
    return z;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        ans.clear();
        for(int i=1;i<=n;++i) a[i].clear();
        b.clear();
        for(int i=1;i<=n*n;++i) d[i]=0;
        for(int i=1;i<=n;++i)
        {
            for(int j=(i-1)*n+1;j<=i*n;++j) a[i].insert(j);
            int x=query(a[i]);
            a[i].erase(x);
            b.insert(x);
            d[x]=i;
        }
        for(int i=1;i<=n*n-n;++i)
        {
            int x=query(b);
            b.erase(x);
            ans.push_back(x);
            if(i<=n*n-n-(n-1))
            {
                for(int j=1;j<=n;++j)
                {
                    if(j==d[x]) continue;
                    while(a[j].size()>0&&a[d[x]].size()<n)
                    {
                        a[d[x]].insert(*a[j].begin());
                        a[j].erase(*a[j].begin());
                    }
                }
                int z=query(a[d[x]]);
                a[d[x]].erase(z);
                b.insert(z);
                d[z]=d[x];
            }
            else
            {
                for(int j=1;j<=n;++j)
                {
                    if(a[j].size()>0)
                    {
                        b.insert(*a[j].begin());
                        a[j].erase(*a[j].begin());
                        break;
                    }
                }
            }
        }
        for(auto i:b)
        {
            if(d[i]) ans.push_back(i);
        }
        printf("! ");
        for(auto i:ans) printf("%d ",i);
        printf("\n");
        fflush(stdout);
    }
    return 0;
}