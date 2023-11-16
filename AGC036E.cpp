#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1000001;
int n;
char b[N],g[N];
struct str
{
    char x;
    int q;
    str() {}
    str(char x,int q):x(x),q(q) {}
}a[N];
struct str2
{
    char x;
    int s;
}h[N];
bool cmp(str2 a,str2 b)
{
    return a.s<b.s;
}
void print()
{
    int x=0;
    while(x<=n)
    {
        if(a[x].x>='A'&&a[x].x<='C') printf("%c",a[x].x);
        x=a[x].q;
    }
    printf("\n");
}
int main()
{
    scanf("%s",b+1);
    n=strlen(b+1);
    a[0]=str(0,1);
    for(int i=1;i<=n;++i) a[i]=str(b[i],i+1);
    a[n+1]=str(1,n+1);
    int x=0;
    while(x<=n)
    {
        while(a[a[x].q].x==a[x].x) a[x].q=a[a[x].q].q;
        if(a[x].x>='A'&&a[x].x<='C') ++h[a[x].x-'A'+1].s;
        x=a[x].q;
    }
    h[1].x='A',h[2].x='B',h[3].x='C';
    sort(h+1,h+3+1,cmp);
    x=0;
    while(x<=n)
    {
        while(h[3].s>h[2].s&&a[a[x].q].x==h[3].x&&a[x].x!=a[a[a[x].q].q].x) a[x].q=a[a[x].q].q,--h[3].s;
        x=a[x].q;
    }
    x=0;
    while(x<=n)
    {
        while(h[3].s>h[2].s&&((a[a[x].q].x==h[3].x&&a[a[a[x].q].q].x==h[1].x)||(a[a[x].q].x==h[1].x&&a[a[a[x].q].q].x==h[3].x))&&a[x].x!=a[a[a[a[x].q].q].q].x) a[x].q=a[a[a[x].q].q].q,--h[3].s,--h[1].s;
        x=a[x].q;
    }
    x=0;
    while(x<=n)
    {
        while(h[3].s>h[1].s&&((a[a[x].q].x==h[3].x&&a[a[a[x].q].q].x==h[2].x)||(a[a[x].q].x==h[2].x&&a[a[a[x].q].q].x==h[3].x))&&a[x].x!=a[a[a[a[x].q].q].q].x) a[x].q=a[a[a[x].q].q].q,--h[3].s,--h[2].s;
        x=a[x].q;
    }
    print();
    return 0;
}