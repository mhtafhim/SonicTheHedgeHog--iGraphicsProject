#pragma warning(disable:4996) //Disable Deprecation Errors
#include "iGraphics.h"
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include<string>

using namespace std;

#define screenWidth 1000
#define screenHeight 561
#define JUMPLIMIT 150
#define NUMBEROFENEMY 50
#define NUMBEROFOBSTACLE 40
#define NUMBEROFREWARD 50

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
/*
int characterMode = -1; //when value is 1 sonic speed 
						//when value is 2 run
						//when value is 3 backward run


*/



int gameState = -1;
int levelState = -1;




bool playGame = false;

bool music = true; 



void collusionWithReward();
void restartGame();
void lifeLose();
void setValuesOfLifeBar();

int characterMode = -1; //when value is 1 sonic speed 
//when value is 2 run
//when value is 3 backward run



int passObstacle = 0;
int temp, temp2;


//--------------------level Hardness-------------------------------


int backgroundSpeed = 20;
int enemySpeed = 7;
int jumpSpeed = 15;


//---------------------- level hardness---------------------------

//-----------------------------score----------------------------------
int score = 0;
char score1[10][30] = { "score//score01.bmp", "score//score02.bmp", "score//score03.bmp", "score//score04.bmp", "score//score05.bmp", "score//score06.bmp", "score//score07.bmp", "score//score08.bmp", "score//score09.bmp", "score//score10.bmp" };

int scoreCoordinateX[5];
int scoreCoordinateY[5];

int scoreIndex_1 =0 , scoreIndex_2 = 0, scoreIndex_3=0, scoreIndex_4= 0;

void showScore()
{
	iShowBMP2(962, 490, score1[scoreIndex_1], 0);
	iShowBMP2(929, 490, score1[scoreIndex_2], 0);
	iShowBMP2(896, 490, score1[scoreIndex_3], 0);
	iShowBMP2(863, 490, score1[scoreIndex_4], 0);
}


void updateScore()
{
	//int tempScore = score;
	if (score < 10)
	{
		scoreIndex_1 = score;
	}
	else if (score > 9 && score < 100)
	{
		scoreIndex_1 = score % 10;
		scoreIndex_2 = (score / 10) % 10;
	}
	else if (score > 99 && score < 1000)
	{
		scoreIndex_1 = score % 10;
		scoreIndex_2 = (score / 10) % 10;
		scoreIndex_3 = ((score / 10)/10) % 10;
	}
	else if (score > 999 && score < 10000)
	{
		scoreIndex_1 = score % 10;
		scoreIndex_2 = (score / 10) % 10;
		scoreIndex_3 = ((score / 10) / 10) % 10;
		scoreIndex_4 = (((score / 10) / 10)/ 10) % 10;
	}
}


void showHighScore(){

	FILE* ptr;
	char str[50];
	ptr = fopen("scores.txt", "a+"); // reading the file in append mode
	string scores;
	int all_scores[100];
	int i = 0;

	if (NULL == ptr) {
		printf("file can't be opened \n");
	}


	while (fgets(str, 50, ptr) != NULL) {
		//printf("%s", str);
		//scores += str;
		if (str != "\n"){
			all_scores[i++] = stoi(str); //converting the string into integer and storing it in an array

		}
	}
	fclose(ptr);
	int len = i, a;

	//sorting in descending order to determine high scores...

	for (i = 0; i < len; ++i){
		for (int j = i + 1; j < len; ++j)
		{
			if (all_scores[i] < all_scores[j])
			{
				a = all_scores[i];
				all_scores[i] = all_scores[j];
				all_scores[j] = a;
			}
		}

	}




	int space = 130, max_scores = 10;
	char score_text[1000], c;

	for (int i = 0; i < len; i++){
		strcpy_s(score_text, to_string(all_scores[i]).c_str()); // converting the ints to string first and then char array
		iText(150, screenHeight - (space), score_text, GLUT_BITMAP_TIMES_ROMAN_24); // rendering it on display
		space += 35; // space for the next score
		max_scores--; // if it reaches 0, it means total 10 scores have been painted
		if (max_scores <= 0){
			break;
		}

	}


}
 


/*function to save score in a file in the same directory*/
void saveScore(){
	FILE *fp; //file pointer

	fp = fopen("scores.txt", "a"); //open the existing file in append mode
	char final_score[33];

	itoa(score, final_score, 10); //converting numbers to string

	fprintf(fp, "%s", final_score); // printing final score to text file
	fprintf(fp, "%s", "\n");

	fclose(fp); //close file
}




//------------------------------------score-------------------------------------------------



//-------------------------------------------------------------------------character -----------------------------------------------------

int roundX = 0;
int roundY = 45;
//92
//150
//45



//---------------round character---------------------------------

char roundChar[9][15] = { "round\\1.bmp", "round\\2.bmp", "round\\3.bmp", "round\\4.bmp", "round\\5.bmp", "round\\6.bmp", "round\\7.bmp", "round\\8.bmp", "round\\9.bmp" };

int roundCharacterIndex = 3;

//------------------------round character End -----------------------------

//-------------run charecter ----------------------------

char runChar[14][20] = { "run\\1.bmp", "run\\2.bmp", "run\\3.bmp", "run\\4.bmp", "run\\5.bmp", "run\\6.bmp", "run\\7.bmp", "run\\8.bmp", "run\\9.bmp", "run\\10.bmp", "run\\11.bmp", "run\\12.bmp", "run\\13.bmp", "run\\14.bmp", };
char runBackChar[14][20] = { "runBack\\1.bmp", "runBack\\2.bmp", "runBack\\3.bmp", "runBack\\4.bmp", "runBack\\5.bmp", "runBack\\6.bmp", "runBack\\7.bmp", "runBack\\8.bmp", "runBack\\9.bmp", "runBack\\10.bmp", "runBack\\11.bmp", "runBack\\12.bmp", "runBack\\13.bmp", "runBack\\14.bmp", };
int runIndex = 8;
int runBackIndex = 13;


//-----------------run end charecter -------------------



//-----------------stand character-------------------------

char standChar[3][15] = { "stand\\1.bmp", "stand\\2.bmp", "stand\\3.bmp" };
bool standPosition = true;
int standCounter = 0;
//--------------stand charater end ---------------------------


//---------------------jump--------------------------
char jumpChar[2][20] = { "jump\\up.bmp", "jump\\down.bmp" };
bool jump;
bool jumpUP;
int CoordinateJump = 0;

//--------------------jump end ---------------------





//---------------------------------------------------------------character ---------------------------------------------

//--------------run,jump,sonic---------------------

void sonicAllMode()
{

	if (jump)
	{
		if (jumpUP)
		{
			iShowBMP2(roundX, roundY + CoordinateJump, jumpChar[0], 0);
		}
		else
		{
			iShowBMP2(roundX, roundY + CoordinateJump, jumpChar[1], 0);
		}
	}
	else
	{
		/*
		iCircle(0, 0, 50);
		iText(250, 250, "Play Game", GLUT_BITMAP_HELVETICA_18);

		*/
		if (standPosition)
		{
			iShowBMP2(roundX, roundY, "stand\\2.bmp", 0);
		}
		else if (characterMode == 1)
		{
			iShowBMP2(roundX, roundY, roundChar[roundCharacterIndex], 0);
			standCounter++;
			if (standCounter >= 100)
			{
				standCounter = 0;
				roundCharacterIndex = 0;
				standPosition = true;
				characterMode = -1;

			}
		}

		else if (characterMode == 2)
		{
			iShowBMP2(roundX, roundY, runChar[runIndex], 0);
			standCounter++;
			if (standCounter >= 100)
			{
				standCounter = 0;
				runIndex = 0;
				standPosition = true;
				characterMode = -1;

			}
		}
		
		else if (characterMode == 3)
		{
			iShowBMP2(roundX, roundY, runBackChar[runBackIndex], 0);
			standCounter++;
			if (standCounter >= 100)
			{
				standCounter = 0;
				runIndex = 0;
				standPosition = true;
				characterMode = -1;

			}
		}
	}

}

//----------------------------------------------------------



//---------------enemy---------------------------------

char enemyChar[10][20] = { "enemy\\1.bmp", "enemy\\2.bmp", "enemy\\3.bmp", "enemy\\4.bmp","enemy\\blast1.bmp", "enemy\\blast2.bmp" , "enemy\\blast3.bmp" , "enemy\\blast4.bmp"};

bool enemyShow[NUMBEROFENEMY];

int enemyX[NUMBEROFENEMY];
int enemyY[NUMBEROFENEMY];

int enemyCollusion = 0;

int enemyIndex = 1;

void enemyAnimation()
{
	if (playGame)
	{
		enemyIndex++;
		if (enemyIndex >= 3)
		{
			enemyIndex = 1;
		}
		
	}
	

}


void collusionWithEnemy()
{
	for (int i = 0; i < NUMBEROFENEMY; i++)
	{
		if (roundX + 65 >= enemyX[i] && roundY + CoordinateJump <= enemyY[i] + 45 && roundX  <= enemyX[i] +75 )
		{
			if (enemyShow[i])
			{
				if (music)
				{
				//	mciSendString();
				}
				enemyCollusion++;
				cout << enemyCollusion << endl;
				lifeLose();
			}
				enemyShow[i] = false;			
		}
	}
}

int enemyScore = 0;
void scoreCountingWithEnemy()
{
	if (roundX > enemyX[enemyScore])
	{
		if (enemyShow[enemyScore])
		{
			score += 5;
			cout << "score : " << score << endl;

		}
		enemyScore++;
	}
}



void moveEnemy()
{
	if (playGame)
	{
		for (int i = 0; i < NUMBEROFENEMY; i++)
			enemyX[i] -= enemySpeed;

		collusionWithEnemy();
		collusionWithReward();
		scoreCountingWithEnemy();
		updateScore();
	}
	

}

void moveEnemy2()
{
	if (playGame)
	{
		for (int i = 0; i < NUMBEROFENEMY; i++)
			enemyX[i] -= backgroundSpeed; 
			
	}
	

}


void randomEnemy()
{
	enemyShow[0] = true;
	enemyX[0] = 1200;
	enemyY[0] = roundY;
	for (int i = 1; i < NUMBEROFENEMY; i++)
	{
		enemyShow[i] = true;
		enemyX[i] = enemyX[i - 1] + ((rand() % 5)+1) * 300;
		enemyY[i] = enemyY[i - 1];
	}

}


int blastIndex = 5;
//-------------this function is for enemy showing-------------
void showEnemy(){
	for (int i = 0; i < NUMBEROFENEMY; i++)
	{
		if (enemyShow[i])
		{
			if (i % 3 == 0)
			{
				iShowBMP2(enemyX[i], enemyY[i], enemyChar[0], 0);
			}
			else
				iShowBMP2(enemyX[i], enemyY[i], enemyChar[enemyIndex], 0);
		}
		else
		{
			iShowBMP2(enemyX[i], enemyY[i], enemyChar[blastIndex], 0);
		}

	}

}



// -------------- - obstacle--------------

char obstacleChar[7][20] = { "obstacle\\1.bmp", "obstacle\\2.bmp", "obstacle\\3.bmp", "obstacle\\4.bmp", "obstacle\\5.bmp", "obstacle\\6.bmp" };

int obstacleX[NUMBEROFOBSTACLE];
int obstacleY[NUMBEROFOBSTACLE];

int lifeBar = 5;

void setValueOfObstacle()
{

	obstacleX[0] = 700;
	obstacleY[0] = roundY;
	for (int i = 1; i < NUMBEROFOBSTACLE; i++)
	{
		obstacleX[i] = obstacleX[i - 1] + ((rand() % 5) * 400);
		obstacleY[i] = obstacleY[i - 1];

	}
}

bool obstacle = true;

void collusionWithObstacle()
{
	for (int i = 0; i < NUMBEROFOBSTACLE; i++)
	{
		if (roundX + 30 < obstacleX[i] && roundY + CoordinateJump > obstacleY[i] + 45 && roundX > obstacleX[i] + 30)
		{

		}

	}
}


void runObstacle()
{
	if (playGame)
	for (int i = 0; i < NUMBEROFOBSTACLE; i++)
	{
		obstacleX[i] -= 20;

		//	collusionWithObstacle();
	}



}



void showObstacle()
{
	for (int i = 0; i < NUMBEROFOBSTACLE; i++)
	{

		{
			iShowBMP2(obstacleX[i], obstacleY[i], obstacleChar[0], 0);
		}
	}

}




//---------------obstacle end---------------


//----------------reward ring--------------

bool rewardShow[NUMBEROFREWARD];
int rewardCoordinateX[NUMBEROFREWARD];
int rewardCoordinateY[NUMBEROFREWARD];
int rewardIndex = 1;

void setRewardCoordinateValues()
{
	rewardShow[0] = true;
	rewardCoordinateX[0] = ((rand() % 3) + 1) * 200;
	rewardCoordinateY[0] = roundY + 18 + (rand() % 10) * 15;
	for (int i = 1; i < NUMBEROFREWARD; i++)
	{
		rewardShow[i] = true;
		rewardCoordinateX[i] = rewardCoordinateX[i - 1] + ((rand() % 5) + 1) * 200;
		rewardCoordinateY[i] = roundY + 18 + (rand() % 10) * 15;
	}
}

void showReward()
{
	for (int i = 0; i < NUMBEROFREWARD; i++)
	{
		if (rewardShow[i])
		{
			iShowBMP2(rewardCoordinateX[i], rewardCoordinateY[i], obstacleChar[rewardIndex], 0);
		}
	}


}


void rewardAnimation()
{
	rewardIndex++;
	if (rewardIndex > 5)
	{
		rewardIndex = 1;
	}
}


void runReward()
{
	if (playGame)
	for (int i = 0; i < NUMBEROFREWARD; i++)
	{
		rewardCoordinateX[i] -= backgroundSpeed;

		//	collusionWithObstacle();
	}

}


void collusionWithReward()
{

	for (int i = 0; i < NUMBEROFREWARD; i++)
	{
		if (roundX + 65 >= rewardCoordinateX[i] && roundY + CoordinateJump + 90 >= rewardCoordinateY[i] && roundX <= rewardCoordinateX[i] + 20 && roundY + CoordinateJump <= rewardCoordinateY[i] + 30)
		{
			if (rewardShow[i])
			{

				//PlaySound("music//bip.WAV", NULL, SND_SYNC);
				if (music)
				{
					mciSendString("play music//coinhit.wav", NULL, 0, NULL);
				}



				score += 15;
				cout << "score : " << score << endl;
			}


			rewardShow[i] = false;

		}
	}

}


//--------------end reward ring-------------


/*
void Blasting()
{
	for (int i = 0; i < NUMBEROFENEMY; i++)
	{

		if (enemyShow[i])
		{
			blastIndex++;
			if
		}

	}
}
*/
//---------enemy end---------------------

/*
//--------------firing-------------------------

char fire[1][20] = { "fire\\1.bmp" };



int enemyFireX[20];
int enemyFireY[20];

void setFireIndex()
{
	enemyFireX[0] = 10;
	enemyFireY[0] = 40;
	for (int i = 1; i < 20; i++)
	{
		enemyFireX[i] = enemyFireX[i - 1] + 100;
		enemyFireY[i] = 40;
	}
}




void firing()
{
	if (playGame)
	for (int i = 0; i < 20; i++)
	{
		enemyFireX[i] -= 5;
		if (enemyFireX[i] < -1000)
			enemyFireX[i] = 10;
	}
	
}

void showFiring()
{
	for (int i = 0; i < NUMBEROFENEMY; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (enemyFireX[j]< 10 && enemyX[i]< screenWidth && i%3 ==0)
			iShowBMP2(enemyX[i] + enemyFireX[j], enemyY[i] + enemyFireY[j], fire[0], 0);
		}

		
	}
	
}


//----------------end firing-----------------------------------

*/



//-------------------------Home Menu Bar ---------------------------------

int option,resume,gameover,highscore;


char menu[4][20] = { "menu\\menu1.bmp", "menu\\menu3.bmp", "menu\\menu2.bmp", "menu\\menu4.bmp" };
struct buttonCoordinate
{
	int x;
	int y;
}menuCoordinate[4];

void setValue(){
	int sum = 361;
	for (int i = 0; i < 4; i++)
	{
		menuCoordinate[i].x = 150;
		menuCoordinate[i].y = sum;
		sum -= 100;
	}
}

void menuBar()
{
	iShowBMP(0, 0, "backgroud.bmp");
	for (int i = 0; i < 4; i++)
	{
		iShowBMP2(menuCoordinate[i].x, menuCoordinate[i].y, menu[i], 0);
	}
	iShowBMP2(1000 - 100, 10, "menu\\exit.bmp", 0);
	iShowBMP2(480, 80, "menu\\Soniclogo.bmp", 0);
	iShowBMP2(5, 5, "menu\\credit.bmp",0);

}
//-------------------------Home Menu End--------------------------------------


//------------------background ----------------------
bool runWithCharecter = false;
char background1[20][20] = { "background\\1.bmp", "background\\2.bmp", "background\\3.bmp", "background\\4.bmp", "background\\5.bmp", "background\\6.bmp", "background\\7.bmp", "background\\8.bmp", "background\\9.bmp", "background\\10.bmp", "background\\11.bmp", "background\\12.bmp", "background\\13.bmp", "background\\14.bmp", "background\\15.bmp", "background\\16.bmp", "background\\17.bmp", "background\\18.bmp", "background\\19.bmp", "background\\20.bmp" };
int setBGValue;
double slowBackground = 0;
struct backggroundCoordinate
{
	int x;
	int y;
}bgCoordinate1[20];


void setBGCordinate1()
{
	setBGValue = 0;
	for (int i = 0; i < 20; i++)
	{
		bgCoordinate1[i].x = setBGValue;
		bgCoordinate1[i].y = 0;
		setBGValue += 50;
	}
}


void runBackground()
{
	
	{

		for (int i = 0; i < 20; i++)
		{
			bgCoordinate1[i].x -= 50;

			if (bgCoordinate1[i].x < 0)
			{
				bgCoordinate1[i].x = screenWidth - 50;
			}
		}
	}

}

//-----------------background end----------------



//------------------showing background--------------

void showBackground()
{

	for (int i = 0; i < 20; i++)
	{
		iShowBMP(bgCoordinate1[i].x, bgCoordinate1[i].y, background1[i]);
	}

}



//-------------------end game------------------

void endGame()
{
	if (enemyX[NUMBEROFENEMY - 1] + 1000 < roundX)
		restartGame();
}


//------------------

//---------------game over-----------------

void showGameOver()
{
	if (lifeBar <= 0)
	{
		iText(400, 250, "Game Over");

	}
}



//---------------back and home button --------------

void backButton()
{
	iShowBMP2( 5 , screenHeight - 50, "menu\\back.bmp", 0);
}

void HomeButton()
{

}



int pauseIndex = 0;
void pauseButton()
{
	char pauseButton[2][20] = { "menu\\pause.bmp", "menu\\play.bmp" };
	iShowBMP2(55, screenHeight - 50, pauseButton[pauseIndex] ,0);
	if (!playGame && pauseIndex == 1)
	{
		iShowImage(100, 29, 800, 503, resume);
	}
}

//---------------life bar ---------------------
char heartChar[20] = "lifebar\\heart.bmp";

struct lifeBar
{
	int x, y;
	bool show;
}heart[5];


void setValuesOfLifeBar()
{
	int diff = 0;
	for (int i = 0; i < 5; i++)
	{
		heart[i].x = screenWidth - 300 + diff;
		heart[i].y = screenHeight - 135;
		diff += 60;
		heart[i].show = true;
	}
}

bool replay = false;
int index = 4;
void lifeLose()
{
	//int diff = 3;
	
	if (index > 0)
	{
		if (enemyCollusion % 1 == 0)
		{
			heart[index].show = false;
			cout << heart[index].show<< " "<< index <<endl;
			index--;
			
			
		}
	}
	else
	{
		playGame = false;	
		replay = true;
		index = 4;
	}
		
		
}

void showHeart()
{
	for (int i = 0; i < 5; i++)
	{
		if (heart[i].show)
		iShowBMP2(heart[i].x, heart[i].y, heartChar, 0);
	}
	
}


//---------------------life bar ------------------------------------



int image[3];
int bgIndex = 2;

int bgX = 0;
int bgX1 = 1000;

int bgX2 = 0;
int bgX12 = 1000;

void bg()
{
	iShowImage(bgX, 0, screenWidth, screenHeight, image[bgIndex]);

	iShowImage(bgX1, 0, screenWidth, screenHeight, image[bgIndex]);
}


void bg2()
{
	iShowImage(bgX2, 0, screenWidth, screenHeight, image[1]);

	iShowImage(bgX12, 0, screenWidth, screenHeight, image[1]);
}




void runBG()
{
	bgX-=backgroundSpeed;
	if (bgX <= -1000)
	{
		bgX = 1000;
	}
	bgX1-=backgroundSpeed;
	if (bgX1 <= -1000)
	{
		bgX1 = 1000;
	}
}

void runBG2()
{
	bgX2 -= 20;
	if (bgX2 <= -1000)
	{
		bgX2 = 1000;
	}
	bgX12 -= 20;
	if (bgX12 <= -1000)
	{
		bgX12 = 1000;
	}
}



void gameOver()
{
	if (replay)
	{
		iShowImage(0, 0, screenWidth, screenHeight, gameover);
		iShowBMP2(420, screenHeight-495, score1[scoreIndex_1], 0);
		iShowBMP2(455, screenHeight - 495, score1[scoreIndex_2], 0);
		iShowBMP2(490, screenHeight - 495, score1[scoreIndex_3], 0);
		iShowBMP2(525, screenHeight - 495, score1[scoreIndex_4], 0);
		
	}
}

//----------------------- --------------option & music bar----------------------------------------------

char musicOffOn[2][20] = { "music\\on.bmp", "music\\off.bmp" };
int bgmOnOff = 0;
int bip = 0;


void optionBar()
{
	iShowImage(0, 0, screenWidth, screenHeight, option);
	iShowBMP2(365, screenHeight - 230, musicOffOn[bgmOnOff], 0);
	iShowBMP2(365, screenHeight - 380, musicOffOn[bip], 0);

}



void iDraw()
{
	iClear();
	if (gameState == -1)
	{
		menuBar();
	}
	if (gameState == 0)
	{

		if (levelState == -1)
		{
			iShowBMP(0, 0, "menu\\chooseBG.bmp");
			iShowImage(90, screenHeight -  380, 250, 200, image[0]);
			iShowImage(400, screenHeight - 380, 250, 200, image[1]);
			iShowImage(700, screenHeight - 380, 250, 200, image[2]);
		}
		else if (levelState == 0)
		{

		}
		
		else if (levelState == 1)
		{
			//showBackground();
			bg();

			showObstacle();

			showReward();
			//iShowBMP2(rewardX, rewardY, obstacleChar[rewardIndex], 0);

			showEnemy();

			//showFiring();

			sonicAllMode();



			showScore();
			showGameOver();

			backButton();

			showHeart();


			pauseButton();

			gameOver();
		}

	
		
		

	}
	if (gameState == 1)
	{
		iShowImage(0, 0, screenWidth, screenHeight, highscore);
		showHighScore();
		//iText(250, 250, "Score", GLUT_BITMAP_HELVETICA_18);
		backButton();
	}
	if (gameState == 2)
	{
		optionBar();
		backButton();
	}
	if (gameState == 3)
	{

	//	iText(250, 250, "Help", GLUT_BITMAP_HELVETICA_18);
		bg2();
		sonicAllMode();
		backButton();


	}
	if (gameState == 4)
	{
		iShowBMP(0, 0, "menu\\creditpage.bmp");
		backButton();
	}
	

}





/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{
	
}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	
}

void iMouse(int button, int state, int mx, int my)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (gameState == -1)
		{
			for (int i = 0; i < 4; i++)
			{
				if (mx >= menuCoordinate[i].x && mx <= (menuCoordinate[i].x + 200) && my >= menuCoordinate[i].y && my <= menuCoordinate[i].y + 94)
				{
					gameState = i; 
					
					
				}
			}
			if (mx >= screenWidth-100 && mx <= screenWidth-20 && my >= 10 && my <= 90)
			{
			//	gameState = 4;
				exit(0);
			}
			if (mx >= 5 && mx <= 5 + 100 && my >= 5 && my <= 5 + 38)
			{
				gameState = 4;
			}
		}
		
		for (int i = 0; i <= 4; i++)
		{
			if (gameState == i)
			{
				if (mx >= 5 && mx <= 5+40 && my >= screenHeight-50 && my <= screenWidth-10)
				{
					gameState = -1;
					restartGame();
					playGame = false;

				}
			}
			
		}
		
		if (gameState == 0)
		{
			if (mx >= 55 && mx <= 55 + 40 && my >= screenHeight - 50 && my <= screenWidth - 10)
			{
				if (playGame)
				{
					playGame = false;
					pauseIndex = 1;
				}
					
				else
				{
					playGame = true;
					pauseIndex = 0;

				}
					

			}
		}
		if (gameState == 2)
		{
			if (mx >= 365 && mx <= 365+150 && my >= 561 - 230 && my <= 561 - 230 +56)
			{
				if (bgmOnOff == 0)
				{
					PlaySound(0, 0, 0);
					bgmOnOff = 1;
				}
				else
				{
					PlaySound("music\\mainbgm.wav", NULL, SND_ASYNC | SND_LOOP);
					bgmOnOff = 0;
				}
			}
			else if (mx >= 365 && mx <= 365 + 150 && my >= 561 - 380 && my <= 561 - 380 + 56)
			{
				if (music)
				{
					music = false;
					bip = 1;
				}
				else
				{
					music = true;
					bip = 0;
				}
			}
			
		}
		
	}

	if (gameState == 0 && replay)
	{
		if (mx >= 680 && mx <= 820 && my >= 561 - 412 && my <= 561 - 367)
		{
			replay = false;
			restartGame();
		}
		else if (mx >= 680 && mx <= 820 && my >= 561 - 490 && my <= 561 - 448)
		{
			replay = false;
			restartGame();
			gameState = -1;
		}
	}
	if (gameState == 0 && !playGame)
	{
		if (mx >= 137 && mx <= 258 && my >= 561 - 390 && my <= 561 - 331)
		{
			playGame = true;
			pauseIndex = 0;
		}
		else if (mx >= 267 && mx <= 396 && my >= 561 - 390 && my <= 561 - 331)
		{
			replay = false;
			restartGame();
		}
		else if (mx >= 415 && mx <= 537 && my >= 561 - 390 && my <= 561 - 331)
		{
			replay = false;
			restartGame();
			gameState = -1;
		}


		if (gameState == 0 && levelState == -1)
		{	
			if (mx >= 90 && mx <= 250 + 90 && my >= screenHeight - 380 && my <= screenHeight - 380 + 200)
			{
				levelState = 1;
				roundY = 92;
				bgIndex = 0;
				restartGame();
				playGame = true;
				
			}
			else if (mx >= 400 && mx <= 250 + 400 && my >= screenHeight - 380 && my <= screenHeight - 380 + 200)
			{
				levelState = 1;
				roundY = 150;
				bgIndex = 1;
				restartGame();
				playGame = true;

			}
			else if (mx >= 700 && mx <= 250 + 700 && my >= screenHeight - 380 && my <= screenHeight - 380 + 200)
			{
				levelState = 1;
				roundY = 45;
				bgIndex = 2;
				restartGame();
				playGame = true;
			}
		}
		

	}
	
	
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key)
{
	if (key == '\r')
	{
		
	}
	/*
	if (key == ' ')
	{

		characterMode = 1;

		if (roundX >= 400)
		{
			for (int i = 0; i < 20; i++)
			{
				bgCoordinate1[i].x -= 50;
				runObstacle();
				if (bgCoordinate1[i].x < 0)
				{
					bgCoordinate1[i].x = screenWidth - 50;
				}
			}
			roundCharacterIndex++;
			moveEnemy2();
			moveEnemy2();
			moveEnemy2();
			moveEnemy2();
			moveEnemy2();
			moveEnemy2();
			moveEnemy2();
			moveEnemy2();
			moveEnemy2();
			
			if (roundCharacterIndex >= 9)
			{
				roundCharacterIndex = 0;
			}
			standPosition = false;
		}
		else
		{
			roundX += 10;
			if (roundX >= 1000)
				roundX = 0;
			roundCharacterIndex++;
			if (roundCharacterIndex >= 8)
			{
				roundCharacterIndex = 3;
			}
			standPosition = false;
		}

	}

	*/
	
	
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT

for (int i = 0; i < NUMBEROFOBSTACLE; i++)
{
if (roundX + 30 < obstacleX[i] && roundY + CoordinateJump > obstacleY[i] + 45 && roundX > obstacleX[i] + 30)
{

}

}
*/

void iSpecialKeyboard(unsigned char key)
{

	
	if (key == GLUT_KEY_RIGHT)
	{
		if (gameState == 0)
		{
			if (playGame)
			{


				characterMode = 2;

				if (roundX >= 200)
				{
					if (!(roundX + 80 >= obstacleX[passObstacle] && roundY + CoordinateJump <= obstacleY[passObstacle] + 45 && roundX <= obstacleX[passObstacle] + 30))
					{
						if (roundX > obstacleX[passObstacle])
							passObstacle++;

						//	if (temp == runIndex)
						//	{
						runBG();
						
						runObstacle();
						moveEnemy2();
						runReward();
						collusionWithReward();
					
					/*	for (int i = 0; i < 20; i++)
						{

							//slowBackground += .5;
							//	if (slowBackground == 1)

							bgCoordinate1[i].x -= 50;

							if (bgCoordinate1[i].x < 0)
							{
								bgCoordinate1[i].x = screenWidth - 50;
							}

							//	slowBackground = 0;
						} */
						//	}
					}

					/*
						slowBackground += .4;
						temp = runIndex + .8;
						if (slowBackground >= 1)
						{
						//temp = runIndex + 1;


						slowBackground = 0;

						}
						//if (temp == runIndex)
						//	temp2 = temp;
						*/
					runIndex++;

					if (runIndex > 13)
					{
						runIndex = 8;
					}
					standPosition = false;
				}
				else
				{
					collusionWithReward();
					roundX += 10;
					//if (roundX >= 301)
					//	roundX = 0;
					runIndex++;
					if (runIndex > 13)
					{
						runIndex = 8;
					}
					standPosition = false;
				}


			}
		}


	}
	if (key == GLUT_KEY_LEFT)
	{
		if (playGame)
		{

			characterMode = 3;

			roundX -= 10;
			if (roundX <= 0)
				roundX = 0;

			runBackIndex++;
			if (runBackIndex > 13)
			{
				runBackIndex = 8;
			}
			standPosition = false;
		}

	}
	
	if (key == GLUT_KEY_UP)
	{
		if (!jump)
		{
			jump = true;
			jumpUP = true;
		}
	}
	
}

void timerForJump()
{
	if (jump && playGame)
	{
		if (jumpUP)
		{
			CoordinateJump += jumpSpeed;
			if (CoordinateJump >= JUMPLIMIT)
			{
				jumpUP = false; 
			}
		}
		else
		{
			CoordinateJump -= jumpSpeed;
			if (CoordinateJump < 0)
			{
				jump = false;
				CoordinateJump = 0;
			}
		}
	}
}



//------------------restart game----------------------

void restartGame()
{
	
	saveScore();
	//lifeBar = 3;
	setValue();
	setBGCordinate1();
	randomEnemy();
	setValueOfObstacle();
	enemyCollusion = 0;
	roundX = 0;
	passObstacle = 0;
	setValuesOfLifeBar();
	setRewardCoordinateValues();
	score = 0;
	index = 4;
	scoreIndex_1 = 0;
	scoreIndex_2 = 0;
	scoreIndex_3 = 0;
	scoreIndex_4 = 0;
	playGame = true;
}

void loadImage()
{
	image[0] = iLoadImage("background\\bg.png");
	image[1] = iLoadImage("background\\bg2.png");
	image[2] = iLoadImage("background\\bg3.png");
	option = iLoadImage("menu\\Music.png");
	resume = iLoadImage("menu\\resume.png");
	gameover = iLoadImage("menu\\gameover.png");
	highscore = iLoadImage("menu\\highscore.png");
}


int main()
{
	
	restartGame();
	

	iSetTimer(1, moveEnemy);
	
	iSetTimer(250, enemyAnimation);
	iSetTimer(1, timerForJump);
	iSetTimer(300, rewardAnimation);

	iSetTimer(10, runBG2);
	
	//PlaySound("music\\mainbgm.wav", NULL, SND_ASYNC | SND_LOOP);
	
	iInitialize(screenWidth, screenHeight, "Sonic The Hedgehog");


	loadImage();
	iStart();
	return 0;
}