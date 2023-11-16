#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001;
int n,m1,m2,a[N],a2[N],b[N],b2[N];
char z[N];
int main()
{
    scanf("%d",&n);
    scanf("%s",z+1);
    for(int i=1;i<=n-1;++i)
    {
        if(z[i]!=z[i+1]) a[++m1]=i,a2[m1]=z[i]-'0';
    }
    a2[m1+1]=z[n]-'0';
    scanf("%s",z+1);
    for(int i=1;i<=n-1;++i)
    {
        if(z[i]!=z[i+1]) b[++m2]=i,b2[m2]=z[i]-'0';
    }
    b2[m2+1]=z[n]-'0';
    int w=1e9;
    for(int i=-m1-1;i<=m2+1;++i)
    {
        if(i+1>=1&&i+1<=m2+1)
        {
            if(a2[1]!=b2[i+1]) continue;
        }
        int s=0;
        if(1+i>1)
        {
            for(int j=1;j<=(1+i)-1;++j) s+=b[j];
        }
        else if(1-i>1)
        {
            for(int j=1;j<=(1-i)-1;++j) s+=a[j];
        }
        for(int j=1;j<=m1;++j)
        {
            if(i+j>=1&&i+j<=m2)
            {
                if(a2[j]!=b2[i+j]) s=1e9;
                s+=abs(a[j]-b[i+j]);
            }
        }
        if(m1+i<m2)
        {
            for(int j=(m1+i)+1;j<=m2;++j) s+=(n-b[j]);
        }
        else if(m2-i<m1)
        {
            for(int j=(m2-i)+1;j<=m1;++j) s+=(n-a[j]);
        }
        w=min(w,s);
    }
    printf("%d",w);
    return 0;
}