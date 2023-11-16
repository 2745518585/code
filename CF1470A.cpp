#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N],b[N];
priority_queue<int,vector<int>,greater<int> > Q1,Q2;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=m;++i)
        {
            scanf("%d",&b[i]);
        }
        sort(a+1,a+n+1);
        while(!Q1.empty()) Q1.pop();
        while(!Q2.empty()) Q2.pop();
        ll s=0;
        for(int i=1;i<=n;++i)
        {
            for(int j=a[i-1]+1;j<=a[i];++j) Q1.push(b[j]);
            Q2.push(b[a[i]]);
            if(!Q1.empty()&&Q1.top()<Q2.top())
            {
                s+=Q1.top();
                Q1.pop();
            }
            else
            {
                s+=Q2.top();
                Q2.pop();
            }
        }
        printf("%lld\n",s);
    }
    return 0;
}