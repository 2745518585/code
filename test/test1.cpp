#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1000001;
int n,tot=1,b[N][26],f[N],g[N],l[N];
char a[N];
int find(int x,int k)
{
    while(k-l[x]-1<=0||a[k-l[x]-1]!=a[k]) x=f[x];
    return x;
}
int main()
{
    scanf("%s",a+1);
    n=strlen(a+1);
    f[0]=1,l[1]=-1;
    int x=0;
    for(int i=1;i<=n;++i)
    {
        a[i]=(a[i]-'a'+g[x])%26+'a';
        x=find(x,i);
        if(b[x][a[i]-'a']==0)
        {
            b[x][a[i]-'a']=++tot;
            f[tot]=b[find(f[x],i)][a[i]-'a'];
            l[tot]=l[x]+2;
            g[tot]=g[f[tot]]+1;
        }
        x=b[x][a[i]-'a'];
        printf("%d ",g[x]);
    }
    return 0;
}