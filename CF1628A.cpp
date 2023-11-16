#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=200001;
int n,q,a[N],d[N];
queue<int> b[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<=n;++i)
        {
            while(!b[i].empty()) b[i].pop();
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            b[a[i]].push(i);
        }
        q=0;
        for(int i=1;i<=n;++i)
        {
            int x=0,t=i;
            while(x<=n)
            {
                while(!b[x].empty()&&b[x].front()<i) b[x].pop();
                if(b[x].empty()) break;
                t=max(t,b[x].front());
                ++x;
            }
            d[++q]=x;
            i=t;
        }
        printf("%d\n",q);
        for(int i=1;i<=q;++i)
        {
            printf("%d ",d[i]);
        }
        printf("\n");
    }
    return 0;
}