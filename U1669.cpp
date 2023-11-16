#include<bits/stdc++.h>
using namespace std;
const int N=500001;
int n,tot=2,a[N<<5][2],b[N],b1[N],b2[N],f[N];
void add(int x,int k)
{
    for(int i=30;i>=0;--i)
    {
        int z=(x&(1<<i))!=0;
        if(a[k][z]==0) a[k][z]=++tot;
        k=a[k][z];
    }
}
int find(int x,int k)
{
    int s=0;
    for(int i=30;i>=0;--i)
    {
        int z=(x&(1<<i))==0;
        if(a[k][z]!=0) k=a[k][z],s=s*2+z;
        else k=a[k][z^1],s=s*2+(z^1);
    }
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    add(0,1);
    for(int i=1;i<=n;++i)
    {
        b1[i]=b1[i-1]^b[i];
        f[i]=find(b1[i],1)^b1[i];
        add(b1[i],1);
    }
    for(int i=1;i<=n;++i) f[i]=max(f[i],f[i-1]);
    add(0,2);
    int s=0;
    for(int i=n;i>=1;--i)
    {
        b2[i]=b2[i+1]^b[i];
        s=max(s,f[i-1]+(find(b2[i],2)^b2[i]));
        add(b2[i],2);
    }
    printf("%d",s);
    return 0;
}