#include<iostream>
#include<vector>
using namespace std;

string init(const string &s){
    string res;
    for(auto c : s)
    {
        res.push_back('#');
        res.push_back(c);
    }

    res.push_back('#');
    return res;
}

int Manacher(const string & str){
    int n = str.size();
    vector<int>p(n,1);

    int res = 1;
    int id = -1, maxp = -1;
    for(int i = 1; i < n; ++i){
        if(i < maxp)
            p[i] = min(p[2 * id - i], maxp - i);
        else 
            p[i] = 1;
        
        while(i - p[i] >= 0 && i + p[i] < n && str[i - p[i]] == str[i + p[i]])
            p[i]++;
        if(maxp < i + p[i]){
            id = i;
            maxp = i + p[i];
        }

        res = max(res, p[i] - 1);
    }

    return res;
}

int main()
{   
    char a[] = "ababcbadabe";
    char b[] = "abacde";

   // cout << LCS(a,11,b,4);
    string s = init(string(a));
    cout << s;
    cout << Manacher(s);
    return 0;
}