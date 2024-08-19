#include <iostream>
#include<bits/stdc++.h>
using namespace std;


class Integer{
    public:
    vector<int> n;
    Integer(){
        
    }
    //Initializing with a string
    Integer(string m){
        //can be positive or negative string
        if(m[0]=='-'){
            //negative number
            for(int i=1;i<m.length();i++){
                n.push_back(m[i]-'0');
            }
            //at last make first dig -ve
            n[0]*=-1;
        }else{
            //positive number
            for(int i=0;i<m.length();i++){
                n.push_back(m[i]-'0');
            }
        }
    }
    Integer operator+(Integer& m){
        //we have to consider 4 cases in total
        if(n[0]>0 && m.n[0]<0){
            //i.e the case of n-m: tackel in the subtract function 
            m.n[0]*=-1;
            Integer res=(*this)-m;
            m.n[0]*=-1;
            return res;
        }else if(n[0]<0 && m.n[0]>0){
            //i.e the case of m-n: tackle in the subtract function
            n[0]*=-1;
            Integer res=m-(*this);
            n[0]*=-1;
            return res;
        }else if(n[0]<0 && m.n[0]<0){
            //convert both to positive then add and then attach a negative sign -(m+n)
            n[0]*=-1;
            m.n[0]*=-1;
            Integer result=*this + m;
            //multiply the result with -1
            result.n[0]*=-1;
            //make the numbers as it is
            n[0]*=-1;
            m.n[0]*=-1;
            return result;
        }else{
            //main logic goes here
        int s1=n.size();
        int s2=m.n.size();
        reverse(n.begin(),n.end());
        reverse(m.n.begin(),m.n.end());
        int less=min(s1,s2);
        int carry=0;
        Integer res;
        int i;
        for(i=0;i<less;i++){
            int add=n[i]+m.n[i]+carry;
            res.n.push_back(add%10);
            carry=add/10;
        }
        while(i<s1){
            int add=n[i]+carry;
            res.n.push_back(add%10);
            carry=add/10;
            i++;
        }
        while(i<s2){
            int add=m.n[i]+carry;
            res.n.push_back(add%10);
            carry=add/10;
            i++;
        }
        while(carry!=0){
        res.n.push_back(carry%10);
        carry=carry/10;
        }
        reverse(n.begin(),n.end());
        reverse(m.n.begin(),m.n.end());
        reverse(res.n.begin(),res.n.end());
        return res;
        }
        Integer res;
        return res;
    }
    
    Integer operator-(Integer& m){
        //check all the cases
        if(n[0]>0 && m.n[0]<0){
            //i.e it is the case of m+n
            //make positive send and then reverse the wrong doing
            m.n[0]*=-1;
            Integer res=(*this)+m;
            m.n[0]*=-1;
            return res;
        }else if(n[0]<0 && m.n[0]>0){
            //i.e the case of -n-m .ie -(n+m)
            n[0]*=-1;
            Integer res=(*this)+m;
            n[0]*=-1;
            res.n[0]*=-1;
            return res;
        }else if(n[0]<0 && m.n[0]<0){
            //both the number are negative: -n+m::-(n-m)
            //make m positive and send and then attach a negative sign
            m.n[0]*=-1;
            Integer res=*this-m;
            m.n[0]*=-1;
            res.n[0]*=-1;
            return res;
        }else{
            //both positive wala case
            //I will subtract smaller from bigger
            if(*this>=m){
                return helper(*this,m);
            }else{
                Integer res=  helper(m,*this);
                res.n[0]*=-1;
                return res;
            }
        }
        Integer res;
        return res;
    }
    Integer helper(Integer& num, Integer &m){
        //consider that n is greater than m
       reverse(num.n.begin(),num.n.end());
        reverse(m.n.begin(),m.n.end());
        int size1=m.n.size();
        //run a for loop and ensure that first element is greater
        int i;
        Integer res;
        for(i=0;i<size1;i++){
            //2 things can happen
            if(num.n[i]<m.n[i]){
                //we need to borrow
                num.n[i+1]--;//borrow success full
                res.n.push_back(10+num.n[i]-m.n[i]);
            }else{
                res.n.push_back(num.n[i]-m.n[i]);
            }
        }
        while(i<num.n.size()){
                //copy the remainig part as it was
                if(num.n[i]<0){
                    num.n[i+1]--;
                    res.n.push_back(10+num.n[i]);
                }else{
                    res.n.push_back(num.n[i]);
                }
            i++;
            }
        reverse(num.n.begin(),num.n.end());
        reverse(m.n.begin(),m.n.end());
        reverse(res.n.begin(),res.n.end());
        //remove the zeros at the beginning
        remove_zeros(res);
        return res;    
    }
    Integer& operator+=(Integer& m){
        Integer res=*this+m;
        n.clear();
        for(int i=0;i<res.n.size();i++){
            n.push_back(res.n[i]);
        }
        return *this;
    }
    Integer& operator-=(Integer& m){
        Integer res=*this-m;
        n.clear();
        for(int i=0;i<res.n.size();i++){
            n.push_back(res.n[i]);
        }
        return *this;
    }
    //code for multiplication 
    Integer operator*(Integer& m){
        int flag1=(n[0]<0)?-1:1;
        int flag2=(m.n[0]<0)?-1:1;
        int flag=flag1*flag2;
        if(flag1==-1){
            n[0]*=-1;    
        }
        if(flag2==-1){
            m.n[0]*=-1;    
        }
        
        //flag contains the sign of the result
        string zero="0";
        Integer z(zero);
        Integer curr(zero);
        Integer ans(zero);
        if((*this)==z || m==z){
            return z;
        }
        //corner case checked
        int carry=0;
        reverse(n.begin(),n.end());
        reverse(m.n.begin(),m.n.end());
        //we will multiply n with num
        int s1=n.size();
        int s2=m.n.size();
        for(int i=0;i<s2;i++){
            curr.n.clear();
            for(int j=0;j<s1;j++){
                int mul=(n[j]*m.n[i])+carry;
                carry=mul/10;
                curr.n.push_back(mul%10);
            }
            while(carry!=0){
                curr.n.push_back(carry%10);
                carry=carry/10;
            }
            //add trailing zeros
            reverse(curr.n.begin(),curr.n.end());
            for(int j=0;j<i;j++){
                curr.n.push_back(0);
            }
            ans+=curr;
        }
        //reverse(ans.num.begin(),ans.num.end());
        ans.n[0]*=flag;
        if(flag1==-1){
            n[0]*=-1;    
        }
        if(flag2==-1){
            m.n[0]*=-1;    
        }
        reverse(n.begin(),n.end());
        reverse(m.n.begin(),m.n.end());
        return ans;
    }
    Integer& operator*=(Integer& m){
        Integer res=(*this)*m;
        n.clear();
        for(int i=0;i<res.n.size();i++){
            n.push_back(res.n[i]);
        }
        return *this;
    }
    
    bool operator<(Integer& m){
        //eliminate based on the sign
        if(n[0]<0 && m.n[0]>=0){
            return true;
        }else if(n[0]>=0 && m.n[0]<0){
            return false;
        }
        //i.e the sign of both numbers is same
        if(n[0]>=0 && m.n[0]>=0){
            //both numbers are positive compare the size
            if(n.size()<m.n.size()){
                return true;
            }else if(n.size()>m.n.size()){
                return false;
            }else{
                //both numbers are same in size
                for(int i=0;i<n.size();i++){
                    if(n[i]<m.n[i]){
                        return true;
                    }else if(n[i]>m.n[i]){
                        return false;
                    }else{
                        //both characters are equal
                        continue;
                    }
                }
                return false;
            }
        }else if(n[0]<0 && m.n[0]<0){
            //both numbers are negative
            if(n.size()>m.n.size()){
                return false;
            }else if(n.size()<m.n.size()){
                return true;
            }else{
                //both are same in size
                for(int i=0;i<n.size();i++){
                    if(n[i]<m.n[i]){
                        return false;
                    }else if(n[i]>m.n[i]){
                        return true;
                    }else{
                        //both characters are equal
                        continue;
                    }
                }
            }
        }
        return false;
    }
    bool operator==(Integer& m){
        if(n.size()!=m.n.size()){
            return false;
        }
        for(int i=0;i<n.size();i++){
            if(n[i]!=m.n[i]){
                return false;
            }
        }
        return true;
    }
    bool operator!=(Integer& m){
        return !(*this==m);
    }
    bool operator<=(Integer& m){
        if(*this<m || *this==m){
            return true;
        }else{
            return false;
        }
    }
    bool operator>(Integer& m){
        return !(*this<=m);
    }
    bool operator>=(Integer& m){
        if(*this>m || *this==m){
            return true;
        }else{
            return false;
        }
    }
    
    
    Integer operator/(Integer& m){
        //I will follow the length logic
        //we have to execute n/m
        int flag1=(n[0]<0)?-1:1;
        int flag2=(m.n[0]<0)?-1:1;
        int flag=flag1*flag2;
        if(flag1==-1){
            n[0]*=-1;    
        }
        if(flag2==-1){
            m.n[0]*=-1;    
        }
        //we have made both of them positive
        if(*this<m){
            Integer res("0");
            return res;
        }
        
        int i=0;
        Integer quotient;
        //generate using numbers of this
        Integer remainder;
        string zero="0";
        Integer z(zero);
        Integer divident(zero);
        
        while(i<n.size()){
            int count=0;
            
            while(divident<m && i<n.size()){
                if(divident==z){
                    divident.n.clear();
                }
                divident.n.push_back(n[i]);
                i++;
                count++;
            }
            //insert count-1 zeros in the quotient
            
            while(count>1){
                quotient.n.push_back(0);
                count--;
            }
            //trying to divide and lets see what is quotient and remainder
            //divident.print();
            int f=0;
            for(int j=9;j>=0;j--){
                //multiply and see
                Integer num;
                num.n.push_back(j);
                Integer mul=num*m;
                //m.print();
                //num.print();
                //mul.print();
                if(mul<=divident){
                    //cout<<"hi";
                    //divident.print();
                    //mul.print();
                    //cout<<j<<endl;
                    quotient.n.push_back(j);
                    f=1;
                    divident-=mul;
                    break;
                }
                
            }
            if(f==0){
                //unable to find quotient
                //nothing more to add
                break;
            }
        }
        //divident.print();
        // if(divident>z){
        //     quotient.n.push_back(0);
        // }
        
        
        if(flag1==-1){
            n[0]*=-1;    
        }
        if(flag2==-1){
            m.n[0]*=-1;    
        }
        remove_zeros(quotient);
        quotient.n[0]*=flag;
        return quotient;
    }
    
    Integer& operator/=(Integer& m){
        Integer res=(*this)/m;
        n.clear();
        for(int i=0;i<res.n.size();i++){
            n.push_back(res.n[i]);
        }
        return *this;
    }
    
    Integer operator%(Integer& m){
        //I will follow the length logic
        //we have to execute n/m
        int flag1=(n[0]<0)?-1:1;
        int flag2=(m.n[0]<0)?-1:1;
        int flag=flag1*flag2;
        if(flag1==-1){
            n[0]*=-1;    
        }
        if(flag2==-1){
            m.n[0]*=-1;    
        }
        //we have made both of them positive
        if(*this<m){
            Integer res("0");
            return res;
        }
        
        int i=0;
        Integer quotient;
        //generate using numbers of this
        Integer remainder;
        string zero="0";
        Integer z(zero);
        Integer divident(zero);
        
        while(i<n.size()){
            int count=0;
            
            while(divident<m && i<n.size()){
                if(divident==z){
                    divident.n.clear();
                }
                divident.n.push_back(n[i]);
                i++;
                count++;
            }
            //insert count-1 zeros in the quotient
            
            while(count>1){
                quotient.n.push_back(0);
                count--;
            }
            //trying to divide and lets see what is quotient and remainder
            //divident.print();
            int f=0;
            for(int j=9;j>=0;j--){
                //multiply and see
                Integer num;
                num.n.push_back(j);
                Integer mul=num*m;
                //m.print();
                //num.print();
                //mul.print();
                if(mul<=divident){
                    //cout<<"hi";
                    //divident.print();
                    //mul.print();
                    //cout<<j<<endl;
                    quotient.n.push_back(j);
                    f=1;
                    divident-=mul;
                    break;
                }
                
            }
            if(f==0){
                //unable to find quotient
                //nothing more to add
                break;
            }
        }
        //divident.print();
        // if(divident>z){
        //     quotient.n.push_back(0);
        // }
        
        
        if(flag1==-1){
            n[0]*=-1;    
        }
        if(flag2==-1){
            m.n[0]*=-1;    
        }
        remove_zeros(divident);
        if(flag1==1 && flag2==1){
            //no operation    
        }else if(flag1==-1 && flag2==-1){
            divident.n[0]*=-1;
        }else if(flag1==1 && flag2==-1){
            //no operation
        }else{
            divident.n[0]*=-1;
        }
        return divident;
    }
    Integer operator%=(Integer& m){
        Integer res=(*this)%m;
        n.clear();
        for(int i=0;i<res.n.size();i++){
            n.push_back(res.n[i]);
        }
        return *this;
    }
    
    
    void remove_zeros(Integer& m){
        int i=0;
        Integer temp;
        for(int i=0;i<m.n.size();i++){
            temp.n.push_back(m.n[i]);
        }
        while(m.n[i]==0 && i<(m.n.size())){
            i++;
        }
        string zero="0";
        if(i>=m.n.size()){
             m.n.clear();
            //i.e there were all zeros in it
            m.n.push_back(0);
        }else{
             m.n.clear();
            while(i<temp.n.size()){
                m.n.push_back(temp.n[i]);
                i++;
            }
        }
    }
    
    void print(){
        
        for(int i=0;i<n.size();i++){
            cout<<n[i];
        }
        cout<<endl;
    }
};



int main() {
    // Integer one("55");
    // Integer two("4");
    // one.print();
    // two.print();
    // //cout<<(one<two);
    // Integer res=one/two;
    // //one*=two;
    // res.print();
    
    
    while(true){
        string op;
        string one;
        string two;
        cin>>op;
        cin>>one;
        cin>>two;
        Integer a(one);
        Integer b(two);
        
        if(op=="end"){
            return 0;
        }else if(op=="+"){
            Integer res= a+b;
            res.print();
        }else if(op=="-"){
            Integer res=a-b;
            res.print();
        }else if(op=="*"){
            Integer res=a*b;
            res.print();
        }else if(op=="+="){
            a+=b;
            a.print();
        }else if(op=="-="){
            a-=b;
            a.print();
        }else if(op=="*="){
            a*=b;
            a.print();
        }else if(op=="=="){
            bool res=(a==b);
            if(res){
                cout<<"true"<<endl;    
            }else{
                cout<<"false"<<endl;
            } 
        }else if(op=="!="){
            bool res=(a!=b);
            if(res){
                cout<<"true"<<endl;    
            }else{
                cout<<"false"<<endl;
            } 
        }else if(op=="<"){
            bool res=(a<b);
            if(res){
                cout<<"true"<<endl;    
            }else{
                cout<<"false"<<endl;
            } 
        }else if(op=="<="){
            bool res=(a<=b);
            if(res){
                cout<<"true"<<endl;    
            }else{
                cout<<"false"<<endl;
            } 
        }else if(op==">"){
            bool res=(a>b);
            if(res){
                cout<<"true"<<endl;    
            }else{
                cout<<"false"<<endl;
            } 
        }else if(op==">="){
            bool res=(a>=b);
            if(res){
                cout<<"true"<<endl;    
            }else{
                cout<<"false"<<endl;
            } 
        }else if(op=="/"){
            Integer res=a/b;
            res.print();
        }else if(op=="/="){
            a/=b;
            a.print();
        }else if(op=="%"){
            Integer res=a%b;
            res.print();
        }
        else if(op=="%="){
            a%=b;
            a.print();
        }
    }
    return 0;
}