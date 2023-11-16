#include<cstdio>
#include<algorithm>
#include<bitset>
using namespace std;
const int N=200001,M=101;
int n,p,q,a[N<<3],b[N<<3],sg[N<<3];
bool h[N<<3];
bitset<N> f[M],g;
int main()
{
    scanf("%d%d",&n,&p);
    for(int i=1;i<=n;++i)
    {
        int x1,x2,x3;
        scanf("%d%d%d",&x1,&x2,&x3);
        a[i*2-1]=x2-x1;
        a[i*2]=x3-x2;
    }
    n*=2;
    for(int i=2;i<=200000;++i)
    {
        for(int j=2;i*j<=200000;++j) h[i*j]=true;
    }
    for(int i=2;i<=200000;++i)
    {
        if(h[i]==false) b[++q]=i,g[i]=1;
    }
    for(int i=1;i<=q;++i)
    {
        for(int j=1;j<=q&&b[i]*b[j]<=200000;++j)
        {
            g[b[i]*b[j]]=true;
        }
    }
    g[p]=false;
    for(int i=1;i<=200000;++i)
    {
        while(f[sg[i]][i]) ++sg[i];
        f[sg[i]]|=g<<i;
    }
    int s=0;
    for(int i=1;i<=n*2;++i) s^=sg[a[i]];
    if(s) printf("Alice\nBob");
    else printf("Bob\nAlice");
    return 0;
}