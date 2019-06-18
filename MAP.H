#include <iostream.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>

#define MAP_STARTX 150
#define MAP_STARTY 30
#define MAP_WIDTH  10
#define MAP_HEIGHT 20
#define BAR_WIDTH  20
#define BAR_HEIGHT 20
#define BAR_DEPTH  0
#define COLOR YELLOW

/************************* OTHER USEFUL FUNCTIONS **********************/

void InitGraph ()
{
	int gdriver = DETECT,
		gmode, errorcode;

	initgraph (&gdriver, &gmode, "C:\\PROGRA~1\\BC311\\BGI");

	errorcode = graphresult ();
	if (errorcode != grOk)
	{
		cout<<"Graphics error :"<<grapherrormsg(errorcode)<<endl;
		cout<<"Press any key to halt:";
		getch();
		exit(1);
	}
}

void CloseGraph()
{
	cout<<"Press any key:";
	getch();
	closegraph();
}
/************************ END OF USEFUL FUNCTIONS **********************/

/************************** PLAY ARENA OF THE GAME *********************/

class MAP
{
	friend class Game;
	private :
		int MapContent[MAP_HEIGHT][MAP_WIDTH];
		int MaxHeight;
		int Score;
	public :
		void InitMap ();
		void DrawBorders ();
		void DeleteRow ();
		void UpdateView ();
		void MoveUpperContent (int);

		//void RandomStart ();
};

/********************** END OF MAP CLASS DEFINITION ********************/
/*
void MAP::RandomStart ()
{
	randomize ();
	for (int i=0; i<MAP_HEIGHT; i++)
		for (int j=0; j<MAP_WIDTH; j++)
			MapContent [i][j] = random(50);
	for (i=0; i<MAP_WIDTH; i++)
		MapContent [3][i] = 1;
}
*/
void MAP::InitMap ()
{
	for (int i=0; i<MAP_HEIGHT; i++)
		for (int j=0; j<MAP_WIDTH; j++)
			MapContent [i][j] = 0;
	Score = 0;
}

void MAP::DrawBorders ()
{
	setfillstyle (5, BLUE);
	for (int i=0; i<MAP_HEIGHT; i++)
	{
		bar3d (MAP_STARTX, MAP_STARTY+BAR_HEIGHT*i, MAP_STARTX+BAR_WIDTH,  MAP_STARTY+BAR_HEIGHT*(i+1), BAR_DEPTH, 1);
		bar3d (MAP_STARTX+BAR_WIDTH*(MAP_WIDTH+1), MAP_STARTY+BAR_HEIGHT*i, MAP_STARTX+BAR_WIDTH*(MAP_WIDTH+1)+BAR_WIDTH,  MAP_STARTY+BAR_HEIGHT*(i+1), BAR_DEPTH, 1);
	}
	for (i=0; i<(MAP_WIDTH+2); i++)
		bar3d (MAP_STARTX+BAR_WIDTH*i, MAP_STARTY+MAP_HEIGHT*BAR_HEIGHT, MAP_STARTX+BAR_HEIGHT*(i+1),  MAP_STARTY+MAP_HEIGHT*BAR_HEIGHT+BAR_HEIGHT, BAR_DEPTH, 1);
}

void MAP::DeleteRow ()
{
	int check = 0;

	for (int i=0; i<MAP_HEIGHT; i++)
	{
		for (int j=0; j<MAP_WIDTH; j++)
		{
			if (!MapContent [i][j])
				check = 1;
		}
		if (!check)
		{
			for (int k=0; k<MAP_WIDTH; k++)
				MapContent [i][k] = 0;
			MoveUpperContent (i+1);
			UpdateView ();
			i--;
			Score++;
		}
		check = 0;
	}
}

void MAP::UpdateView ()
{
	setfillstyle (2, COLOR);

	for (int i=0; i<MAP_HEIGHT; i++)
		for (int j=0; j<MAP_WIDTH; j++)
		{
			if (MapContent[i][j])
				bar3d (MAP_STARTX+BAR_WIDTH*(j+1), MAP_STARTY+BAR_HEIGHT*(MAP_HEIGHT-i), MAP_STARTX+BAR_WIDTH*(j+2), MAP_STARTY+BAR_HEIGHT*(MAP_HEIGHT-i-1), BAR_DEPTH, 1);
			else
			{
				setfillstyle(2, BLACK);
				bar3d (MAP_STARTX+BAR_WIDTH*(j+1), MAP_STARTY+BAR_HEIGHT*(MAP_HEIGHT-i), MAP_STARTX+BAR_WIDTH*(j+2), MAP_STARTY+BAR_HEIGHT*(MAP_HEIGHT-i-1), BAR_DEPTH, 1);
				setfillstyle (2, COLOR);
			}
		}
}

void MAP::MoveUpperContent (int k)
{
	if (k == MAP_HEIGHT)
		return ;

	for (int i=k; i<MAP_HEIGHT; i++)
		for (int j=0; j<MAP_WIDTH; j++)
			MapContent [i-1][j] = MapContent [i][j];

	for (int l=0; l<MAP_WIDTH; l++)
		MapContent [MAP_HEIGHT-1][l] = 0;
}

/********************* END OF MAP METHODS DEFINITION *******************/
