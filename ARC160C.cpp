#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
const ll P=998244353;
int n,q,b[N],d[N];
ll *f[N];
int main()
{
    scanf("%d",&n);
    priority_queue<int,vector<int>,greater<int>> Q;
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        q=max(q,x);
        Q.push(x);
        ++b[x],++d[x];
    }
    while(!Q.empty())
    {
        int k1=Q.top();
        Q.pop();
        if(Q.empty()||k1!=Q.top()) continue;
        int k2=Q.top();
        Q.pop();
        Q.push(k1+1);
        ++d[k1+1];
    }
    f[0]=new ll[10];
    f[0][0]=1;
    for(int i=1;i<=q*2;++i)
    {
        f[i]=new ll[d[i]+10];
        for(int j=0;j<=b[i]-1;++j) f[i][j]=0;
        for(int j=b[i];j<=d[i];++j)
        {
            if((j-b[i])*2<=d[i-1]) f[i][j]=f[i-1][(j-b[i])*2];
        }
        for(int j=d[i]-1;j>=0;--j) f[i][j]=(f[i][j]+f[i][j+1])%P;
    }
    printf("%lld",f[q*2][0]);
    return 0;
}