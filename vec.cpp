#include <iostream>
#include <vector>
#include<stdio.h>
using namespace std;
int main()
{
	vector <string> v;

	int i;
	char x[]="abcd";
	//for(i=0;i<5;i++)
	//{v.push_back(x);
	//	x++;
	//}
	//cout << x;
	v.push_back(x);
   // int size=v.size();
	//for(vector <int> :: iterator j = v.begin() ; j != v.end() ; j++)
	//cout<<*j<<" ";
	cout<< v[0];
    //printf("%s",v[0]);
    //for(i=0;i<size;i++)
    //	printf("%s",v[i]);

return 0;
}