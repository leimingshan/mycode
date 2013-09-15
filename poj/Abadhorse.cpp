/* Problem
 *
 * As the leader of the Evil League of Evil, Bad Horse has a lot of problems to deal with. Most recently, there have been far too many arguments and far too much backstabbing in the League, so much so that Bad Horse has decided to split the league into two departments in order to separate troublesome members. Being the Thoroughbred of Sin, Bad Horse isn't about to spend his valuable time figuring out how to split the League members by himself. That what he's got you -- his loyal henchman -- for.
 *
 * Input
 *
 * The first line of the input gives the number of test cases, T. T test cases follow. Each test case starts with a positive integer M on a line by itself -- the number of troublesome pairs of League members. The next M lines each contain a pair of names, separated by a single space.
 *
 * Output
 *
 * For each test case, output one line containing "Case #x: y", where x is the case number (starting from 1) and y is either "Yes" or "No", depending on whether the League members mentioned in the input can be split into two groups with neither of the groups containing a troublesome pair.
 *
 * Limits
 *
 * 1 ≤ T ≤ 100.
 * Each member name will consist of only letters and the underscore character.
 * Names are case-sensitive.
 * No pair will appear more than once in the same test case.
 * Each pair will contain two distinct League members.
 *
 * Small dataset
 *
 * 1 ≤ M ≤ 10.
 *
 * Large dataset
 *
 * 1 ≤ M ≤ 10000
 */
#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int m;
        bool result = true;
        cin >> m;
        string s1, s2;

        set<string> set1;
        set<string> set2;
        set<string>::iterator it11, it12, it21, it22;

        multimap<string, string> table;
        for (int j = 0; j < m; j++) {
            cin >> s1 >> s2;
            if (s1.compare(s2) < 0)
                table.insert(make_pair(s1, s2));
            else
                table.insert(make_pair(s2, s1));

            
        }
        multimap<string,string>::iterator it = table.begin();
        set1.insert((*it).first);
        set2.insert((*it).second);
        table.erase(it++);
        while (!table.empty()) {
            //cout << (*it).first << " => " << (*it).second << '\n';

            it11 = set1.find((*it).first);
            it12 = set1.find((*it).second);
            it21 = set2.find((*it).first);
            it22 = set2.find((*it).second);

            if ((it11 != set1.end() && it12 != set1.end()) || (it21 != set2.end() && it22 != set2.end())) {
                result = false;
                break;
            }
            else if (it11 != set1.end()) {
                set2.insert((*it).second);
                table.erase(it++);
            }
            else if (it12 != set1.end()) {
                set2.insert((*it).first);
                table.erase(it++);
            }
            else if (it21 != set2.end()) {
                set1.insert((*it).second);
                table.erase(it++);
            } 
            else if (it22 != set2.end()) {
                set1.insert((*it).first);
                table.erase(it++);
            }
            else 
                it++;
            
            if (it == table.end())
                it = table.begin();

        }

        cout << "Case #" << i+1 << ": ";
        if (result)
            cout << "Yes";
        else 
            cout << "No";
        cout << endl;
    }

    return 0;
}
