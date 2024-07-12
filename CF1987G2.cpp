#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,a[N],S[N],T,f[N][3];
char c[N];
struct tree
{
    int l,r;
}b[N];
void dfs(int x)
{
    if(x==0) return;
    dfs(b[x].l);
    dfs(b[x].r);
    f[x][0]=f[b[x].l][0];
    f[x][1]=f[b[x].r][1];
    f[x][2]=f[b[x].l][0]+f[b[x].r][1];
    if(c[x]!='R')
    {
        f[x][0]=max(f[x][0],max(f[b[x].l][1],f[b[x].r][0])+1);
        f[x][2]=max(f[x][2],max(f[b[x].l][1]+f[b[x].r][1],f[b[x].r][2])+1);
    }
    if(c[x]!='L')
    {
        f[x][1]=max(f[x][1],max(f[b[x].l][1],f[b[x].r][0])+1);
        f[x][2]=max(f[x][2],max(f[b[x].l][0]+f[b[x].r][0],f[b[x].l][2])+1);
    }
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        scanf("%s",c+1);
        if(![&](){
            int p=0;
            for(int i=1;i<=n;++i)
            {
                if(p<a[i]&&a[i]!=n)
                {
                    if(c[i]=='L') return false;
                    c[i]='R';
                }
                p=max(p,a[i]);
            }
            p=0;
            for(int i=n;i>=1;--i)
            {
                if(p<a[i]&&a[i]!=n)
                {
                    if(c[i]=='R') return false;
                    c[i]='L';
                }
                p=max(p,a[i]);
            }
            return true;
        }())
        {
            printf("-1\n");
            continue;
        }
        for(int i=1;i<=n;++i) b[i].l=b[i].r=f[i][0]=f[i][1]=f[i][2]=0;
        T=0;
        for(int i=1;i<=n;++i)
        {
            S[T+1]=0;
            while(T>0&&a[S[T]]<a[i]) --T;
            if(T>0) b[S[T]].r=i;
            b[i].l=S[T+1];
            S[++T]=i;
        }
        dfs(S[1]);
        int s=0;
        for(int i=1;i<=n;++i)
        {
            s=max(s,f[b[i].l][1]+f[b[i].r][0]);
            if(c[i]!='R'&&a[i]!=n)
            {
                s=max(s,f[b[i].l][0]+f[b[i].r][0]+1);
                s=max(s,f[b[i].l][2]+1);
            }
            if(c[i]!='L'&&a[i]!=n)
            {
                s=max(s,f[b[i].l][1]+f[b[i].r][1]+1);
                s=max(s,f[b[i].r][2]+1);
            }
        }
        printf("%d\n",s);
    }
    return 0;
}