#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,q,c[N];
char a[N],b[N];
void solve(int l,int r,int t)
{
    if(l>r) return;
    if(t==0)
    {
        if(a[l]==b[r-l+1]) c[++q]=1;
        c[++q]=r-l+1;
        solve(l+1,r,t^1);
    }
    else
    {
        if(a[r]!=b[r-l+1]) c[++q]=1;
        c[++q]=r-l+1;
        solve(l,r-1,t^1);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s%s",&n,a+1,b+1);
        q=0;
        solve(1,n,0);
        printf("%d ",q);
        for(int i=1;i<=q;++i)
        {
            printf("%d ",c[i]);
        }
        printf("\n");
    }
    return 0;
}