// -------------- - obstacle--------------

char obstacleChar[7][20] = { "obstacle\\1.bmp", "obstacle\\2.bmp", "obstacle\\3.bmp", "obstacle\\4.bmp", "obstacle\\5.bmp", "obstacle\\6.bmp" };

int obstacleX = 500;
int obstacleY = 92;

int rewardX = 400;
int rewardY = 140;
int rewardIndex = 1;

void runObstacle()
{
	obstacleX -= 10;
	if (obstacleX <= 0)
		obstacleX = screenWidth - 95;

}

void roundReward()
{
	rewardIndex++;
	if (rewardIndex >= 6)
	{
		rewardIndex = 1;
	}
}


//---------------obstacle end---------------

