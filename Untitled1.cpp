#include<iostream>
#include<string>
#include <cstring>
#include<fstream>
#include <cctype>
#include <cstdio>
#include <ctime>
#include<iomanip>
#include <stdio.h>
#include<conio.h>
#include<dos.h> 
#include<ctype.h>
#include<stdlib.h>
#include <windows.h>
#include <time.h>
#include<string.h>

#define SCREEN_WIDTH 90 // car racing
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 

#define LEFT 1// snake
#define RIGHT 2
#define UP 3
#define DOWN 4
using namespace std;

//the entire driving game code system is located from here down
using namespace std; 
void TextColor(int x)
{
     HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = { ' ','±','±',' ', 
				   '±','±','±','±', 
				   ' ','±','±',' ',
				   '±','±','±','±' }; 
					
int carPos = WIN_WIDTH/2;
int score = 0; 

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void drawBorder(){  
	for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<17; j++){
			gotoxy(0+j,i); cout<<"±";
			gotoxy(WIN_WIDTH-j,i); cout<<"±";
		}
	} 
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(SCREEN_WIDTH,i); cout<<"±";
	} 
}
void genEnemy(int ind){
	enemyX[ind] = 17 + rand()%(33);  
}
void drawEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]); TextColor(11);cout<<" *** ";
		gotoxy(enemyX[ind], enemyY[ind]+1);   TextColor(8);cout<<"*"; TextColor(9); cout << "*"; TextColor(11);cout <<"*"; TextColor(9); cout <<"*"; TextColor(8); cout << "*";  
		gotoxy(enemyX[ind], enemyY[ind]+2); TextColor(9);cout<<" *** "; 
		gotoxy(enemyX[ind], enemyY[ind]+3); TextColor(8);cout<<"*"; TextColor(9); cout << "***"; TextColor(8); cout << "*"; 
		gotoxy(enemyX[ind], enemyY[ind]+4); TextColor(9);cout<<"  *  ";
			TextColor(7);  
	} 
}
void eraseEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]);   cout<<"     ";  
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"     "; 
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"     "; 
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"     "; 
	} 
}
void resetEnemy(int ind){
	eraseEnemy(ind);
	enemyY[ind] = 1;
	genEnemy(ind);
}

void drawCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<car[i][j];
		}
	}
}
void eraseCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<" ";
		}
	}
}
 
int collision(){
	if( enemyY[0]+4 >= 23 ){
		if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){
			return 1;
		}
	}
	return 0;
} 
void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\tPress any key to go back to menu.";
	getch();
}
void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

void instructions(){
	
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Avoid Cars by moving left or right. ";
	cout<<"\n\n Press 'a' to move left";
	cout<<"\n Press 'd' to move right";
	cout<<"\n Press 'escape' to exit";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

void play(){
	TextColor(7);
	carPos = -1 + WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;
	  
	system("cls"); 
	drawBorder(); 
	updateScore();
	genEnemy(0);
	genEnemy(1);
	
	gotoxy(WIN_WIDTH + 7, 2);cout<<"Car Game";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right"; 
	
	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch=='D' ){
				if( carPos < 50 )
					carPos += 4;
			} 
			if(ch==27){
				break;
			}
		} 
		
		drawCar(); 
		drawEnemy(0); 
		drawEnemy(1); 
		if( collision() == 1  ){
			gameover();
			return;
		} 
		Sleep(50);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);   
		
		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;
		
		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;
		
		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;
		 
		if( enemyY[0] > SCREEN_HEIGHT-4 ){
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 ){
			resetEnemy(1);
			score++;
			updateScore();
		}
	}
}

//--------------------------------------------------------------
//The system of the snake game code is from here

//This method is used to provide a particular color to elements
void textcolor(int fc,int bc=-1){
	if(fc<0 || fc>15)
		return;
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	if(bc>=0 && bc<16)
		SetConsoleTextAttribute(h,fc|bc*16);
	else
		SetConsoleTextAttribute(h,fc);
}

//This method is used to provide a particular color to elements
void textcolor(char *fc,char *bc=""){
	int x,y=16;
	char *colors[]={"Black","Blue","Green","Aqua","Red","Purple","Yellow","White","Gray",
	"LightBlue","LightGreen","LightAqua","LightRed","LightPurple","LightYellow","BrightWhite"};
	for(x=0;x<16;x++)
		if(strcmpi(colors[x],fc)==0)
			break;
	if(strlen(bc)>0)
		for(y=0;y<16;y++)
			if(strcmpi(colors[y],bc)==0)
				break;
	textcolor(x,y);
}

//This method is used to provide a particular color to elements
void textcolor(char *fc,int bc){
	int x;
	char *colors[]={"Black","Blue","Green","Aqua","Red","Purple","Yellow","White","Gray",
	"LightBlue","LightGreen","LightAqua","LightRed","LightPurple","LightYellow","BrightWhite"};
	for(x=0;x<16;x++)
		if(strcmpi(colors[x],fc)==0)
			break;
	textcolor(x,bc);
}

//This method is used to provide a particular color to elements
void textcolor(int fc,char *bc){
	int y;
	char *colors[]={"Black","Blue","Green","Aqua","Red","Purple","Yellow","White","Gray",
	"LightBlue","LightGreen","LightAqua","LightRed","LightPurple","LightYellow","BrightWhite"};
	if(strlen(bc)>0)
		for(y=0;y<16;y++)
			if(strcmpi(colors[y],bc)==0)
				break;
	textcolor(fc,y);
}

//This method is used to set the position to a particular coordinate
void gotoxy2(int x, int y)
{
 COORD coord;
 coord.X = x;
 coord.Y = y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//This method is used to draw the texts on the screen
void getup(){
	HANDLE hout;
	CONSOLE_CURSOR_INFO cursor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.dwSize=1;
	cursor.bVisible=false;
	SetConsoleCursorInfo(hout, &cursor);
	system("mode con:cols=80 lines=25");
	system("title Snake Game");
	system("cls");
	textcolor("Yellow");
	printf("\n  %c",218);
	int x;
	for(x=0;x<75;x++)
		printf("%c",196);
	printf("%c  ",191);
	for(x=0;x<17;x++){
		gotoxy2(2,x+2);
		printf("%c",179);
		gotoxy2(78,x+2);
		printf("%c ",179);
	}
	printf("  %c",192);
	for(x=0;x<75;x++)
		printf("%c",196);
	printf("%c  ",217);
	printf(" %c",218);
	for(x=0;x<21;x++)
	printf("%c",196);
	printf("%c\n",191);
	printf("  %cPress Enter to Replay%c\n",179,179);
	printf("  %c",192);
	for(x=0;x<21;x++)
		printf("%c",196);
	printf("%c",217);

	gotoxy2(59,20);
	printf("%c",218);
	for(x=0;x<18;x++)
		printf("%c",196);
	printf("%c",191);
	gotoxy2(59,21);
	printf("%c SCORE : 100      %c",179,179);
	gotoxy2(59,22);
	printf("%c STATUS: Playing  %c",179,179);
	gotoxy2(59,23);
	printf("%c",192);
	for(x=0;x<18;x++)
		printf("%c",196);
	printf("%c",217);
	gotoxy2(32,21);
	printf("Eat the food #");
	gotoxy2(32,22);
	printf("Press 'space' to Pause");
	textcolor(7);
}

//This method is used to update the score variable on the right side down screen
void score2(int sc){
	gotoxy2(69,21);
	printf("%6d",sc*10);
}

//This method is used to update the status variable which is initially set to playing on the right side down screen
void status(char *s,int c=7){
	gotoxy2(69,22);
	textcolor(c);
	int x;
	for(x=0;x<strlen(s);x++)
		printf("%c",s[x]);
	for(;x<8;x++)
		printf(" ");
	textcolor(7);
}

//--------------------------------------------------------------
//  and finally the game code to answer the question
int myarr=0;
string mydata[50][5];
int point=0;	
void gotoXY3(int x, int y); 
void timer();
void write_student();	//ban ghi trong tep nhi phan
void firstscreen();
void quiz();
void info();
void display_all();	//doc tat ca ban ghi tu tep
void class_result();	// hien thi ban ghi
void result();		//display result menu
double duration;
double maxtime=100;
	string comm;
enum color{ // liet ke
	NONE,
	DARK_BLUE,
	GREEN,
	DARK_CYAN,
	DARK_RED,
	PURPLE,
	DARK_YELLOW,
	NORMAL,
	GRAY,
	BLUE,
	LIME,
	CYAN,
	RED,
	PINK,
	YELLOW,
	WHITE
};
void setcolor   (color newColor);

struct question
{
  	string ques;
  	string ans1;
	string ans2;
	string ans3;
	string ans4;
	char ans;
};

void gotoxy3(int x,int y)
{  
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = {x, y};
    SetConsoleCursorPosition(h, a);
}
class student
{
	int rollno;
	char name[50];
	int obt;
	double per;
	char grade;
	
	void calculate();	// ham tinh diem
		void Result();
public:
	void getdata();		//chuc nang nhap du lieu
	void showdata() const;	//chuc nang hien thi
	void show_tabular() const;
}; //class ends here
void student::calculate()
{
	per=point/10*10;
	
	if(per>= 90)
	{
		grade='A';
		comm="Excellent";
		}
	else if(per>=70)
		{
			grade='B';
			comm="Good";
		}
		
	else if(per>=50)
		{
			grade='C';
			comm="Must try harder";
		}
	else
		{
			grade='F';
			comm="Stupid";
		}
}

void student::getdata()
{	
	point=0;
	cout<<"\nNhap 1 so bat ki ma ban muon:  ";
	cin>>rollno;
	cout<<"\n\nNhap ten nguoi choi:  ";
	cin.ignore();
	cin.getline(name,50);
	system("cls");
	quiz();	
	obt=point;
	
	calculate();
	system("cls");
	Result();
}

void student::showdata() const
{
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nName of student : "<<name;
}

void student::show_tabular() const
{
	if (per >= 80) {
	
	cout<<setw(12)<<rollno<<setw(15)<<name<<setw(10)<<obt<<setw(11)<<per<<setw(8)<<grade<< setw(8) << "10k " <<endl;
	myarr++;
}
else 
		cout<<setw(12)<<rollno<<setw(15)<<name<<setw(10)<<obt<<setw(11)<<per<<setw(8)<<grade <<endl;
	myarr++;

}

void ebod()
{
 			
			for(int x = 20; x < 103; x++){
			setcolor(CYAN);
			gotoXY3(x,4);	
			cout<<char(205);
			}
			for(int x = 20; x < 103; x++){
			setcolor(PURPLE);
			gotoXY3(x,12);	
			cout<<char(205);
			}

			for(int x = 5; x < 12; x++){
			setcolor(CYAN);
			gotoXY3(20,x);	
			cout<<char(186);
			}
			for(int x = 5; x < 12; x++){
			setcolor(CYAN);
			gotoXY3(103,x);	
			cout<<char(186);
			}
			setcolor(CYAN);

			gotoXY3(20,4);	
			cout<<char(201);
			gotoXY3(103,4);	
			cout<<char(187);
			gotoXY3(103,12);	
			cout<<char(188);
			gotoXY3(20,12);	
			cout<<char(200);

}
void gotoXY3(int x, int y) 	//function to decide location of the screem
{
	//A "handle" is a generic identifier (typically a pointer) used to represent something
	//Retrieves a handle to the specified standard device (standard input, standard output).
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 		 
	COORD CursorPosition; 
	CursorPosition.X = x; // Locates column
	CursorPosition.Y = y; // Locates Row
	//Sets the cursor position in the specified console screen buffer.
	//A COORD structure that specifies the new cursor position, in characters. The coordinates are 
	//the column and row of a screen buffer character cell. The coordinates must be within the 
	//boundaries of the console screen buffer.
	SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
}
void info()
{
	setcolor(RED);
	gotoXY3(56,4);	
		cout<<"Instruction"<<endl;
    TextColor(11);
	gotoXY3(50,5);	
		cout<<"Press Enter to Home Menu"<<endl;
		setcolor(GREEN);
		setcolor(LIME);
		gotoXY3(38,6);	
		cout<<"   ________________________________________"<<endl;
		gotoXY3(38,7);
		cout<<" / \\                             	         \\."<<endl;
		gotoXY3(38,8);
		cout<<"|   |                                      |."<<endl;
		gotoXY3(38,9);
		cout<<" \\_ | Select==>                            |."<<endl;
		gotoXY3(38,10);
		cout<<"    | Press only Valid Opton--> (a,b,c,d)  |."<<endl;
		gotoXY3(38,11);
		cout<<"    | if u Press Other key consider wrong  |."<<endl;
		gotoXY3(38,12);
		cout<<"    | answer.                              |."<<endl;
		gotoXY3(38,13);
		cout<<"    |                            	   	 |."<<endl;
		gotoXY3(38,14);
		cout<<"    | Skip==>                              |."<<endl;
		gotoXY3(38,15);
		cout<<"    | Press Enter to Skip the Question     |."<<endl;
		gotoXY3(38,16);
		cout<<"    |                            	         |."<<endl;
		gotoXY3(38,17);
		cout<<"    | Points==>                            |."<<endl;
		gotoXY3(38,18);
		cout<<"    | 10 Point will be awarded for each    |."<<endl;
		gotoXY3(38,19);
		cout<<"    | correct answer.                      |."<<endl;
		gotoXY3(38,20);
		cout<<"    |                                      |."<<endl;
		gotoXY3(38,21);
		cout<<"    | Time==>                              |."<<endl;
		gotoXY3(38,22);
		cout<<"    | Team will be given 60 seconds for    |."<<endl;
		gotoXY3(38,23);
		cout<<"    | each question.                       |."<<endl;
		gotoXY3(38,24);
		cout<<"    |                            	         |."<<endl;
		gotoXY3(38,25);
		cout<<"    | Identification==>                    |."<<endl;
		gotoXY3(38,26);
		cout<<"    | Enter Roll Number and Name for Recod |."<<endl;
		gotoXY3(38,27);
		cout<<"    | save                          	 |."<<endl;
		gotoXY3(38,28);
		cout<<"    |   ___________________________________|___"<<endl;
		gotoXY3(38,29);
		cout<<"    |  /                                      /."<<endl;
		gotoXY3(38,30);
		cout<<"    \\_/______________________________________/."<<endl;
	
}


void student::Result()
{
	int f=30;
	setcolor(RED);
	gotoXY3(0,3);
	cout<<"  _____                 _ _   "<<endl;
	gotoXY3(0,4);
	cout<<" |  __ \\               | | |  "<<endl;
	gotoXY3(0,5);
	cout<<" | |__) |___  ___ _   _| | |_ "<<endl;
	gotoXY3(0,6);
	cout<<" |  _  // _ \\/ __| | | | | __|"<<endl;
	gotoXY3(0,7);
	cout<<" | | \\ \\  __/\\__ \\ |_| | | |_ "<<endl;
	gotoXY3(0,8);
	cout<<" |_|  \\_\\___||___/\\__,_|_|\\__|"<<endl;
	
	setcolor(YELLOW);
gotoXY3(f,1);
cout<<"                     ,---.           ,---.   "<<endl;
gotoXY3(f,2);
cout<<"                    / /^`.\\.--''''-./,'^\\ \\	"<<endl;
gotoXY3(f,3);
cout<<"                    \\ \\    _       _    / /	"<<endl;
gotoXY3(f,4);
cout<<"                     `./  / __   __ \\  \\,'	"<<endl;
gotoXY3(f,5);
cout<<"                      /    /_O)_(_O\\    \\	"<<endl;
gotoXY3(f,6);
cout<<"                      |  .-'  ___  `-.  |	"<<endl;
gotoXY3(f,7);
cout<<"                   .--|       \\_/       |--.	"<<endl;
gotoXY3(f,8);
cout<<"                 ,'    \\   \\   |   /   /    `."<<endl;
gotoXY3(f,9);
cout<<"                /       `.  `--^--'  ,'       \\"<<endl;
gotoXY3(f,10);
cout<<"             .-^^^^^-.    `--.___.--'     .-^^^^^-."<<endl;
gotoXY3(f,11);
cout<<".-----------/         \\------------------/         \\--------------."<<endl;
gotoXY3(f,12);
cout<<"| .---------\\         /----------------- \\         /------------. |"<<endl;
gotoXY3(f,13);
cout<<"| |          `-`--`--'                    `--'--'-'             | |"<<endl;
gotoXY3(f,14);
cout<<"| |                                                             | |"<<endl;
gotoXY3(f,15);
cout<<"| |                                                             | |"<<endl;
gotoXY3(f,16);
cout<<"| |                                                             | |"<<endl;
gotoXY3(f,17);
cout<<"| |                                                             | |"<<endl;
gotoXY3(f,18);
cout<<"| |_____________________________________________________________| |"<<endl;
gotoXY3(f,19);
cout<<"|_________________________________________________________________|"<<endl;
gotoXY3(f,20);
cout<<"                   )__________|__|__________("<<endl;
gotoXY3(f,21);
cout<<"                  |            ||            |"<<endl;
gotoXY3(f,22);
cout<<"                  |____________||____________|"<<endl;
gotoXY3(f,23);
cout<<"                    ),-----.(      ),-----.("<<endl;
gotoXY3(f,24);
cout<<"                  ,'   ==.   \\    /  .==    `."<<endl;
gotoXY3(f,25);
cout<<"                 /            )  (            \\"<<endl;
gotoXY3(f,26);
cout<<"                 `==========='    `==========='  "<<endl;
	setcolor(CYAN);
	gotoXY3(35,14);
	cout<<"Name ==>"<<name;
	setcolor(CYAN);
	gotoXY3(70,14);
	cout<<"Roll No ==> "<<rollno;
	setcolor(CYAN);
	gotoXY3(35,15);
	cout<<"Total Score ==> 100";
	gotoXY3(70,15);
	cout<<"Your Score ==> "<<point;
	setcolor(CYAN);
	gotoXY3(35,16);
	cout<<"Percentage ==> "<<per;
	gotoXY3(70,16);
	cout<<"Grade ==> "<<grade;
	setcolor(CYAN);
	gotoXY3(35,17);
	cout<<"Comments==> "<<comm;
_getch();
	
}

void Borders() 
{
	{

		for(int x = 2; x < 70; x++){
		setcolor(DARK_CYAN);

		//setcolor(WHITE);
		gotoXY3(x,1);	
		cout<<char(205);
		}

		Beep(200, 25);
		gotoXY3(135,1);	
		cout<<char(187);		
		for(int y = 2; y < 50; y++){
		gotoXY3(135,y);	
		cout<<char(186);
		}

		Beep(300, 25);
		gotoXY3(135,50);	
		cout<<char(188);		
		for(int x = 134; x > 1; x--){
		gotoXY3(x,50);	
		cout<<char(205);			
		}

		Beep(400, 25);

		gotoXY3(1,50);	
		cout<<char(200);		
		for(int y = 49; y > 1; y--){
		gotoXY3(1,y);	
		cout<<char(186);		
		}
		gotoXY3(1,1);	
		cout<<char(201);		
		Beep(500, 25);
	}
}
void setcolor   (color newColor) 
{
	//A "handle" is a generic identifier (typically a pointer) used to represent something.
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), (newColor ) );
}


void quiz()
{
	std::clock_t start;
    start = std::clock();	

	char a,b,e;
    int t=0;
	int i=0;
	int right=0;
	int wrong=0;
	char answer;
	struct question abc[10];
	int srno=0;
	int chon;
	cout << "\n  ____________________________________________________________________ ";
	cout << "\n |   1. Dia ly   |   2. Hoa hoc   |   3. Do vui   |    4. The thao    |";
	cout << "\n |_______________|________________|_______________|___________________|" << endl;
    cout << "\n Ban muon chon phan nao: ";
	cin>> chon;

	
	if (chon == 1) {
	abc[0] = {"Quoc Gia nao co dan so lon thu 2 tren the gioi ? ","An Do","Trung Quoc","Chau Phi","Viet Nam",'b'};
	abc[1] = {"Quoc Gia nao co nguoi dau tien dat chan len mat trang ?","Trung Quoc.","Nga.","My","Anh.",'c'};
	abc[2] = {"Quoc Gia co dan so va dien tich lon nhat Nam My?","Argentina.","Colombia.","Brazil.","Chile.",'c'};
	abc[3] = {"Dua theo dien tich dat lien, Quoc gia nao co dien tich lon nhat tren the gioi ?","Nga.","Canada","Trung Quoc.","Brazil.",'a'};
	abc[4] = {"Quoc Gia nao co nhieu nguoi noi tieng Tay Ban Nha nhat the gioi ?","Argentina","Costa Rica","Chile","Mexico",'d'};//
    abc[5] = {"Bieu tuong chim dai bang ngam 1 con ran o trong mieng cua nuoc nao ? ","Malaysia","Mexico","Thailand","Singapore",'b'};
	abc[6] = {"Adidas và Volkswagen la 2 cong ty noi tieng cua quoc gia nao ?","Duc.","Anh.","My","Phap.",'a'};
	abc[7] = {"Leonardo da Vinci sinh ra tai quoc gia nao ?","Italy.","France.","Brazil.","Colombia.",'a'};
	abc[8] = {"Nui Phu Si thuoc quoc gia nao ?","Nga.","Nhat","My.","Phap.",'b'};
	abc[9] = {"Lyon và Marseille la 2 thanh pho cua quoc gia nao ?","Italy","Brazil","Argentina","France",'d'};
   
	do {
		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			setcolor(RED);			
			gotoXY3(69,3);
			cout << (maxtime + 20)-duration << endl;
		if (duration>=maxtime) {
			t=0;
			break;
		}

		if (srno==i) {
			system("cls");

			srno++;
			b=' ';
			e=' ';
			answer=abc[i].ans;

			ebod();
			for(int x = 12; x < 16; x++){
			setcolor(CYAN);
			gotoXY3(20,x);	
			cout<<char(186);
			}
			for(int x = 20; x < 103; x++){
			setcolor(CYAN);
			gotoXY3(x,16);	
			cout<<char(205);
			}
			for(int x = 12; x < 16; x++){
			setcolor(CYAN);
			gotoXY3(103,x);	
			cout<<char(186);
			}


			setcolor(CYAN);
			gotoXY3(103,16);	
			cout<<char(188);
			gotoXY3(20,16);	
			cout<<char(200);

			int col=23;
			setcolor(BLUE);
			gotoXY3(23,5);
			
			cout << "Question "<<srno<<") " <<endl;
			gotoXY3(23,6);cout<< abc[i].ques<< endl;
	  		gotoXY3(col,8);
			setcolor(DARK_YELLOW);
			cout <<" a - " << abc[i].ans1<< endl;
	  		gotoXY3(col,9);
			cout <<" b - " << abc[i].ans2<< endl;
	  		gotoXY3(col,10);
			cout << " c - " << abc[i].ans3<< endl;
	  		gotoXY3(col,11);
			cout << " d - " << abc[i].ans4<< endl;
			gotoXY3(45,13);		
			cout << " Press Enter to skip ";
			gotoXY3(45,14);		
			cout << " Select your Option ==> ";
			setcolor(YELLOW);
			gotoXY3(45,3);		
			cout << " Your Remaning Time ==> ";

		}

		if(_kbhit()){
			setcolor(YELLOW);
			gotoXY3(70,14);
			a=_getch();
			//cin>>a;
			cout<<a;

			if(int(a)==13){

					gotoXY3(30,18);
					setcolor(RED);
				cout << "You skipped this Question";
			} else {
				if(a==answer){
					gotoXY3(62,18);
					setcolor(LIME);
					point=point+10;
					cout << "Congratulation You selected right option";
				} else {
					gotoXY3(70,18);
					setcolor(GREEN);
					cout << "Correct Option is  ==> "<<answer;
					gotoXY3(30,18);
					setcolor(RED);
					cout << "You selected wrong option.";

				}
			}
			_getch();
			i++;
		} 
	} while (i<10);
}
else if (chon == 3) {
	abc[0] = {"Tan Tong thong Ukraine Volodymyr Zelensky lam nghe gi truoc khi nham chuc? ","Vo si quyen anh.","dien vien hai.","bac si.","doanh nhan.",'b'};
	abc[1] = {"Dot bien o NST bao nhieu gay ra benh Down? ","20.","21.","22.","23.",'b'};
	abc[2] = {"El Nino la gi ?","1 loai duong xi.","1 loai dieu nhay.","1 khu rung o Chau Phi.","1 hien tuong thoi tiet.",'d'};
	abc[3] = {"So 3 duoc viet the nao trong he nhi phan ?","0.","1.","11.","100.",'c'};
	abc[4] = {"Trong am thuc Nhat Ban, Matcha la loai nguyen lieu nao ?","bot gao.","bot tra xanh.","bot ngo.","bot dau.",'b'};
	abc[5] = {"Ran co may la phoi ? ","2.","4.","1.","3.",'c'};
	abc[6] = {"To 1 co bao nhieu thanh vien (tinh ca Mai Quy Khang) ? ","9.","10.","11.","8.",'b'};
	abc[7] = {"Quoc ca cua Singapore bang tieng gi ?","Ma lai.","Trung Quoc.","An Do.","Tieng Anh.",'a'};
	abc[8] = {"Ga Phong hien suu tam bao nhieu con figure ?","23.","25.","27.","28.",'b'};
	abc[9] = {"Con vat nao khong the boi ?","Ca.","Chim canh cut.","Vit.","Voi.",'d'};

	do {
		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			setcolor(RED);			
			gotoXY3(69,3);
			cout << maxtime-duration << endl;
		if (duration>=maxtime) {
			t=0;
			break;
		}

		if (srno==i) {
			system("cls");

			srno++;
			b=' ';
			e=' ';
			answer=abc[i].ans;

			ebod();
			for(int x = 12; x < 16; x++){
			setcolor(CYAN);
			gotoXY3(20,x);	
			cout<<char(186);
			}
			for(int x = 20; x < 103; x++){
			setcolor(CYAN);
			gotoXY3(x,16);	
			cout<<char(205);
			}
			for(int x = 12; x < 16; x++){
			setcolor(CYAN);
			gotoXY3(103,x);	
			cout<<char(186);
			}


			setcolor(CYAN);
			gotoXY3(103,16);	
			cout<<char(188);
			gotoXY3(20,16);	
			cout<<char(200);

			int col=23;
			setcolor(BLUE);
			gotoXY3(23,5);
			
			cout << "Question "<<srno<<") " <<endl;
			gotoXY3(23,6);cout<< abc[i].ques<< endl;
	  		gotoXY3(col,8);
			setcolor(DARK_YELLOW);
			cout <<" a - " << abc[i].ans1<< endl;
	  		gotoXY3(col,9);
			cout <<" b - " << abc[i].ans2<< endl;
	  		gotoXY3(col,10);
			cout << " c - " << abc[i].ans3<< endl;
	  		gotoXY3(col,11);
			cout << " d - " << abc[i].ans4<< endl;
			gotoXY3(45,13);		
			cout << " Press Enter to skip ";
			gotoXY3(45,14);		
			cout << " Select your Option ==> ";
			setcolor(YELLOW);
			gotoXY3(45,3);		
			cout << " Your Remaning Time ==> ";

		}

		if(_kbhit()){
			setcolor(YELLOW);
			gotoXY3(70,14);
			a=_getch();
			//cin>>a;
			cout<<a;

			if(int(a)==13){

					gotoXY3(30,18);
					setcolor(RED);
				cout << "You skipped this Question";
			} else {
				if(a==answer){
					gotoXY3(62,18);
					setcolor(LIME);
					point=point+10;
					cout << "Congratulation You selected right option";
				} else {
					gotoXY3(70,18);
					TextColor(10);
					cout << "Correct Option is  ==> "<<answer;
					gotoXY3(30,18);
					setcolor(RED);
					cout << "You selected wrong option.";

				}
			}
			_getch();
			i++;
		} 
	} while (i<10);
}


else if (chon == 4) {
	abc[0] = {"Quoc Gia nao vo dich World Cup 2014 ? ","Phap.","Argentina.","Duc.","Y.",'c'};
	abc[1] = {"Ronaldo khi moi sang Real Madrid, anh mac ao so bao nhieu ?","8.","9.","10.","11.",'b'};
	abc[2] = {"CLB nao co nhieu chuc vo dich Champons League nhat ?","Real Madrid.","AC Milan.","Barcelona.","Manchester United.",'a'};
	abc[3] = {"Messi giu ki luc voi bao nhieu Qua bong vang ?","5.","6.","7.","8.",'b'};
	abc[4] = {"Doi tuyen nao vo dich World Cup nhieu lan nhat ?","Argentina.","Phap.","Duc.","Brazil.",'d'};
    abc[5] = {"The van hoi Olympic duoc to chuc may nam 1 lan ?","2 nam.","3 nam.","4 nam.","5 nam.",'c'};
    abc[6] = {"Thu mon Hugo Lloris dang choi cho cau lac bo nao ?","Tottenham.","Everton.","Manchester City.","Aston Villa.",'a'};
    abc[7] = {"Doi tuyen quoc gia nao la nha vo dich cua Euro 2016 ?","Phap.","Bo Dao Nha.","Tay Ban Nha.","Duc.",'b'};
    abc[8] = {"Cau thu nao dat giai Vua pha luoi tai Euro 2016 ?","Kylian Mbappe.","Cristiano Ronaldo.","Fernando Torres.","Antoine Griezmann.",'d'};
    abc[9] = {"David Beckham la cau thu chuyen nghiep nguoi .... ","Anh.","Phap.","Tay Ban Nha.","Duc.",'a'};
	do {
		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			setcolor(RED);			
			gotoXY3(69,3);
			cout << maxtime-duration << endl;
		if (duration>=maxtime) {
			t=0;
			break;
		}

		if (srno==i) {
			system("cls");

			srno++;
			b=' ';
			e=' ';
			answer=abc[i].ans;

			ebod();
			for(int x = 12; x < 16; x++){
			setcolor(CYAN);
			gotoXY3(20,x);	
			cout<<char(186);
			}
			for(int x = 20; x < 103; x++){
			setcolor(CYAN);
			gotoXY3(x,16);	
			cout<<char(205);
			}
			for(int x = 12; x < 16; x++){
			setcolor(CYAN);
			gotoXY3(103,x);	
			cout<<char(186);
			}


			setcolor(CYAN);
			gotoXY3(103,16);	
			cout<<char(188);
			gotoXY3(20,16);	
			cout<<char(200);

			int col=23;
			setcolor(BLUE);
			gotoXY3(23,5);
			
			cout << "Question "<<srno<<") " <<endl;
			gotoXY3(23,6);cout<< abc[i].ques<< endl;
	  		gotoXY3(col,8);
			setcolor(DARK_YELLOW);
			cout <<" a - " << abc[i].ans1<< endl;
	  		gotoXY3(col,9);
			cout <<" b - " << abc[i].ans2<< endl;
	  		gotoXY3(col,10);
			cout << " c - " << abc[i].ans3<< endl;
	  		gotoXY3(col,11);
			cout << " d - " << abc[i].ans4<< endl;
			gotoXY3(45,13);		
			cout << " Press Enter to skip ";
			gotoXY3(45,14);		
			cout << " Select your Option ==> ";
			setcolor(YELLOW);
			gotoXY3(45,3);		
			cout << " Your Remaning Time ==> ";

		}

		if(_kbhit()){
			setcolor(YELLOW);
			gotoXY3(70,14);
			a=_getch();
			//cin>>a;
			cout<<a;

			if(int(a)==13){

					gotoXY3(30,18);
					setcolor(RED);
				cout << "You skipped this Question";
			} else {
				if(a==answer){
					gotoXY3(62,18);
					setcolor(LIME);
					point=point+10;
					cout << "Congratulation You selected right option";
				} else {
					gotoXY3(70,18);
					setcolor(GREEN);
					cout << "Correct Option is  ==> "<<answer;
					gotoXY3(30,18);
					setcolor(RED);
					cout << "You selected wrong option.";

				}
			}
			_getch();
			i++;
		} 
	} while (i<10);
}
else if (chon == 2) {
	abc[0] = {"Cong thuc hoa hoc cua Axit Sulfuric ? ","HNO3.","H2SO4.","H2CO3.","H3PO4.",'b'};
	abc[1] = {"Chat nao sau day khong tham gia phan ung trung hop ?","propen.","stiren.","isopren.","toluen.",'d'};
	abc[2] = {"Hop chat Este la ?","CH3CH2Cl.","HCOOC6H5.","CH3CH2NO3.","C2H5COOH.",'b'};
	abc[3] = {"Cong thuc tong quat cua Este no, don chuc, mach ho ?","CnH2nO (n >= 1).","CnH2nO2 (n >= 1).","CnH2nO2 (n >= 2).","CnH2nO3 (n >= 2).",'c'};
	abc[4] = {"Trong cac loai nuoc, nuoc nao la nuoc tinh khiet ?","nuoc mua.","nuoc song.","nuoc cat.","nuoc khoang.",'c'};
    abc[5] = {"Chat gay hai chu yeu co trong thuoc la ? ","Becberin.","Nicotin.","Axit nicotinic.","Moocphin.",'b'};
	abc[6] = {"Canxi phan ung voi Clo sinh ra san pham nao sau day ?","CaCl2.","NaCl.","CaOCl2."," Ca(OH)2.",'a'};
	abc[7] = {"O dieu kien thuong, chat nao sau day la chat khi ?","Tristearin.","Glucozo.","Metylamin.","Alanin.",'c'};
	abc[8] = {"Cong thuc cua metyl fomiat la  ?","CH3COOCH3.","HCOOCH3.","CH3COOC2H5.","HCOOC2H5.",'b'};
	abc[9] = {"Kim loai co tinh deo nhat ?","Au.","Cu.","Al.","Fe.",'a'};
	do {
		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			setcolor(RED);			
			gotoXY3(69,3);
			cout << (maxtime + 50)-duration << endl;
		if (duration>=maxtime) {
			t=0;
			break;
		}

		if (srno==i) {
			system("cls");

			srno++;
			b=' ';
			e=' ';
			answer=abc[i].ans;

			ebod();
			for(int x = 12; x < 16; x++){
			setcolor(CYAN);
			gotoXY3(20,x);	
			cout<<char(186);
			}
			for(int x = 20; x < 103; x++){
			setcolor(CYAN);
			gotoXY3(x,16);	
			cout<<char(205);
			}
			for(int x = 12; x < 16; x++){
			setcolor(CYAN);
			gotoXY3(103,x);	
			cout<<char(186);
			}


			setcolor(CYAN);
			gotoXY3(103,16);	
			cout<<char(188);
			gotoXY3(20,16);	
			cout<<char(200);

			int col=23;
			setcolor(BLUE);
			gotoXY3(23,5);
			
			cout << "Question "<<srno<<") " <<endl;
			gotoXY3(23,6);cout<< abc[i].ques<< endl;
	  		gotoXY3(col,8);
			setcolor(DARK_YELLOW);
			cout <<" a - " << abc[i].ans1<< endl;
	  		gotoXY3(col,9);
			cout <<" b - " << abc[i].ans2<< endl;
	  		gotoXY3(col,10);
			cout << " c - " << abc[i].ans3<< endl;
	  		gotoXY3(col,11);
			cout << " d - " << abc[i].ans4<< endl;
			gotoXY3(45,13);		
			cout << " Press Enter to skip ";
			gotoXY3(45,14);		
			cout << " Select your Option ==> ";
			setcolor(YELLOW);
			gotoXY3(45,3);		
			cout << " Your Remaning Time ==> ";

		}

		if(_kbhit()){
			setcolor(YELLOW);
			gotoXY3(70,14);
			a=_getch();
			//cin>>a;
			cout<<a;

			if(int(a)==13){

					gotoXY3(30,18);
					setcolor(RED);
				cout << "You skipped this Question";
			} else {
				if(a==answer){
					gotoXY3(62,18);
					setcolor(LIME);
					point=point+10;
					cout << "Congratulation You selected right option";
				} else {
					gotoXY3(70,18);
					setcolor(GREEN);
					cout << "Correct Option is  ==> "<<answer;
					gotoXY3(30,18);
					setcolor(RED);
					cout << "You selected wrong option.";

				}
			}
			_getch();
			i++;
		} 
	} while (i<10);
}

	if (i<10) {
		cout<<"\nTime is up. You failed to attempt all questions"<<endl;
		system("pause");
		return;
	} 
		        
	_getch();
}
void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("nauzer.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    //	cout<<"\n\nStudent record Has Been Created ";
	//cin.ignore();
	cin.get();
}

//***************************************************************
//    	function to read all records from file
//****************************************************************

void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("nauzer.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}


//***************************************************************
//    	function to display all students grade report
//****************************************************************

void class_result()
{
	student st;
	ifstream inFile;

	inFile.open("nauzer.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();

		cin.get();
		return;
	}

	cout<<"\n\n\t\tALL STUDENTS RESULT \n";
	cout<<"\n\t\tPress Enter to Go Back Home Screen\n";
	cout<<"       ==========================================================\n";
	cout<<"          R.No         Name       Points     %       Grade"<<endl;
	cout<<"       ==========================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}

//***************************************************************
//    	function to display result menu
//****************************************************************



void firstscreen()		//simply desgin screen
{

	doo :
	system("CLS");		
	setcolor(NORMAL);
						
	int type;
	do {
	system("cls");
			
	setcolor(GREEN);
	gotoXY3(50,20);
	cout<<" >>";
	gotoXY3(74,20);
	cout<<" >>";
	gotoXY3(54,20);
	setcolor(WHITE);
	cout<<"Press Enter Continue";
	Beep(500, 100);
	gotoXY3(45,10);
	TextColor(11);
	cout<<"====== Select Following Option ======";
	gotoXY3(50,12);
	setcolor(WHITE);
	cout<<"  1-->  New Game";
	gotoXY3(50,13);
	cout<<"  2-->  Instructions";
	gotoXY3(50,14);
	cout<<"  3-->  Result Record";  
	gotoXY3(42,16);
	cout<<"Select : ";  
	TextColor(7);  
	Beep(500, 100);
	go:                                     
	int type;
	gotoXY3(51,16);
	cin>>type;	
	switch(type)
	{
		case 1:
			{
						system("CLS");
			
			system("COlOR 3f");
			write_student();	
			break;
			}
	case 2:
			{
			system("CLS");
	
			info();
			_getch();
			goto doo;
			break;
			}
			case 3:
			{
			system("CLS");		
				setcolor(GREEN);	
		        setcolor(LIME);
			class_result();
			
			system("CLS");
			goto doo;
			break;
			}
			case 4: {
				exit(0);
			}
			default:
			
			cout<<"/n INVALID CHOICE";
			_getch();
			goto go;
	}
	//system("CLS");
}while(type != 5);
}
//----------------------------------------------------------------------------------------------------------------------------------
// casino game

void instruction4() {
    system("cls");
    cout << endl << endl;
	setcolor(GREEN);
		setcolor(LIME);	
		cout<<"           ________________________________________"<<endl;
		cout<<"         / \\                             	   \\."<<endl;
		cout<<"        |  |                                       |."<<endl;
		cout<<"         \\_|                                       |."<<endl;
		cout<<"           |                                       |."<<endl;
		cout<<"           | 1. Choose any number between 1 to 5   |."<<endl;
		cout<<"           | 2. If you win you will get 10 times   |."<<endl;
		cout<<"           |of money you bet                       |."<<endl;
		cout<<"           | 3. If you bet on wrong number         |."<<endl;
		cout<<"           |you will lose your betting totalMoney  |."<<endl;
		cout<<"           |                            	   |."<<endl;
		cout<<"           |                                       |."<<endl;
		cout<<"           |  _____________________________________|___"<<endl;
		cout<<"           |  /                                      /."<<endl;
		cout<<"           \\_/______________________________________/."<<endl;
    getch();
}

void play4() {
    system("cls");

    string personName;
    int totalMoney;
    int betMoney;
    int guess;
    int dice;
    char option;

    srand(time(0));
TextColor(11);
    cout << "                           ------------------------------------" << endl;
    cout << "                          |";
	TextColor(10);
	cout << "            CASINO GAME";
	TextColor(11);
	cout << "             |" << endl;
    cout << "                           ------------------------------------" << endl << endl;
TextColor(9);
    cout << "Enter Your Name : ";
TextColor(7);
    cin.ignore();
    getline(cin, personName);

    cout << endl << endl;
TextColor(9);
    cout << "Enter Deposit Money to start game : $";
TextColor(7);
    cin >> totalMoney;

    do {
        system("cls");
        
	   TextColor(11);
    cout << "                           ------------------------------------" << endl;
    cout << "                          |";
	TextColor(10);
	cout << "            CASINO GAME";
	TextColor(11);
	cout << "             |" << endl;
    cout << "                           ------------------------------------" << endl << endl;
        TextColor(9);
		cout << "\nCurrent balance is";
		TextColor(12);
		cout << " $ " << totalMoney << endl;

        do {
        	TextColor(10);
            cout << personName;
			TextColor(7);
			cout << ", Please Enter amount to bet :";
			TextColor(12);
			cout << " $";
            cin >> betMoney;
            
            if (betMoney > totalMoney)
                cout << "Betting Amount is more than current balance" << endl << "Re-enter data" << endl;

        } while (betMoney > totalMoney || betMoney < 1);

        do {
        	TextColor(7);
            cout << "Enter Guess number to bet between 1 to 5 :";
            cin >> guess;
            if (guess < 1 || guess > 5)
                cout << "Number should be between 1 to 5" << endl << "Re-enter data " << endl;

        } while (guess < 1 || guess > 5);

        dice = rand() % 5 + 1;

        if (dice != guess) {
            totalMoney -= betMoney;
            cout << endl << endl << "You lost $ " << betMoney << endl;
        } else {
            totalMoney += (betMoney * 10);
            cout << endl << endl << "Congratulations!! You won Rs." << betMoney * 10;
        }

        cout << "\nThe winning number was : " << dice << endl;
        cout << "\n" << personName << ", You have $ " << totalMoney << endl;
        if (totalMoney == 0) {
            cout << "You have no money to play ";
            break;
        }
        cout << endl << endl << " Do you want to play again (y/n)? ";
        cin >> option;
    } while (option == 'Y' || option == 'y');
    system("cls");
setcolor(YELLOW);
cout<<"                     ,---.           ,---.   "<<endl;
cout<<"                    / /^`.\\.--''''-./,'^\\ \\	"<<endl;
cout<<"                    \\ \\    _       _    / /	"<<endl;
cout<<"                     `./  / __   __ \\  \\,'	"<<endl;
cout<<"                      /    /_O)_(_O\\    \\	"<<endl;
cout<<"                      |  .-'  ___  `-.  |	"<<endl;
cout<<"                   .--|       \\_/       |--.	"<<endl;
cout<<"                 ,'    \\   \\   |   /   /    `."<<endl;
cout<<"                /       `.  `--^--'  ,'       \\"<<endl;
cout<<"             .-^^^^^-.    `--.___.--'     .-^^^^^-."<<endl;
cout<<".-----------/         \\------------------/         \\--------------."<<endl;
cout<<"| .---------\\         /----------------- \\         /------------. |"<<endl;
cout<<"| |          `-`--`--'                    `--'--'-'             | |"<<endl;
cout<<"| |                                                             | |"<<endl;
cout<<"| |";
TextColor(11);
cout <<"      Thanks for playing. Your Current Money is $ " << totalMoney << endl;
setcolor(YELLOW);
cout<<"| |                                                             | |"<<endl;
cout<<"| |                                                             | |"<<endl;
cout<<"| |_____________________________________________________________| |"<<endl;
cout<<"|_________________________________________________________________|"<<endl;
cout<<"                   )__________|__|__________("<<endl;
cout<<"                  |            ||            |"<<endl;
cout<<"                  |____________||____________|"<<endl;
cout<<"                    ),-----.(      ),-----.("<<endl;
cout<<"                  ,'   ==.   \\    /  .==    `."<<endl;
cout<<"                 /            )  (            \\"<<endl;
cout<<"                 `==========='    `==========='  "<<endl;
    getch();
}

int main()
{
	/*
	system("COLOR 0e");
    system("cls");
    printf("\e[?25l");

    //Set ASCII to print special character.
    //Code page 437
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;

    cout << "\n\n\n\t\t\t\t  Loading...";
    cout << "\n\n\n\t\t\t\t";
TextColor(8);
    for(int i = 0; i < 25; i++)
        cout << (char)bar1;
TextColor(10);
    cout <<"\r";
    cout <<"\t\t\t\t";
    for(int i = 0; i < 25; i++)
    {
        cout << (char)bar2;
        Sleep(50);
    }
    cout << "\n";
    cout <<"\n";
TextColor(7);
    cout<<"\n\t\t\t\t";
*/    
system("cls");
	int lua;
	setcolor(NORMAL);
	TextColor(10);
	int type;
		
	system("cls");
						
	cout <<"\n\n\n\t\t\t\t __      __   ___  | |   ___    ___    _ __ ___     ___  "<<endl;
	cout <<"\t\t\t\t \\ \\ /\\ / /  / _ \\ | |  / __|  / _ \\  | '_ ` _ \\   / _ \\ "<<endl;
	cout <<"\t\t\t\t  \\ V  V /  |  __/ | | | (__  | (_) | | | | | | | |  __/ "<<endl;
	cout <<"\t\t\t\t   \\_/\\_/    \\___| |_|  \\___|  \\___/  |_| |_| |_|  \\___| "<<endl;
	cout << "\n";
	TextColor(11);
	cout << "\n                             _______________________________________________________________";
	cout << "\n                            |   ";
	TextColor(10);
	cout << "1. Racing game";
	TextColor(11);
	cout << "           |                                  |";
	cout << "\n                            |";
	TextColor(10);
	cout << "   2. snake game";
	TextColor(11);
	cout << "            |";
	TextColor(7);
	cout<< "   To play any game, please";
	TextColor(11);
	cout << "       |";
	cout << "\n                            |";
	TextColor(10);
	cout << "   3. Q.A game";
	TextColor(11);
	cout << "              |";
	TextColor(7);
	cout << "   choose the number 1, 2 or 3";
	TextColor(11);
	cout << "    |";
	cout << "\n                            |";
	TextColor(10);
	cout << "   4. Casino game.";
	TextColor(11);
	cout << "          |";
	TextColor(7);
	cout << "   respectively";
	TextColor(11);
	cout << "                   |";
	cout << "\n                            |";
	TextColor(10);
	cout << "   5. Exit.";
	TextColor(11);
	cout << "                 |";
	TextColor(7);
	cout << "            ";
	TextColor(11);
	cout << "                      |";
	cout << "\n                            |____________________________|__________________________________|" <<endl;
	cout << "\n Please enter the game you want to play ^^ :  ";
	cin >> lua;
	switch(lua) {
		
	 case 1: {
	system("cls");
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("COLOR 0e");
    system("cls");
    printf("\e[?25l");

    //Set ASCII to print special character.
    //Code page 437
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;
    TextColor(11);
    cout << "\n\n\n\t\t\t\t       wait a few minutes to load...";
    cout << "\n\n\n\t\t\t\t";
    TextColor(11);
    for(int i = 0; i < 45; i++)
        cout << (char)bar1;
    TextColor(11);
    cout <<"\r";
    cout <<"\t\t\t\t";
    for(int i = 0; i < 45; i++)
    {
        cout << (char)bar2;
        Sleep(50);
    }
    cout << "\n";
    cout <<"\n";
    TextColor(10);
    cout<<"\n\t\t\t\t" << (char)1 <<"!";
    
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |        Car Game        | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Start Game";
		gotoxy(10,10); cout<<"2. Instructions";	 
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: ";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	}while(1);
}
 case 2: {
 	system("COLOR 0e");
    system("cls");
    printf("\e[?25l");

    //Set ASCII to print special character.
    //Code page 437
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;
    TextColor(11);
    cout << "\n\n\n\t\t\t\t       wait a few minutes to load...";
    cout << "\n\n\n\t\t\t\t";
    TextColor(11);
    for(int i = 0; i < 45; i++)
        cout << (char)bar1;
    TextColor(11);
    cout <<"\r";
    cout <<"\t\t\t\t";
    for(int i = 0; i < 45; i++)
    {
        cout << (char)bar2;
        Sleep(50);
    }
    cout << "\n";
    cout <<"\n";
    TextColor(7);
    cout<<"\n\t\t\t\t" << (char)1 <<"!";
 	
 	system("cls");
 	TextColor(10);
	cout<<"\n            /^\\/^\\                                             ";
			cout<<"\n          _|__|  O|                                              ";
			cout<<"\n \\/     /~     \\_/ \\                                          ";
			cout<<"\n  \\____|__________/  \\                                         ";
			cout<<"\n         \\_______      \\                                       ";
			cout<<"\n                 `\\     \\                 \\                   ";
			cout<<"\n                   |     |                  \\                   ";
			cout<<"\n                  /      /                    \\                 ";
			cout<<"\n                 /     /                       \\\\              ";
			cout<<"\n               /      /                         \\ \\            ";
			cout<<"\n              /     /                            \\  \\          ";
			cout<<"\n            /     /             _----_            \\   \\        ";
			cout<<"\n           /     /           _-~      ~-_         |   |          ";
			cout<<"\n          (      (        _-~    _--_    ~-_     _/   |          ";
			cout<<"\n           \\      ~-____-~    _-~    ~-_    ~-_-~    /          ";
			cout<<"\n             ~-_           _-~          ~-_       _-~";
			TextColor(3);
			cout << "      press enter to continue..      ";
			TextColor(10);
			cout<<"\n                ~--______-~                ~-___-~               ";
			system("pause");
			system("cls");
	getup();
	register int flow,size,i,xb,yb;
	int speed,restart=1,tmp,xpos[100],ypos[100],scr;
	srand(time(NULL));
	while(true){
		if(restart){
			status("Playing",10);
			for(int k=1;k<75;k+=2)
				for(int j=0;j<17;j++){
					gotoxy2(k+3,j+2);
					printf(" ");
				}
			size=5;
			speed=200;
			scr=0;
			score2(scr);
			flow=RIGHT;
			xpos[0]=20;
			for(i=0;i<size;i++){
				xpos[i]=xpos[0]-i*2;
				ypos[i]=10;
			}
			for(i=0;i<size;i++){
				gotoxy2(xpos[i],ypos[i]);
				printf("*");
			}
			for(tmp=1;true;){
				do{
					xb=rand()%75+3;
				}while(xb%2!=0);
				yb=rand()%17+2;
				for(i=0;i<size;i++)
					if(xb==xpos[i] && yb==ypos[i]){
						tmp=0; break;
					}
				if(tmp)
					break;
			}
			gotoxy2(xb,yb);
			textcolor("lightred");
			printf("#");
			textcolor(7);
			restart=0;
		}
		while(!kbhit() && !restart)	{
			if(xpos[0]==xb && ypos[0]==yb){
				for(tmp=1;true;){
					do{
						xb=rand()%75+3;
					}while(xb%2!=0);
					yb=rand()%17+2;
					for(i=0;i<size;i++)
						if(xb==xpos[i] && yb==ypos[i]){
							tmp=0; break;
						}
					if(tmp)
						break;
				}
				gotoxy2(xb,yb);
				textcolor("lightred");
				printf("#");
				textcolor(7);
				size++;
				scr++;
				speed-=3;
				score2(scr);
			}
			gotoxy2(xpos[size-1],ypos[size-1]);
			for(i=size-1;i>0;i--){
				xpos[i]=xpos[i-1];
				ypos[i]=ypos[i-1];
			}
			switch(flow){
				case RIGHT :xpos[i]+=2; break;
				case LEFT :	xpos[i]-=2; break;
				case UP :	ypos[i]-=1; break;
				case DOWN :	ypos[i]+=1;
			}
			tmp=1;
			for(i=1;i<size;i++)
				if(xpos[i]==xpos[0] && ypos[i]==ypos[0]){
					tmp=0;
					break;
				}
			if(xpos[0]>76 || xpos[0]<4 || ypos[0]<2 ||ypos[0]>18)
				tmp=0;
			if(tmp){
				printf(" ");
				gotoxy2(xpos[0],ypos[0]);
				printf("O");
				gotoxy2(xpos[1],ypos[1]);
				printf("*");
			}
			else{
				textcolor("LIGHTRED");
				printf("*");
				gotoxy2(xpos[1],ypos[1]);
				printf("O");
				for(i=2;i<size;i++){
					gotoxy2(xpos[i],ypos[i]);
					printf("*");
				}
				textcolor(7);
				status("GameOver",12);
				restart=1;
				getch();
			}
			//delay(speed);
			Sleep(speed);
		}
		char ch=getch();
		switch(tolower(ch)){
			case 'x' : 	system("cls");
						return 0;
			case ' ' : status("Paused");
						while(true){
							char z=getch();
							if(z=='x')
								return 0;
							if(z==' ')
								break;
						}
						status("Playing",10);
						break;
			case -32: {
				char chh=getch();
				if(chh==72 && flow!=DOWN)
					flow=UP;
				else if(chh==80 && flow!=UP)
					flow=DOWN;
				else if(chh==75 && flow!=RIGHT)
					flow=LEFT;
				else if(chh==77 && flow!=LEFT)
					flow=RIGHT;
				break;
			}
		}
	}
}

case 3: {
char name;
system("COLOR 0e");
    system("cls");
    printf("\e[?25l");

    //Set ASCII to print special character.
    //Code page 437
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;
    TextColor(11);
    cout << "\n\n\n\t\t\t\t       wait a few minutes to load...";
    cout << "\n\n\n\t\t\t\t";
    TextColor(11);
    for(int i = 0; i < 45; i++)
        cout << (char)bar1;
    TextColor(11);
    cout <<"\r";
    cout <<"\t\t\t\t";
    for(int i = 0; i < 45; i++)
    {
        cout << (char)bar2;
        Sleep(50);
    }
    cout << "\n";
    cout <<"\n";
    TextColor(7);
    cout<<"\n\t\t\t\t" << (char)1 <<"!";
		cout.setf(ios::fixed|ios::showpoint);
		cout<<setprecision(2); // xuat so thap phan sang hai chu so thap phan
		firstscreen();
		
		_getch();
		system("cls");
	
		
}

case 4: {
	char name;
system("COLOR 0e");
    system("cls");
    printf("\e[?25l");

    //Set ASCII to print special character.
    //Code page 437
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;
    TextColor(11);
    cout << "\n\n\n\t\t\t\t       wait a few minutes to load...";
    cout << "\n\n\n\t\t\t\t";
    TextColor(11);
    for(int i = 0; i < 45; i++)
        cout << (char)bar1;
    TextColor(11);
    cout <<"\r";
    cout <<"\t\t\t\t";
    for(int i = 0; i < 45; i++)
    {
        cout << (char)bar2;
        Sleep(50);
    }
    cout << "\n";
    cout <<"\n";
    TextColor(7);
    cout<<"\n\t\t\t\t" << (char)1 <<"!";
    
    
	system("cls");
srand((unsigned) time(NULL));

    do {
    system("cls");
    TextColor(11);
    cout << "\n     ===============================================================================================";
	cout << "\n     ||";
	TextColor(10);
	cout << "            CCCCC      A        SSSSSSSSS   IIIIIIIII  NN     NN    OOOOOOOO";
	TextColor(11);
	cout << "               ||";
	cout << "\n     ||";
	TextColor(10);
	cout << "          CC          A  A      SS             III     NN N   NN   OO      OO";
	TextColor(11);
	cout << "              ||";
	cout << "\n     ||";
	TextColor(10);
	cout << "         CC          A    A     SSSSSSSSS      III     NN  N  NN   OO      OO";
	TextColor(11);
	cout << "              ||";
	cout << "\n     ||";
	TextColor(10);
	cout << "          CC        AAAAAAAA           SS      III     NN   N NN   OO      OO";
	TextColor(11);
	cout << "              ||";
	cout << "\n     ||";
	TextColor(10);
	cout << "            CCCCC  A        A   SSSSSSSSS   IIIIIIIII  NN     NN    OOOOOOOO";
	TextColor(11);
	cout << "               ||";
	cout << "\n     ===============================================================================================\n" << endl;
	cout << "\n";
	TextColor(9);
	cout<<"\n                                 ====== Select Following Option ======               " << endl;
	TextColor(7);
    cout << "\n                                           1. Start Game" << endl;
    cout << "\n                                           2. instructions" << endl;
    cout << "\n                                           3. Quit" << endl;
    cout << "\nSelect option: ";
    char op = getche();

        if (op == '1') play4();
        else if (op == '2') instruction4();
        else if (op == '3') exit(0);

    } while (1);	
}

case 5: {
	break;
}
default:
		
			system("cls");
	int lua;
	setcolor(NORMAL);
	TextColor(10);
	int type;
		
	system("cls");
						
	cout <<"\n\n\n\t\t\t\t __      __   ___  | |   ___    ___    _ __ ___     ___  "<<endl;
	cout <<"\t\t\t\t \\ \\ /\\ / /  / _ \\ | |  / __|  / _ \\  | '_ ` _ \\   / _ \\ "<<endl;
	cout <<"\t\t\t\t  \\ V  V /  |  __/ | | | (__  | (_) | | | | | | | |  __/ "<<endl;
	cout <<"\t\t\t\t   \\_/\\_/    \\___| |_|  \\___|  \\___/  |_| |_| |_|  \\___| "<<endl;
	cout << "\n";
	TextColor(11);
	cout << "\n                             _______________________________________________________________";
	cout << "\n                            |   ";
	TextColor(10);
	cout << "1. Racing game";
	TextColor(11);
	cout << "           |                                  |";
	cout << "\n                            |";
	TextColor(10);
	cout << "   2. snake game";
	TextColor(11);
	cout << "            |";
	TextColor(7);
	cout<< "   To play any game, please";
	TextColor(11);
	cout << "       |";
	cout << "\n                            |";
	TextColor(10);
	cout << "   3. Q.A game";
	TextColor(11);
	cout << "              |";
	TextColor(7);
	cout << "   choose the number 1, 2 or 3";
	TextColor(11);
	cout << "    |";
	cout << "\n                            |";
	TextColor(10);
	cout << "   4. Casino game.";
	TextColor(11);
	cout << "      |";
	TextColor(7);
	cout << "   respectively";
	TextColor(11);
	cout << "                   |";
	cout << "\n                            |";
	TextColor(10);
	cout << "   5. Exit.";
	TextColor(11);
	cout << "                 |";
	TextColor(7);
	cout << "            ";
	TextColor(11);
	cout << "                      |";
	cout << "\n                            |____________________________|__________________________________|" <<endl;
	cout << "\n Please enter the game you want to play ^^ :  ";
	cin >> lua;
	while (lua < 1 || lua > 4) {
		system("cls");
	int lua;
	setcolor(NORMAL);
	TextColor(10);
	int type;
		
	system("cls");
						
	cout <<"\n\n\n\t\t\t\t __      __   ___  | |   ___    ___    _ __ ___     ___  "<<endl;
	cout <<"\t\t\t\t \\ \\ /\\ / /  / _ \\ | |  / __|  / _ \\  | '_ ` _ \\   / _ \\ "<<endl;
	cout <<"\t\t\t\t  \\ V  V /  |  __/ | | | (__  | (_) | | | | | | | |  __/ "<<endl;
	cout <<"\t\t\t\t   \\_/\\_/    \\___| |_|  \\___|  \\___/  |_| |_| |_|  \\___| "<<endl;
	cout << "\n";
	TextColor(11);
	cout << "\n                             _______________________________________________________________";
	cout << "\n                            |   ";
	TextColor(10);
	cout << "1. Racing game";
	TextColor(11);
	cout << "           |                                  |";
	cout << "\n                            |";
	TextColor(10);
	cout << "   2. snake game";
	TextColor(11);
	cout << "            |";
	TextColor(7);
	cout<< "   To play any game, please";
	TextColor(11);
	cout << "       |";
	cout << "\n                            |";
	TextColor(10);
	cout << "   3. Q.A game";
	TextColor(11);
	cout << "              |";
	TextColor(7);
	cout << "   choose the number 1, 2 or 3";
	TextColor(11);
	cout << "    |";
	cout << "\n                            |";
	TextColor(10);
	cout << "   4. Exit.";
	TextColor(11);
	cout << "                 |";
	TextColor(7);
	cout << "   respectively";
	TextColor(11);
	cout << "                   |";
	cout << "\n                            |";
	TextColor(10);
	cout << "   5. Exit.";
	TextColor(11);
	cout << "                 |";
	TextColor(7);
	cout << "            ";
	TextColor(11);
	cout << "                      |";
	cout << "\n                            |____________________________|__________________________________|" <<endl;
	cout << "\n Please enter the game you want to play ^^ :  ";
	cin >> lua;
	}

}while(lua != 6)
	return 0;
}
