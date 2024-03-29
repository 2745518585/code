#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,las=1,tot=1,f[N],l[N];
char b[N];
struct tree
{
    int s[26],l,f;
}a[N];
void add(int c)
{
    int x=las,nx=las=++tot;
    f[tot]=1;
    a[nx].l=a[x].l+1;
    while(x!=0&&a[x].s[c]==0)
    {
        a[x].s[c]=nx;
        x=a[x].f;
    }
    if(x==0) a[nx].f=1;
    else
    {
        int y=a[x].s[c];
        if(a[x].l+1==a[y].l) a[nx].f=y;
        else
        {
            int ny=++tot;
            a[ny]=a[y];
            a[ny].l=a[x].l+1;
            a[y].f=a[nx].f=ny;
            while(x!=0&&a[x].s[c]==y)
            {
                a[x].s[c]=ny;
                x=a[x].f;
            }
        }
    }
}
int main()
{
    scanf("%s",b+1);
    n=strlen(b+1);
    for(int i=1;i<=n;++i) add(b[i]-'a');
    for(int i=2;i<=tot;++i) ++l[a[i].f];
    queue<int> Q;
    for(int i=1;i<=tot;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        f[a[k].f]+=f[k];
        --l[a[k].f];
        if(l[a[k].f]==0) Q.push(a[k].f);
    }
    ll s=0;
    for(int i=1;i<=tot;++i)
    {
        if(f[i]!=1) s=max(s,(ll)f[i]*a[i].l);
    }
    printf("%lld",s);
    return 0;
}