#include<cstdio>
#include<algorithm>
#include<deque>
using namespace std;
const int N=1000001;
int n;
struct str
{
    int a,b;
}a[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i].a);
    }
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i].b);
    }
    a[0].a=-2e9,a[0].b=2e9;
    deque<pair<int,int>> Q;
    Q.push_back(make_pair(0,a[1].b));
    int s=2e9;
    for(int i=2;i<=n;++i)
    {
        if(a[i].b>a[i-1].b)
        {
            Q.push_back(make_pair(i-1,a[i].b-a[i-1].b));
        }
        else
        {
            int x=a[i-1].b-a[i].b;
            while(x>0)
            {
                auto k=Q.front();
                Q.pop_front();
                if(k.first!=0) s=min(s,a[i].a-a[k.first].a-2);
                int z=min(k.second,x);
                k.second-=z;
                x-=z;
                if(k.second>0) Q.push_front(k);
            }
        }
    }
    if(s>1e9) printf("-1\n");
    else printf("%d\n",s);
    return 0;
}