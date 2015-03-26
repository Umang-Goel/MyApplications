#include<bits/stdc++.h>
using namespace std;

int main()
{
	string b = "ab";
	string c = "";
	c += b[1];
	string *a= &c;
	//cout<< b << endl;
	cout << *a;
	return 0;
}
