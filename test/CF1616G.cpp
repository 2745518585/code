#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,b[N];
bool f[N][2];
vector<int> a1[N],a2[N];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        n+=2;
        for(int i=1;i<=n;++i) a1[i].clear(),a2[i].clear(),b[i]=f[i][0]=f[i][1]=0;
        for(int i=1;i<=m;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            ++x,++y;
            a1[x].push_back(y);
            a2[y].push_back(x);
            if(y==x+1) b[x+1]=1;
        }
        for(int i=2;i<=n;++i)
        {
            a1[1].push_back(i);
            a2[i].push_back(1);
        }
        for(int i=1;i<=n-1;++i)
        {
            a1[i].push_back(n);
            a2[n].push_back(i);
        }
        b[2]=b[n]=1;
        for(int i=1;i<=n;++i) b[i]+=b[i-1];
        if(b[n]==n-1)
        {
            printf("%lld\n",(ll)(n-2)*(n-3)/2);
            continue;
        }
        int l=1;
        while(b[l]!=b[l+1]) ++l;
        f[l][0]=true;
        for(int i=l-1;i>=1;--i)
        {
            for(auto j:a1[i])
            {
                if(j==i+1) continue;
                if(b[j-1]-b[i+1]==j-i-2)
                {
                    f[i][0]|=f[j-1][1];
                    f[i][1]|=f[j-1][0];
                }
            }
        }
        for(int i=l+1;i<=n;++i)
        {
            for(auto j:a2[i+1])
            {
                if(j==i) continue;
                if(b[i]-b[j+1]==i-j-1)
                {
                    f[i][0]|=f[j][1];
                    f[i][1]|=f[j][0];
                }
            }
        }
        // for(int i=1;i<=n;++i) printf("%d: %d %d\n",i,f[i][0],f[i][1]);
        int r=n;
        while(b[r]!=b[r-1]) --r;
        // printf("%d %d\n",l,r);
        int w[3]={0,0,0};
        for(int i=r-1;i<=n;++i)
        {
            w[0]+=f[i][0];
            w[1]+=f[i][1];
            w[2]+=f[i][0]&f[i][1];
        }
        ll s=0;
        for(int i=1;i<=l;++i)
        {
            if(f[i][0]) s+=w[0];
            if(f[i][1]) s+=w[1];
            if(f[i][0]&&f[i][1]) s-=w[2];
        }
        if(l==r-1) --s;
        printf("%lld\n",s);
    }
    return 0;
}