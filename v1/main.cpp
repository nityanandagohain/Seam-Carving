#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <climits>
using namespace std;
struct node{
	int weight;
	int vertex;
	node *next;
};

struct adjList{
	node *head;
};

void dijkstra(adjList **graph, int len, int);
class Graph{
	public:
		int row,col;
		adjList *graph;
		int l;
		Graph(int **g,int ,int );
		~Graph();
		void call();
		void display();
		void insert(int vertex,node **temp);
		void reformImgAndLoad();
};
void Graph::call(){
	dijkstra(&graph,l,col);
	display();
	reformImgAndLoad();
}
void Graph::display(){
	for(int i=0;i<l;i++){
		cout<<i<<": ";
		node *temp = graph[i].head;
		while(temp!=NULL){
			cout<<"-> w:"<<temp->weight<<" v:"<<temp->vertex<<" ";
			temp=temp->next;
		}
		cout<<endl;
	}
}


Graph::Graph(int **IMG,int r, int c){
	graph = new adjList[r*c + 2]; //for source and destination
	l=r*c + 2;
	row = r;
	col = c;
	int v=1;
	int weight;

	//First one in adjList will contain source
	//adjList[0] will be the source
	//adjList[l-1] will be the destination

	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if(i<row-1){
				//bottom left
				if(j>0){
					weight = IMG[i][j] - IMG[i+1][j-1];
					if(weight<0)
						weight = -weight;
					node *temp = new node;
					temp->weight = weight;
					temp->vertex = (i+1)*col + (j-1) + 1;
					temp->next=NULL;
					insert(v,&temp);
				}

				//bottom middle
				weight = IMG[i][j]-IMG[i+1][j];
				if(weight<0)
					weight = -weight;
				node *temp = new node;
				temp->weight = weight;
				temp->vertex = (i+1)*col + j + 1;
				temp->next = NULL;
				insert(v,&temp);

				//bottom right
				if(j<col-1){
					weight = IMG[i][j]-IMG[i+1][j+1];
					if(weight<0)
						weight = -weight;
					node *temp = new node;
					temp->weight = weight;
					temp->vertex = (i+1)*col + (j+1) + 1;
					temp->next=NULL;
					insert(v,&temp);
				}
			}else{
				node *temp = new node;
				temp->weight = IMG[i][j];
				temp->vertex = l-1;
				temp->next = NULL;
				insert(v,&temp);
			}
			v++;
		}
	}

	//source to the first row of vertices in graph
	for(int i=1;i<=col;i++){
		node *temp = new node;
		//directly keeping weight as initial value
		temp->weight = IMG[0][i-1];
		temp->vertex = i;
		temp->next = NULL;
		insert(0,&temp);
	}

}


//Destructor
Graph::~Graph(){
	for(int i=0;i<l;i++){
		node *temp=graph[i].head;
		while(temp!=NULL){
			node *del = temp;
			temp=temp->next;
			delete del;
		}
	}
	delete graph;
}

void Graph::insert(int vertex,node **temp){
	if(graph[vertex].head == NULL){
		graph[vertex].head = *temp;
		return;
	}
	(*temp)->next = graph[vertex].head;
	graph[vertex].head=*temp;
}


void readLine(FILE **fp, char str[]){
	int i=0;
	char c;
	//Reading the line
	while((c=getc(*fp))!='\n'){
		str[i++]=c;
	}
}




int minDistance(int dist[], bool sptSet[],int len){
	int min = INT_MAX, min_index;
	for (int v = 0; v < len; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;
	return min_index;
}


void dijkstra(adjList **graph, int len, int col){
	int dist[len];
	int parent[len];
	bool sptSet[len];
	for (int i = 0; i < len; i++){
		dist[i] = INT_MAX;
		parent[i]=-1;
		sptSet[i] = false;
	}
	cout<<"init"<<endl;
	dist[0] = 0;
	parent[0]=-1;
	while(1){
		int u = minDistance(dist, sptSet, len);
		sptSet[u] = true;
		node *curr = (*graph)[u].head;
		int flagEnd=0;
		while(curr!=NULL){
			if(curr->vertex == len-1){
				cout<<"End Reached"<<endl;
				flagEnd=1;
				break;
			}
			if (!sptSet[curr->vertex] && dist[u] != INT_MAX && dist[u]+curr->weight < dist[curr->vertex]){
				dist[curr->vertex] = dist[u] + curr->weight;
				parent[curr->vertex] = u;
			}
			curr = curr->next;
		}
		cout<<endl;
		//cout<<"min vertex: "<<u<<endl;
		//***********************************************************************
		//Deleting link to U from the whole graph
		//***********************************************************************

		int i;
		if(u-col-1>0){
			i=u-col-1;
		}else{
			i=0;
		}
		for(; i < u; i++){
			node *prev = NULL; 
			curr = (*graph)[i].head;

			if(curr!=NULL && curr->vertex==u){
				(*graph)[i].head = curr->next;
				cout<<"Deleting "<<curr->vertex<<" in :"<<i<<endl;
				delete curr;
			}else{
				while(curr!=NULL && curr->vertex!=u){
					prev = curr;
					curr=curr->next;
				}

				if(curr != NULL){
					prev->next = curr->next;
					cout<<"Deleting "<<curr->vertex<<" in :"<<i<<endl;
					delete curr;
				}
			}
		}

		//Deleteig the entire list
		if(u>0){ //because 1st just contains links to nodes
		curr = (*graph)[u].head;
		cout<<"\ndeleting Entire of "<<u<<":";
		while(curr!=NULL){
			cout<<" "<<curr->vertex;
			node *temp = curr;
			curr=curr->next;
			delete temp;
		}
		cout<<endl;
		(*graph)[u].head = NULL;
		}
		if(flagEnd == 1){
			break;
		}
	}
}

void Graph::reformImgAndLoad(){
	/*
	int **tempMat;
	tempMat = new int*[row];
	for(int i=0;i<col-1;i++){
		tempMat[i] = new int[col-1];
	}
	int j=0,k=0;
	for(int i=1;i<len;i++){
		k=0;
		for(;i<col;i++){
			
		}
	*/
}


int main(int argc,char *argv[]){
	FILE *fp=fopen(argv[1],"r");
	int row,col,maxWeight;
	int **IMG;
	if(fp!=NULL){
		char temp[100];
		fscanf(fp,"%s\n",temp);
		int len =0;
		if(strcmp(temp,"P2")==0){
			cout<<"It is a pgm file"<<endl;
		}else{
			printf("NOT a pgm fie");
			exit(1);
		}
		readLine(&fp,temp);
		cout<<"temp: "<<temp<<endl;
		fscanf(fp,"\n%d %d %d",&col,&row,&maxWeight);
		cout<<"Row: "<<row<<" Cols: "<<col<<" MaxWeight: "<<maxWeight<<endl;

		//Initializing the matrix
		IMG = new int*[row];
		for(int i=0;i<row;i++){
			IMG[i]= new int[col];
		}
		int t;

		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				fscanf(fp,"%d",&t);
				IMG[i][j] = t; 
			}
			fscanf(fp,"\n");
		}

		cout<<"Matrix initialized"<<endl;
		Graph g(IMG,row, col);
		g.display();


		//Graph created 

		//Applying Dijkstra's algo

		g.call();
	}
	fclose(fp);
	return 0;
}
