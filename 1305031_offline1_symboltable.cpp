
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<string>
#include<iostream>
#include <vector>
#include <fstream>

#include <sstream>
#define NULL_VALUE -999999
#define INFINITY 999999

using namespace std;

class SymbolInfo{
    public:
    string name;
    string type;
    SymbolInfo(){}

    SymbolInfo(string name, string type)
    {
        this->name = name;
        this->type = type;
    }
    void setName(string name)
    {

        this->name = name;
    }
    void setType(string type)
    {

        this->type = type;
    }

    string getName(){
        return name;
    }
    string getType(){return type;}

    void printSymbol(){cout<<name<<type;}
    };

//****************Dynamic ArrayList class based************************
class ArrayList
{
	SymbolInfo * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(SymbolInfo item) ;
    void insertItem(SymbolInfo item) ;
	void removeItem(SymbolInfo item) ;
	void removeItemAt(int item);
	SymbolInfo getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new SymbolInfo[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(SymbolInfo newitem)
{
	SymbolInfo * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new SymbolInfo[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i].name = list[i].name ;
            tempList[i].type = list[i].type ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};


	list[length].name = newitem.name ;
	list[length].type = newitem.type ;
	//cout<<"the inserted item: name "<<list[length].name<<" type: "<<list[length].type;
	 //store new item
	length++ ;
}

int ArrayList::searchItem(SymbolInfo item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i].name == item.name ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	/*list[position] = list[length-1] ;
	length-- ;*/
	int i;
	for(i = position+1;i<length;i++)
	{
        list[i-1].name = list[i].name;
        list[i-1].type = list[i].type;

	}
	length--;
}


void ArrayList::removeItem(SymbolInfo item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


SymbolInfo ArrayList::getItem(int position)
{
	//if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        //printf("name:%s type:%s\n", list[i].name, list[i].type);
        cout<<list[i].name<<" "<<list[i].type<<endl;
    //printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************
//******************Graph class starts here**************************
class SymbolTable
{
	int node ;

	ArrayList  * adjList ;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	SymbolTable();
	~SymbolTable();
	void setNode(int n);


    void insert(SymbolInfo s);

    void lookUp(string searchKey);

    void printTable();
	 //will run dfs in the graph
	 void deleteEntry(string key);
};

SymbolTable::SymbolTable()
{
	node = 0 ;
	//nEdges = 0 ;
	adjList = 0 ;
	//directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void SymbolTable::setNode(int n)
{
	this->node = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[node] ;
	//cout<<node<<endl;
}



void SymbolTable:: insert(SymbolInfo s)
{
    string key = s.name;
    //determine hash
    int value = 0;
    for(int i = 0;i<key.length();i++)
    {
        value+= key[i];
    }
    int index = (value* key.length()) % node;
    //hash determined

    if(adjList[index].searchItem(s) == NULL_VALUE)
    {
        adjList[index].insertItem(s);
        //cout<<"\nadded\n";
        return;
    }
    cout<<"\n already in the list\n";


}

void SymbolTable :: lookUp(string searchKey)
{
    string key = searchKey;
    //determine hash
    int value = 0;
    for(int i = 0;i<key.length();i++)
    {
        value+= key[i];
    }
    int index =(value* key.length())  % node;
    //hash determined
    SymbolInfo temp(searchKey,"null");

    int position = adjList[index].searchItem(temp);
    if( position!= NULL_VALUE)
    {
        cout<<"\n FOUND AT "<<index<<", "<<position<<endl;
    }
    else cout<<"\nNOT FOUND\n";
}

void SymbolTable::printTable()
{
    //printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<node;i++)
    {
        printf("%d->", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            //printf(" %d", adjList[i].getItem(j));
            SymbolInfo temp = adjList[i].getItem(j);
            cout<<"<"<<temp.name<<", "<<temp.type<<"> ";
        }
        printf("\n");
    }
}

void SymbolTable::deleteEntry(string key)
{
    //determine hash
    int value = 0;
    for(int i = 0;i<key.length();i++)
    {
        value+= key[i];
    }
    int index = (value* key.length())  % node;
    //hash determined
    SymbolInfo temp(key,"null");

    int position = adjList[index].searchItem(temp);
    if(position!= NULL_VALUE)
    {
        adjList[index].removeItem(temp);
        cout<<"deleted from "<<index<<", "<<position<<"\n";
    }
    else{
        cout<<"\nitem could not be deleted\n";
    }
}

SymbolTable::~SymbolTable()
{
    //write your destructor here
    if(adjList) delete[] adjList;
    adjList = 0;
}


//**********************Graph class ends here******************************
int main()
{
    cout<<"enter length of hash table: ";
    int n;
    cin>>n;
    SymbolTable table;
    table.setNode(n);

    cout<<"\n1.from file 2.manual\n";
    int c;
    cin>>c;

    if(c == 1)
    {
        ifstream infile("input.txt");
    string line;
    while (getline(infile, line))
    {

        string name = line;


      string buf;
      stringstream ss(name);
      vector<string>tokens;
      while(ss>>buf)
      {
          tokens.push_back(buf);
      }
      //cout<<tokens[0]<<tokens[1]<<tokens[2]<<endl;
      string option = tokens[0];
      if(option == "I")
      {
            string n, t;
            n = tokens[1];
            t = tokens[2];
            SymbolInfo sym(n,t);
            table.insert(sym);
      }
      else if(option == "P")
      {
          table.printTable();
      }
      else if(option == "L")
      {
           string n;
           n = tokens[1];
           table.lookUp(n);
      }
      else if(option == "D")
      {
          string n;
           n = tokens[1];
           table.deleteEntry(n);
      }


    }
    }
    else if(c == 2)
    {
        cin.ignore();
    cout<<"\n I= insert P =print L=look up D=delete\n";
    string name;
    while(1){
      //cout << "Please, enter your full name: ";
      getline (cin,name);
      //cout << "Hello, " << name << "!\n";
      string buf;
      stringstream ss(name);
      vector<string>tokens;
      while(ss>>buf)
      {
          tokens.push_back(buf);
      }
      //cout<<tokens[0]<<tokens[1]<<tokens[2]<<endl;
      string option = tokens[0];
      if(option == "I")
      {
            string n, t;
            n = tokens[1];
            t = tokens[2];
            SymbolInfo sym(n,t);
            table.insert(sym);
      }
      else if(option == "P")
      {
          table.printTable();
      }
      else if(option == "L")
      {
           string n;
           n = tokens[1];
           table.lookUp(n);
      }
      else if(option == "D")
      {
          string n;
           n = tokens[1];
           table.deleteEntry(n);
      }

    }
    }



    return 0;
}


