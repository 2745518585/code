#include<bits/stdc++.h>
using namespace std;
const int N=5e3+50;

struct node
{
    int l,r;
}p[N];

int T,n,a[N],tot,b[N];

void print()
{
    cout<<tot<<'\n';
    for(int i=1;i<=tot;i++)cout<<p[i].l<<' '<<p[i].r<<'\n';
    // for(int i=1;i<=n;i++)cout<<a[i]<<' ';
}

void mk(int l,int r)
{
    int cc=0;
    for(int i=n-r+1;i<=n;i++)b[++cc]=a[i];
    for(int i=l+1;i<=n-r;i++)b[++cc]=a[i];
    for(int i=1;i<=l;i++)b[++cc]=a[i];
    swap(a,b);p[++tot]=(node){l,r};
}

void sol()
{
    cin>>n;tot=0;
    for(int i=1;i<=n;i++)cin>>a[i];
    if(n==3)
    {
        if(a[1]>a[3])mk(1,1);
        return;
    }
    int pos=1;
    for(int i=2;i<=n;i++)if(a[i]==1)pos=i;
    if(pos==2)mk(2,1),mk(1,1);
    if(pos>2)mk(1,n-pos+1);
    for(int i=2;i<n;i++)
    {
        int x=a[n],t=1;
        for(int j=1;j<=i;j++)if(a[j]<x)t=j;
        if(t==i&&n==i+1)continue;
        if(t>=n-2)break;
        mk(t,2);mk(1,t);
    }
    if(a[n]==n&&a[n-1]!=n-1)
    {
        int x=a[n-1]-1,y=n-1-a[n-1];
        mk(x,2);mk(1,x+y);mk(y,1);mk(1,y+1);mk(1,x+1);
        return;
    }
    if(a[n]==n)return;
    mk(1,1);mk(n-2,1);mk(2,n-3);mk(n-3,1);mk(1,n-2);
}

main()
{
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    cin>>T;
    while(T--)sol(),print();
}