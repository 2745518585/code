#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,t,mn,mx,a[N],b[N],p[N];
int query(int x)
{
    printf("? %d\n",x);
    fflush(stdout);
    char z;
    scanf("%s",&z);
    if(z=='<')
    {
        --t;
        return -1;
    }
    else if(z=='>')
    {
        ++t;
        return 1;
    }
    else return 0;
}
void move(int k)
{
    while(t>k) query(mn);
    while(t<k) query(mx);
}
void solve(int l,int r,int ml,int mr)
{
    if(l>r) return;
    if(ml==mr)
    {
        for(int i=l;i<=r;++i) b[a[l]]=ml;
        return;
    }
    int z=ml+mr>>1,p1=l-1,p2=r+1;
    for(int i=l;i<=r;++i)
    {
        move(z);
        if(query(a[i])<=0) p[++p1]=a[i];
        else p[--p2]=a[i];
    }
    for(int i=l;i<=r;++i) a[i]=p[i];
    solve(l,p1,ml,z);
    solve(p2,r,z+1,mr);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        mn=mx=1;
        while(query(1));
        for(int i=2;i<=n;++i)
        {
            if(query(i)==1) query(mn);
            else
            {
                while(query(i));
                mn=i;
            }
        }
        while(query(1));
        for(int i=2;i<=n;++i)
        {
            if(query(i)==-1) query(mx);
            else
            {
                while(query(i));
                mx=i;
            }
        }
        t=n;
        int q=1;
        for(int i=1;i<=n;++i)
        {
            if(i!=mn&&i!=mx) a[++q]=i;
        }
        b[mn]=1,b[mx]=n;
        solve(2,n-1,2,n-1);
        printf("! ");
        for(int i=1;i<=n;++i)
        {
            printf("%d ",b[i]);
        }
        printf("\n");
        fflush(stdout);
    }
    return 0;
}