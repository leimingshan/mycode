#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	int s[40] = {0};
	int p[20] = {0};
	int w[20] = {0};
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		int s_i = 0;
		for(int i = 0; i < n; i++)
			cin >> p[i];
		for(s_i = 0; s_i < p[0]; s_i++)
			s[s_i] = -1;
		s[s_i++] = 1;
		for(int j = 1; j < n; j++) {
			for(int i = 0; i < (p[j]-p[j-1]); i++)
				s[s_i++] = -1;
			s[s_i++] = 1;
		}
		/*
		for(int i = 0; i < 2*n; i++)
			if(s[i] == -1)
				cout<<'(';
			else
				cout<<')';
		cout<<endl;
		*/
		int w_i = n-1;
		for(int i = 2*n-1; i >= 0; i--)
		{
			int j;
			if(s[i] == 1)
			{
				int t = 1;
				for(j = i-1; t>0; j--)
					t+=s[j];
				w[w_i--] = (i-j+1)/2;
			}
		}
		cout<<w[0];
		for(int i=1;i<n;i++) 
			cout<<' '<<w[i];
		cout<<endl;
	}

    return 0;
}
