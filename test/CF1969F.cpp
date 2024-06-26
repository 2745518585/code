#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
const int N=2001;
int n,m,a[N],f[N];
set<int> Set;
set<pair<int,int>> Set2;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=0;i<=n;++i) f[i]=1e9;
    int x=0;
    while(x<n&&(Set.size()<m||x<m)) 
    {
        ++x;
        if(Set.count(a[x])) Set.erase(a[x]);
        else Set.insert(a[x]);
    }
    if(x==n)
    {
        printf("%d",n/2-(int)Set.size()/2);
        return 0;
    }
    int s=0;
    f[x]=1;
    for(int i=0;i<=n;i+=2)
    {
        Set.clear();
        Set2.clear();
        for(int j=i+2;j<=n;j+=2)
        {
            if(Set.count(a[j-1])) Set.erase(a[j-1]);
            else Set.insert(a[j-1]);
            if(Set.count(a[j])) Set.erase(a[j]);
            else Set.insert(a[j]);
            if(Set.size()==2)
            {
                int x1=*Set.begin(),x2=*next(Set.begin());
                if(Set2.count(make_pair(min(x1,x2),max(x1,x2)))) continue;
                Set2.insert(make_pair(min(x1,x2),max(x1,x2)));
                f[j]=min(f[j],f[i]+1);
            }
        }
        int u=[](){
            int w1=0,w2=0;
            for(auto i:Set2)
            {
                if((!Set.count(i.first))&&(!Set.count(i.second))) ++w1;
                if((!Set.count(i.first))||(!Set.count(i.second))) ++w2;
            }
            int q=m-Set.size();
            if(w1<q*(q-1)/2) return q-2;
            if(w2<q*(m-1)-q*(q-1)/2) return q;
            if(Set2.size()<m*(m-1)/2) return q+2;
            return (int)1e9;
        }();
        s=max(s,n/2-(f[i]+u/2));
    }
    printf("%d",s);
    return 0;
}