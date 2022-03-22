

using namespace std;

#define screenWidth 1000
#define screenHeight 561
#define JUMPLIMIT 150



//-------------------------Home Menu Bar ---------------------------------
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
	iShowBMP2(1000 - 150, 0, "menu\\credit.bmp", 0);

}
//-------------------------Home Menu End--------------------------------------



