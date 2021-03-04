#include<iostream>
#include<string>
#include<ctime>
#include<queue> 
#include<unistd.h>
#include<stdlib.h>
using namespace std;

class patient
{
    public:
    char p_firstname[15], p_lastname[15]; //User name
	
	long long pnum, area_code;//Mobile number, Area code of patient
    
	int age, num_sym, pea, symptoms[13], weightages[13];
    //Number of symptoms in patient, PEA flag, List of symptoms 
	
	string pid, booking_time, fpea;
	long long timestamp;
	
	//Constructor
    patient()
    {
        num_sym=0;
        pid=""; //patiednt id
        weightages[0]=weightages[1]=weightages[2]=10;
        weightages[3]=weightages[4]=weightages[5]=weightages[6]=7;
        weightages[7]=weightages[8]=weightages[9]=7;
        weightages[10]=weightages[11]=weightages[12]=4;
    } 
    //Constructor overloading


    //Function to display the menu
    void display_symptoms()
    {
        cout<<"\nSymptoms:\n";
        cout<<"1.Loss of speech or movement.\n";
        cout<<"2.Chest pain or pressure.\n";
        cout<<"3.Difficulty breathing or shortness of breath.\n";
        cout<<"4.A rash on skin, or discolouration of fingers or toes.\n";
        cout<<"5.Loss of taste or smell.\n";
        cout<<"6.Headache.\n";
        cout<<"7.Conjunctivitis.\n";
        cout<<"8.Diarrhoea.\n";
        cout<<"9.Sore throat.\n";
        cout<<"10.Aches and pains.\n";
        cout<<"11.Fever.\n";
        cout<<"12.Dry cough.\n";
        cout<<"13.Tiredness.\n";
    }
    
    void display_pea()
    {
        cout<<"\nPre existing ailments:\n";
        cout<<"1. Hypertension or High BP.\n";
        cout<<"2. Heart Diseases.\n";
        cout<<"3. Diabetes.\n";
        cout<<"4. Atrial Fibrillation.\n";
        cout<<"5. Active cancer (in the past five years).\n";
        cout<<"6. Chronic Kidney Diseases.\n";
        cout<<"7. COPD.\n";
        cout<<"8. Lung diseases.\n";
        cout<<"9. Suffered a stroke.\n";
    }
    //Function to collect details 
    void collectDetails()
    {
        cout<<"\nEnter your first name: ";
        cin>>p_firstname;
        cout<<"Enter your last name: ";
        cin>>p_lastname;
        cout<<"Enter age: ";
        cin>>age;
        cout<<"Enter mobile number: ";
        cin>>pnum;
        cout<<"Enter Area code: ";
        cin>>area_code;
        display_symptoms();
        cout<<"Please enter the number of symptoms you have from this list: ";
        cin>>num_sym;
        cout<<"Please enter the sympton numbers separated by a space: ";
        for(int i=0;i<num_sym;++i)
            cin>>symptoms[i];
        display_pea();
        cout<<"Do you have any pre existing ailments from this list?[y/n]: ";
        cin>>fpea;
        if(fpea.compare("y")==0||fpea.compare("Y")==0)
            pea=1;
        else
            pea=0;
    } 

    void bookingTime()
    {
        time_t now = time(0);
        timestamp=now;
        char* ltm = ctime(&now);
        booking_time=ltm;
    }

    void pidGenerator()
    {
        static const char alphanum[] ="0123456789"
                                      "abcdefghijklmnopqrstuvwxyz";

        for (int i = 0; i < 4; ++i) 
          pid+= alphanum[rand() % (sizeof(alphanum) - 1)];
    }
};

class testingCentre: public patient
{
    public:
    string name, address; //Name and address of the testing centre
    int capacity; //Total Number of people the centre can hold at a time
	int filled; //Number of people who are at the centre currently
    int available;
    int score;//Score based on which priority is assigned 
    testingCentre()
    {
        score=0;
    } 
    testingCentre(int score)
    {
        score=score;
    } 
    testingCentre(string tcN, string tcA, int cap, int fill)
    {
        name.replace(0, tcN.length(), tcN);
        address.replace(0, tcA.length(), tcA);
        capacity=cap;
        filled=fill;
    }
    //Function to calculate score based on the choice made by the patient
    int calculateScore()
    {
        for(int i=0; i<num_sym; i++)
            score+=weightages[symptoms[i]-1];
        score+=num_sym;
        if(pea==1)
            score+=5;
        return score;
    }
    void patientDisp()
    {
        cout<<"\nPatient details:\n";
        cout<<"Patient name: "<<p_firstname<<" "<<p_lastname<<endl;
        cout<<"Patient age: "<<age<<endl;
        cout<<"Mobile number: "<<pnum<<endl;
        display_symptoms();
        cout<<"Patient has symptoms: ";
        for(int i=0; i<num_sym; i++)
            cout<<symptoms[i]<<" ";
        cout<<"\nPID: "<<pid<<endl;
        cout<<"Booking time: "<<booking_time<<endl;
        cout<<"Score: "<<score<<endl;
    }
    int get_status()
    { //To check if testing centre can take in more people
            if((capacity-filled)>0)
                available=1;
            else
                available=0;
			return (capacity-filled);
	}
    void adminDisp()
    {
        cout<<"\nTesting centre details:\n";
        cout<<"Address: "<<address<<endl;
        cout<<"Capacity: "<<capacity<<endl;
        cout<<"Filled: "<<filled<<endl;
        cout<<"Availability status: ";
        get_status();
        (available==1)?(cout<<"Available\n"):(cout<<"Not available\n");
    }
};

class hospital: public testingCentre
{
    public:
    int bedCap, bedFill, pStat, severity;
    string hname, haddress;
    hospital(){ }
    hospital(string hn, string ha, int cap, int fill)
    {
        hname.replace(0, hn.length(), hn);
        haddress.replace(0, ha.length(), ha);
        bedCap=cap;
        bedFill=fill;
    }
    int vacancy()
    {
        return (bedCap-bedFill);
    }
    void hospDisp()
    {
        cout<<"\nHospital details:\n";
        cout<<"Address: "<<haddress<<endl;
        cout<<"Capacity: "<<bedCap<<endl;
        cout<<"Filled: "<<bedFill<<endl;
        cout<<"Availability status: ";
        (vacancy()>0)?(cout<<"Available\n"):(cout<<"Not available\n");
    }
};

struct compScoreTC 
{
    bool operator()(testingCentre const& u1, testingCentre const& u2) 
    {
        // return "true" if "u1" has a lower score than u2
        //Priority queue ADT considers a lesser than comparison by default
        if(u1.score==u2.score)
        {
            if(u1.age==u2.age)
                return u1.timestamp>u2.timestamp;
            else
                return u1.age<u2.age;
        }
        return u1.score < u2.score;
    }
};

struct compScoreH 
{
    bool operator()(hospital const& u1, hospital const& u2) 
    {
        // return "true" if "u1" has a lower score than u2
        //Priority queue ADT considers a lesser than comparison by default
        if(u1.score==u2.score)
        {
            if(u1.severity==u2.severity)
            {
                if(u1.age==u2.age)
                    return u1.timestamp>u2.timestamp;
                else
                    return u1.age<u2.age;
            }
            else
                return u1.severity<u2.severity;
        }
        return u1.score<u2.score;
    }
};

int main()
{
    hospital p[3];
    hospital p1[3];
    priority_queue<hospital, vector<hospital>, compScoreTC>qTC; //priority queue of patients
    priority_queue<hospital, vector<hospital>, compScoreH>qH;
    queue<hospital>qBuffer;
    queue<hospital>qBA;
    int score,i,ch;
    
    for(i=0;i<3;i++)
    {
        p[i].patient::collectDetails();
        p[i].bookingTime();
        p[i].pidGenerator();
        score=p[i].calculateScore();
        qTC.push(p[i]);
    }
    testingCentre* tc= new testingCentre[3];
    tc[0]=testingCentre("TC 1","TC 1 address",125,123);
	tc[1]=testingCentre("TC 2","TC 2 address",210,210); 
	tc[2]=testingCentre("TC 3","TC 3 address",315,314);
    cout<<"############################################################################################################################################\n\n\n";
	cout<<"Admins will be able to see the details of the prioritized patient:\n";
	for(int i=0;i<3;i++)
    {
        hospital top_patient=qTC.top(); //The patient with highest priority 
        testingCentre tc1; //Testing centre that is going to serve the patient 
        int max_cap=0, cap=0, max;
        for(int j=0;j<3;j++)
        {
            cap=tc[j].get_status();
            if(cap==0)
            { 
                cout<<"Dear admin of ";
                cout<<tc[j].name;
                cout<<", looks like your capacity is full.\n";	
            }
            if(cap>max_cap)
            {
                max_cap=cap;
                tc1=tc[j];
                max=j;
            } 	 
        }
        if(max_cap<=0)
        {  
            cout<<"No testing centre.\n";  
        }
        else
        {
            cout<<"Admin will see this:\n";
            top_patient.patientDisp();
            cout<<"Patient will see this:\n";
            tc1.adminDisp();
            tc[max].filled++;
            qBuffer.push(top_patient);
            qTC.pop();
        }
    }
    cout<<"############################################################################################################################################\n\n\n";
    cout<<"Admin will be able to see this:\n";
    int posCount=0;
    for(int i=0; i<3; i++)
    {
        hospital patient=qBuffer.front();
        cout<<patient.p_firstname<<" "<<patient.p_lastname<<"'s test result(O for positive/1 for negative): ";
        cin>>patient.pStat;
        cout<<"Severity of their condition on a scale of 1-10: ";
        cin>>patient.severity;
        if(patient.pStat==0)
        {
            qH.push(patient);
            posCount++;
        }
        qBuffer.pop();
    }
    
    hospital* h= new hospital[3];
    h[0]=hospital("Hospital 1","hospital 1 address",210,210);
	h[1]=hospital("Hospital 2","hospital 2 address",125,123); 
	h[2]=hospital("Hospital 3","hospital 3 address",315,314);
    cout<<"############################################################################################################################################\n\n\n";
	cout<<"Admins will be able to see the details of the prioritized patient:\n";
	for(int i=0;i<posCount;i++)
    {
        hospital toppatient=qH.top(); //The patient with highest priority 
        hospital h1; //Testing centre that is going to serve the patient 
        int max_cap=0, cap=0, max;
        for(int j=0;j<3;j++)
        {
            cap=h[j].vacancy();
            if(cap==0)
            { 
                cout<<"Dear admin of ";
                cout<<h[j].hname;
                cout<<", looks like your capacity is full.\n";	
            }
            if(cap>max_cap)
            {
                max_cap=cap;
                h1=h[j];
                max=j;
            } 	 
        }
        if(max_cap<=0)
        {  
            cout<<"No beds available.\n";  
        }
        else
        {
            cout<<"Admin will see this:\n";
            toppatient.patientDisp();
            cout<<"Patient will see this:\n";
            h1.hospDisp();
            h[max].bedFill++;
            qBA.push(qH.top());
            qH.pop();
        }
    }
    
    return 0;
}
