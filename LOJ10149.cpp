#include<cstdio>
#include<algorithm>
using namespace std;
struct num
{
    int a[1001],l;
    num operator +(const num& b)const
	{
        num c;
		c.l=max(l,b.l);
        for(int i=1;i<=c.l;++i)
        {
            c.a[i]=a[i]+b.a[i];
        }
        while(c.a[c.l]>9)
        {
            c.a[c.l+1]=c.a[c.l]/10;
            c.a[c.l]%=10;
            ++c.l;
        }
        return c;
	}
    num operator *(const num& b)const
	{
        num c;
		c.l=l+b.l-1;
        for(int i=1;i<=l;++i)
        {
            for(int j=1;j<=b.l;++j)
            {
                c.a[i+j-1]=a[i]*b.a[j];
            }
        }
        while(c.a[c.l]>9)
        {
            c.a[c.l+1]=c.a[c.l]/10;
            c.a[c.l]%=10;
            ++c.l;
        }
        return c;
	}
    bool operator <(const num& b)const
	{
        if(l!=b.l) return l<b.l;
        for(int i=l;i>=1;--i)
        {
            if(a[i]!=b.a[i]) return a[i]<b.a[i];
        }
        return true;
	}
};
void input(num &a)
{
    int x;
    scanf("%d",&x);
    a.l=0;
    while(x!=0)
    {
        a.a[++a.l]=x%10;
        x/=10;
    }
}
void print(num x)
{
    for(int i=x.l;i>=1;--i)
    {
        printf("%d",x.a[i]);
    }
}
int n;
num a[101],f[101][101],MAX;
int main()
{
    MAX.l=100;
    MAX.a[100]=1;
    scanf("%d\n",&n);
    for(int i=1;i<=n;++i)
    {
        input(a[i]);
        a[i+n]=a[i];
    }
    for(int i=3;i<=n;++i)
    {
        for(int j=1;j<=n*2-i+1;++j)
        {
            f[j][i+j-1]=MAX;
        }
    }
    for(int i=3;i<=n;++i)
    {
        for(int j=1;j<=n*2-i+1;++j)
        {
            int l=j,r=j+i-1;
            for(int k=l+1;k<=r-1;++k)
            {
                if(f[l][k]+f[k][r]+a[l]*a[k]*a[r]<f[l][r])
                {
                    f[l][r]=f[l][k]+f[k][r]+a[l]*a[k]*a[r];
                }
            }
        }
    }
    num s=MAX;
    for(int i=1;i<=n;++i)
    {
        if(f[i][i+n-1]<s)
        {
            s=f[i][i+n-1];
        }
    }
    print(s);
    return 0;
}