#include "map.h"
#include "figures.h"
#include <dos.h>
#include <string.h>
#include <stdio.h>
#include <io.h>


#define NORMAL_DELAY 360
#define FAST_DELAY 180


struct PLAYER
{
	char Name[255];
	char Surname[255];
	int  hiScore;
};


/********************** MAIN GAME CONTROLS  CLASS ***********************/

class Game
{
	private :
		FIGURES F;
		MAP M;
		PLAYER P;
		int CURR_X, CURR_Y; // Relative to Map Area
		int STATE; // Block Moving or Stopped (Moving = 0; Stopped = 1;)
		int Delay;
	public  :
		Game ();
		void MoveLeft  ();
		void MoveRight ();
		void ViewBlock (int, int); // Y and X coordinates (Relative To Map Area)
		void UpdateMapContent ();
		int  CheckForBarrier ();
		int  CheckLowerBound ();
		int  CheckRightBound ();
		int  CheckLeftBound ();
		int  CanBeRotated ();
		int  RotCheckSideBounds ();
		void ViewHelp ();
		void EndGame ();
		void QuitGame ();
		void MoveDown  ();
		void ShowNextFigure ();
		void ShowScore ();
		void  ReadHiScore ();
		//void WriteHiScore ();
		void ShowHiScore ();
		void SaveScore ();
		void StartGame ();
};

/****************** END OF MAIN GAME CONTROLS  CLASS ********************/

/************************** METHODS OF GAME CLASS ***********************/

Game::Game ()
{
	MAP INITIAL_M;
	FIGURES INITIAL_F;
	Delay = NORMAL_DELAY;

	InitGraph ();

	INITIAL_M.InitMap ();
	INITIAL_M.DrawBorders ();
	INITIAL_F.AssignNewBlock ();
	F = INITIAL_F;
	M = INITIAL_M;
	setfillstyle (2, RED);

	STATE = 1;
	ReadHiScore ();
	ShowHiScore ();
}

void Game::ReadHiScore ()
{

	FILE* f = fopen ("hiscore.hsc", "r");
		if (!f)
		{
			strcpy (P.Name, "Unknown");
			strcpy (P.Surname, "Unknown");
			P.hiScore = 0;
		}
		else
		{
			fscanf (f, "%s %s %d", P.Name, P.Surname, &P.hiScore);
			fclose (f);
		}
}

void Game::SaveScore ()
{
	if (M.Score > P.hiScore)
	{
		char Name[255];
		char Surname[255];

		FILE* f = fopen ("hiscore.hsc", "w");
			if (!f) return;
		cout<<"YOU ARE THE NEW CHAMPION :"<<endl;
		cout<<"Your Name Please : ";
		cin>>Name;
		cout<<"Your Surname Please : ";
		cin>>Surname;
		fprintf (f, "%s %s %d", Name, Surname, M.Score);
		fclose (f);
	}
}

/*
void Game::WriteHiScore ()
{
	char name[255], surname[255];
	int check = 0;


	FILE* f = fopen ("hiscore.hsc", "w");

	int i;
	if (!ReadHiScore ())
	{
			cout<<"Enter your Name:";
			cin>>name;
			cout<<"Enter your Surname:";
			cin>>surname;

			fprintf (f, "%s %s %d\n", name, surname, M.Score);
			return;
	}


	for (i=0; i<3; i++)
	{
		if (strcmp (P[i].Name, "") == 0)
		{
			cout<<"Enter your Name:";
			cin>>name;
			cout<<"Enter your Surname:";
			cin>>surname;

			fprintf (f, "%s %s %d\n", name, surname, M.Score);
			return;
		}
		if (M.Score > P[i].score)
		{
			cout<<"Enter your Name:";
			cin>>name;
			cout<<"Enter your Surname:";
			cin>>surname;
			fprintf (f, "%s %s %d\n", name, surname, M.Score);
			check = 1;
			break;
		}
		else
			fprintf (f, "%s %s %d\n", P[i].Name, P[i].Surname, P[i].score);
	}

	if (!check)
		return;
	else
		for (int j=i; j<3; j++)
			fprintf (f, "%s %s %d\n", P[i].Name, P[i].Surname, P[i].score);
}
*/
void Game::ViewBlock (int p, int q)
{
	for (int i=0; i<BLOCK_SIZE; i++)
		for (int j=0; j<BLOCK_SIZE; j++)
			if (F.CURR_BLOCK.cells[i][j])
				bar3d (MAP_STARTX+BAR_WIDTH*(q+1) + BAR_WIDTH*j, MAP_STARTY+BAR_HEIGHT*p+BAR_HEIGHT*i, MAP_STARTX+BAR_WIDTH*(q+2)+BAR_WIDTH*j,  MAP_STARTY+BAR_HEIGHT*(p+1)+BAR_HEIGHT*i, BAR_DEPTH, 1);
}

void Game::MoveLeft ()
{
	if (CURR_X > 0 && !CheckLeftBound ())
	{
		M.UpdateView ();
		ViewBlock (CURR_Y, CURR_X--);
	}
}
/*Check Move Right If !RightBound()*/
void Game::MoveRight ()
{
	if (MAP_WIDTH-CURR_X > F.HorSize () && !CheckRightBound ())
	{
		M.UpdateView ();
		ViewBlock (CURR_Y, CURR_X++);
	}
}
/*Check Rotate if !RotCheckLowerBound() && !RotCheckForBarrier()*/
int Game::CanBeRotated ()
{
	if (MAP_WIDTH-CURR_X >= F.VertSize () && MAP_HEIGHT-CURR_Y >= F.HorSize () && !RotCheckSideBounds ())
		return 1;
	return 0;
}

int Game::RotCheckSideBounds ()
{
	BLOCK t = F.CURR_BLOCK;
	F.RotateBlock (t);

	for (int i=0; i<BLOCK_SIZE; i++)
		for (int j=0; j<BLOCK_SIZE; j++)
			if (t.cells[i][j] && (M.MapContent[MAP_HEIGHT-1-CURR_Y-i][CURR_X+j] || M.MapContent[MAP_HEIGHT-2-CURR_Y-i][CURR_X+j]))
				return 1;
	if (F.HorSize () >= MAP_HEIGHT-CURR_Y)
		return 1;
	return 0;
}

int Game::CheckForBarrier ()
{
	int checkForBarrier = 0;

	for (int k=0; k<BLOCK_SIZE; k++)
	{
		for (int l=0; l<BLOCK_SIZE; l++)
			if (F.CURR_BLOCK.cells[k][l] && M.MapContent[MAP_HEIGHT-CURR_Y-k-2][CURR_X+l])
			{
				checkForBarrier = 1;
				break;
			}
		if (checkForBarrier)
			break;
	}
	return checkForBarrier;
}

int Game::CheckLeftBound ()
{
	for (int i=0; i<BLOCK_SIZE; i++)
		for (int j=0; j<BLOCK_SIZE; j++)
			if (F.CURR_BLOCK.cells[j][i] && M.MapContent[MAP_HEIGHT-1-CURR_Y-j][CURR_X+i-1])
				return 1;
	return 0;
}


int Game::CheckRightBound ()
{
	for (int i=BLOCK_SIZE-1; i>=0; i--)
		for (int j=0; j<BLOCK_SIZE; j++)
			if (F.CURR_BLOCK.cells[j][i] && M.MapContent[MAP_HEIGHT-1-CURR_Y-j][CURR_X+i+1])
				return 1;
	return 0;
}
int Game::CheckLowerBound ()
{
	if (MAP_HEIGHT-CURR_Y > F.VertSize ())
		return 0;
	return 1;
}

void Game::MoveDown ()
{
	if (CheckForBarrier () || CheckLowerBound ())
		STATE = 1;
	else
		CURR_Y++;
	ViewBlock (CURR_Y, CURR_X);
}

void Game::ShowScore ()
{
	setfillstyle (1, BLACK);
	bar3d (10, 100, 130, 150, BAR_DEPTH, 1);

	char scr[10];
	char temp[50] = "Score : ";
	itoa (M.Score, scr, 10);
	strcat(temp, scr);
	outtextxy (15, 120, temp);
}

void Game::ShowHiScore ()
{
		char scr[10];
		char temp[50] = "Hi-Score : ";
		itoa (P.hiScore, scr, 10);
		strcat (temp, scr);
		outtextxy (15, 180, P.Name);
		outtextxy (15, 190, P.Surname);
		outtextxy (15, 200, temp);
}


void Game::EndGame ()
{
	char scr[10];
	char temp[50] = "Score : ";
	itoa (M.Score, scr, 10);
	strcat(temp, scr);

	for (int i=0; i<MAP_WIDTH; i++)
		if (M.MapContent[MAP_HEIGHT-1][i])
		{
			settextstyle(2, 2, 35);
			outtextxy (100, 200, "LOOSER");
			outtextxy (430, 100, temp);
			CloseGraph ();
			SaveScore ();
			//WriteHiScore ();
			getch ();
			exit(0);
		}
}

void Game::QuitGame ()
{
	char scr[10];
	char temp[50] = "Score : ";
	itoa (M.Score, scr, 10);
	strcat(temp, scr);

	settextstyle(2, 2, 35);
	outtextxy (430, 100, temp);
	CloseGraph ();
	SaveScore ();
	exit(0);
}

void Game::UpdateMapContent ()
{
	for (int i=0; i<BLOCK_SIZE; i++)
		for (int j=0; j<BLOCK_SIZE; j++)
			if (F.CURR_BLOCK.cells[i][j])
				M.MapContent[MAP_HEIGHT-1-CURR_Y-i][CURR_X+j] = 1;
}

void Game::StartGame ()
{
	int Key;

//	ReadHiScore ();
	while (Key != 'q')
	{
		if (STATE)
		{
			Delay = NORMAL_DELAY;
			EndGame ();
			UpdateMapContent ();
			F.AssignNewBlock ();
			F.AssignNextBlock ();
			ShowNextFigure ();
			CURR_X = MAP_WIDTH/2;
			CURR_Y = 0;
			M.DeleteRow ();
			ViewHelp ();
			M.UpdateView ();
			STATE = 0;
			ShowScore ();
		}
		else
		{
			M.UpdateView ();
			MoveDown ();
			delay (Delay);
		}
		while (kbhit())
		{
			Key = getch ();
			if (!Key) Key = getch();
			switch (Key)
			{
				case 80  : if (!STATE && Delay) Delay -= FAST_DELAY; break;
				case 75  : if (!STATE) MoveLeft  (); break;
				case 77  : if (!STATE) MoveRight (); break;
				case 72  : if (!STATE && CanBeRotated ()) { F.RotateBlock (); ViewBlock (CURR_Y, CURR_X); } break;
				case 'p' : while ((Key = getch())!='p'); break;
			}
		}
	}
	QuitGame ();
}

void Game::ShowNextFigure ()
{
	int i, j;

	setfillstyle (1, BLACK);
	for (i=0; i<BLOCK_SIZE; i++)
		for (j=0; j<BLOCK_SIZE; j++)
			bar3d (10+BAR_WIDTH*i, 10+BAR_HEIGHT*j, 10+BAR_WIDTH*(i+1), 10+BAR_HEIGHT*(j+1), BAR_DEPTH, 1);

	setfillstyle (1, YELLOW);
	for (i=0; i<BLOCK_SIZE; i++)
		for (j=0; j<BLOCK_SIZE; j++)
			if (F.NEXT_BLOCK.cells[j][i])
				bar3d (10+BAR_WIDTH*i, 10+BAR_HEIGHT*j, 10+BAR_WIDTH*(i+1), 10+BAR_HEIGHT*(j+1), BAR_DEPTH, 1);
}

void Game::ViewHelp ()
{
//	char temp[255] = "";
//	char tempScore[15] = "";

	outtextxy (430, 10, "Pause  : p");
	outtextxy (430, 20, "Quit   : q");
	outtextxy (430, 30, "Left   : <Left Arrow>");
	outtextxy (430, 40, "Right  : <Right Arrow>");
	outtextxy (430, 50, "Down   : <Down Arrow>");
	outtextxy (430, 60, "Rotate : <Up Arrow>");
/*	if (ReadHiScore ())
		for (int i=0; i<3; i++)
		{
			if (strcmp (P[i].Name, ""))
				break;
			strcat (temp, P[i].Name);
			strcat (temp, " ");
			strcat (temp, P[i].Surname);
			strcat (temp, " ");
			itoa (P[i].score, temp, 10);
			strcat (temp, tempScore);
			outtextxy (430, 80+10*i, temp);
		}
*/
	setpalette (WHITE, BLACK);
	setpalette (BLACK, WHITE);
}
/************************* END METHODS OF GAME CLASS ********************/

/**************************** MAIN FUNCTION *****************************/
void main (void)
{
	cout<<"HAVE FUN, TRY FRESHEST VERSION OF TETRIS!!!";
	getch();
	Game G;
	getch ();
	G.ViewHelp ();
	G.StartGame ();
	getch ();
}
/**************************** COMPLETE END *****************************/
