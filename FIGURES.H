#define BLOCK_SIZE  4
#define BLOCK_TYPES 7

struct BLOCK
{
	int cells[BLOCK_SIZE][BLOCK_SIZE];
};

class FIGURES
{
	friend class Game;
	private :
		BLOCK BL[BLOCK_TYPES];
		BLOCK CURR_BLOCK, NEXT_BLOCK;
	public  :
		FIGURES ();
		void RotateBlock ();
		void RotateBlock (BLOCK);
		void AssignNewBlock ();
		void AssignNextBlock ();
		//void PrintTest(int);
		int  VertSize ();
		int  HorSize ();
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
	//BL[0].cells[0][0] = BL[0].cells[1][1] =
	//BL[0].cells[2][2] = BL[0].cells[3][3] = 1;

	BL[1].cells[0][0] = BL[1].cells[1][0] =
	BL[1].cells[2][0] = BL[1].cells[3][0] = 1;
	//BL[1].cells[0][0] = BL[1].cells[0][1] =
	//BL[1].cells[0][2] = BL[1].cells[1][0] =
	//BL[1].cells[1][2] = BL[1].cells[2][0] =
	//BL[1].cells[2][1] = BL[1].cells[2][2] = 1;

	BL[2].cells[0][0] = BL[2].cells[0][1] =
	BL[2].cells[1][0] = BL[2].cells[2][0] = 1;

	BL[3].cells[0][1] = BL[3].cells[1][0] =
	BL[3].cells[1][1] = BL[3].cells[2][0] = 1;

	BL[4].cells[0][0] = BL[4].cells[0][1] =
	BL[4].cells[1][0] = BL[4].cells[1][1] = 1;
	//BL[4].cells[0][1] = BL[4].cells[1][0] =
	//BL[4].cells[1][1] = BL[4].cells[1][2] =
	//BL[4].cells[2][1] = 1;

	BL[5].cells[0][0] = BL[5].cells[1][0] =
	BL[5].cells[1][1] = BL[5].cells[2][1] = 1;
	//BL[5].cells[0][1] = BL[5].cells[1][0] =
	//BL[5].cells[1][1] = BL[5].cells[1][2] =
	//BL[5].cells[2][1] = BL[5].cells[3][0] =
	//BL[5].cells[3][2] = 1;

	BL[6].cells[0][0] = BL[6].cells[0][1] =
	BL[6].cells[1][1] = BL[6].cells[2][1] = 1;

	randomize ();
	NEXT_BLOCK = BL[random (BLOCK_TYPES)];
}

void FIGURES::AssignNewBlock ()
{
	CURR_BLOCK = NEXT_BLOCK;
}


void FIGURES::AssignNextBlock ()
{
	randomize ();
	int temp = random(BLOCK_TYPES*1000);
	NEXT_BLOCK = BL[temp%BLOCK_TYPES];
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

void FIGURES::RotateBlock (BLOCK t)
{
	BLOCK TempBLOCK = t;
	int k = 0,
		l = 0,
		check = 0;

	for (int i=BLOCK_SIZE-1; i>=0; i--)  // Main Rotation Part
	{
		for (int j=0; j<BLOCK_SIZE; j++)
		{
			t.cells[k][l++] = TempBLOCK.cells[j][i];
		}
		k++;
		l=0;
	}

	for (int p=0; p<BLOCK_SIZE; p++)   // Removing Upper Empty Lines of Blocks
	{
		for (int q=0; q<BLOCK_SIZE; q++)
		{
			if (t.cells[0][q])
			{
				check = 1;
				break;
			}
		}
		if (check)
			break;
		for (int m=1; m<BLOCK_SIZE; m++)
			for (int n=0; n<BLOCK_SIZE; n++)
				t.cells[m-1][n] = t.cells[m][n];
		for (k=0; k<BLOCK_SIZE; k++)
			t.cells[BLOCK_SIZE-1][k] = 0;
	}
}

/*
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
*/
int FIGURES::VertSize ()
{
	for (int i=BLOCK_SIZE-1; i>=0; i--)
	{
		for (int j=0; j<BLOCK_SIZE; j++)
			if (CURR_BLOCK.cells[i][j])
				return i+1;
	}
	return 0;
}

int FIGURES::HorSize ()
{
	for (int i=BLOCK_SIZE-1; i>=0; i--)
	{
		for (int j=0; j<BLOCK_SIZE; j++)
			if (CURR_BLOCK.cells[j][i])
				return i+1;
	}
	return 0;
}


/********************** END OF FIGURES METHODS DESCRIPTION ****************/
