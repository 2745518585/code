#include<cstdio>
#include<algorithm>
#include<cstring>
#include<deque>
using namespace std;
const int N=510001;
int n,q,b[N],c[N],S[N],T;
char a[N],d[N];
bool h[N];
deque<int> *f[N];
bool check(const deque<int> &a,const deque<int> &b)
{
    for(int i=0;i<a.size()&&i<b.size();++i)
    {
        if(a[i]!=b[i]) return a[i]<b[i];
    }
    return true;
}
void merge(int x,int y)
{
    if(f[y]==NULL) swap(f[x],f[y]);
    if(f[x]==NULL) return;
    if(check(*f[x],*f[y]))
    {
        if(f[x]->size()<f[y]->size())
        {
            while(!f[x]->empty()) f[y]->push_front(f[x]->back()),f[x]->pop_back();
        }
        else
        {
            while(!f[y]->empty()) f[x]->push_back(f[y]->front()),f[y]->pop_front();
            swap(f[y],f[x]);
        }
    }
}
int main()
{
    scanf("%s",a+1);
    n=strlen(a+1);
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='(') S[++T]=i;
        else
        {
            c[i]=S[T];
            h[c[i]]=true;
            if(T>=1) --T;
        }
    }
    int p=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='(') continue;
        int z=c[i];
        if(c[i]==0) z=p,p=i;
        f[i]=new deque<int>;
        int x=i-1;
        while(x>z)
        {
            merge(x,i);
            x=c[x]-1;
        }
        if(a[z]=='(') f[i]->push_front(0);
        if(a[i]==')') f[i]->push_back(1);
    }
    for(int i=1;i<=n;++i)
    {
        if(a[i]=='(')
        {
            if(h[i]==false) printf("(");
        }
        else
        {
            if(c[i]==0)
            {
                for(auto j:*f[i]) printf("%c",'('+j);
            }
        }
    }
    return 0;
}