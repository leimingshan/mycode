#include <iostream>

using namespace std;

class A {
public:
    A() { }
    virtual ~A() { }
};

int main()
{
    cout<<sizeof(A)<<endl;
    return 0;
}
