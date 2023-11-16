#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,k,a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        priority_queue<int,vector<int>,greater<int>> Q;
        int w=0;
        ll s=0;
        for(int i=1;i<=n;++i)
        {
            if(a[i-1]%k<a[i]%k)
            {
                --w;
                Q.push(a[i]%k-a[i-1]%k);
            }
            else Q.push(a[i]%k+k-a[i-1]%k);
            if(w<0)
            {
                s+=Q.top();
                Q.pop();
                ++w;
            }
        }
        printf("%lld\n",s);
    }
    return 0;
}