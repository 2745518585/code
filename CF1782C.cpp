#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,g[N];
char a[N];
bool f[N];
struct str
{
    int x,s;
}h[N];
bool cmp(str a,str b)
{
    return a.s>b.s;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s",&n,a+1);
        for(int i=1;i<=26;++i) h[i].s=0,h[i].x=i;
        for(int i=1;i<=n;++i) ++h[a[i]-'a'+1].s;
        sort(h+1,h+26+1,cmp);
        int s=1e9,q=0;
        for(int i=1;i<=26;++i)
        {
            if(n%i!=0) continue;
            int w=0;
            for(int j=1;j<=i;++j) w+=max(n/i-h[j].s,0);
            if(w<s) s=w,q=i;
        }
        printf("%d\n",s);
        for(int i=1;i<=26;++i) g[i]=0;
        for(int i=1;i<=q;++i) g[h[i].x]=n/q;
        for(int i=1;i<=n;++i) f[i]=false;
        for(int i=1;i<=n;++i)
        {
            if(g[a[i]-'a'+1]!=0)
            {
                f[i]=true;
                --g[a[i]-'a'+1];
            }
        }
        for(int i=1;i<=n;++i)
        {
            if(f[i])
            {
                putchar(a[i]);
                continue;
            }
            for(int j=1;j<=26;++j)
            {
                if(g[j]!=0)
                {
                    putchar('a'+j-1);
                    --g[j];
                    break;
                }
            }
        }
        printf("\n");
    }
    return 0;
}