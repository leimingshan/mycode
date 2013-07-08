#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct longfloat {
	longfloat()
	{
		num = vector<short>(0);
		point = 0;
	}
	longfloat(int n)
	{
		num = vector<short>(n, 0);
		point = 0;
	}
	vector<short> num;
	int point;
};

istream& operator>>(istream& sin, longfloat& r)
{
	string s;
	sin >> s;
	if (s.find(".", 0) == string::npos)
		r.point = 0;
	else
		r.point = s.size() - 1 - s.find(".", 0);
	r.num = vector<short>(0);
	
	for (int i = s.size() - 1; i >= 0; i--) {
		if (s[i] != '.')
			r.num.push_back(s[i] - '0');
	}
	
	return sin;
}

ostream& operator<<(ostream& sout, longfloat r)
{
	while (r.num[r.num.size() - 1] == 0 && r.num.size() > r.point)
		r.num.pop_back();
	
	int n = 0;
	int m = r.num.size() - r.point;
	while (r.num[n] == 0 && n < r.point)
		n++;
	
	for (int i = r.num.size() - 1, j = 0; i >= n; i--, j++) {
		if (j == m)
			sout<<'.';
		sout<<r.num[i];
	}
	return sout;
}

longfloat operator*(const longfloat& r1, const longfloat& r2){
	longfloat result(r1.num.size() + r2.num.size());
	result.point = r1.point + r2.point;
	
	for (int i = 0; i < r1.num.size(); i++)
		for (int j = 0; j < r2.num.size(); j++)
			result.num[i + j] += r1.num[i] * r2.num[j];
	
	for (int i = 0; i < result.num.size(); i++) {
		if (result.num[i] >= 10) {
			result.num[i + 1] += result.num[i] / 10;
			result.num[i] %= 10;
		}
	}
	
	return result;
}

longfloat pow(longfloat r, int n)
{
	longfloat re = r;
	for (int i = 1; i < n; i++)
		re = re * r;
	
	return re;
}

int main()
{
	longfloat r;
	int n ;
	while (cin >> r >> n)
		cout << pow(r, n) << endl;
}