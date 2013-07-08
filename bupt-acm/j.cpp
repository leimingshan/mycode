#include <iostream>
#include <set>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct node {
	int energy;
	double average_score;
	node() { energy = average_score = 0;}
	node(const node &s)
	{
		energy = s.energy;
		average_score = s.average_score;
	}
	bool operator < (const node &s1) const
	{
		return s1.average_score < average_score;
	}
 
};

int main()
{
	int n, m;
	std::set<node> myset;
	std::set<node>::iterator it;
	
	while(scanf("%d %d", &n, &m) != EOF)
	{
		myset.clear();
		node p;
		int score;
		for(int i = 0; i < n; i++)
		{
			scanf("%d %d", &p.energy, &score);
			p.average_score = (double)score / p.energy;
			it = myset.find(p);
			if(it != myset.end()) {
				if(p.energy < (*it).energy) {
					myset.erase(it);
					myset.insert(p);
				}
			} else
				myset.insert(p);
		}
		/*
		for (it = myset.begin(); it != myset.end(); ++it)
			cout << ' ' << (*it).energy << ' ' << (*it).average_score << endl;
		cout << '\n';
		*/
		for(int j = 0; j < m; j++)
		{
			int total_energy = 0;
			double max_score = 0;
			scanf("%d", &total_energy);
			for (it = myset.begin(); it != myset.end(); ++it)
			{
				if(total_energy >= (*it).energy) {
					max_score += (*it).average_score * (*it).energy;
					total_energy -= (*it).energy;
				}
			}
			printf("%.3f\n", max_score);
		}
	}
	return 0;
	
}