#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int N=100001;
int n,tot=1,a[N][2],f[N],l[N];
bool g[N],h[N];
void add(char *x)
{
    int q=1;
    for(int i=1;x[i];++i)
    {
        if(a[q][x[i]-'0']==0) a[q][x[i]-'0']=++tot;
        q=a[q][x[i]-'0'];
    }
    g[q]=true;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        static char b[N];
        scanf("%s",b+1);
        add(b);
    }
    a[0][0]=a[0][1]=1;
    f[1]=0;
    queue<int> Q;
    Q.push(1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        g[k]|=g[f[k]];
        for(int i=0;i<=1;++i)
        {
            if(a[k][i]!=0)
            {
                f[a[k][i]]=a[f[k]][i];
                Q.push(a[k][i]);
            }
            else a[k][i]=a[f[k]][i];
        }
    }
    for(int i=1;i<=tot;++i)
    {
        if(g[i]==false) ++l[a[i][0]],++l[a[i][1]];
    }
    for(int i=1;i<=tot;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(g[k]==true) continue;
        for(auto i:{a[k][0],a[k][1]})
        {
            --l[i];
            if(l[i]==0) Q.push(i);
        }
    }
    for(int i=1;i<=tot;++i)
    {
        if(g[i]==false&&l[i]!=0)
        {
            printf("TAK");
            return 0;
        }
    }
    printf("NIE");
    return 0;
}