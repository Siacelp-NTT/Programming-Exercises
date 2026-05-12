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
string addition(string a, string b){
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

string substraction (string a, string b){
    if (a.length()==b.length() && b[0]>a[0])swap(a,b);
    else if(b.length() > a.length()) swap(a,b);
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
    return res;
}

string multiplication(string a, string b){
    if (a.length()==b.length() && b[0]>a[0])swap(a,b);
    else if(b.length() > a.length()) swap(a,b);
    int index = a.length()+b.length()-1;
    int i = a.length()-1;
    string res(index+1,'0');
    int scale = 0;
    while(i>=0){
        int n1 = a[i--] - '0';
        int add = 0, subindex = a.length();
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
    return res;
}
/*
string division(string a, string b){

}
*/

int main(){
    /*
    ifstream infile("tests.txt");
    string s;
    while (infile >> s){
        preproc(s);
    }

    infile.close();
    return 0;
    */
    cout << multiplication("99","0") << "\n";
    cout << substraction("3123","0");
    return 0;
}