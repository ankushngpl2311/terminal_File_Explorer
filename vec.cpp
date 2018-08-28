#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector <int> v;

	int i;
	for(i=0;i<5;i++)
	v.push_back(i);

	for(vector <int> :: iterator j = v.begin() ; j != v.end() ; j++)
	cout<<*j<<" ";

return 0;
}