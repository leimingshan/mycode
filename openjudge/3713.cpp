#include <iostream>
#include <map>
#include <cstring>

struct StringInt {
	char *str;
	int num;
};

StringInt si[] = {
	{"negative", -1 }, 
	{"zero" 0},
	one, two, three, four, five, six, seven, eight,
nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen,
seventeen, eighteen, nineteen, twenty, thirty, forty, fifty, sixty,
seventy, eighty, ninety, hundred, thousand, million
}

using namespace std;

map<string, int> mapsi;


int main()
{
	int si_size = sizeof(si) / sizeof(*si);
	for (int i = 0; i < si_size; i++)
		mapsi[si[i].str] = si[i].num;
	
	return 0;	
}