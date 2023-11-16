#include<bits/stdc++.h>
using namespace std;
const int N=10001,M=20000001;
int n,a[10],b[N],c[10];
short h[M];
bool check()
{
    for(int i=1;i<=8;++i)
    {
        if(a[i]!=c[i]) return false;
    }
    return true;
}
void change1()
{
    swap(a[1],a[8]);
    swap(a[2],a[7]);
    swap(a[3],a[6]);
    swap(a[4],a[5]);
}
void change2()
{
    swap(a[3],a[4]);
    swap(a[2],a[3]);
    swap(a[1],a[2]);
    swap(a[6],a[5]);
    swap(a[7],a[6]);
    swap(a[8],a[7]);
}
void rechange2()
{
    swap(a[1],a[2]);
    swap(a[2],a[3]);
    swap(a[3],a[4]);
    swap(a[8],a[7]);
    swap(a[7],a[6]);
    swap(a[6],a[5]);
}
void change3()
{
    swap(a[2],a[3]);
    swap(a[7],a[2]);
    swap(a[6],a[7]);
}
void rechange3()
{
    swap(a[6],a[7]);
    swap(a[7],a[2]);
    swap(a[2],a[3]);
}
int sum()
{
    int s=0;
    for(int i=1;i<=8;++i)
    {
        s=s*8+a[i]-1;
    }
    return s;
}
int dfs(int x)
{
    if(x==n+1)
    {
        if(check()) return true;
        return false;
    }
    if(h[sum()]!=0&&h[sum()]<x) return false;
    h[sum()]=x;
    change1();
    b[x]=1;
    if(dfs(x+1)) return true;
    change1();
    change2();
    b[x]=2;
    if(dfs(x+1)) return true;
    rechange2();
    change3();
    b[x]=3;
    if(dfs(x+1)) return true;
    rechange3();
    return false;
}
int main()
{
    for(int i=1;i<=8;++i)
    {
        scanf("%d",&c[i]);
        a[i]=i;
    }
    for(n=0;;++n)
    {
        if(dfs(1))
        {
            printf("%d ",n);
            for(int i=1;i<=n;++i)
            {
                printf("%c",b[i]+'A'-1);
            }
            return 0;
        }
    }
    return 0;
}