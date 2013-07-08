#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main()
{
	int T;
	cin >> T;
	int case_count = 1;
	while(T--)
	{
		int N, M;
		cin >> N >> M;
		map<string, string> keylist;
		string a, b;
		for(int i = 0; i < M; i++)
		{
			cin >> a >> b;
			keylist[a] = b;
		}
		string word, wordlist;
		vector<string> sentence;
		getline(cin, wordlist);
		getline(cin, wordlist);
		//cout<<wordlist<<endl;
		
		int start = 0;
		for(int i = 0; i < wordlist.size(); i++)
		{
			if(wordlist[i] == ' ')
			{
				word = wordlist.substr(start, i - start);
				start = i + 1;
				sentence.push_back(word);	
			}	
		}
		word = wordlist.substr(start, wordlist.size() - start);
		sentence.push_back(word);	
				
		for(int i = 1; i < N; i++)
		{
			for(int j = 0; j < sentence.size(); j++)
			{
				if(keylist.count(sentence[j]) > 0)
					sentence[j] = keylist[sentence[j]];
			}
		}
		cout << "Case #" << case_count <<':';
		case_count++;
		for(int j = 0; j < sentence.size(); j++)
			cout<<' '<<sentence[j];
		cout<<endl;
	}
    return 0;
}
