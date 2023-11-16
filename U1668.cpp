#include<bits/stdc++.h>
using namespace std;
const int N=3000001;
int n,tot=1,a[N][2],b[N];
void add(int x)
{
    int k=1;
    for(int i=30;i>=0;--i)
    {
        int z=(x&(1<<i))!=0;
        if(a[k][z]==0) a[k][z]=++tot;
        k=a[k][z];
    }
}
int find(int x)
{
    int k=1,s=0;
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
    int s=0;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        s=max(s,find(b[i])^b[i]);
        add(b[i]);
    }
    printf("%d",s);
    return 0;
}