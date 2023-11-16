#include<bits/stdc++.h>
#define max(x,y) x>y?x:y
#define min(x,y) x<y?x:y
const int N=100001;
int a1,a2,n,b[N],c[N];
inline int gcd(register int a,register int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void dfs(register int x,register int k1,register int k2)
{
    if(x==n+1)
    {
        if(k1==0&&b[n]<c[n])
        {
            for(int i=1;i<=n;++i) c[i]=b[i];
        }
        return;
    }
    if(k1==0) return;
    for(register int i=max(b[x-1]+1,k2/k1);i<=c[n]&&(n-x+1)*k2>=k1*i;++i)
    {
        if(k2>k1*i) continue;
        b[x]=i;
        int z=k2*i/gcd(k2,i);
        dfs(x+1,k1*(z/k2)-z/i,z);
    }
}
int main()
{
    scanf("%d%d",&a1,&a2);
    int z=gcd(a1,a2);
    a1/=z,a2/=z;
    for(n=1;;++n)
    {
        c[n]=1e9;
        dfs(1,a1,a2);
        if(c[n]!=1e9)
        {
            for(int i=1;i<=n;++i)
            {
                printf("%d ",c[i]);
            }
            return 0;
        }
    }
    return 0;
}