

#define screenWidth 1000
#define screenHeight 561
#define JUMPLIMIT 150
#define NUMBEROFENEMY 60
//-------enemy-------------------------
bool playGame = false;
char enemyChar[4][20] = { "enemy\\1.bmp", "enemy\\2.bmp", "enemy\\3.bmp", "enemy\\4.bmp" };



int enemyX[NUMBEROFENEMY] = { 1000 };
int enemyY[NUMBEROFENEMY] = { 92 };



int enemyIndex = 1;

void enemyAnimation()
{
	enemyIndex++;
	if (enemyIndex >= 3)
	{
		enemyIndex = 1;
	}

}

void moveEnemy()
{
	if (playGame)
	for (int i = 0; i < NUMBEROFENEMY; i++)
		enemyX[i] -= 2;

}

void moveEnemy2()
{
	if (playGame)
	for (int i = 0; i < NUMBEROFENEMY; i++)
		enemyX[i] -= 3;

}


void randomEnemy()
{
	for (int i = 1; i < NUMBEROFENEMY; i++)
	{
		enemyX[i] = enemyX[i - 1] + (rand() % 5) * 200;
		enemyY[i] = enemyY[i - 1];
	}

}
//---------enemy end---------------------

//-------------this function is for enemy showing-------------
void showEnemy(){
	for (int i = 0; i < NUMBEROFENEMY; i++)
	{
		if (i % 3 == 0)
		{
			iShowBMP2(enemyX[i], enemyY[i], enemyChar[0], 0);
		}
		else
			iShowBMP2(enemyX[i], enemyY[i], enemyChar[enemyIndex], 0);

	}

}
