#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,q,b[N],f[N],g[N];
vector<int> c[N];
struct str
{
    int x,w;
    str(){}
    str(int x,int w):x(x),w(w){}
};
vector<str> a[N];
int main()
{
    int F;
    scanf("%d",&F);
    while(F--)
    {
        q=0;
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            int k;
            scanf("%d",&k);
            c[i].push_back(0);
            for(int j=1;j<=k;++j)
            {
                int x;
                scanf("%d",&x);
                c[i].push_back(x);
                b[++q]=x;
            }
        }
        sort(b+1,b+q+1);
        q=unique(b+1,b+q+1)-b-1;
        for(int i=1;i<=n;++i)
        {
            int k=c[i].size()-1;
            for(int j=1;j<=k;++j)
            {
                c[i][j]=lower_bound(b+1,b+q+1,c[i][j])-b;
            }
            int w=0,p=0;
            for(int j=1;j<=k;++j)
            {
                if(c[i][j]>w)
                {
                    g[++p]=c[i][j];
                    w=c[i][j];
                }
            }
            for(int j=1;j<=p;++j)
            {
                a[g[p]].push_back(str(g[j]-1,p-j+1));
            }
        }
        f[0]=0;
        for(int i=1;i<=q;++i)
        {
            f[i]=f[i-1];
            for(auto j:a[i])
            {
                // printf("%d %d %d\n",b[j.x],b[i],j.w);
                f[i]=max(f[i],f[j.x]+j.w);
            }
            // printf("%d %d\n",b[i],f[i]);
        }
        printf("%d\n",f[q]);
        for(int i=1;i<=n;++i) c[i].clear();
        for(int i=1;i<=q;++i) a[i].clear();
    }
    return 0;
}