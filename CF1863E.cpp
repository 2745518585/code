#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,t,q,b[N],c[N],l[N];
ll f[N];
bool h[N];
vector<int> a[N];
bool cmp(int x,int y)
{
    return b[x]<b[y];
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&t);
        q=0;
        for(int i=1;i<=n;++i) a[i].clear(),l[i]=0,f[i]=0,h[i]=false;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&b[i]);
        }
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[y].push_back(x);
            ++l[x];
            h[y]=true;
        }
        queue<int> Q;
        for(int i=1;i<=n;++i)
        {
            if(l[i]==0)
            {
                Q.push(i);
                f[i]=b[i];
            }
        }
        while(!Q.empty())
        {
            int k=Q.front();
            Q.pop();
            for(auto i:a[k])
            {
                f[i]=max(f[i],f[k]+(b[i]>b[k])*t);
                --l[i];
                if(l[i]==0) Q.push(i);
            }
        }
        for(int i=1;i<=n;++i)
        {
            if(h[i]==false) c[++q]=i;
        }
        sort(c+1,c+q+1,cmp);
        ll s=1e18,w=0;
        for(int i=1;i<=q;++i)
        {
            w=max(w,f[c[i]]);
        }
        for(int i=1;i<=q;++i)
        {
            s=min(s,w-b[c[i]]);
            w=max(w,f[c[i]]+t);
        }
        printf("%lld\n",s);
    }
    return 0;
}