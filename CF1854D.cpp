#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1001;
int n;
bool h[N];
bool query(int x,int k,int l,int r)
{
    printf("? %d %d %d ",x,k,r-l+1);
    for(int i=l;i<=r;++i) printf("%d ",i);
    printf("\n");
    fflush(stdout);
    int z;
    scanf("%d",&z);
    return z;
}
bool query(int x,int k,const vector<int> a)
{
    printf("? %d %d %d ",x,k,a.size());
    for(auto i:a) printf("%d ",i);
    printf("\n");
    fflush(stdout);
    int z;
    scanf("%d",&z);
    return z;
}
int find(int x,int k)
{
    int l=1,r=n;
    while(l<r)
    {
        int z=l+r>>1;
        if(query(x,k,l,z)) r=z;
        else l=z+1;
    }
    return l;
}
int main()
{
    scanf("%d",&n);
    vector<int> x;
    for(int i=1;i<=63;++i)
    {
        int z=find(1,n+i);
        if(h[z]) break;
        h[z]=true;
        x.push_back(z);
    }
    if(x.size()==63)
    {
        int p=x.size();
        while(true)
        {
            for(int i=1;i<=n;++i)
            {
                if(!h[i]&&query(i,p,x))
                {
                    h[i]=true;
                    x.push_back(i);
                }
            }
            p*=2;
            if(x.size()<p) break;
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(!h[i]&&query(i,n,x)) x.push_back(i);
    }
    sort(x.begin(),x.end());
    printf("! %d ",x.size());
    for(auto i:x) printf("%d ",i);
    fflush(stdout);
    return 0;
}