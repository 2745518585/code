#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,q,f[N][3];
vector<int> a[N];
bool b[N],h[N];
void dfs(int x,int fa)
{
    if(b[x]) h[x]=true;
    int s=0,s0=0,s1=0,s2=0,w0=0,w1=0,w2=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs(i,x);
        if(!h[i]) continue;
        h[x]|=h[i];
        if(f[i][0]>=f[i][1]&&f[i][0]>=f[i][2]) s+=f[i][0],++w0;
        else if(f[i][1]>=f[i][2]) s+=f[i][1],++w1;
        else s+=f[i][2],++w2;
        s0+=f[i][0],s1+=f[i][1],s2+=f[i][2];
    }
    if(w0+w1+w2==0) return;
    if(w0>0&&w1==0) f[x][0]=s+(w0-1);
    else f[x][0]=s+(w0+w1/2);
    f[x][1]=s+(w0+(w1+1)/2);
    if(w1+w2!=0)
    {
        if(w1==0&&w2>0) f[x][2]=s+(w0);
        else f[x][2]=s+((w0+w1/2+1));
    }
    if(b[x]) f[x][2]=max(f[x][2],s0+(w0+w1+w2));
    else f[x][2]=max(f[x][2],s0+(w0+w1+w2+1));
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&q);
        for(int i=1;i<=n;++i) a[i].clear(),b[i]=h[i]=f[i][0]=f[i][1]=f[i][2]=0;
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        for(int i=1;i<=m;++i)
        {
            int x;
            scanf("%d",&x);
            b[x]=true;
        }
        dfs(1,0);
        // for(int i=1;i<=n;++i)
        // {
        //     printf("%d %d %d\n",f[i][0],f[i][1],f[i][2]);
        // }
        // printf("%d\n",f[1][0]);
        int s=0;
        for(int i=1;i<=n;++i)
        {
            if(h[i]) ++s;
        }
        for(int i=1;i<=q;++i)
        {
            int x;
            scanf("%d",&x);
            printf("%d ",2*(s-1)-min(x,f[1][0]));
        }
        printf("\n");
    }
    return 0;
}