

#define screenWidth 1000
#define screenHeight 561
#define JUMPLIMIT 150
//------------------background ----------------------
bool runWithCharecter = false;
char background1[20][20] = { "background\\1.bmp", "background\\2.bmp", "background\\3.bmp", "background\\4.bmp", "background\\5.bmp", "background\\6.bmp", "background\\7.bmp", "background\\8.bmp", "background\\9.bmp", "background\\10.bmp", "background\\11.bmp", "background\\12.bmp", "background\\13.bmp", "background\\14.bmp", "background\\15.bmp", "background\\16.bmp", "background\\17.bmp", "background\\18.bmp", "background\\19.bmp", "background\\20.bmp" };
int setBGValue = 0;
double slowBackground = 0;
struct backggroundCoordinate
{
	int x;
	int y;
}bgCoordinate1[20];


void setBGCordinate1()
{
	for (int i = 0; i < 20; i++)
	{
		bgCoordinate1[i].x = setBGValue;
		bgCoordinate1[i].y = 0;
		setBGValue += 50;
	}
}


void runBackground()
{
	if (playGame)
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