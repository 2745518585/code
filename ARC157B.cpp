#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,k,q,w;
char a[N];
bool h[N];
struct str
{
    int l,r;
}b[N],c[N];
bool cmp(str a,str b)
{
    return a.r-a.l<b.r-b.l;
}
bool cmp2(str a,str b)
{
    return a.r-a.l>b.r-b.l;
}
void add(int x)
{
    if(k<=0||h[x]==true) return;
    if(a[x]=='X') a[x]='Y';
    else a[x]='X';
    --k;
    h[x]=true;
}
int main()
{
    scanf("%d%d%s",&n,&k,a+1);
    int x=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='Y')
        {
            if(x!=0) b[++q]=(str){x+1,i-1};
            x=i;
        }
    }
    x=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='X')
        {
            if(x!=0) c[++w]=(str){x+1,i-1};
            x=i;
        }
    }
    sort(b+1,b+q+1,cmp);
    sort(c+1,c+w+1,cmp2);
    for(int i=1;i<=q;++i)
    {
        for(int j=b[i].l;j<=b[i].r;++j) add(j);
    }
    x=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='Y')
        {
            x=i;
            break;
        }
    }
    for(int i=x-1;i>=1;--i) add(i);
    x=0;
    for(int i=n;i>=1;--i)
    {
        if(a[i]=='Y')
        {
            x=i;
            break;
        }
    }
    for(int i=x+1;i<=n;++i) add(i);
    for(int i=1;i<=n;++i)
    {
        if(h[i]==false) add(i);
        else break;
    }
    for(int i=n;i>=1;--i)
    {
        if(h[i]==false) add(i);
        else break;
    }
    for(int i=1;i<=w;++i)
    {
        for(int j=c[i].l;j<=c[i].r;++j) add(j);
    }
    // printf("%s\n",a+1);
    int s=0;
    for(int i=1;i<=n-1;++i)
    {
        if(a[i]=='Y'&&a[i+1]=='Y') ++s;
    }
    printf("%d",s);
    return 0;
}