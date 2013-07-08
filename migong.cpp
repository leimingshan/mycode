#include <iostream>
#include <stdlib.h>

#define STACK_INIT_SIZE 100  //´æ´¢¿Õ¼ä³õÊ¼·ÖÅäÁ¿ 
#define STACKINCREAMENT 10 //´æ´¢¿Õ¼ä·ÖÅäÔöÁ¿

#define SIZE_OF_MAPH 20 //ÃÔ¹¬¸ß¶È 
#define SIZE_OF_MAPW 20 //ÃÔ¹¬³¤¶È 

using namespace std;

// MazeCell¹¦ÄÜ£ºÓÃÀ´ÃèÊöÃÔ¹¬×é³Éµ¥ÔªµÄÐÅÏ¢ 
typedef struct 
{ 
	int Pass; 		 // Pass: µ±PassÎª1Ê±£¬±íÊ¾µ¼Í¨¿é£»Îª0Ôò±íÊ¾ÕÏ°­¿é£» 
	bool Footprint; // Footprint: µ± FootprintÎª1Ê±£¬±íÊ¾ÁôÏÂ×ã¼££¬·´Ö®£¬±íÊ¾Î´¾­´ËµØ¡£ 
}MazeCell; 

// SElemType¹¦ÄÜ£º ´ËÎªÕ»µÄÔªËØ£¬ÓÃÀ´±íÊ¾µ±Ç°Î»ÖÃ£¬£¨Õ»ÓÃÀ´ÃèÊöµ±Ç°Â·¾¶£© 
typedef struct 
{ 
	int ord; 		// ord: Í¨µÀ¿éµÄÐòºÅ
	int x; 		// x : µ±Ç°Î»ÖÃµÄºá×ø±ê
	int y; 		// y : µ±Ç°Î»ÖÃµÄ×Ý×ø±ê
	int di; 		// di : ËÑË÷·½Ïò 1Ïò¶«£¬2ÏòÄÏ£¬3ÏòÎ÷£¬4Ïò±±
}SElemType; 

// SqTack¹¦ÄÜ£º ´ËÎªÕ»£¬ÓÃÀ´¼ÇÂ¼µ±Ç°Â·¾¶
typedef struct 
{ 
	SElemType *base; 		// *base Õ»µ×Ö¸Õë£¬Ö¸ÏòÆðµã
	SElemType *top; 		// *top Õ»¶¥Ö¸Õë£¬Ö¸ÏòÂ·¾¶µÄÄ©µã
	int stacksize; 			// stacksize Õ»µÄÈÝÁ¿
}SqStack; 

// Seat¹¦ÄÜ£º ÓÃÀ´¼ÇÂ¼ÃÔ¹¬×ø±ê£¬´Ë½á¹¹ÌåÎªÖÐ¼ä±äÁ¿£¬´¿´âÎª·½±ã±à³Ì¶ø½¨Á¢
typedef struct 
{ 
	int x; 		// x: ÓÃÀ´¼ÇÂ¼ºá×ø±ê
	int y; 		// y: ÓÃÀ´¼ÇÂ¼×Ý×ø±ê
}Seat; 

// InitStack¹¦ÄÜ£º´Ëº¯ÊýÓÃÓÚ¹¹ÔìÒ»¸ö¿ÕÕ»£¬·ÖÅä³õÊ¼¿Õ¼ä
// º¯Êý²ÎÊý£º SqStack &S
// º¯Êý·µ»ØÖµÀàÐÍ£º bool
bool InitStack(SqStack &S) 		
{ 							
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType)); 
	if(!S.base)  
		exit(1); 

	S.top=S.base; 
	S.stacksize=STACK_INIT_SIZE; 
	return 0; 
} 

// InputMaze¹¦ÄÜ£º ÏòÊý×éÀïÊäÈëÔªËØ
// ·µ»ØÖµÀàÐÍ£ºÎÞ
void InputMaze(int map[][SIZE_OF_MAPW], int &line, int &column) 
{ 
	int w,h;
	cout<<"ÇëÊäÈëÃÔ¹¬µÄÐÐÊý(ÐÐÊýÐ¡ÓÚµÈÓÚ"<<SIZE_OF_MAPH<<")£º"<<endl;
	cin>>h;
	cout<<"ÇëÊäÈëÃÔ¹¬µÄÁÐÊý(ÁÐÊýÐ¡ÓÚµÈÓÚ"<<SIZE_OF_MAPW<<")£º"<<endl;
	cin>>w;

	cout<<"1±íÊ¾µ¼Í¨¿é£»0±íÊ¾ÕÏ°­¿é"<<endl;
	
	for (int i = 0; i < h; i++) {
		cout<<"ÇëÊäÈëµÚ"<<i<<"ÐÐ:"<<endl;
		for (int j = 0; j < w; j++)
			cin>>map[i][j];
	}
	line = h;
	column = w;
} 

// BuideMaze¹¦ÄÜ£º ´Ëº¯ÊýµÄ¹¦ÄÜÊÇÓÃÓÚ¸ù¾ÝÓÃ»§ÒªÇó½¨Á¢Ò»¸öÃÔ¹¬µØÍ¼£¬½«ÓÃ»§ÊäÈëµÄ// ÕûÐÎÊý×éÐÎ×´¸øÃÔ¹¬Êý×é 		
// º¯Êý²ÎÊý£º MazeCell Map[SIZE_OF_MA[SIZE_OF_MAP]
// Seat &start Æðµã×ø±ê 
// Seat &end ÖÕµã×ø±ê
// º¯Êý·µ»ØÖµÀàÐÍ£º bool ½¨Á¢³É¹¦Ôò·µ»Ø1£¬·´Ö®·µ»Ø0¡£
void BuideMaze(MazeCell	Map[SIZE_OF_MAPH][SIZE_OF_MAPW], int ma[SIZE_OF_MAPH][SIZE_OF_MAPW])
{ 
	for(int i=0;i<SIZE_OF_MAPH;i++) 
	{ 
		for(int j=0;j<SIZE_OF_MAPW;j++) 
		{ 
			Map[i][j].Pass=ma[i][j]; 
			Map[i][j].Footprint=0; 
		} 
	} 
} 

// Pass¹¦ÄÜ£º ´Ëº¯ÊýÓÃÓÚÅÐ¶Ïµ±Ç°µãÊÇ·ñ¿ÉÍ¨£¬Èç¹û¿ÉÍ¨Ôò·µ»Ø1£¬·´Ö®·µ»Ø0¡£
bool Pass(Seat curpos,MazeCell Map[SIZE_OF_MAPH][SIZE_OF_MAPW]) 
{ 
	// ²ÎÊýSeat curpos µ±Ç°¿éµÄ×ø±ê£¬
	// MazeCell Map[SIZE_OF_MAP][SIZE_OF_MAP] ÃÔ¹¬µØÍ¼
	// º¯Êý·µ»ØÖµÀàÐÍ£º bool Èôµ±Ç°¿é¿ÉÍ¨Ôò·µ»Ø1£¬·´Ö®Ôò·µ»Ø0¡£
	if(Map[curpos.x][curpos.y].Pass==0) 
		return 0; 
	else if(Map[curpos.x][curpos.y].Footprint==1) 
		return 0; 
	else 
		return 1; 
} 

// FootPrint¹¦ÄÜ£º ´Ëº¯ÊýÓÃÓÚÔÚµ±Ç°Â·¾¶ÏÂÁôÏÂ½ÅÓ¡¡£
// Seat curpos µ±Ç°×ø±ê
// MazeCell Map[SIZE_OF_MAP][SIZE_OF_MAP] ÃÔ¹¬µØÍ¼ 
// º¯Êý·µ»ØÖµÀàÐÍ£º ÎÞ 
void FootPrint(Seat curpos,MazeCell Map[SIZE_OF_MAPH][SIZE_OF_MAPW]) 
{ 
	Map[curpos.x][curpos.y].Footprint=1; 
} 

//ÈëÕ»²Ù×÷£º²åÈëÔªËØeÎªÐÂµÄÕ»¶¥ÔªËØ
bool Push(SqStack &S,SElemType e)
{ 
	if(S.top-S.base>=S.stacksize) 
	{ 
		S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREAMENT)*sizeof(SElemType)); 
		if(!S.base) 
		{ 
			return 0; 
		} 
		S.top=S.base+S.stacksize; 
		S.stacksize=S.stacksize+STACKINCREAMENT; 
	} 
	*S.top++=e; 
	return 1; 
}

//³öÕ»²Ù×÷£ºÈôÕ»²»¿Õ£¬ÔòÉ¾³ýSµÄÕ»¶¥ÔªËØ£¬ÓÃe·µ»ØÆäÖµ£¬²¢·µ»Øtrue£»·ñÔò·µ»Øfalse
bool Pop(SqStack &S,SElemType &e)
{ 
	if(S.base==S.top)
		return false; 
	S.top--; 
	e=*S.top; 
	return true; 
} 

// NextPos¹¦ÄÜ£º ´Ëº¯ÊýÓÃÓÚ½«×ø±êÎªx,yÎ»ÖÃµÄdi·½ÏòÎ»ÖÃÇÐ»»Îªµ±Ç°Î»ÖÃ¡£
// Seat curpos µ±Ç°×ø±ê£¬ int di ·½Ïò£¬int x,y ×ø±ê£¬º¯Êý·µ»ØÖµÀàÐÍ£º ÎÞ
void NextPos(int x,int y,Seat &curpos,int di) 
{
	switch(di) {
	case 1:
		curpos.y=y+1; 
		curpos.x=x; 
		break;
	case 2:
		curpos.x=x+1; 
		curpos.y=y; 
		break;
	case 3:
		curpos.y=y-1; 
		curpos.x=x; 
		break;
	case 4:
		curpos.x=x-1; 
		curpos.y=y; 
		break;
	}
} 

// Display¹¦ÄÜ£º ÓÃÓÚÏÔÊ¾Õ»ÖÐËùÓÐÔªËØ
void DisplayStack(SqStack S) 
{ 
	int i=1; 
	SElemType *p; 
	p=S.base;
	cout<<"diËÑË÷·½Ïò:di=1Ïò¶«£¬di=2ÏòÄÏ£¬di=3ÏòÎ÷£¬di=4Ïò±±"<<endl; 
	while(p!=S.top) //´Óbaseµ½top´òÓ¡ÔªËØ 
	{ 
		cout<<"µÚ"<<i<<"²½: "; 
		cout<<"("<<(*p).y; 
		cout<<","<<(*p).x<<",";
		switch((*p).di) {
		case 1:
			cout<<"ÓÒ";
			break;
		case 2:
			cout<<"ÏÂ";
			break;
		case 3:
			cout<<"×ó";
			break;
		case 4:
			cout<<"ÉÏ";
			break;
		}
		cout<<")"<<endl; 
		p++; 
		i++; 
	} 
} 

void DisplayMaze(int map[SIZE_OF_MAPH][SIZE_OF_MAPW], int line, int column) 
{ 
	cout<<"ÃÔ¹¬Îª(1´ú±í¿ÉÒÔÍ¨¹ý£»0´ú±í²»¿ÉÒÔÍ¨¹ý): "<<endl; 
	for(int i = 0; i < line; i++) 
	{ 
		for(int j = 0; j < column; j++) 
		{ 
			cout<<map[i][j]<<" "; 
		} 
		cout<<endl; 
	} 
	cout<<endl; 
} 


// MazePath¹¦ÄÜ£º ×éÖ¯ËùÓÐ×Óº¯Êý£¬Çó½âÃÔ¹¬
// º¯Êý·µ»ØÖµÀàÐÍ£º int ÃÔ¹¬ÓÐ½âÔò·µ»Ø1£¬·´Ö®Ôò·µ»Ø0£»
int MazePath(MazeCell Map[SIZE_OF_MAPH][SIZE_OF_MAPW],Seat start,Seat end) 
{ 
	SElemType e; 
	SqStack S; //¶¨ÒåÒ»¸öÕ» 
	InitStack(S); //³õÊ¼»¯Õ» 
	Seat curpos; //¶¨Òåµ±Ç°Î»ÖÃ 
	int curstep; //¼Æ²½Æ÷ 
	curstep=1; //¼Æ²½Æ÷¼Æ1 
	curpos.x=start.x; // 
	curpos.y=start.y; //µ±Ç°Î»ÖÃÉèÎªÆðµã 
	cout<<"ÆðµãÊÇ:"<<start.y<<" "<<start.x<<endl; 
	cout<<"ÖÕµãÊÇ:"<<end.y<<" "<<end.x<<endl; 

	/////////////////////////////////////////////////////////////////////////// 
	// 
	// ÏÂÃæµÄÑ­»·ÊÇÇó½âÃÔ¹¬µÄºËÐÄ³ÌÐò 

	//////////////////////////////////////////////////////////////////////////// 
	do 
	{ 
		if(Pass(curpos,Map)) //Èç¹ûµ±Ç°¿é¿ÉÍ¨£¬Ôò½øÐÐÈçÏÂ²Ù×÷ 
		{ 
			FootPrint(curpos,Map); //ÁôÏÂ½ÅÓ¡ 
			e.ord=curstep; //¼ÇÏÂ¼Æ²½Æ÷ 
			e.x=curpos.x; //¼ÇÏÂÐÐÊý 
			e.y=curpos.y; //¼ÇÏÂÁÐÊý 
			e.di=1; //ÉèÒ»¸ö·½ÏòÎª¶«·½ 
			Push(S,e); //Ñ¹Õ»²Ù×÷£¬½«µ±Ç°Î»ÖÃÄÉÈëµ±Ç°Â·¾¶ 
			if(curpos.x==end.x&&curpos.y==end.y) //Èç¹ûµ±Ç°¿éÎªÖÕµã£¬½øÐÐÈçÏÂ²Ù×÷ 
			{ // 
				cout<<"Â·¾¶ÒÑÕÒµ½!"<<endl;  
				DisplayStack(S); //µ÷ÓÃÏÔÊ¾Õ»µÄ×Ó³ÌÐòÏÔÊ¾½á¹û 
				return 1; //º¯Êý·µ»Ø1 
			} // 
			else //Èç¹ûµ±Ç°Î»ÖÃ²»ÊÇÖÕµã£¬½øÐÐÈçÏÂ²Ù×÷ 
			{ // 
				NextPos(curpos.x,curpos.y,curpos,1); //ÇÐ»»¶«·½ÏòµÄÎ»ÖÃÎªµ±Ç°Î»ÖÃ 
				curstep++; //¼Æ²½Æ÷×ÔÔö1 
			} 
		}//if 
		else 
		{ 
			if(S.base!=S.top) //Èç¹ûµ±Ç°¿é²»Í¨£¬ÇÒÕ»²»Îª¿Õ£¨ËµÃ÷»¹ÓÐ½â£© 
			{ 
				Pop(S,e); //½«Õ»¶¥ÔªËØµ¯³ö½øÐÐ¹Û²ì 
				while(e.di==4&&(S.top-S.base)) //Èç¹ûÕ»¶¥ÔªËØËÄ·½¾ù²»Í¨ 
				{ 
					Pop(S,e); //µ¯³öÏÂÒ»¸öÕ»¶¥ÔªËØ½øÐÐ¹Û²ì 
				}//while 
				if(e.di<4) //Èç¹ûÕ»¶¥ÔªËØ»¹ÓÐÆäËû·½ÏòÃ»ÓÐ×ß¹ý 
				{ // 
					e.di++; //ÇÐ»»ÏÂÒ»¸ö·½ÏòÎªµ±Ç°·½Ïò 
					Push(S,e); //Ñ¹ÈëÕ» 
					NextPos(e.x,e.y,curpos,e.di); //ÇÐ»»ÏÂÒ»¸ö·½ÏòÎ»ÖÃÎªµ±Ç°Î»ÖÃ 
				}//if 
			}//if 
		}//else 
	}while(S.base!=S.top); //Ö»ÒªÕ»²»¿ÕÔòËµÃ÷ÓÐ½â£¬ÖØ¸´Ñ­»·

	cout<<"Ã»ÕÒµ½Â·¾¶"<<endl; 
	return 0;
} 



int main()
{
	MazeCell Map[SIZE_OF_MAPH][SIZE_OF_MAPW]; 
	//¶¨ÒåÒ»¸öÃÔ¹¬Êý×é 
	int migong[SIZE_OF_MAPH][SIZE_OF_MAPW]= {0};
	int migong_default[10][10]= { 
								{0,0,0,0,0,0,0,0,0,0},
								{0,1,1,0,1,1,1,0,1,0},
								{0,1,1,0,1,1,1,0,1,0},
								{0,1,1,1,1,0,0,1,1,0},
								{0,1,0,0,0,1,1,1,1,0},
								{0,1,1,1,0,1,1,1,1,0},
								{0,1,0,1,1,1,0,1,1,0},
								{0,1,0,0,0,1,0,0,1,0},
								{0,0,1,1,1,1,1,1,1,0},
								{0,0,0,0,0,0,0,0,0,0}
								}; //ÒÔÊý×é±íÊ¾µÄÃÔ¹¬*/ 
	
	cout<<"ÊÇ·ñ²ÉÓÃÄ¬ÈÏÃÔ¹¬£¿(Y/N)"<<endl;
	char input;
	cin>>input;

	int line, column;
	if (input == 'N' || input == 'n') {
		InputMaze(migong, line, column);
		DisplayMaze(migong, line, column); //ÏÔÊ¾ÃÔ¹¬µÄÐÎ×´ 
	}
	else {
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				migong[i][j] = migong_default[i][j];

		DisplayMaze(migong, 10, 10); //ÏÔÊ¾ÃÔ¹¬µÄÐÎ×´ 
	}
	
	BuideMaze(Map,migong); //µ÷ÓÃ½¨Á¢ÃÔ¹¬µÄ×Óº¯Êý 
	
	Seat start,end; 
	//¶¨Òåµ±Ç°Î»ÖÃ£¬ÆðµãÎ»ÖÃ£¬ÖÕµãÎ»ÖÃµÄ½á¹¹Ìå 
	
	while(1)
	{
		cout<<"½øÈëÃÔ¹¬µÄÎ»ÖÃ (n m):"<<endl;
		cin>>start.y;
		cin>>start.x;
		if(start.x < 0 || start.y < 0 || start.x >= SIZE_OF_MAPH || start.y >= SIZE_OF_MAPW)
			cout<<"ÊäÈëÊý¾Ý´íÎó,ÇëÖØÐÂÊäÈë"<<endl;
		else 
			break;
	}
	while(1)
	{
		cout<<"×ß³öÃÔ¹¬µÄÎ»ÖÃ (n m):"<<endl;
		cin>>end.y;
		cin>>end.x;
		if(end.x < 0 || end.y < 0 || end.x >= SIZE_OF_MAPH || end.y >= SIZE_OF_MAPW)
			cout<<"ÊäÈëÊý¾Ý´íÎó,ÇëÖØÐÂÊäÈë"<<endl;
		else 
			break;
	}
	
	MazePath(Map,start,end); 

	return 0;
}
