#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void preproc(string &s){
    for(int i = 0; i <= s.length(); i++){
        if(s[i] == ' ') s.erase(i, 1);
    }
}
void swap(string &a, string &b){
    string t = a;
    a = b; 
    b = t;
    return;
}
bool cmp(string a, string b){
    if(a.length()>b.length())return 1;
    if(a.length()<b.length())return 0;
    return a>=b;
}
string addition(string a, string b){
    if(a=="error"||b=="error")return "error";
    int index = (a.length() > b.length()) ? a.length():b.length();
    int i = a.length()-1, j = b.length()-1;
    string res(index+1,'0');
    int add = 0;
    while (i >= 0 && j >= 0){
        int n1 = a[i--] - '0';
        int n2 = b[j--] - '0';
        if(n1 + n2 + add >= 10){
            res[index--] = (n1 + n2 + add)% 10 + '0';
            add = 1;
        }
        else{
            res[index--] = (n1 + n2 + add) + '0';
            add = 0;
        }
    }
    while(i >=0){
        int n1 = a[i--] - '0';
        if(n1 + add >= 10){
            res[index--] = (n1 + add)% 10 + '0';
            add = 1;
        }
        else{
            res[index--] = (n1 + add) + '0';
            add = 0;
        }
    }
    while(j >=0){
        int n1 = b[j--] - '0';
        if(n1 + add >= 10){
            res[index--] = (n1 + add)% 10 + '0';
            add = 1;
        }
        else{
            res[index--] = (n1 + add) + '0';
            add = 0;
        }
    }
    if(add)res[0] = add + '0';
    else res.erase(0, 1);
    return res;
}
string subtraction (string a, string b){
    if(a=="error"||b=="error")return "error";
    bool sign = 0;
    if (!cmp(a,b)){swap(a,b);sign =1;}
    else if(b.length() > a.length()){swap(a,b);sign =1;}
    int index = a.length()-1;
    int i = a.length()-1, j = b.length()-1;
    string res(index + 1 ,'0');
    int add = 0;
    while (j >= 0){
        int n1 = a[i--] - '0';
        int n2 = b[j--] - '0';
        if(n1 - n2 - add < 0){
            res[index--] = n1+10 - n2 - add + '0';
            add = 1;
        }
        else{
            res[index--] = n1 - n2 - add + '0';
            add = 0;
        }
    }
    while(i >=0){
        int n1 = a[i--] - '0';
        if(n1 - add < 0){
            res[index--] = n1+10 - add + '0';
            add = 1;
        }
        else{
            res[index--] = n1 - add + '0';
            add = 0;
        }
    }
    while(res[0]=='0') res.erase(0,1);
    if(res.empty()) return "0";
    if(sign)return '-' + res;
    return res;
}
string multiplication(string a, string b){
    if(a=="error"||b=="error")return "error";
    bool asign = (a[0] == '-'), bsign = (b[0] =='-');
    bool sign = (asign != bsign);
    if(asign) a.erase(0,1);
    if(bsign) b.erase(0,1);

    if (a.length()==b.length() && b[0]>a[0])swap(a,b);
    else if(b.length() > a.length()) swap(a,b);
    int index = a.length()+b.length()-1;
    int i = a.length()-1;
    string res(index+1,'0');
    int scale = 0;
    while(i>=0){
        int n1 = a[i--] - '0';
        int add = 0, subindex = b.length();
        string subres(subindex+1,'0');
        for(int j = b.length()-1; j>=0;j--){
            int n2 = b[j] - '0';
            int ans = (n1*n2) + add;
            subres[subindex--]= ans % 10 + '0';
            add = ans / 10;
        }
        if(add != 0)subres[0] = add + '0';
        else subres.erase(0,1);
        res = addition(res, subres + string(scale,'0'));
        scale++;
    }
    while(res[0]=='0') res.erase(0,1);
    if(res.empty()) res = string(1,'0');
    if(sign) res = '-' + res;
    return res;
}

string division(string a, string b){
    if(a=="error"||b=="error")return "error";
    bool asign = (a[0] == '-'), bsign = (b[0] =='-');
    bool sign = (asign != bsign);
    if(asign) a.erase(0,1);
    if(bsign) b.erase(0,1);
    if (b == "0") return "error";
    else if (!cmp(a,b)) return "0";
    int index = 0;
    string res(0,'0'), subres(0,'0');
    for(char c:a){
        if(subres=="0") subres = string(0,'0');
        subres += c;
        if(!cmp(subres,b)){
            if(res.length()>0)res+= '0';
            continue;
        }
        for(int i = 9; i>=0;i--){
            string mult = multiplication(b, to_string(i));
            if(cmp(subres, mult)){
                subres = subtraction(subres, mult);
                res += i + '0';
                break;
            }
        }

    }
    if(sign)res = '-' +res;
    return res;
}

string btier(string &s, int &index);
string htier(string &s, int &index);
string ltier(string &s, int &index);
string numproc(string &s, int &index){
    string res;
    while((s[index] >= '0' && s[index] <= '9')){
        res+=s[index++];
    }
    return res;
}
bool isValid(string &s, int i){
    if(i>s.length()) return 0;
    return(s[i] >= '0' && s[i] <='9')|| s[i] =='(';
}
string btier(string &s, int &index){
    bool sign = 0;
    if ( index <s.length()&&s[index] == '-'){ sign =1;index++;}
    string res(0,'0');
    if(index <s.length()&& s[index] == '('){
        index++;
        res = ltier(s,index);
        if(index<s.length()&& s[index] ==')') index++;
    }
    else{
        res = numproc(s,index);
    }
    if(res=="0")return "0";
    if(res =="")return "error";
    if(res[0]=='-'&&sign){res.erase(0,1);return res;}
    else if(sign) return '-' +res;
    return res;
}
string htier(string &s, int &index){
    string A = btier(s, index);
    while(index<s.length() && (s[index] == '*' || s[index] == '/')){
        char type = s[index++];
        string B = btier(s,index);
        if(B=="error")return"error";
        if(type == '*') A= multiplication(A,B);
        else A= division(A,B);
    }
    return A;
}
string ltier(string &s, int &index){
    string A = htier(s, index);
    while(index<s.length() && (s[index]=='+' || s[index]=='-')){
        char type = s[index++];
        string B=htier(s,index);
        if(B=="error")return"error";
        if(type == '+'){
            if(A[0]!='-' && B[0]!='-')A= addition(A,B);
            else if(A[0]=='-' && B[0]=='-'){
                A.erase(0,1);B.erase(0,1);
                A= '-' + addition(A,B);
            }
            else if(A[0]=='-' && B[0]!= '-'){
                A.erase(0,1);
                A= subtraction(B,A);
            }
            else{
                B.erase(0,1);
                A= subtraction(A,B);
            }
        }
        else{
            if(A[0]!='-' && B[0]!='-')A= subtraction(A,B);
            else if(A[0]=='-' && B[0]=='-'){
                A.erase(0,1);B.erase(0,1);
                A= subtraction(B,A);
            }
            else if(A[0]=='-' && B[0]!= '-'){
                A.erase(0,1);
                A = '-'+addition(A,B);
            }
            else{
                B.erase(0,1);
                A = addition(A,B);
            }
        }
    }
    return A;
}

int main(int argc, char* argv[]){
    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);
    string s;
    while ( getline(infile, s)){
        preproc(s);
        int i =0;
        string res = ltier(s,i);
        cout << res <<"\n";
        outfile << res<<"\n";
    }

    infile.close();
    outfile.close();
    
    return 0;
}