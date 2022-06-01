#include<iostream>
#include<string>
using namespace std;


void cell1tocell2(const string & str){

    int n = str.size();
    int r = 0, c = 0;   

    int i,j;
    for(i = 1 ; i < n; ++i){
        if(str[i] >= '0' && str[i] <= '9')
            r = r * 10 + (str[i] - '0');
        else
            break;
    }

    for(j = i + 1; j < n; ++j){
        if(str[j] >= '0' && str[j] <= '9')
            c = c * 10 + (str[j] - '0');
        else{
            break;
        }
    }

    string col;
    while(c>0){
        c -= 1;
        col.push_back((char)(c%26 + 'A'));
        c /= 26;
    }
    
    //for(i = col.size() -1; i >=0; --i) cout << col[i];
    reverse(col.begin(),col.end()), cout << col;
    cout << r << endl;
}

void cell2tocell1(const string & str){
    int n = str.size();
    int r = 0, c = 0;   

    int i;
    for(i = 0 ; i < n; ++i){
        if(str[i] >= '0' && str[i] <= '9')
            r = r * 10 + (str[i] - '0');
        else
            c = c * 26 + (str[i] - 'A') + 1;
    }

    cout << 'R';
    cout << r;
    cout << 'C';
    cout << c << endl;
}

int main(){
    int n;
    cin >> n;

    while(n--){
        string str;
        cin >> str;
        bool iscell1 = false;

        for(int i = str.size()-1; i >= 0; --i){
            if(isalpha(str[i]) && i > 0 && isdigit(str[i-1]))
            {
                iscell1 = true;
                break; 
            }
        }

        if(iscell1)
            cell1tocell2(str);
        else
            cell2tocell1(str);


    }
    return 0;
}
