#include <bits/stdc++.h> 
using namespace std; 
struct det
{
	int phn;
	char name[30];
	int prob;
};
int main() 
{ 
    map<int, char> mp; 
    det val;
    int n=2;
    for(int i=1;i<n;i++)
    {
        cout<<"Type your name: ";
        cin>>val.name;
        cout<<"Type your phone number: ";
        cin>>val.phn;
        cout<<"Type the choice according to the severity:\n1.Extremely serious\n2.Serious\n3.Moderate\n4.Not serious\nChoice: ";
        cin>>val.prob;
    	mp.insert({ i, val.name[30]});
	}
    cout << "KEY\tELEMENT\n"; 
    for (auto itr = mp.begin(); itr != mp.end(); ++itr) { 
        cout << itr->first 
             << '\t' << itr->second << '\n'; 
    } 
    return 0; 
} 
