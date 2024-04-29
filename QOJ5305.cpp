#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,a[N];
vector<pair<int,int>> ans;
void check(int x,int y)
{
    ans.push_back(make_pair(x,y));
    static int z[N];
    int q=0;
    for(int i=n-y+1;i<=n;++i) z[++q]=a[i];
    for(int i=x+1;i<=n-y;++i) z[++q]=a[i];
    for(int i=1;i<=x;++i) z[++q]=a[i];
    for(int i=1;i<=n;++i) a[i]=z[i];
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        ans.clear();
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
        }
        if(n==3)
        {
            if(a[1]>a[3]) check(1,1);
            printf("%d\n",ans.size());
            for(auto i:ans) printf("%d %d\n",i.first,i.second);
            continue;
        }
        int x=0;
        while(a[x]!=1) ++x;
        if(x==2) check(2,1),check(1,1);
        else if(x>2) check(1,n-x+1);
        for(int i=1;i<=n-3;++i)
        {
            if(a[n]==n)
            {
                int x=1;
                while(a[x]!=n-1) ++x;
                if(x>i+1) check(i,2),check(1,i);
                if(x>i) continue;
            }
            int x=1;
            while(x+1<=i&&a[x+1]<a[n]) ++x;
            check(x,2),check(1,x);
        }
        // for(int i=1;i<=n;++i) printf("%d ",a[i]);printf("\n");
        if(a[n]==n)
        {
            int x=a[n-1];
            if(a[n-1]!=n-1) check(x-1,2),check(1,n-2),check(n-x-1,1),check(1,n-x),check(1,x);
        }
        else
        {
            for(int i=n-2;i<=n-1;++i)
            {
                int x=1;
                while(x+1<=i&&a[x+1]<a[n]) ++x;
                if(x<n-2) check(x,2),check(1,x);
                else if(x<n-1) check(1,1),check(n-2,1),check(2,n-3),check(n-3,1),check(1,n-2);
            }
        }
        printf("%d\n",ans.size());
        for(auto i:ans) printf("%d %d\n",i.first,i.second);
        // for(int i=1;i<=n;++i) printf("%d ",a[i]);printf("\n");
    }
    return 0;
}