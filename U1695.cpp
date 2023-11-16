#include<bits/stdc++.h>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=1000001,M=10000001;
int n,m1,m2,s1,p=1,t[N],f[N];
bool h[N];
struct str
{
    int m,q,w;
}a[M];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
int main()
{
    scanf("%d%d%d%d",&n,&m1,&m2,&s1);
    for(int i=1;i<=m1;++i)
    {
        int x=read(),y=read(),w=read();
        road(x,y,w);
        road(y,x,w);
    }
    for(int i=1;i<=m2;++i)
    {
        int x=read(),y=read(),w=read();
        road(x,y,w);
    }
    for(int i=1;i<=n;++i) f[i]=1e9;
    f[s1]=0;
    h[s1]=true;
    queue<int> Q;
    Q.push(s1);
    while(!Q.empty()) 
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[k]+a[i].w<f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                h[a[i].m]=true;
                Q.push(a[i].m);
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(f[i]==1e9) printf("NO PATH\n");
        else printf("%d\n",f[i]);
    }
    return 0;
}