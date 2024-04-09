#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,k,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&a[i]);
        }
        sort(a+1,a+m+1);
        a[m+1]=a[1];
        int s=m-2;
        vector<int> p,q;
        for(int i=1;i<=m;++i)
        {
            if((a[i+1]-a[i]+n)%n%2==0) p.push_back((a[i+1]-a[i]+n)%n);
            else q.push_back((a[i+1]-a[i]+n)%n);
        }
        sort(p.begin(),p.end());
        sort(q.begin(),q.end());
        for(auto i:p)
        {
            int z=min(i/2-1,k);
            k-=z,s+=z;
            if(z==i/2-1) s+=i/2;
            else s+=z;
        }
        for(auto i:q)
        {
            int z=min(i/2,k);
            k-=z,s+=z,s+=z;
        }
        printf("%d\n",s);
    }
    return 0;
}