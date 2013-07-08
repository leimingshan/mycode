#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int i, pos;
    string str;
    int k1, k2, k3;
    char re[81];
    vector<int> n1, n2, n3;
    
    while(true)
    {
        cin >> k1 >> k2 >> k3;
        if(k1 == 0 && k2 == 0 && k3 == 0)
            break;
        
        cin >> str;

        n1.clear();
        n2.clear();
        n3.clear();

        for(i = 0; i < str.length(); i++)
        {
            if (str[i] >= 'a' && str[i] <= 'i') 
                n1.push_back(i);
            else if (str[i] >= 'j' && str[i] <= 'r') 
                n2.push_back(i);
            else 
                n3.push_back(i);
        }

        for(i = 0; i < n1.size(); i++)
        {
            pos = (i+k1) % n1.size();
            re[n1[pos]] = str[n1[i]];
        }
        for(i = 0; i < n2.size(); i++)
        {
            pos = (i+k2) % n2.size();
            re[n2[pos]] = str[n2[i]];
        }
        for(i = 0; i < n3.size(); i++)
        {
            pos = (i+k3) % n3.size();
            re[n3[pos]] = str[n3[i]];
        }
        re[str.length()] = 0;
        cout<<re<<endl;
    }
    return 0;
}
