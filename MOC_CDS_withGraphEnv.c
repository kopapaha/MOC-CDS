#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


#define opengl

#ifdef opengl
#include <GL/glut.h>

/************************************************	*********************************************************************
VHMATA
1. pros8hkh komvwn
2. diasindesh komvwn
3. telikos graphos (aristero klik)
********************************	*************************************************************************************/
#define ADDNODES 1
#define DRAWNODES 2
#define OK 3


int screenWidth = 640;
int screenHeight = 480;

int menu; // for menu creation
int sel; // for menu choices

int timesPushed=0; //aristero klik pontiki

int ** graph;  //telikos graphos diktyou
#endif



#ifdef opengl
extern  void startAlgo();

struct coord
{
	int x,y;
};
struct coord *node; //pinakas me syntetagnenes komvwn sto para8yro

int nofNodes=0;
int *f;

/************************************************************************************************************************
		openGL functions
*************************************************************************************************************************/
void mainDisplay(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();

}

void init(){
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,640,0, 480); 
	glClearColor(0,0,0,0);
  	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(16);
	glFlush();
	

}


void keyEvent(unsigned char key, int x, int y)
{


  switch (key)
  {
	//Quit
	case 'Q':
	case 'q':
	exit(-1);
	break;
	case 'c':
		startAlgo();
	default:
	break;	
  }
}



void addNewNode(GLint x, GLint y)
{
	node= (struct coord *)realloc(node,(timesPushed+1)*sizeof(struct coord));
	node[timesPushed].x=x;
	node[timesPushed].y=y;
}


void drawNewNode()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	//glBegin (GL_LINE_LOOP);
	glColor3f(1,1,1);
	
	glVertex2i(node[timesPushed].x, node[timesPushed].y);


	glEnd();

	glColor3f(0,0,0);
	//glRasterPos2f(node[timesPushed].x-3, node[timesPushed].y-3);

	if (timesPushed>9)
	{
		glRasterPos2f(node[timesPushed].x-3, node[timesPushed].y-3);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48+(timesPushed/10));
		glRasterPos2f(node[timesPushed].x+2, node[timesPushed].y-3);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48+(timesPushed%10));

		
	}
	else
	{
		glRasterPos2f(node[timesPushed].x-3, node[timesPushed].y-3);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48+timesPushed);

	}
	//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48+timesPushed);

	glFlush();
}


void myMouse(int button, int state, GLint x, GLint y)
{
		int i,j,tol=20;
		static int time=0,firstSel2;
		static int fx,fy,tx,ty;	
		static int f_node, t_node;
		static int mallocV=1;
		int **tempGraph;
		static int prevSize=0;

	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN&&sel==ADDNODES)
	{
		addNewNode(x, screenHeight - y);
		//if (timesPushed==2){printf("node0! %d ", node[0].x);}
		printf("%d ", node[timesPushed].x);
		printf("%d \n", node[timesPushed].y);
		drawNewNode();

		timesPushed++;
		nofNodes = timesPushed;
		//drawNode(timesPushed);
		
		firstSel2=1;
	
	}
	else if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN&&sel==DRAWNODES)
	{
		//desmefsh mnhmhs grafou diashndeshs
		if(firstSel2)
		{
			

			//graph = (int **)realloc(graph, timesPushed*sizeof(int *));
			//for(i=0;i<timesPushed;i++)
			//{
			//	graph[i]=(int *)realloc(graph[i], timesPushed*sizeof(int));
			//}
			if (mallocV)
			{
				graph = (int **)malloc(timesPushed*sizeof(int *));
				for(i=0;i<timesPushed;i++)
				{
					graph[i]=(int *)malloc( timesPushed*sizeof(int));
				}
				mallocV=0;
			}
			else
			{
				/*printf("pushed %d\n", timesPushed);
				printf("REALLOC\n");
				graph = (int **)realloc(graph, timesPushed*sizeof(int *));
				if (graph==NULL) {printf("NULL1");}
				for(i=0;i<timesPushed;i++)
				{
					graph[i]=(int *)realloc(graph[i], timesPushed*sizeof(int));
					if (graph[i]==NULL) {printf("NULL1");}
				}
				printf("REALLOC1\n");*/
				tempGraph = (int **)malloc(timesPushed*sizeof(int *));

				for(i=0;i<timesPushed;i++)
				{
					tempGraph[i]=(int *)malloc( timesPushed*sizeof(int));

				}
				for (i=0;i<prevSize;i++)
				{
					for(j=0;j<prevSize;j++)
					{
						tempGraph[i][j]=graph[i][j];
				
					}
				}
				free(graph);
				graph=tempGraph;
				

			}

			firstSel2=0;
		}


		for(i=0;i<timesPushed;i++){
			if ((x > node[i].x-tol)&& ((screenHeight -y)< node[i].y + tol)&& (x < node[i].x+tol)&& ((screenHeight -y) > node[i].y-tol))
			{
	
				
				switch (time%2) 
				{
				case 0:
					//printf("gg0\n");
					fx = node[i].x;
					fy = node[i].y;
					f_node=i;
					break;
				case 1:
					//printf("gg1\n");
					
					tx = node[i].x;
					ty = node[i].y;
					t_node=i;

					glBegin(GL_LINES);
					glColor3f(1,1,1);
		
					glVertex2i(fx, fy);
					glVertex2i(tx, ty);

					glEnd();


					graph[f_node][t_node]=1;
					graph[t_node][f_node]=1;

					glColor3f(0,0,0);


					if (f_node>9)
					{
						glRasterPos2f(node[f_node].x-3, node[f_node].y-3);
						glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48+(f_node/10));
						glRasterPos2f(node[f_node].x+2, node[f_node].y-3);
						glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48+(f_node%10));
	
					}						
					else
					{
						glRasterPos2f(node[f_node].x-3, node[f_node].y-3);
						glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48+f_node);

					}
					if (t_node>9)
					{
						glRasterPos2f(node[t_node].x-3, node[t_node].y-3);
						glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48+(t_node/10));
						glRasterPos2f(node[t_node].x+2, node[t_node].y-3);
						glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48+(t_node%10));
	
					}						
					else
					{
						glRasterPos2f(node[t_node].x-3, node[t_node].y-3);
						glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48+t_node);

					}
					break;
				}
				time++;


			}
		}


		glFlush();
	}
	else if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN&&sel==OK)
	{
		prevSize=timesPushed;
		for (i=0;i<timesPushed;i++)
		{
			for(j=0;j<timesPushed;j++)
			{
				if (i==j)
					graph[i][j]=0;

				if (graph[i][j]!=1)
					graph[i][j]=0;
				
			}
		}

		printf("\nTelikos Grafos:\n");
		for (i=0;i<timesPushed;i++)
		{
			for(j=0;j<timesPushed;j++)
			{
				printf("%d ",graph[i][j]);
				
			}
			printf("\n");
		}


	}
}


void myMenu(int selection)
{
	if(selection==ADDNODES) 
	{
		//glutPostRedisplay(); 
		sel=ADDNODES;
		
	}
	if(selection==2)
	{
		sel=DRAWNODES;
	}
	if(selection==OK) 
	{
		//printf("ar komv %d ",timesPushed);
		
		sel=OK;
		
	}
}

#endif



#ifndef opengl

//#define nofNodes 3 //number of nodes
//int graph[nofNodes][nofNodes]={
//				{0,1,1},
//				{1,0,0},
//				{1,0,0}
//		};

//#define nofNodes 5 //number of nodes
//int graph[nofNodes][nofNodes]={
//				{0,1,1},
//				{1,0,1},
//				{1,1,0}
//				};

//#define nofNodes 5 //number of nodes
//int graph[nofNodes][nofNodes]={
//				{0,1,1,1,0},
//				{1,0,0,0,0},
//				{1,0,0,1,1},
//				{1,0,1,0,0},
//				{0,0,1,0,0}
//				};

#define nofNodes 7 //number of nodes
int graph[nofNodes][nofNodes]={
				{0,1,0,0,1,1,0},
				{1,0,1,1,0,0,0},
				{0,1,0,0,0,0,0},
				{0,1,0,0,0,1,0},
				{1,0,0,0,0,1,1},
				{1,0,0,1,1,0,0},
				{0,0,0,0,1,0,0}
				};


//#define nofNodes  20 //number of nodes
//int graph[nofNodes][nofNodes]={
//{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//{1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//{0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0},
//{0 ,0 ,0 ,1 ,0 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
//},
//{0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
//},
//{0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
//},
//{0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
//},
//{0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0
//},
//{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
//},
//{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0
//},
//{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
//},
//{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
//},
//{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0
//},
//{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,0
//},
//{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,1 ,0 ,0
//},
//{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,1 ,1
//},
//{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,1 ,0
//},
//{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0
//},
//{0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0}
//};






int f[nofNodes];

#endif

struct nodesP
{
	int x,y;
	struct nodesP *nxt;
};

struct nodesP **P;


struct nodes 
{
	int id;
	int black;
	int *fpool; //a table that keeps all collected f's
	int *flagstab;   //if node received flag from node i then flagstab[i]=1 else 0
	struct nodesP **P;
	struct nodes *nxt;
};

struct nodes *nodestab;




/*****
****** pros8hkh komvwn (j,check) sto P tou komvou i
****** to struct mpainei sthn arxh ths listas
******/
void add2P (struct nodesP **Pi, int x, int y)
{
	struct nodesP *s;

	s = (struct nodesP *) malloc(sizeof(struct nodesP));
	s->x=x;
	s->y=y;

	if(Pi==NULL)
	{
		*Pi=s;
		s->nxt=NULL;
	}
	else
	{
		s->nxt=*Pi;	
		*Pi=s;
	}
	
}








void deleteP(int i,int x,int y){

struct nodesP *curr,*prev;

for(prev=NULL,curr=P[i]; (curr != NULL) && ((curr->x != x) || (curr->y != y) );
prev=curr,curr=curr->nxt);
if (curr != NULL) {
	if (prev == NULL) {
		P[i] = curr->nxt;
}
    else {
		prev->nxt = curr->nxt;
	}
	//free(curr);
}
}



void computeP()
{
	int i, j, check;


	P = (struct nodesP **)malloc(nofNodes*sizeof(struct nodesP *));
	for (i=0; i<nofNodes; i++)
	{
		P[i]=NULL;
	}

	//ypologismos tou P
	for (i=0; i<nofNodes; i++)
	{
		for(j=0; j<nofNodes; j++)
		{
			if(graph[i][j])
			{
				for(check=(j+1); check<nofNodes; check++)
				{
					if(graph[i][check])
					{
						if(!graph[j][check])
						{
							add2P(&P[i], j, check);
							f[i]++;
						}
					}
				}
			}
		}
	}

}


void intersectionP(int x,int y){//tomi twn P[x] kai P[y]
	struct nodesP *l1;
	struct nodesP *l2;
	//printf("Computing intersection of P[%d] to P[%d]!\n",x,y);

	for(l1=P[x];l1!=NULL;l1=l1->nxt){
		for(l2=P[y];l2!=NULL;l2=l2->nxt){
			if(l1->x==l2->x && l1->y==l2->y){printf("Deleting (%d,%d) from P[%d]!\n",l2->x,l2->y,y);
			deleteP(y,l2->x,l2->y);}
		}
	}
}





void send2(int x,int y,char *str,int val){
	int j;
	printf("%d send %s to %d!\n",x,str,y);
	if(!strcmp(str,"f")){
		nodestab[y].fpool[x]=val;}
	if(!strcmp(str,"flag")){
		nodestab[y].flagstab[x]=1;}
	if(!strcmp(str,"P")){//val keeps from which node is the current P
		if(x==val){//Tote to P einai tou geitnona pou to esteile, ara to stelnei se olous tous geitones tou
			for(j=0;j<nofNodes;j++){
				if(graph[y][j] && j!=x){send2(y,j,"P",x);}
			}
		}
		else{//Tote to P den einai tou geitona ara prepei na ypologisw tin tomi tou P pou stalthike me to P tou komvou
			intersectionP(val,y);}
	}
			
}

int check(){ //Check if the algorithm ends
	int i;
	
	for(i=0; i<nofNodes; i++){
		if(f[i]>0){return 0;}
	}
	return 1;
}

void computef(){
	int i;
	struct nodesP *l;
	for(i=0; i<nofNodes; i++){
		f[i]=0;
		for(l=P[i];l!=NULL;l=l->nxt){
			f[i]++;}
	}
}






void startAlgo(void)
{
  int i,j,k,max,maxid,flags,count;
  struct nodesP *l;
  int *nofnbrs;	
  count=0;


#ifdef opengl
	f = (int *)malloc(nofNodes*sizeof(int));
#endif
	nodestab = (struct nodes *) malloc(nofNodes*sizeof(struct nodes));
	for (i=0;i<nofNodes;i++)
	{
		nodestab[i].fpool = (int *) malloc(nofNodes*sizeof(int));
		nodestab[i].flagstab = (int *) malloc(nofNodes*sizeof(int));
	}
	nofnbrs = (int *)malloc(nofNodes*sizeof(int));

	for (i=0;i<nofNodes;i++)
	{
		f[i]=0;
		nofnbrs[i]=0;
		nodestab[i].black=0;
		//nodestab[i].
		for(j=0;j<nofNodes;j++)
		{
			nodestab[i].fpool[j]=0;
			nodestab[i].flagstab[j]=0;
		}
		
	}


//#endif
	
  //ektypwsh topologias diktyou
  printf("\nGrafos eisagwghs:\n");
  for(i=0;i<nofNodes;i++)
  {
	  for(j=0;j<nofNodes;j++)
	  {
		  printf("%d ",graph[i][j]);
	  }
	  printf("\n");
  }


	//Arxikopoisi
  for(i=0;i<nofNodes;i++){
	  nodestab[i].id=i;
      nodestab[i].black=0;}
  //counting number of neighbours of every node
  for(i=0;i<nofNodes;i++){
	  nofnbrs[i]=0;
	  for(j=0;j<nofNodes;j++){
		  if(graph[i][j]){nofnbrs[i]++;}
	  }
  }



  //Step 1
  for(i=0;i<nofNodes;i++)
  {
	  f[i]=0;
  }

  
  computeP();

  printf("Pinakas f: \n");
  for(i=0;i<nofNodes;i++)
  {
	  printf("%d ", f[i]);
  }
  
  printf("\nP:\n");
  for(i=0;i<nofNodes;i++){
	  printf("node[%d]: ",i);
	  for(l=P[i];l!=NULL;l=l->nxt)
	  {
		  printf("(%d %d) ",l->x,l->y);
	  }
	  printf("\n");
  }

  while(!check()){

	  //Arxikopoiisi gia kathe epanalipsi
	  for(i=0;i<nofNodes;i++){
		  for(j=0;j<nofNodes;j++){
			nodestab[i].flagstab[j]=0;
			nodestab[i].fpool[j]=0;
		  }
	  }
	  count++;
	  computef();

  //Send f's
  for(i=0;i<nofNodes;i++){
	  for(j=0;j<nofNodes;j++){
		  if(graph[i][j]){
			  send2(i,j,"f",f[i]);}
	  }
  }

  /*
  for(i=0;i<nofNodes;i++){
	  for(j=0;j<nofNodes;j++){
		  printf("%d)fpool[%d]=%d\n",i,j,nodestab[i].fpool[j]);}
  }
  */

  //Step 2
  //Send flag to the neighbor with greatest f
  for(i=0;i<nofNodes;i++){
	  max=0;
      maxid=0;
	  for(j=0;j<nofNodes;j++){
		  if(nodestab[i].fpool[j]>max){max=nodestab[i].fpool[j];maxid=j;}
		  else if(nodestab[i].fpool[j]==max && j>maxid){max=nodestab[i].fpool[j];maxid=j;}
	  }
	  if(graph[i][maxid] && nodestab[i].fpool[maxid]!=0){send2(i,maxid,"flag",1);}
  }
  /*
   for(i=0;i<nofNodes;i++){
	  for(j=0;j<nofNodes;j++){
		  printf("%d)flagstab[%d]=%d\n",i,j,nodestab[i].flagstab[j]);}
  }
  */
  
  //Step 3
  //If flags=nofnbrs then node=black
  for(i=0;i<nofNodes;i++){
	  flags=0;//printf("flagstab=");
	  for(j=0;j<nofNodes;j++){//printf(" %d ",nodestab[i].flagstab[j]);
		  if(nodestab[i].flagstab[j]){flags++;}
	  }
	  //printf("\n");
	  //printf("%d)neighbors=%d\n",i,nofnbrs[i]);
	  if(flags==nofnbrs[i]){nodestab[i].black=1;printf("%d node is black!\n",i);
#ifdef opengl
	  Sleep(500);
	  	glBegin(GL_POINTS);
			glColor3f(0,1,1);
			glVertex2i(node[i].x, node[i].y);
			


		glEnd();
		
		glColor3f(0,0,0);

			if (i>9)
			{
				glRasterPos2f(node[i].x-3, node[i].y-3);
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48+(i/10));
				glRasterPos2f(node[i].x+2, node[i].y-3);
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48+(i%10));

		
			}
			else
			{
				glRasterPos2f(node[i].x-3, node[i].y-3);
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 48+i);

			}
			glFlush();
#endif
	  //Step 4,5
	  for(k=0;k<nofNodes;k++){
				if(graph[i][k]){send2(i,k,"P",i);}
			}
	  for(l=P[i];l!=NULL;l=l->nxt){deleteP(i,l->x,l->y);}   //P=0
	  //f[i]=0;
	  }
	  //else{nodestab[i].black=0;}
  }

  //for(i=0;i<nofNodes;i++){printf("%d)black?=%d\n",i,nodestab[i].black);}

  //Steps 4,5 in send function

  //Print Information
  printf("Epanalipsi %d\n",count);
  printf("Pinakas f: \n");
  for(i=0;i<nofNodes;i++)
  {
	  printf("%d ", f[i]);
  }

  printf("\nP:\n");
  for(i=0;i<nofNodes;i++){
	  printf("node[%d]: ",i);
	  for(l=P[i];l!=NULL;l=l->nxt)
	  {
		  printf("(%d %d) ",l->x,l->y);
	  }
	  printf("\n");
  }
  for(i=0;i<nofNodes;i++){printf("%d)black?=%d\n",i,nodestab[i].black);}
  for(i=0;i<nofNodes;i++){
  computef();
  }
  
}
//  exit(-1);

}


/************************************************************************************************************************
				Minimum Routing Cost - Connected Dominating Sets
*************************************************************************************************************************/

int main (int argc, char *argv[]){



#ifdef opengl
  glutInit(&argc, argv);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutCreateWindow("moc-cds");
  init();

  glutDisplayFunc(mainDisplay);
  glutKeyboardFunc(keyEvent);
  glutMouseFunc(myMouse);



    // menu creation
  menu = glutCreateMenu(myMenu);

  glutAddMenuEntry("Προσθήκη κόμβων", ADDNODES);
  glutAddMenuEntry("Διασύνδεση κόμβων", DRAWNODES);
  glutAddMenuEntry("Τελικός γράφος",OK);
	
  // register menu to right mouse button
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();

  free(node);
  free (graph);
#endif

#ifndef opengl

  startAlgo();
#endif
  
}