#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200001;
const ll inf=5e18;
int n,m,v,tot=1,a[N<<6][2];
ll b[N<<6],c[N<<6];
void add(ll x,ll k)
{
    int q=1;
    for(int i=v-1;i>=0;--i)
    {
        b[q]+=k;
        c[q]=min(c[q],x);
        int z=(x&(1ll<<i))!=0;
        if(a[q][z]==0)
        {
            a[q][z]=++tot;
            a[tot][0]=a[tot][1]=0;
            b[tot]=0;
            c[tot]=inf;
        }
        q=a[q][z];
    }
    b[q]+=k;
    c[q]=min(c[q],x);
}
void dfs()
{

}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&v);
        tot=1;
        a[tot][0]=a[tot][1]=0;
        b[tot]=0;
        c[tot]=inf;

    }
    return 0;
}