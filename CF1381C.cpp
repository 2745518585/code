#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=200001;
int n,a[N],c[N];
struct str
{
    int x,s;
    str(){}
    str(int x,int s):x(x),s(s){}
}b[N];
queue<int> d[N];
bool cmp(str a,str b)
{
    return a.s>b.s;
}
bool cmp2(str a,str b)
{
    return a.x<b.x;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int x,y;
        scanf("%d%d%d",&n,&x,&y);
        for(int i=1;i<=n+1;++i)
        {
            b[i]=str(i,0);
            while(!d[i].empty()) d[i].pop();
        }
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            ++b[a[i]].s;
        }
        int z=0;
        for(int i=1;i<=n+1;++i)
        {
            if(b[i].s==0) z=b[i].x;
        }
        sort(b+1,b+n+2,cmp);
        int q=0;
        while(q<n-x)
        {
            for(int i=1;i<=n+1;++i)
            {
                if(b[i].s==0) break;
                --b[i].s;
                c[++q]=b[i].x;
                if(q>=n-x) break;
            }
        }
        sort(c+1,c+q+1);
        int u=0;
        for(int i=1;i<=q;++i)
        {
            int j=i;
            while(j+1<=q&&c[j+1]==c[i]) ++j;
            u=max(u,j-i+1);
            i=j;
        }
        if(u*2>(n-x)+(n-y))
        {
            printf("NO\n");
            continue;
        }
        bool v=true;
        int p=u+1,s=0;
        for(int i=1;i<=q;++i)
        {
            if(p<=u+(y-x)&&c[i]!=c[(p-1)%q+1])
            {
                d[c[i]].push(c[(p-1)%q+1]);
                ++p;
            }
        }
        sort(b+1,b+n+2,cmp2);
        printf("YES\n");
        for(int i=1;i<=n;++i)
        {
            if(b[a[i]].s>0)
            {
                printf("%d ",a[i]);
                --b[a[i]].s;
            }
            else if(!d[a[i]].empty())
            {
                printf("%d ",d[a[i]].front());
                d[a[i]].pop();
            }
            else printf("%d ",z);
        }
        printf("\n");
    }
    return 0;
}