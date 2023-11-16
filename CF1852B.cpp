#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=200001;
int n,b[N];
queue<int> a[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<=n;++i) while(!a[i].empty()) a[i].pop();
        for(int i=1;i<=n;++i)
        {
            int x;
            scanf("%d",&x);
            a[x].push(i);
        }
        int w1=0,w2=0;
        bool u=true;
        for(int i=n;i>=1;--i)
        {
            if(!a[n-w1].empty())
            {
                b[a[n-w1].front()]=i;
                a[n-w1].pop();
                ++w2;
            }
            else if(!a[w2].empty())
            {
                b[a[w2].front()]=-i;
                a[w2].pop();
                ++w1;
            }
            else
            {
                u=false;
                break;
            }
        }
        if(u)
        {
            printf("YES\n");
            for(int i=1;i<=n;++i)
            {
                printf("%d ",b[i]);
            }
            printf("\n");
        }
        else printf("NO\n");
    }
    return 0;
}