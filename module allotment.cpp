#include <bits/stdc++.h> 
using namespace std; 
string bookingTime()
    {
        string booking_time;
		time_t now = time(0);
        char* ltm = ctime(&now);
        booking_time=ltm;
        return booking_time;
    }
struct hos
{
	char hosname[30];
	int size;
	int fill;
}admin[10]={
	             {"ABC",700,0},
	             {"DEF",500,0},
	             {"GHI",300,0},
	             {"JKL",600,0},
	             {"MNO",100,0},
	             {"PQR",700,0},
	             {"STU",200,0},
	             {"VWX",400,0},
				 {"YZA",600,0},
	             {"BCD",800,0}
	           };
struct det
{
	string phn;
	string name;
	int prob;
	string booking;
};
int main() 
{ 
    map<int, string> mp; 
    det val[100];
    int n=4;
    int j=1,k=20,l=40,m=60;
    for(int i=1;i<n;i++)
    {
        cout<<"Patient "<<i<<":\n";
		cout<<"Type your name: ";
        cin>>val[i].name;
        cout<<"Type your phone number: ";
        cin>>val[i].phn;
        cout<<"Type the choice according to the severity:\n1.Extremely serious\n2.Serious\n3.Moderate\n4.Not serious\nChoice: ";
        cin>>val[i].prob;
        val[i].booking=bookingTime();
        if(val[i].prob==1)
        {
        	mp.insert({ j,val[i].name });
			j++;
		}
        else if(val[i].prob==2)
        {
        	mp.insert({ k,val[i].name });
			k++;
		}
        else if(val[i].prob==3)
        {
        	mp.insert({ l,val[i].name });
			l++;
		}
        else if(val[i].prob==4)
        {
        	mp.insert({ m,val[i].name });
			m++;
		}
        else
        {
        cout<<"\nError, Wrong input\n";
        i--;
        }
	}
    cout << "KEY\tELEMENT\n"; 
    for (auto itr = mp.begin(); itr != mp.end(); ++itr) { 
        cout << itr->first 
             << '\t' << itr->second << '\n'; 
    }
    int counter=0;
    int i=0;
	for(int j=1;j<n;j++)
	{
		if(admin[i].fill!=admin[i].size)
		{
			cout<<"\nThe Hospital you are assigned to: "<<admin[i].hosname;
			cout<<"\nHospital will be able to see the user details as follows:\n";
		    cout<<"Patient "<<j+1<<": ";
	        cout<<"\nDate and Time alloted: "<<val[j].booking;
	        cout<<"Details:\n"<<"Name: "<<val[j].name;
 	        cout<<"\nPhone Number: "<<val[j].phn<<endl;
	        cout<<"\nSeverity: "<<val[j].prob<<endl;  
			continue;
		}
		    else if(admin[i].fill<admin[i].size)
		    {
		       admin[i].fill++;
		       counter=1;
		       break;
		    }
		else
		{
			counter=0;
			i++;
			continue;
		}
	}   
    return 0; 
} 
