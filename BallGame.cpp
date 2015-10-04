#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <process.h>

#define XMAX getmaxx()
#define YMAX getmaxy()
#define SIZE 50 //MAXIMUM NO OF BALLS


// Ball Functions
int drawBalls(int,int,int&); //Draw Balls 
void restore(int&, int&);

int main()
{	
	int g=DETECT,m;
	initgraph(&g,&m,"c:\\tc\\bgi");
	int speed = 2, //control speed 
	 	size = 20,  //control no of balls (max 50)
	 	level = 1,	//present level
	 	res = 1, //result of the game
	 	score = 0;

	char es, msg[100];

	while(es != 27 && res == 1){  // 27 for escape
		
		switch(level){

			case 1: cleardevice();
					outtextxy((XMAX/2)-120, YMAX/3, "Hi there! Welcome to CUBER!");
					outtextxy((XMAX/2)-280, (YMAX/3)+20, "Your aim is to use the cube to reach to the other side of the screen! ");
					outtextxy((XMAX/2)-160, (YMAX/3)+40, "There is nothing on the other side.");
					outtextxy((XMAX/2)-220, (YMAX/3)+60, "but you don't know that because you are a cube!");
					outtextxy((XMAX/2)-100, (YMAX/3)+80,"Press any key to start..");
					getch();
					cleardevice();
					res = drawBalls(size , speed, score);
					break;

			case 2: cleardevice();
					res = drawBalls(size , speed, score);
					break;

			case 3: cleardevice();
					res = drawBalls(size , speed, score);
					break;
			case 4: cleardevice();
					res = drawBalls(size , speed, score);
					break;
			case 5: cleardevice();
					res = drawBalls(size , speed, score);
					break;
			case 6: cleardevice();
					res = drawBalls(size , speed, score);
					break;
		}
		
		if (res == 1)
		{	
			level++;
			if (level == 7)
			{
				cleardevice();
				sprintf(msg,"Your Score %d",score);
				outtextxy((XMAX/2)-150, YMAX/2, "Congratulations! You Won!!");
				outtextxy((XMAX/2)-110, YMAX/2+30, msg);
				outtextxy((XMAX/2)-130, (YMAX/2)+70,"Press any key to exit");
				getch();
				exit(0);
			}

			cleardevice();
			sprintf(msg,"Now, Go to level %d. Press any spacebar to continue...", level);
			outtextxy((XMAX/2)-180, YMAX/2, "Congratulations, You Have Cleared This Level.");
			outtextxy((XMAX/2)-220, (YMAX/2)+30,msg);
			sprintf(msg,"Your Score %d",score);
			outtextxy((XMAX/2)-60, YMAX/2+50, msg);
			es = getch();
			while(es != ' '){
				es = getch();
			}
			
			if (level % 2 == 0)  // increase no of balls on even levels
			{
				size += 10; 
			}else{
				speed++;  // increase speed on odd levels
			}
		}
		else{
			cleardevice();
			outtextxy((XMAX/2)-40, YMAX/2, "GAME OVER");
			sprintf(msg,"Your Score %d",score);
			outtextxy((XMAX/2)-50, YMAX/2+20, msg);
			outtextxy((XMAX/2)-230, (YMAX/2)+40, "You are soo bad at this Simple Game! How are you even alive?");
			outtextxy((XMAX/2)-70, YMAX-20, "Press spacebar to Exit");
			es = getch();
			while(es != ' '){
				es = getch();
			}
			exit(0);
		}
		
	}
	getch();
	closegraph();
	return 0;
} //  main() ends

void restore(int &a, int &b){
	int temp = rand() %2;

	if (temp == 0)
	{
			a = XMAX;
			b = rand() % (YMAX);
	}
	
	else{
			a = rand() % (XMAX);
			b = 0;
			
	}
} //restore() ends

int drawBalls(int size, int s, int &score){
	int x =100, y =100, xpos[SIZE],ypos[SIZE], temp, i ,j ,k,l,xp,yp,speed = s;

	// cube Variables 

	int txpos = 0, typos = YMAX-25;

	char ch,scoretext[50];
	
	void *ptr[SIZE];
	void *cube;

	// BALLS
	setfillstyle(SOLID_FILL, RED);
	cleardevice();
	circle(x, y, 5);
	floodfill(x, y, WHITE);

	for (i = 0; i < size; ++i)
	{
		getimage(x-5,y-5,x+5,y+5,ptr[i]);
	}

	// cube
	cleardevice();

	setfillstyle(SOLID_FILL, GREEN);
	rectangle(10,YMAX-20,30,YMAX);
	floodfill(11, YMAX-15, WHITE);
	getimage(10,YMAX-21,31,YMAX+1,cube);


	for (i = 0; i < size ; ++i)
	{
		restore(xpos[i], ypos[i]);
	}
	
	cleardevice();
	int iarr[SIZE], jarr[SIZE];
	for ( i = 0; i < size; ++i)
	{
		iarr[i] = 0;
		jarr[i] = 0;
 	}	
	do{
		
		for (k = 0; k < size; ++k)
		{	
			xp = xpos[k]-iarr[k];
			yp = ypos[k]+jarr[k];

			

			if (txpos < 0)
			{
				txpos = 0;
			}
			if (txpos >= XMAX-20)
			{
				// You WON!, this level
				return 1;
			}
			putimage(xp, yp , ptr[k], COPY_PUT);
			putimage(txpos, typos, cube, COPY_PUT);

			sprintf(scoretext,"Score: %d",score);
			outtextxy(10, 5, scoretext);

			if (xp < 0 || yp > YMAX)
			{
				restore(xpos[k], ypos[k]);
				iarr[k] = 0;
				jarr[k] = 0;
			}
			
			for (l = 0; l < size; ++l)
			{
				if ((xpos[l]-iarr[l] + 20 > txpos) && (xpos[l]-iarr[l] < txpos + 20) && (ypos[l]+jarr[l] + 20 > typos) )
				{
					return 0; //failed
				}
			}
			
			iarr[k]+= speed;
			jarr[k]+= speed;

		}

		if (kbhit())	//if a key is pressed
		{
			ch = getch();
			switch(ch){
				
				case 75: //left
						 txpos -= 20;
					break;
				case 77: //right
						 txpos += 20;
					break;
				case 27: exit(0);
					break;
			}
		}
		k = 0;
		delay(10);
		score++;
		cleardevice(); //clear the screen

	}while(1);
}  // drawballs() ends


