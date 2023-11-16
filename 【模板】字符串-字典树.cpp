#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1000001,M=26;
int n,m,a[N][M],q=1;
bool g[N],h[N];
void add(char *x)
{
    int k=1;
    for(int i=1;x[i];++i)
    {
        if(a[k][x[i]-'a']==0) a[k][x[i]-'a']=++q;
        k=a[k][x[i]-'a'];
    }
    g[k]=true;
}
int find(char *x)
{
    int k=1;
    for(int i=1;x[i];++i)
    {
        if(a[k][x[i]-'a']==0) return -1;
        else k=a[k][x[i]-'a'];
    }
    if(g[k]==false) return -1;
    return k;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        char x[100];
        scanf("%s",x+1);
        add(x);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        char x[100];
        scanf("%d",x+1);
        int z=find(x);
        if(z!=-1)
        {
            if(h[z]==true) printf("REPEAT\n");
            else
            {
                printf("OK\n");
                h[z]=true;
            }
        }
        else printf("WRONG\n");
    }
}