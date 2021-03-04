#include<iostream>
#include<string>
#include<ctime>
#include<queue> 
#include <unistd.h>
#include<stdlib.h> 
#include<limits.h> 
	//Module 10,social distancing in shops 
class user{ 
  public:
	char c_firstname[15];//User name
	char c_lastname[15];
	
	long long cnum;//mobile number
	
	long long area_code;//Area code of user
	
	int num_req; //Number of categories user wishes to procure from.
	
	int requirements[8];//List of requirements 
	int weightages[8];
	
	std::string secret_key;//Like an OTP 
	int booking_hour;//Hour part of booking time
	int booking_minute;//Minute part of booking time 
	
		//Constructor
		user(){
			num_req=0;
		    secret_key=""; //Like an OTP 
			weightages[0]=10;weightages[1]=7;
			weightages[2]=8;weightages[3]=8;
			weightages[4]=5;weightages[5]=7;
			weightages[6]=7;weightages[7]=4;
		} 
		
		
		//Function to display the menu
		void display_menu(){
			std::cout<<"\n1.Heart Medicines.";
			std::cout<<"\n2.Medicines for chronic illnesses.";
			std::cout<<"\n3.Diabetes medicines.";
			std::cout<<"\n4.Blood pressure medicines.";
			std::cout<<"\n5.Diapers.";
			std::cout<<"\n6.Allergy medication.";
			std::cout<<"\n7.Sanitary products.";
			std::cout<<"\n8.Other medicines.";
		}
		//Function to collect details 
		void collect_details(){
			std::cout<<"\nEnter your first name:";
			std::cin>>c_firstname;
			std::cout<<"\nEnter your last name:";
			std::cin>>c_lastname;
			std::cout<<"\nEnter mobile number:";
			std::cin>>cnum;
			std::cout<<"\nEnter Area code:";
			std::cin>>area_code;
			display_menu();
			std::cout<<"\nPlease enter the number of categories you need to procure from this list: ";
			std::cin>>num_req;
			std::cout<<"\nPlease enter the category numbers separated by a space:";
			
			for(int i=0;i<num_req;++i){
				std::cin>>requirements[i]; 
			}   
		} 
		
		
		void booking_time(){
			time_t now = time(0);
            tm *ltm = localtime(&now);
            booking_hour=ltm->tm_hour;
            booking_minute=ltm->tm_min;
		}   
		
		void secret_key_generator(){
			static const char alphanum[] ="0123456789"
                                          "abcdefghijklmnopqrstuvwxyz";
    
            for (int i = 0; i < 4; ++i) 
              secret_key+= alphanum[rand() % (sizeof(alphanum) - 1)];
		} 					
};  

class shop:public user{
	
	
	int capacity; //Total capacity of the shop
	
	 
	
    char availability; //Checks if shop has all items required by user
	
	public:
		bool wait; 
		int filled; //number of people already inside the shop 
		int wait_hours; //number of hours to wait,in case waiting is required
	    int wait_minutes;//number of minutes to wait
		int hours; //shops copy of wait time 
		int mins;   
		bool a;//Flag if items not available 
		std::string shop_name;
        std::string shop_address;
		int score;//Score based on which priority is assigned 
		shop(){ 
		 score=0;
		 capacity=0;
		 filled=0;
		 a=true;
		 wait=false;
		} 
		shop(int score)
		{	
		  score=score;
		} 
		
		shop(std::string name,std::string address,int cap,int fill){
			shop_name.replace(0,shop_name.length(),name);
			shop_address.replace(0,shop_address.length(),address);
			capacity=cap;
			filled=fill; 
			a=true; 
		} 
		
		
		//Function that returns wait hours
		int get_waithours(){
			return wait_hours;
		}
		int get_waitmins(){
			return wait_minutes;
		}
		
		int get_wait(){
			return hours+mins; 
		}
		//Function to calculate score based on the choice made by the user
	    void calculate_score(){
			for(int i=0;i<num_req;++i){
				score+=weightages[requirements[i]-1];	
			} 
			score+=num_req; //User with more number of requirements gets a slightly higher score
		}  
		
		int get_status(){ //To check if shop can take in more people 
			return (capacity-filled);
		}
		bool availability_check(shop top_user){ //For shops
		    std::cout<<"\nDear shopkeeper of "<<shop_name<<",";
			std::cout<<"\nYou have a request for categories ";
			for(int i=0;i<top_user.num_req;++i){
				std::cout<<top_user.requirements[i]<<",";
			} 
			std::cout<<"\nPlease confirm if you have the necessary items(y/n):";
			std::cin>>availability;
			if(availability=='y'||availability=='Y'){
				a=true; 
				filled++;
				return true;
			} 
			else{ 
			    a=false;
				return false;
			} 
		}  
	    
	    bool assign_wait(){//To initiate waiting process

	        std::cout<<"\nPlease give an approximate waiting time (in hours&mins separated by space):";
			std::cin>>hours;
			std::cin>>mins;
			
		} 
		
		
		void shop_display(shop top_user){//To ensure shop details are released only 1 hour before appointment time in case of waiting period
			std::cout<<"\nDear ";
			std::cout<<top_user.c_firstname<<" ";
			std::cout<<top_user.c_lastname<<",";
			std::cout<<"your items are available in  ";
			std::cout<<shop_name;
			std::cout<<"\nThe address is:";
			std::cout<<shop_address;
			std::cout<<"\nPlease head to the shop on time to collect your items.\n\n";
		} 
		
		//Function to display the user details to the shop admins
		void user_display(){
			std::cout<<"\n"<<"Customer name:";
			std::cout<<c_firstname<<" "<<c_lastname;
			std::cout<<"\nMobile number:"<<cnum;
			display_menu();
			std::cout<<"\nCustomer needs items from categories ";
			for(int i=0;i<num_req;++i){
				std::cout<<requirements[i]<<",";
			} 
			std::cout<<"\nSecret key:"<<secret_key;
			std::cout<<"\nBooking time: "<<booking_hour<<":"<<booking_minute;	
		} 		
};

struct compare_score {
    bool operator()(shop const& u1, shop const& u2){ 
        // return "true" if "u1" has a lower score than u2
        //Priority queue ADT considers a lesser than comparison by default 
        return u1.score < u2.score;
    }
}; 

	
using namespace std; 
int main(){
	
	bool capacity;//Flag if no capacity 
	int flag=1,counter=0;
    shop obj1[3]; //object of users
	priority_queue<shop, vector<shop>, compare_score>Q; //priority queue of users
	    for(int i=0;i<3;++i){ 
    	obj1[i].collect_details(); 
    	obj1[i].booking_time();
    	srand( (unsigned) time(NULL) * getpid());
    	obj1[i].secret_key_generator(); 
		obj1[i].calculate_score(); 
	    Q.push(obj1[i]);
	}   
    
    
	shop *obj2=new shop[3]; //object of shops 
    obj2[0]=shop("Shop 1","Shop 1 address",10,5);
	obj2[1]=shop("Shop 2","Shop 2 address",20,10); 
	obj2[2]=shop("Shop 3","Shop 3 address",15,8);
	cout<<"###########################################################################################################################################################################################################";
	cout<<"\n\n\nAdmins(shopkeepers) will be able to see the requirements of the prioritized customer:";
	
	for(int i=0;i<3;++i){ 
		
	shop top_user=Q.top(); //The customer with highest priority gets served first 
	shop sh,temp;//Shop that is going to serve the user 
	label:int max_cap=0,cap=0,max,minw;//capacities
	int w=0,mw=INT_MAX;//waiting times  
	for(int i=0;i<3;++i){
	    if(!obj2[i].a){ 
	    	continue;
		} 
		cap=obj2[i].get_status();
		if(cap==0){ 
			std::cout<<"\nDear shopkeeper of ";
			std::cout<<obj2[i].shop_name;
			std::cout<<", looks like your capacity is full.";
			obj2[i].assign_wait();	
		}
		if(cap>max_cap){ 
			max_cap=cap;
			sh=obj2[i];
			max=i;
		} 	 
	}  
	if(max_cap<=0){//Find minimum waiting time  
		for(int j=0;j<3;++j){
			w=obj2[j].get_wait();
			if(w<mw){
				mw=w;
				sh=obj2[j];
				minw=j;
			}
		} 
		sh.wait=true;  
	} 	
	
	if(sh.availability_check(top_user)){//If items requested are available
	     if(sh.wait){
	     	int m;//to process minutes 
	     	top_user.wait_hours=sh.hours;
	     	top_user.wait_minutes=sh.mins;
	     	obj2[minw]=sh;
			cout<<"\n\nAdmin will be able to see the following:";
			top_user.user_display();
			cout<<"\nAppointment has been scheduled for ";
			if(top_user.booking_minute+top_user.get_waitmins()>=60){
				cout<<1+top_user.booking_hour+top_user.get_waithours();
			    cout<<":";	
			    m=(top_user.booking_minute+top_user.get_waitmins())%60; 
			    cout<<m; 
			}
			else{
			cout<<top_user.booking_hour+top_user.get_waithours();
			cout<<":";
			cout<<top_user.booking_minute+top_user.get_waitmins();	
			}
			
			cout<<"\n\nUser will be able to see the following:";
			cout<<"\nYour approximate wait time is ";
			cout<<top_user.get_waithours()<<" hours";
			cout<<",";
			cout<<top_user.get_waitmins()<<" mins"; 
		 }  
		 else{
	     cout<<"\n\nAdmin will be able to see the following:";
		 top_user.user_display(); 
		 cout<<"\n\nUser will be able to see the following:";
		 sh.shop_display(top_user);
		 obj2[max]=sh;
	     } 
	}   
	
	else{  
	     obj2[max]=sh;
		 cout<<"\nChecking next shop.";
		 counter++;
		 if(counter<3) //counter=number of shops 
		 goto label;		 	
	} 
	for(int i=0;i<3;++i){
		if(!obj2[i].a){
			flag=0;
		} 
		else{
			flag=1;
			break; 
		} 
	} 
	if(flag==0){
		cout<<"\nUser will be able to see the following message if items are not available:";
		cout<<"\nDear ";
		cout<<top_user.c_firstname;
		cout<<" ";
		cout<<top_user.c_lastname<<",";
		cout<<"\nThe requested items not available in any of the shops. Apologies!";
	}  
	Q.pop(); 
	sh.filled--; 
	return 0; 
}
			
}  
