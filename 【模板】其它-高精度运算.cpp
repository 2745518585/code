#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
template<int he=10> class Int
{
  public:
    int *s=NULL,zero=0,len=0,sign=0;
    Int() {}
    Int(long long num)
    {
        if(s!=NULL) delete[] s,s=NULL;
        if(num==0) {len=sign=0;return;}
        if(num>0) sign=1;
        else sign=-1,num=-num;
        auto tmp=num;len=0;
        while(tmp) ++len,tmp/=he;
        s=new int[len];tmp=num;
        for(int i=0;i<=len-1;++i) {s[i]=tmp%he;tmp/=he;}
    }
    Int(std::string str)
    {
        if(s!=NULL) delete[] s,s=NULL;
        if(str[0]=='-') sign=-1,str=str.substr(1);
        else sign=1;
        len=str.size();
        s=new int[len];
        for(int i=0;i<=len-1;++i) s[i]=str[len-i-1]-'0';
    }
    Int(const Int& a)
    {
        if(this!=&a)
        {
            delete[] s,s=NULL;
            len=a.len,sign=a.sign;
            s=new int[len];
            for(int i=0;i<=len-1;++i) s[i]=a[i];
        }
    }
    ~Int()
    {
        if(s!=NULL) delete[] s,s=NULL;
    }
    Int& operator=(const Int& a)
    {
        if(this!=&a)
        {
            delete[] s,s=NULL;
            len=a.len,sign=a.sign;
            s=new int[len];
            for(int i=0;i<=len-1;++i) s[i]=a[i];
        }
        return *this;
    }
    operator std::string() const
    {
        std::string str;
        if(sign==1) str="";
        else str="-";
        bool u=false;
        for(int i=len-1;i>=0;--i)
        {
            if(s[i]) u=true;
            if(u) str+=s[i]+'0';
        }
        if(u==false) return "0";
        return str;
    }
    int &operator[](const int pos) {if(pos>=0&&pos<=len-1) return s[pos]; return zero=0;}
    int operator[](const int pos) const {if(pos>=0&&pos<=len-1) return s[pos]; return 0;}
    friend std::istream &operator>>(std::istream &stream,Int &a)
    {
        std::string str;
        stream>>str;
        a=str;
        return stream;
    }
    friend std::ostream &operator<<(std::ostream &stream,const Int a)
    {
        stream<<(std::string)a;
        return stream;
    }
    void resize(int _len)
    {
        delete[] s,s=NULL;
        len=_len;
        s=new int[len];
        for(int i=0;i<=len-1;++i) s[i]=0;
    }
    void update()
    {
        for(int i=0;i<=len-1;++i)
        {
            s[i+1]+=(s[i]-(s[i]%he+he)%he)/he;
            s[i]=(s[i]%he+he)%he;
        }
        while(len>0&&s[len-1]==0) --len;
    }
    friend Int operator+(const Int &a,const Int &b)
    {
        Int c;c.resize(std::max(a.len,b.len)+1),c.sign=1;
        for(int i=0;i<=std::max(a.len,b.len)-1;++i)
        {
            c[i]+=a[i]*a.sign+b[i]*b.sign;
            c[i+1]+=(c[i]-(c[i]%he+he)%he)/he;
            c[i]=(c[i]%he+he)%he;
        }
        if(c[c.len-1]<0)
        {
            c.sign=-1;
            for(int i=0;i<=c.len-1;++i) c[i]=-c[i];
            for(int i=0;i<=c.len-1;++i)
            {
                c[i+1]+=(c[i]-(c[i]%he+he)%he)/he;
                c[i]=(c[i]%he+he)%he;
            }
        }
        c.update();
        return c;
    }
    friend Int operator+=(Int &a,const Int &b) {return a=a+b;}
    friend Int operator-(const Int &a)
    {
        Int b=a;
        b.sign=-b.sign;
        return b;
    }
    friend Int operator-(const Int &a,const Int &b) {return a+(-b);}
    friend Int operator-=(Int &a,const Int &b) {return a=a-b;}
    friend Int operator*(const Int &a,const Int &b)
    {
        Int c;c.resize(a.len+b.len),c.sign=a.sign*b.sign;
        for(int i=0;i<=a.len-1;++i)
        {
            for(int j=0;j<=b.len-1;++j)
            {
                c[i+j]+=a[i]*b[j];
            }
        }
        c.update();
        return c;
    }
    friend Int operator*=(Int &a,const Int &b) {return a=a*b;}
};
using namespace std;
int main()
{
    Int a,b;
    cin>>a>>b;
    cout<<a+b;
    return 0;
}