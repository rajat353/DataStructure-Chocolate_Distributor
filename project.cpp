#include<iostream>
#include<stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include<vector>
#include<iterator>
#include<utility>
#include<time.h>
#include<queue>
#include<stdlib.h>
#include<windows.h>
#define PI 3.14159265
# define INF 0x3f3f3f3f
using namespace std;
int error=0;
typedef pair<int,int> iPair;
COORD coord={0,0};
void gotoxy(int x,int y)
 {
   coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }
//All the classes
class Manager;
class citymap;
class item;
class category;
class distributor;

void displayGraph(vector<pair<int,int> > arr[],int n);
void primMST(vector<pair<int,int> > adj[], int V);
void dijkstra(vector<pair<int,int> > adj[],int graph[11][11], int src, int des,citymap Delhi);

class Manager
{ char *name;
  char *password;
  public:
      char* getName(){return name;}
      bool verifyLogin(char *pass);
      Manager(char name[],char newp[]);
};
class item
{
    char *name;
    int quantity;
    int price;
    item *next;
    public:
        item();
        item(char[],int,int);
        void display(int,int);
        void increase(int q){quantity+=q;}
        void decrease(int q){quantity-=q;}
        void setnext(item *a){next=a;}
        char* getname(){return name;}
        item* getnext(){return next;}
        int getQuantity(){return quantity;}
        int getPrice(){return price;}
};

class category
{
    char *name;
    item *first;
    item *last;
    category *next;
    int total;
    public:
        category();
        category(char[]);
        void addItem(char[],int,int);
        void shipItem(char[],int);
        void display(int,int);
        void shipCheap();
        char* getname(){return name;}
        category* getnext(){return next;}
        void setnext(category *a){next=a;}
        item* getfirst(){return first;}

};
class distributor
{ char *name;
  category *first;
  category *last;
  int total;
  Manager *manager;
  public:
      distributor(char[],char[],char[]);
      void addCategory(char[]);
      void addItem(char[],char[],int,int);
      void shipItem(char[],char[],int);
      void shipAll(char[]);
      void shipCheap();  //ship Cheapest item in all categories
      void display();
      Manager* getManager(){return manager;}
};
class citymap
{       char index[11][30];

public:
    vector< pair<int,int> > arr[11];
    citymap()
    {
        strcpy(index[0],"Gupta_Confectionery");
        strcpy(index[1],"Paul_Confectioners");
        strcpy(index[2],"Channa_Confectionery");
        strcpy(index[3],"Easy_Day");
        strcpy(index[4],"All_in_One_General_Store");
        strcpy(index[5],"Delhi_Delights_Confectioners");
        strcpy(index[6],"Rohini_General_Store");
        strcpy(index[7],"Balaji_General_Store");
        strcpy(index[8],"Choco_Street");
        strcpy(index[9],"Sindhi_Confectioners");
        strcpy(index[10],"Distibutor");
    }
    char* printshop(int i)
    {
        return index[i];
    }
    int getIndex(char ar[])
    {
        for(int i=0;i<11;i++)
            if(strcmp(ar,index[i])==0)
              return i;
        error=1;
    }
    void addEdge(int,int,int);
    void displayGraphCity(){displayGraph(arr,11);}

};
void citymap::addEdge(int u, int v,int weight)
{
    arr[u].push_back(make_pair(v,weight));
    arr[v].push_back(make_pair(u,weight));
}
Manager::Manager(char name[],char newp[])
{
this->name= new char[strlen(name)];
this->password=new char[strlen(newp)];
strcpy(this->name,name);
strcpy(this->password,newp);
}

void displayGraph(vector<pair<int,int> > arr[],int n)
{
    vector< pair<int,int> > coords;
    int maxX=200;int maxY=300;
    // The Coordinate set for the nodes
    coords.push_back(make_pair(160,140 ));
    coords.push_back(make_pair(500,180 ));
    coords.push_back(make_pair(150,400 ));
    coords.push_back(make_pair(80,300 ));
    coords.push_back(make_pair(80,80));
    coords.push_back(make_pair(510,270));
    coords.push_back(make_pair(350,420 ));
    coords.push_back(make_pair(200,220));
    coords.push_back(make_pair(440,50));
    coords.push_back(make_pair(480,420 ));
    coords.push_back(make_pair(320,310 ));

    vector< pair<int,int> >::iterator i;
    char str[5];
    for(int f=0;f<n;f++)
    {
        for(i = arr[f].begin();i <  arr[f].end();i++)
        {
            line(coords[f].first,coords[f].second,coords[(*i).first].first,coords[(*i).first].second);
            sprintf(str,"%d",(*i).second);
            outtextxy((coords[(*i).first].first + coords[f].first)/2 - 5,(coords[(*i).first].second + coords[f].second)/2 -7,str);
        }
    }


    char symbol[1];
    strcpy(symbol,"A");
    setbkcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    for(int i=0;i<coords.size();i++)
    {   if(i==0)
        {
        setbkcolor(RED);
        setfillstyle(SOLID_FILL,RED);
        setcolor(RED);
        circle(coords[i].first,coords[i].second,15);
        floodfill(coords[i].first+1,coords[i].second+1,RED);
        setcolor(BLACK);
        outtextxy(coords[i].first-5,coords[i].second-7,symbol);
        *symbol+=1;
        }
        else{
        setbkcolor(YELLOW);
        setfillstyle(SOLID_FILL,YELLOW);
        setcolor(YELLOW);
        circle(coords[i].first,coords[i].second,15);
        floodfill(coords[i].first+1,coords[i].second+1,YELLOW);
        setcolor(BLACK);
        outtextxy(coords[i].first-5,coords[i].second-7,symbol);
        *symbol+=1;
        }
    }
}
item::item()
{
    name=new char(7);
    strcpy(name,"item 1");
    quantity=0;
    next=NULL;
    price=0;
}
item::item(char nm[],int q,int p)
{
    name=new char(strlen(nm));
    strcpy(name,nm);
    quantity=q;
    price=p;
    next=NULL;
}
category::category()
{
  name=new char(15);
  strcpy(name,"category 1");
  first=NULL;
  last=NULL;
  next=NULL;
  total=0;
}
category::category(char nm[])
{
  name=new char(strlen(nm));
  strcpy(name,nm);
  first=NULL;
  last=NULL;
  next=NULL;
  total=0;
}
void category::addItem(char itemName[],int pr,int q)
{   int f=0;
  if(first==NULL)
  {
      item *a=new item(itemName,q,pr);
      first=a;
      last=a;
      total++;
      return;
  }
  item *temp=first;
  while(temp!=NULL)
  {
      if(strcmp(temp->getname(),itemName)==0)
      {
          temp->increase(q);
          f=1;
          return;
      }
      temp=temp->getnext();
  }
  if(f==0)
  { item *a=new item(itemName,q,pr);
     last->setnext(a);
     last=a;
     total++;
  }
}
void category::shipItem(char itemName[],int q)
{
  if(first==NULL)
  {   system("cls");
      error=1;
      gotoxy(40,13);
      cout<<"Item Not Available";
      _getch();
      return;
  }
  item *temp=first;
  while(temp!=NULL)
  {
      if(strcmp(temp->getname(),itemName)==0)
      {   if(temp->getQuantity() - q >0)
          { temp->decrease(q);
             _getch();

            return;
          }
          else
          {   system("cls");
                error=1;
                gotoxy(40,13);
              cout<<itemName<<" - Limited Stock";
              _getch();
              return;
          }
      }
      temp=temp->getnext();
  }

   system("cls");
      error=1;
      gotoxy(40,13);
      cout<<"--->Item Not Available<---";
      _getch();
}

void category::shipCheap()
{
  int f=0;
  if(first==NULL)
  {
      cout<<"\n\nNo Items in "<<name<<" category\n";
      return;
  }
  int minp=first->getPrice();
  item *temp;
  for(item *i1=first;i1!=NULL;i1=i1->getnext())
  {
      if(i1->getPrice()<minp)
      {minp=i1->getPrice();
       temp=i1;
      }
  }
  shipItem(temp->getname(),1);
}
distributor::distributor(char nm[],char man[],char ps[])
{   name=new char(strlen(nm));
  strcpy(name,nm);
  first=NULL;
  last=NULL;
  manager=new Manager(man,ps);
  total=0;
}
void distributor::addCategory(char categoryName[])
{
  int f=0;
  if(first==NULL)
  {
      category *a=new category(categoryName);
      first=a;
      last=a;
      total++;
      return;
  }
  category *temp=first;
  while(temp!=NULL)
  {
      if(strcmp(temp->getname(),categoryName)==0)
      {
          cout<<"\n\nCategory Already Exists !!\n";
          f=1;
          return;
      }
      temp=temp->getnext();
  }
  if(f==0)
  {  category *a=new category(categoryName);
     last->setnext(a);
     last=a;
     total++;
  }
}
void distributor::addItem(char categoryName[],char itm[],int p,int q)
{   int f=0;
  if(first==NULL)
  {
      addCategory(categoryName);
      addItem(categoryName,itm,p,q);
      return;
  }
  category *temp=first;
  while(temp!=NULL)
  {
      if(strcmp(temp->getname(),categoryName)==0)
      {
          temp->addItem(itm,p,q);
          f=1;
          return;
      }
      temp=temp->getnext();
  }
  if(f==0)
  {
      addCategory(categoryName);
      addItem(categoryName,itm,p,q);
  }
}
void distributor::shipItem(char categoryName[],char itemName[],int q)
{   int f=0;
  if(first==NULL)
  {   system("cls");
      gotoxy(40,13);
      cout<<"--->Item Not Available<---";
      error=1;
      _getch();
      return;
  }
  category *temp=first;
  while(temp!=NULL)
  {
      if(strcmp(temp->getname(),categoryName)==0)
      {
          temp->shipItem(itemName,q);
          f=1;
      }
      temp=temp->getnext();
  }
  if(f==0)
  {   system("cls");
      gotoxy(40,13);
      cout<<"--->No Such Category Exists !!<---";
      error=1;
      _getch();
      return;

  }
}
void distributor::shipAll(char categoryName[])
{
  int f=0;
  if(first==NULL)
  {

      cout<<"Category Not Available";
      return;
  }
  category *temp=first;
  while(temp!=NULL)
  {
      if(strcmp(temp->getname(),categoryName)==0)
      {
          f=1;
          break;
      }
      temp=temp->getnext();
  }
  for(item *i1=temp->getfirst();i1!=NULL;i1=i1->getnext())
  {
      temp->shipItem(i1->getname(),1);
  }


}

void distributor::shipCheap()
{
  category *temp;
  for(temp=first;temp!=NULL;temp=temp->getnext())
  {
      temp->shipCheap();
  }
}
void item::display(int x,int y)
{
    gotoxy(x,y);cout<<"Item : "<<name;
    gotoxy(x,y+1);cout<<"Quantity : "<<quantity;
    gotoxy(x,y+2);cout<<"Price : "<<price;
}
void category::display(int x,int y)
{   gotoxy(x+2,y); cout<<name;
  y+=2;
  for(item *temp=first;temp!=NULL;temp=temp->getnext())
  {
      temp->display(x,y);
      y+=5;

  }
}
void distributor::display()
{ system("cls");
  int x=2,y=2;
  for(category *temp=first;temp!=NULL;temp=temp->getnext())
  {
      temp->display(x,y);
      x+=21;
  }

  gotoxy(4,23);
}
void shipStock(distributor &D)
{   D.display();

    char cat[20],item[20];
    int q,p;
    gotoxy(4,23);
    cout<<"Choose which category to Ship Item From : ";
    gotoxy(4,24);
    cout<<"Choose which item to Ship : ";
    gotoxy(4,25);
    cout<<"Enter Quantity :";
    gotoxy(46,23); cin>>cat;
    gotoxy(35,24); cin>>item;
    gotoxy(22,25); cin>>q;
    D.shipItem(cat,item,q);

}
void makeShipment(distributor &D,citymap Delhi)
{


    int choice;
    do
    {  error=0;
        system("cls");
          gotoxy(30,4);
        cout<<"Enter 1 to make shipment to a particular shop";
        gotoxy(30,5);
        cout<<"Enter 2 to see the shortest path covering all shops";
        gotoxy(30,6);
        cout<<"Enter 0 to Go Back";
        gotoxy(30,12);
        cout<<"Enter Your Choice:- ";
        cin>>choice;
        int dest;
        int graph[11][11]={0};
        switch(choice)
        { case 1: shipStock(D);
                if(error==1)
                    return;
                char city[30];
                system("cls");
                cout<<"Shops are:- "<<Delhi.printshop(0)<<endl;
                    for (int i = 1; i < 11; i++)
                    {
                    cout<<"\t    ";
                    cout<<Delhi.printshop(i)<<endl;

                    }
                    cout<<"\n\n";
                cout<<"Enter the shop to visit- ";
                cin>>city;
                dest=Delhi.getIndex(city);
                if(error==1)
                {
                    system("cls");
                      gotoxy(40,13);
                      cout<<"--->No Such Shop Exists !!<---";
                      _getch();
                      continue;
                }
                dijkstra(Delhi.arr,graph,10,dest,Delhi);
                _getch();
                break;
          case 2: primMST(Delhi.arr,11);
                 break;
         default: return;
        }
    }while(choice !=0);


}

void addStock(distributor &D)
{   D.display();

    char cat[20],item[20];
    int q,p;
    gotoxy(4,23);
    cout<<"Choose which category to add ";
    gotoxy(4,24);
    cout<<"Choose which item to Add in Stock  ";
    gotoxy(4,25);
    cout<<"Enter Quantity  ";
    gotoxy(4,26);
    cout<<"Enter Price";
    gotoxy(35,23); cin>>cat;
    gotoxy(39,24); cin>>item;
    gotoxy(20,25); cin>>q;
    gotoxy(18,26); cin>>p;
    D.addItem(cat,item,p,q);
    D.display();

}

int getweight(vector< pair<int,int> > arr[],int a, int b)
{
    vector< pair<int,int> > :: iterator it;
    for(it=arr[a].begin(); it!=arr[a].end(); it++)
        if((*it).first==b)
           return(*it).second;
}
void addEdge(vector <pair<int, int> > adj[], int u,int v, int wt)
{
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

void primMST(vector<pair<int,int> > adj[], int V)
{

    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    vector< pair<int,int> > arr[11];

    int src = 0;
    vector<int> key(V, INF);

    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);
    pq.push(make_pair(0, src));
    key[src] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;
        for (auto x = adj[u].begin();x != adj[u].end();x++)
        {
            int v;
            int weight;
             v = (*x).first;
             weight =(*x).second;
            if (inMST[v] == false && key[v] > weight)
            {
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }

        }
    }
    for (int i = 1; i < V; ++i)
            {
                addEdge(arr,parent[i],i,getweight(adj,parent[i],i));
            }
    int gd=DETECT,gm;
    initgraph(&gd, &gm, "");
    displayGraph(arr,11);
    getch();
    closegraph();

}


int minDistance(int dist[],bool sptSet[])
{

    int min = INT_MAX, min_index;

    for (int v = 0; v < 11; v++)
        if (sptSet[v] == false &&
                   dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}
void printPath(citymap Delhi,int parent[], int j)
{

    if (parent[j] == - 1)
        return;

    printPath(Delhi,parent, parent[j]);
    cout<<"\n\t  |";
    cout<<"\n\t  |";
    cout<<"\n\t \\|/";
    printf("\n\t%s ", Delhi.printshop(j));
}
int printSolution(citymap Delhi,int dist[], int n,int parent[],int sr,int a)
{
    int src = sr;

    for (int i = 0; i < 11; i++)
    {   if(i == a)
       {
           cout<<"Total Distance= "<<dist[i]<<" Km"<<"\n\n";
           cout<<"Path:- \n\t"<<Delhi.printshop(src);
            printPath(Delhi,parent, i);
       }
    }
}
void dijkstra(vector<pair<int,int> > adj[],int graph[11][11], int src, int des,citymap Delhi)
{
    vector< pair<int,int> >:: iterator it;
    for(int i=0;i<11;i++)
    {
        for(it=adj[i].begin();it!=adj[i].end();it++)
        {
            graph[i][(*it).first]=(*it).second;
        }
    }
    int dist[11];
    bool sptSet[11];
    int parent[11];
    for (int i = 0; i < 11; i++)
    {
        parent[i] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;
    for (int count = 0; count < 11 - 1; count++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < 11; v++)
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    printSolution(Delhi,dist, 11, parent,src,des);
}
int main()
{
    distributor s1("Complex","utsav","utsav23");
    s1.addItem("Cadbury","Bournville",150,1500);
    s1.addItem("Cadbury","DairyMilk",10,1200);
    s1.addItem("FerreroRocher","GiftPack",475,800);
    s1.addItem("Nestle","Kitkat",10,1000);
    s1.addItem("Cadbury","DairyMilkSilk",200,1000);
    s1.addItem("Lindt","ExcellenceBar",270,1400);
    s1.addItem("Nestle","MilkyBar",10,1500);
    s1.addItem("Cadbury","DairyMilkCrackle",40,900);
    s1.addItem("Nestle","BarOne",20,1000);
    s1.addItem("Lindt","Lindor",150,800);
    s1.addItem("Hershey","GiftPack",350,500);

    citymap Delhi;
    Delhi.addEdge(0,4,15);
    Delhi.addEdge(0,3,23);
    Delhi.addEdge(4,8,50);
    Delhi.addEdge(3,4,25);
    Delhi.addEdge(7,8,35);
    Delhi.addEdge(0,1,40);
    Delhi.addEdge(1,8,20);
    Delhi.addEdge(7,2,17);
    Delhi.addEdge(7,10,5);
    Delhi.addEdge(2,10,8);
    Delhi.addEdge(6,5,17);
    Delhi.addEdge(1,10,15);
    Delhi.addEdge(2,3,13);
    Delhi.addEdge(6,10,10);
    Delhi.addEdge(6,9,10);
    Delhi.addEdge(9,5,15);
    Delhi.addEdge(1,5,20);
    Delhi.addEdge(0,7,13);

    int choice;
    do
    { system("cls");

    gotoxy(27,5);
    cout<<"*************************************************************";
    gotoxy(27,6);
    cout<<"             ---<  MANAGER ACCESS OF THE SHOP >---           ";
    gotoxy(27,8);
    cout<<"                          DESCRIPTION                        ";
    gotoxy(27,10);
    cout<<"         The access program includes many features and       ";
    gotoxy(27,11);
    cout<<"            the manager has access to many functions         ";
    gotoxy(27,12);
    cout<<"                    Choose the functionality                 ";
    gotoxy(27,14);
    cout<<"             (1) See City Map                                ";
    gotoxy(27,16);
    cout<<"             (2) Check Stock                                 ";
    gotoxy(27,18);
    cout<<"             (3) Add Items to the Stock                      ";
    gotoxy(27,20);
    cout<<"             (4) Make a Shipment                             ";
    gotoxy(27,22);
    cout<<"             Please Enter Your Choice Here                   ";
    gotoxy(27,24);
    cout<<"*************************************************************";
    for(int i=6;i<24;i++)
    {
        gotoxy(27,i);
        cout<<"*";
        gotoxy(87,i);
        cout<<"*";
    }
    int gd=DETECT,gm;
    gotoxy(70,22);
    cin>>choice;
    error=0;
    switch(choice)
    {   case 1:
                initgraph(&gd, &gm, "");
                Delhi.displayGraphCity();
                getch();
                closegraph();
                break;
        case 2: s1.display();
                system("pause");
                break;
        case 3: addStock(s1);
                system("pause");
                break;
        case 4: makeShipment(s1,Delhi);
                break;
        default: return 0;

    }
    }while(choice != 0);


    _getch();
    return 0;

}
