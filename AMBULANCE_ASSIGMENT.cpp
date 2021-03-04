#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 
#include<iostream>
#include<string>
using namespace std;
//Module 5 ambulance assignment 

//We construct a graph consisting of ambulances, patients and hospitals

//Then for every patient in need, we consider the shortest path between the 

//Ambulance and patient. This is added on to the shortest path between patient

//And hospitals. So the patient with the smallest sum of distances

//gets priority  

 
// Using adjacency list representation
struct list_node
{
	int dest;  //this structure represents a node in an adjacency list
	int weight;
	struct list_node* next;
};


struct list
{
	
// Pointer to head node of list
struct list_node *head; 
};

// A structure to represent a graph with vert vertices
struct Graph
{
	int vert;
	struct list* array;
};

// to create a new node
struct list_node* new_node(
				int dest, int weight)
{
	struct list_node* newNode =
			(struct list_node*) 
	malloc(sizeof(struct list_node));
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

// creates  a graph of vert vertices
struct Graph* createGraph(int vert)
{
	struct Graph* graph = (struct Graph*) 
			malloc(sizeof(struct Graph));
	graph->vert = vert;

	//array of adjacency lists of size vert
	graph->array = (struct list*) 
	malloc(vert * sizeof(struct list));

	// Initialize adjacency list as empty
	for (int i = 0; i < vert; ++i)
		graph->array[i].head = NULL;

	return graph;
}

// Adding an edge to the graph given source node, dest node and weight
void add_edge(struct Graph* graph, int src, 
				int dest, int weight)
{ 
	struct list_node* newNode = 
			new_node(dest, weight);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	//Undirected graph requires src and dest to both be initialized
	newNode = new_node(src, weight);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}

// Structure to represent a min heap node
struct MinHeapNode
{
	int v;
	int dist;
};

// Structure to represent a min heap
struct MinHeap
{
	
	// current number of nodes
	int size;	 

	// total capacity
	int capacity; 

	int *pos; 
	struct MinHeapNode **array;
};

//creating a new min heap node 
struct MinHeapNode* newMinHeapNode(int v, 
								int dist)
{
	struct MinHeapNode* minHeapNode =
		(struct MinHeapNode*) 
	malloc(sizeof(struct MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->dist = dist;
	return minHeapNode;
} 

// To create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minHeap =
		(struct MinHeap*) 
	malloc(sizeof(struct MinHeap));
	minHeap->pos = (int *)malloc(
			capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array =
		(struct MinHeapNode**) 
				malloc(capacity * 
	sizeof(struct MinHeapNode*));
	return minHeap;
}

//swapping function in minheap
void swapMinHeapNode(struct MinHeapNode** a, 
					struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

// to heapify the nodes and find the shortest path
void minHeapify(struct MinHeap* minHeap, 
								int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < minHeap->size &&
		minHeap->array[left]->dist < 
		minHeap->array[smallest]->dist )
	smallest = left;

	if (right < minHeap->size &&
		minHeap->array[right]->dist <
		minHeap->array[smallest]->dist )
	smallest = right;

	if (smallest != idx)
	{
		// Nodes to be swapped
		MinHeapNode *smallestNode = 
			minHeap->array[smallest];
		MinHeapNode *idxNode = 
				minHeap->array[idx];

		// Swap positions
		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		// Swap nodes
		swapMinHeapNode(&minHeap->array[smallest], 
						&minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

//checking if minheap is empty
int isEmpty(struct MinHeap* minHeap)
{
	return minHeap->size == 0;
}

//extracting minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* 
								minHeap)
{
	if (isEmpty(minHeap))
		return NULL;

	// Store the root node
	struct MinHeapNode* root = 
				minHeap->array[0];

	// Replace root node with last node
	struct MinHeapNode* lastNode = 
		minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	// Update position of last node
	minHeap->pos[root->v] = minHeap->size-1;
	minHeap->pos[lastNode->v] = 0;

	// Reduce heap size and heapify root
	--minHeap->size;
	minHeapify(minHeap, 0);

	return root;
}

// Function to keep track of the minimum node in the heap and 
//the lists
void decreaseKey(struct MinHeap* minHeap, 
						int v, int dist)
{
	// Get the index of v in heap array
	int i = minHeap->pos[v];

	// Get the node and update its dist value
	minHeap->array[i]->dist = dist;

	// If tree is not heapified, traverse from bottom up 
	
	
	// O(Logn) while loop
	while (i && minHeap->array[i]->dist < 
		minHeap->array[(i - 1) / 2]->dist)
	{
		// Swap node with parent
		minHeap->pos[minHeap->array[i]->v] = 
									(i-1)/2;
		minHeap->pos[minHeap->array[
							(i-1)/2]->v] = i;
		swapMinHeapNode(&minHeap->array[i], 
				&minHeap->array[(i - 1) / 2]);

		// move to parent index
		i = (i - 1) / 2;
	}
}

//to check if vertex is in minheap
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
if (minHeap->pos[v] < minHeap->size)
	return true;
return false;
} 


struct mins{
   	  int min=INT_MAX,closest;//closest node, minimum distance
   };

//To keep track of the shortest path
struct mins track(int dist[], int n,int source)
{   
    struct mins s;//to keep track of distance b/w amb & patient
	bool flag=false;
	
	if(source==0||source==3||source==6)
	    	flag=true;
	for (int i = 0; i < n; ++i)
	{   
	    if(flag){
	    	
	    	if(i==1||i==4||i==7||i==9||i==10){ 
	    	 if(dist[i]<s.min){
					s.min=dist[i];
					s.closest=i;
				}
	    } 
	    	
		} 
		
		else{
			if(i==2||i==5||i==8||i==11){
				if(dist[i]<s.min){
					s.min=dist[i];
					s.closest=i;
				}
			} 	
		}
		
	}  
	 
	return s;
		
}

//O(ELogV) Dijkstra algorithm, where E is number of edges and vert is number of vertices
struct mins  dijkstra(struct Graph* graph, int src)
{
	
	// Get the number of vertices in graph
	int vert = graph->vert;

	// dist values used to pick
	// minimum weight edge in cut
	int dist[vert];	 

	// minHeap represents set E
	struct MinHeap* minHeap = createMinHeap(vert);

	// Initialize min heap with all 
	// vertices. dist value of all vertices 
	for (int v = 0; v < vert; ++v)
	{
		dist[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v, 
									dist[v]);
		minHeap->pos[v] = v;
	}

	// Distance between source and itself is 0, so it is extracted first
	minHeap->array[src] = 
		newMinHeapNode(src, dist[src]);
	minHeap->pos[src] = src;
	dist[src] = 0;
	decreaseKey(minHeap, src, dist[src]);

	// Initially size of min heap=vert
	minHeap->size = vert;

 
	// min heap in this while loop contains all nodes
	// without finalized shortest distance
	while (!isEmpty(minHeap))
	{
		// Extract the vertex with 
		// minimum distance value
		struct MinHeapNode* minHeapNode = 
					extractMin(minHeap);
	
		// Store the extracted vertex number
		int u = minHeapNode->v; 

		// Traverse vertices adjacent 
		// to the extracted
		// vertex and update 
		// their distance values
		struct list_node* pCrawl =
					graph->array[u].head;
		while (pCrawl != NULL)
		{
			int v = pCrawl->dest;

			// If shortest distance to v is
			// not finalized yet, and distance to v
			// through extracted vertex < 
			// previously calculated distance
			if (isInMinHeap(minHeap, v) && 
					dist[u] != INT_MAX && 
			pCrawl->weight + dist[u] < dist[v])
			{
				dist[v] = dist[u] + pCrawl->weight;

				// update minheap with new distance
				decreaseKey(minHeap, v, dist[v]);
			}
			pCrawl = pCrawl->next;
		}
	}
//returns object of structure with distance and node number as data members
		struct mins obj=track(dist, vert,src);
	    return obj;
	
} 


class patient{ 
	public:
		struct mins cl_hosp;//node number and distance of the closest hospital
		int node_number; //node number in the graph
        int amb_assigned; //flag to check if ambulance has already been assigned
        float reach_time;
        
		std::string patient_name; 
		std::string patient_address; 
		std::string patient_grievance;   
		
		std::string amb_contact;
		std::string amb_reg;//ambulance details(of the ambulance assigned)
		
		std::string cl_hospital_name;//hospital closest to the patient
		patient(){ 
		} 
		
	    //Assigning hospital name according to the node(vertex) number returned by algorithm
	    void hosp_assign(int num){
	    	switch(num){
	    		case 2:cl_hospital_name.replace(0,cl_hospital_name.length(),"Hospital 1");
	    		break;
	    		
	    		case 5:cl_hospital_name.replace(0,cl_hospital_name.length(),"Hospital 2");
	    		break;
	    		
	    		case 8:cl_hospital_name.replace(0,cl_hospital_name.length(),"Hospital 3");
	    		break;
	    		
	    		case 11:cl_hospital_name.replace(0,cl_hospital_name.length(),"Hospital 4");
	            break;
	            
	            default:break;
			}
	
		} 
		
		//Assign ambulance depending on the node number returned by algorithm
		void det_assign(int num){  
		switch(num){
			case 0:amb_contact.replace(0,amb_contact.length(),"9945623450");
			       amb_reg.replace(0,amb_reg.length(),"KA 01 XX 1234");
			       break;
			       
			case 3:amb_contact.replace(0,amb_contact.length(),"8732156789");
			       amb_reg.replace(0,amb_reg.length(),"KA 02 YY 4569");
			       break; 
			       
			case 6:amb_contact.replace(0,amb_contact.length(),"7693512973");
			       amb_reg.replace(0,amb_reg.length(),"KA 03 ZZ 6669");
			       break;
			
			default:break;	
	        }
	    } 
			 
		//calculating shortest path with src as source
		void assign(struct Graph* gra,int src){
			node_number=src;
		    cl_hosp=dijkstra(gra,src);
		} 
		
		//check if patient is assigned an ambulance
		bool check(int num){
			
			if(node_number==num){
				return true;
			} 
			else{
				return false;
			} 
			
			
		}   
}; 
	 


class ambulance{ 
	public:
	struct mins cl_patient;
	struct mins hosp;
	int node_num;
	int total_distance;
	float travel_time; 
	std::string hosp_name; 
	
	std::string p_name; //details of patient to be picked up 
	std::string p_address;
	std::string p_gr;
	
	ambulance(){
	} 
		  
	void amb(struct Graph* gra,int src){
		node_num=src;
		cl_patient=dijkstra(gra,src); 
	}  
	
    void details(patient &p){
    	if(p.amb_assigned){ 
    			p_name.replace(0,p_name.length(),p.patient_name);
    		    p_address.replace(0,p_address.length(),p.patient_address);
    			p_gr.replace(0,p_gr.length(),p.patient_grievance);
    			hosp_name.replace(0,hosp_name.length(),p.cl_hospital_name);
		} 
	}  
	
	void wait_calc(){
		travel_time=((float(total_distance))/40)*60; //calclating waiting time
		//T=D/S, assuming avg speed to be 40Kmph
	}
	
};

//Function that sorts waiting times in ascending order 
void sort(float arr[],int n){
	
   int i, j, min;
   float temp;
   for (i = 0; i < n - 1; i++) {
      min = i;
      for (j = i + 1; j < n; j++)
      if (arr[j] < arr[min])
      min = j;
      temp = arr[i];
      arr[i] = arr[min];
      arr[min] = temp;
   } 
}

//Main function 
int main()
{ 
	
	int vert = 12;float min[3];
	struct Graph* graph = createGraph(12);//create graph with 12 vertices
	
	//Vertices 0,3 and 6 represent ambulances
	//add_edge takes src,dest and weight as arguments
	add_edge(graph, 0, 1, 4); 
	add_edge(graph, 0, 4, 5); 
	add_edge(graph, 0, 7, 3); 
	add_edge(graph, 0, 9, 2);  
	add_edge(graph, 0, 10, 1); 
	
	add_edge(graph, 3, 1, 3);
	add_edge(graph, 3, 4, 4); 
	add_edge(graph, 3, 7, 5); 
	add_edge(graph, 3, 9, 4);  
	add_edge(graph, 3, 10, 8);  
	
	add_edge(graph, 6, 1, 4);
	add_edge(graph, 6, 4, 5); 
	add_edge(graph, 6, 7, 3); 
	add_edge(graph, 6, 9, 10);  
	add_edge(graph, 6, 10, 11);  
	
	
	//vertices 1,4,7,9,10 represent patients
	add_edge(graph, 1, 2, 17);
	add_edge(graph, 1, 5, 18); 
	add_edge(graph, 1, 8, 19); 
	add_edge(graph, 1, 11, 9);  
	
	add_edge(graph, 4, 2, 3);
	add_edge(graph, 4, 5, 3); 
	add_edge(graph, 4, 8, 4); 
	add_edge(graph, 4, 11, 5);   
	
	add_edge(graph, 7, 2, 14);
	add_edge(graph, 7, 5, 15); 
	add_edge(graph, 7, 8, 7); 
	add_edge(graph, 7, 11, 8);   
	
	add_edge(graph, 9, 2, 5);
	add_edge(graph, 9, 5, 13); 
	add_edge(graph, 9, 8, 10); 
	add_edge(graph, 9, 11, 11); 
	
	add_edge(graph, 10, 2, 14);
	add_edge(graph, 10, 5, 5); 
	add_edge(graph, 10, 8, 12); 
	add_edge(graph, 10, 11, 13); 
	
	patient p[5];
	
	p[0].assign(graph,1); //calculating shortest path with patients as sources
	p[1].assign(graph,4);
	p[2].assign(graph,7);
	p[3].assign(graph,9);
	p[4].assign(graph,10); 
	
	ambulance a[3]; 
	
	a[0].amb(graph,0);//calculating shortest path with ambulances as sources
	a[1].amb(graph,3);
	a[2].amb(graph,6); 
		
    
    
    //Taking details from patients 
    
    for(int i=0;i<5;++i){
    	cout<<"\n\nPatient "<<i+1<<",\nPlease enter name:";
    	getline(cin,p[i].patient_name); 
    	cout<<"\nPlease enter address:";
    	getline(cin,p[i].patient_address);
    	cout<<"\nPlease describe your emergency briefly:";
    	getline(cin,p[i].patient_grievance);
    	p[i].hosp_assign(p[i].cl_hosp.closest);
	} 
	

//This segment maps the ambulance to a patient, depending on 
//the patient closest to each ambulance and
//the hospital closest to each of these patients
    for(int i=0;i<3;++i){ 
    	for(int j=0;j<5;++j){ 
    		if(p[j].check(a[i].cl_patient.closest)){
    			a[i].hosp=p[j].cl_hosp;
    		    a[i].total_distance=a[i].hosp.min+a[i].cl_patient.min; 
    		    a[i].wait_calc(); 
    		    p[j].amb_assigned=1;
    		    a[i].details(p[j]); //note
    		    p[j].det_assign(a[i].node_num);
    		    p[j].reach_time=a[i].travel_time;
    		    break;
				} 
				 
		}     
	}  
	
	
    
//#############################################################################
//Ambulance drivers will be able to see the following

cout<<"\n\n########################################################################################################";
cout<<"\nAmbulance drivers will be able to see the following:\n";
    for(int i=0;i<3;++i){ 
        cout<<"\n\nAmbulance "<<i+1<<",you are instructed to pick up the following patient: ";
    	cout<<"\nName:"<<a[i].p_name<<"\nAddress: "<<a[i].p_address<<endl;
    	cout<<"Emergency:"<<a[i].p_gr;
    	cout<<"\nYou are to transport the patient to "<<a[i].hosp_name<<".";
    	min[i]=a[i].total_distance; 	
	}  
     
    sort(min,3); //Array that stores the distances to be covered by the ambulances
    int ctr=0;
     
//#############################################################################
//Patients will be able to see the following from their side 

cout<<"\n\n############################################################################################################";
cout<<"\n\nPatients will be able to see the following:";
    for(int i=0;i<5;++i){ 
    	if(p[i].amb_assigned){ 
    		cout<<"\n\nDear "<<p[i].patient_name<<", an ambulance will pick you up in "<<p[i].reach_time<<" minutes."<<endl;
    		cout<<"Ambulance details are as follows:";
    		cout<<"\nContact:"<<p[i].amb_contact; 
    		cout<<"\nVehicle registration number:"<<p[i].amb_reg;
    		cout<<"\nYou are assigned "<<p[i].cl_hospital_name<<".";
		} 
		else{ 
			cout<<"\n\nDear "<<p[i].patient_name<<", it looks like there are no ambulances available currently.";
			cout<<"\nYour approximate wait time would be "<<((min[ctr]/40)+0.5)*60<<" minutes.";  
			ctr++;//extra 0.5 hours added to wait time as grace period,assuming avg speed to be 40Kmph 
		}  
	}   
	return 0;  
}   

