#include<cstdio>
#include<algorithm>
using namespace std;
struct Int
{
    int s[101],l,u;
    friend Int operator +(Int a,Int b)
    {
        if(a.u==0) return b; else if(b.u==0) return a;
        Int c; c.l=max(a.l,b.l);
        for(int i=1;i<=c.l;++i) c.s[i]=0;
        if(a.u!=b.u&&abs(a)==abs(b)) {c.read(0);return c;}
        if(a.u==b.u) c.u=a.u; else c.u=abs(a)>abs(b)?a.u:b.u;
        int z1=(a.u==c.u?1:-1),z2=(b.u==c.u?1:-1);
        for(int i=1;i<=c.l;++i)
        {
            if(i<=a.l) c.s[i]+=a.s[i]*z1;
            if(i<=b.l) c.s[i]+=b.s[i]*z2;
            if(c.s[i]>=10) {c.s[i+1]=1;c.s[i]-=10;}
            else if(c.s[i]<-10) {c.s[i+1]=-2;c.s[i]+=20;}
            else if(c.s[i]<0) {c.s[i+1]=-1;c.s[i]+=10;}
            else c.s[i+1]=0;
        }
        while(c.s[c.l+1]>0) {++c.l;if(c.s[c.l]>=10) {c.s[c.l+1]=1;c.s[c.l]-=10;} else c.s[c.l+1]=0;}
        while(c.s[c.l]==0&&c.l>0) --c.l; if(c.l==0) c.u=0; return c;
    }
    friend Int operator +(Int a,int x) {Int b;b.read(x);return a+b;}
    friend Int operator +(int x,Int a) {return a+x;}
    friend Int operator +=(Int& a,Int b) {a=a+b;return a;}
    friend Int operator +=(Int& a,int x) {a=a+x;return a;}
    friend Int operator -(Int a,Int b) {b.u=-b.u;return a+b;}
    friend Int operator -(Int a,int x) {x=-x;return a+x;}
    friend Int operator -(int x,Int a) {a.u=-a.u;return a+x;}
    friend Int operator -=(Int& a,Int b) {b.u=-b.u;a+=b;return a;}
    friend Int operator -=(Int& a,int x) {x=-x;a+=x;return a;}
    friend Int operator *(Int a,Int b)
    {
        Int c; if(a.u==0||b.u==0) {c.read(0);return c;}
        c.l=a.l+b.l-1; for(int i=1;i<=c.l+1;++i) c.s[i]=0;
        if(a.u==b.u) c.u=1; else c.u=-1;
        for(int i=1;i<=a.l;++i)
            for(int j=1;j<=b.l;++j) c.s[i+j-1]+=a.s[i]*b.s[j]; 
        for(int i=1;i<=c.l;++i) {c.s[i+1]+=c.s[i]/10;c.s[i]%=10;}
        while(c.s[c.l+1]>0) {++c.l;c.s[c.l+1]=c.s[c.l]/10;c.s[c.l]%=10;}
        while(c.s[c.l]==0&&c.l>0) --c.l; if(c.l==0) c.u=0; return c;
    }
    friend Int operator *(Int a,int x)
    {
        if(a.u==0||x==0) {a.read(0);return a;}
        if(x<0) a.u=-a.u; x=x*a.u;
        for(int i=1;i<=a.l;++i) a.s[i]*=x;
        for(int i=1;i<=a.l;++i) {a.s[i+1]+=a.s[i]/10;a.s[i]%=10;}
        while(a.s[a.l+1]>0) {++a.l;a.s[a.l+1]=a.s[a.l]/10;a.s[a.l]%=10;}
        while(a.s[a.l]==0&&a.l>0) --a.l; if(a.l==0) a.u=0; return a;
    }
    friend Int operator *(int x,Int a) {return a*x;}
    friend Int operator *=(Int& a,Int b) {a=a*b;return a;}
    friend Int operator *=(Int& a,int x) {a=a*x;return a;}
    friend Int operator /(Int a,Int b)
    {
        Int c,d; if(a.u==0||b.u==0||a.l<b.l) {c.read(0);return c;}
        c.l=a.l-b.l+1; for(int i=1;i<=c.l;++i) d.s[i]=0;
        if(a.u==b.u) c.u=1; else c.u=-1; a.u=b.u=d.u=1;
        for(int i=c.l;i>=1;--i)
        {
            d.s[i]=1;d.l=i;Int x=d*b;int l=0,r=9;
            while(l<r) {int z=l+r+1>>1;if(z*x<=a) l=z;else r=z-1;}
            c.s[i]=l;a-=l*x;d.s[i]=0;
        }
        while(c.s[c.l]==0&&c.l>0) --c.l; if(c.l==0) c.u=0; return c;
    }
    friend Int operator /(Int a,int x)
    {
        Int c; if(a.u==0||x==0) {c.read(0);return c;}
        c.l=a.l; if(a.u*x>0) c.u=1; else c.u=-1; int d=0;x=abs(x);
        for(int i=c.l;i>=1;--i) {c.s[i]=(d*10+a.s[i])/x;d=(d*10+a.s[i])%x;}
        while(c.s[c.l]==0&&c.l>0) --c.l; if(c.l==0) c.u=0; return c;
    }
    friend Int operator /(int x,Int a) {return a/x;}
    friend Int operator /=(Int& a,Int b) {a=a/b;return a;}
    friend Int operator /=(Int& a,int x) {a=a/x;return a;}
    friend Int operator %(Int a,Int b) {return a-(b*(a/b));}
    friend Int operator %(Int a,int x) {return a-(x*(a/x));}
    friend Int operator %(int x,Int a) {return x-(a*(x/a));}
    friend Int operator %=(Int& a,Int b) {a=a%b;return a;}
    friend Int operator %=(Int& a,int x) {a=a%x;return a;}
    friend bool operator ==(Int a,Int b)
    {
        if(a.u!=b.u) return false; if(a.l!=b.l) return false;
        for(int i=a.l;i>=1;--i) if(a.s[i]!=b.s[i]) return false;
        return true;
    }
    friend bool operator ==(Int a,int x) {Int b;b.read(x);return a==b;}
    friend bool operator ==(int x,Int a) {Int b;b.read(x);return a==b;}
    friend bool operator !=(Int a,Int b) {return !(a==b);}
    friend bool operator !=(Int a,int x) {Int b;b.read(x);return a!=b;}
    friend bool operator !=(int x,Int a) {Int b;b.read(x);return a!=b;}
    friend bool operator <(Int a,Int b)
    {
        if(a.u!=b.u) return a.u<b.u; if(a.l!=b.l) return (a.u==-1)^(a.l<b.l);
        for(int i=a.l;i>=1;--i) if(a.s[i]!=b.s[i]) return (a.u==-1)^(a.s[i]<b.s[i]);
        return false;
    }
    friend bool operator <(Int a,int x) {Int b;b.read(x);return a<b;}
    friend bool operator <(int x,Int a) {Int b;b.read(x);return b<a;}
    friend bool operator >=(Int a,Int b) {return !(a<b);}
    friend bool operator >=(Int a,int x) {Int b;b.read(x);return a>=b;}
    friend bool operator >=(int x,Int a) {Int b;b.read(x);return b>=a;}
    friend bool operator >(Int a,Int b)
    {
        if(a.u!=b.u) return a.u>b.u; if(a.l!=b.l) return (a.u==-1)^(a.l>b.l);
        for(int i=a.l;i>=1;--i) if(a.s[i]!=b.s[i]) return (a.u==-1)^(a.s[i]>b.s[i]);
        return false;
    }
    friend bool operator >(Int a,int x) {Int b;b.read(x);return a>b;}
    friend bool operator >(int x,Int a) {Int b;b.read(x);return b>a;}
    friend bool operator <=(Int a,Int b) {return !(a>b);}
    friend bool operator <=(Int a,int x) {Int b;b.read(x);return a<=b;}
    friend bool operator <=(int x,Int a) {Int b;b.read(x);return b<=a;}
    void input()
    {
        char c=getchar();
        while((c<'0'||c>'9')&&c!='-') c=getchar();
        if(c=='-') {u=-1;c=getchar();} else u=1; l=0;
        while(c>='0'&&c<='9') {s[++l]=c-'0';c=getchar();}
        for(int i=1;i<=l/2;++i) {swap(s[i],s[l-i+1]);}
        while(s[l]==0&&l>0) --l; if(l==0) u=0;
    }
    void read(int x)
    {
        if(x==0) {l=0;u=0;return;} else if(x>0) u=1; else u=-1; x=u*x;l=0;
        while(x!=0) {s[++l]=x%10;x/=10;}
    }
    void print()
    {
        if(u==0) {printf("0");return;} if(u==-1) printf("-");
        for(int i=l;i>=1;--i) printf("%d",s[i]);
    }
    friend Int abs(Int a) {a.u=1;return a;}
};
const int N=101;
int n,a[N][N];
Int f[N][N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            scanf("%d",&a[i][j]);
            if(a[i][j]==0) a[i][j]=1e9;
            f[i][j].read(0);
        }
    }
    f[1][1].read(1);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i+a[i][j]<=n) f[i+a[i][j]][j]=f[i+a[i][j]][j]+f[i][j];
            if(j+a[i][j]<=n) f[i][j+a[i][j]]=f[i][j+a[i][j]]+f[i][j];
        }
    }
    f[n][n].print();
    return 0;
}