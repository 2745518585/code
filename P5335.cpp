#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=300001;
int n,tot=1,a[N][10],c[N],d[N];
char p[N];
struct str
{
    int x,s;
    str(){}
    str(int x,int s):x(x),s(s){}
    friend bool operator<(str a,str b)
    {
        return a.s<b.s;
    }
};
vector<str> b[N];
void add(char *x,int t)
{
    int q=1;
    for(int i=1;x[i];++i)
    {
        if(a[q][x[i]-'a']==0) a[q][x[i]-'a']=++tot;
        q=a[q][x[i]-'a'];
        ++c[q];
        if(c[q]>d[q])
        {
            b[q].push_back(str(t,c[q]));
            d[q]=c[q];
        }
    }
}
void del(char *x)
{
    int q=1;
    for(int i=1;x[i];++i)
    {
        if(a[q][x[i]-'a']==0) a[q][x[i]-'a']=++tot;
        q=a[q][x[i]-'a'];
        --c[q];
    }
}
int sum(char *x,int k)
{
    int q=1;
    for(int i=1;x[i];++i)
    {
        if(a[q][x[i]-'a']==0) return -1;
        q=a[q][x[i]-'a'];
    }
    if(k>d[q]) return -1;
    return (*lower_bound(b[q].begin(),b[q].end(),str(0,k))).x;
}
int main()
{
    scanf("%d",&n);
    int las=0;
    for(int i=1;i<=n;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            scanf("%s",p+1);
            add(p,i);
        }
        else if(z==2)
        {
            scanf("%s",p+1);
            del(p);
        }
        else if(z==3)
        {
            int x,y,z;
            scanf("%s%d%d%d",p+1,&x,&y,&z);
            x=((ll)x*abs(las)+y)%z;
            printf("%d\n",las=sum(p,x+1));
        }
    }
    return 0;
}