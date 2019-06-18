#include <stdlib.h>
#include <conio.h>
#include <iostream.h>

#define BLOCK_SIZE  4
#define BLOCK_TYPES 7

struct BLOCK
{
	int cells[BLOCK_SIZE][BLOCK_SIZE];
};

class FIGURES
{
	private :
		BLOCK BL[BLOCK_TYPES];
		BLOCK CURR_BLOCK;
	public  :
		FIGURES ();
		void RotateBlock ();
		void AssignNewBlock ();
		void PrintTest(int);
		int  VertSize (int);
		int  HorSize  (int);
		void Print(int);
};

/********************** END OF FIGURES CLASS DECLARATION****************/

FIGURES::FIGURES ()
{
	for (int i=0; i<BLOCK_TYPES; i++)
		for (int j=0; j<BLOCK_SIZE; j++)
			for (int k=0; k<BLOCK_SIZE; k++)
				BL[i].cells[j][k] = 0;

	BL[0].cells[0][1] = BL[0].cells[1][0] =
	BL[0].cells[1][1] = BL[0].cells[1][2] = 1;

	BL[1].cells[0][0] = BL[1].cells[1][0] =
	BL[1].cells[2][0] = BL[1].cells[3][0] = 1;

	BL[2].cells[0][0] = BL[2].cells[0][1] =
	BL[2].cells[1][0] = BL[2].cells[2][0] = 1;

	BL[3].cells[0][1] = BL[3].cells[1][0] =
	BL[3].cells[1][1] = BL[3].cells[2][0] = 1;

	BL[4].cells[0][0] = BL[4].cells[0][1] =
	BL[4].cells[1][0] = BL[4].cells[1][1] = 1;

	BL[5].cells[0][0] = BL[5].cells[1][0] =
	BL[5].cells[1][1] = BL[5].cells[2][1] = 1;

	BL[6].cells[0][0] = BL[6].cells[0][1] =
	BL[6].cells[1][1] = BL[6].cells[2][1] = 1;
}

void FIGURES::AssignNewBlock ()
{
	randomize ();
	CURR_BLOCK = BL[random (BLOCK_TYPES+1)];
}

void FIGURES::RotateBlock ()
{
	BLOCK TempBLOCK = CURR_BLOCK;
	int k = 0,
		l = 0,
		check = 0;

	for (int i=BLOCK_SIZE-1; i>=0; i--)  // Main Rotation Part
	{
		for (int j=0; j<BLOCK_SIZE; j++)
		{
			CURR_BLOCK.cells[k][l++] = TempBLOCK.cells[j][i];
		}
		k++;
		l=0;
	}

	for (int p=0; p<BLOCK_SIZE; p++)   // Removing Upper Empty Lines of Blocks
	{
		for (int q=0; q<BLOCK_SIZE; q++)
		{
			if (CURR_BLOCK.cells[0][q])
			{
				check = 1;
				break;
			}
		}
		if (check)
			break;
		for (int m=1; m<BLOCK_SIZE; m++)
			for (int n=0; n<BLOCK_SIZE; n++)
				CURR_BLOCK.cells[m-1][n] = CURR_BLOCK.cells[m][n];
		for (k=0; k<BLOCK_SIZE; k++)
			CURR_BLOCK.cells[BLOCK_SIZE-1][k] = 0;
	}
}

void FIGURES::PrintTest (int k)
{
	BLOCK TempBLOCK;
	if (k<=6)
	{
		TempBLOCK = BL[k];
		CURR_BLOCK = BL[k];
	}
	else TempBLOCK = CURR_BLOCK;

	for (int i=0; i<BLOCK_SIZE; i++)
	{
		for (int j=0; j<BLOCK_SIZE; j++)
			cout<<TempBLOCK.cells[i][j]<<" ";
			cout<<endl;
	}
	cout<<endl;
}
int FIGURES::VertSize (int k)
{
	CURR_BLOCK = BL[k];
	for (int i=BLOCK_SIZE-1; i>=0; i--)
	{
		for (int j=0; j<BLOCK_SIZE; j++)
			if (CURR_BLOCK.cells[i][j])
				return i+1;
	}
}

int FIGURES::HorSize (int k)
{
	CURR_BLOCK = BL[k];
	for (int i=BLOCK_SIZE-1; i>=0; i--)
	{
		for (int j=0; j<BLOCK_SIZE; j++)
			if (CURR_BLOCK.cells[j][i])
				return i+1;
	}
}


void FIGURES::Print(int k)
{
	CURR_BLOCK = BL[k];
	for (int i=0; i<BLOCK_SIZE; i++)
	{
		for (int j=0; j<BLOCK_SIZE; j++)
			cout<<CURR_BLOCK.cells[i][j]<<" ";
				cout<<endl;
	}
}
/********************** END OF FIGURES METHODS DESCRIPTION ****************/



void main(void)
{
	clrscr ();
	FIGURES F;
	int i=0;
	F.Print(i);
	cout<<F.VertSize (i)<<endl;
	cout<<F.HorSize (i)<<endl;

}