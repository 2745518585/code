#include<cstdio>
#include<algorithm>
#include<cstring>
#include<stack>
using namespace std;
const int N=1000001;
int n,q,tot,p=1,t[N],r[N],b[N],o[N];
bool f[N],g[N],h[N];
char a1[N],a2[N];
struct tree
{
    int b,c;
}T[N];
struct road
{
    int m,q;
}a[N];
stack<int> S;
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void dfs(int x)
{
    T[x].b=T[x].c=++tot;
    S.push(x);
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(T[a[i].m].b==0)
        {
            dfs(a[i].m);
            T[x].c=min(T[x].c,T[a[i].m].c);
        }
        else if(h[a[i].m]==false)
        {
            T[x].c=min(T[x].c,T[a[i].m].c);
        }
    }
    if(T[x].b==T[x].c)
    {
        if(S.top()==x)
        {
            h[x]=true;
            S.pop();
        }
        else
        {
            ++q;
            while(S.top()!=x)
            {
                h[S.top()]=true;
                r[S.top()]=q;
                S.pop();
            }
            h[x]=true;
            r[x]=q;
            S.pop();
        }
    }
}
int main()
{
    for(int i='A';i<='Z';++i) o[i]=i-'A'+1;
    for(int i='a';i<='z';++i) o[i]=i-'a'+27;
    int F;
    scanf("%d",&F);
    while(F--)
    {
        scanf("%s%s",a1+1,a2+1);
        if(strlen(a1+1)!=strlen(a2+1))
        {
            printf("-1\n");
            continue;
        }
        n=strlen(a1+1);
        p=1;
        tot=q=0;
        for(int i=1;i<=52;++i) t[i]=f[i]=g[i]=h[i]=r[i]=b[i]=T[i].b=T[i].c=0;
        while(!S.empty()) S.pop();
        bool u=true;
        for(int i=1;i<=n;++i)
        {
            f[o[a1[i]]]=true;
            if(b[o[a1[i]]]==0||b[o[a1[i]]]==o[a2[i]]) b[o[a1[i]]]=o[a2[i]];
            else
            {
                u=false;
                break;
            }
        }
        if(u==false)
        {
            printf("-1\n");
            continue;
        }
        for(int i=1;i<=52;++i)
        {
            if(b[i]==i) b[i]=0;
            if(b[i]!=0) road(i,b[i]);
        }
        for(int i=1;i<=52;++i)
        {
            if(T[i].b==0) dfs(i);
        }
        int w=0;
        for(int i=1;i<=52;++i)
        {
            if(r[i]!=0) ++w;
        }
        if(w==52)
        {
            printf("-1\n");
            continue;
        }
        for(int i=1;i<=52;++i)
        {
            if(r[i]==0&&r[b[i]]!=0) g[r[b[i]]]=true;
        }
        int s=0;
        for(int i=1;i<=52;++i)
        {
            if(b[i]!=0) ++s;
        }
        u=false;
        for(int i=1;i<=q;++i)
        {
            if(g[i]==false) ++s,u=true;
        }
        for(int i=1;i<=52;++i)
        {
            if(f[i]==false||(b[i]!=0&&r[i]==0)) u=false;
        }
        if(u) printf("-1\n");
        else printf("%d\n",s);
    }
    return 0;
}