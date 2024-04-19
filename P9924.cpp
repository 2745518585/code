#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=2001;
int n,m,q,tot=1,b1[N][N],b2[N][N],c[N*N][2],d[N*N],g1[N],g2[N];
bool a1[N][N],a2[N][N],f[N][N];
vector<int> e1[N],e2[N];
void add(int x)
{
    int q=1;
    for(int i=1;i<=n;++i)
    {
        if(c[q][a1[x][i]]==0)
        {
            c[q][a1[x][i]]=++tot;
            c[tot][0]=c[tot][1]=d[tot]=0;
        }
        q=c[q][a1[x][i]];
    }
    if(d[q]==0) d[q]=x;
    else g1[x]=d[q];
}
int main()
{
    scanf("%d%d%*d",&n,&m);
    if(m==n*n)
    {
        while((1<<q)<n*2-1) ++q;
        printf("%d\n",q+1);
        for(int i=1;i<=n*2;++i)
        {
            printf("A");
            for(int j=0;(1<<j)<n*2-1;++j)
            {
                if((i-1)&(1<<j)) printf("B");
                else printf("A");
            }
            printf("\n");
        }
        return 0;
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x>y) swap(x,y);
        if(x>n||y<=n) continue;
        a1[x][y-n]=true;
        a2[y-n][x]=true;
    }
    bool u=false;
    for(int i=1;i<=n;++i) add(i);
    tot=1,c[1][0]=c[1][1]=d[1]=0;
    swap(a1,a2);
    swap(g1,g2);
    for(int i=1;i<=n;++i) add(i);
    swap(a1,a2);
    swap(g1,g2);
    int s1=0,s2=0;
    for(int i=1;i<=n;++i) s1+=(g1[i]==0),s2+=(g2[i]==0);
    if(s1>s2)
    {
        u=true;
        swap(a1,a2);
        swap(g1,g2);
    }
    for(int i=1;i<=n;++i)
    {
        if(g1[i]==0) e1[i].push_back(i);
        else e1[g1[i]].push_back(i);
    }
    for(int i=1;i<=n;++i)
    {
        if(g2[i]==0) e2[i].push_back(i);
        else e2[g2[i]].push_back(i);
    }
    bool u1=false,u2=false;
    int s=0;
    for(int i=1;i<=n;++i) s=max(s,(int)e1[i].size());
    for(int i=0;(1<<i)<s;++i)
    {
        u1=true;
        ++q;
        for(int j=1;j<=n;++j) b1[j][q]=1,b2[j][q]=2;
        for(int j=1;j<=n;++j)
        {
            for(int k=0;k<e1[j].size();++k)
            {
                if(k&(1<<i)) b1[e1[j][k]][q]=0;
            }
        }
    }
    s=0;
    for(int i=1;i<=n;++i) s=max(s,(int)e2[i].size());
    for(int i=0;(1<<i)<s;++i)
    {
        u2=true;
        ++q;
        for(int j=1;j<=n;++j) b2[j][q]=1,b1[j][q]=2;
        for(int j=1;j<=n;++j)
        {
            for(int k=0;k<e2[j].size();++k)
            {
                if(k&(1<<i)) b2[e2[j][k]][q]=0;
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(g1[i]!=0) continue;
        bool u=false;
        for(int j=1;j<=n;++j) u|=a1[i][j];
        if(u==false) continue;
        ++q;
        for(int j=1;j<=n;++j) b1[j][q]=1;
        for(int j=1;j<=n;++j)
        {
            if(j==i||g1[j]==i) b1[j][q]=0;
        }
        for(int j=1;j<=n;++j)
        {
            if(a1[i][j]) b2[j][q]=0;
            else b2[j][q]=2;
        }
    }
    if(u1==false||u2==false)
    {
        ++q;
        for(int i=1;i<=n;++i) b1[i][q]=0,b2[i][q]=1;
    }
    if(u) swap(b1,b2);
    printf("%d\n",q);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=q;++j) printf("%c",b1[i][j]+'A');
        printf("\n");
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=q;++j) printf("%c",b2[i][j]+'A');
        printf("\n");
    }
    return 0;
}