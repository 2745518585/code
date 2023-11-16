#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,q,a[N],b[N];
vector<int> c[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    q=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;++i)
    {
        a[i]=lower_bound(b+1,b+q+1,a[i])-b;
        c[a[i]].push_back(i);
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=i+1;j<=n;++j)
        {
            if(a[i]>a[j]) ++s;
        }
    }
    printf("%d\n",s);
    vector<int> d;
    for(int i=1;i<=q;++i)
    {
        for(int j=d.size()-1;j>=0;--j)
        {
            for(auto k:c[i])
            {
                if(k>d[j]) break;
                printf("%d %d\n",k,d[j]);
            }
        }
        for(auto j:c[i]) d.push_back(j);
        sort(d.begin(),d.end());
    }
    return 0;
}