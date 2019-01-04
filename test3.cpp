#include <math.h>
#include "test3.h"
#include "string.h"

// Each byte contains 8 pixels
unsigned char spritemask[40*240];

short int figure1[][2] = {
	{ 15, 15 },
	{ 15, -15 },
	{ -15, -15 },
	{ -15, 15 }
};

short int figure2[][2] = {
	{ -15, 20 },
	{ -9, 20 },
	{ -9, 15 },
	{ -2, 15 },
	{ -2, 28 },
	{ 2, 28 },
	{ 2, 15 },
	{ 9, 15 },
	{ 9, 20 },
	{ 15, 20 },
	{ 15, -20 },
	{ 9, -20 },
	{ 9, -18 },
	{ -9, -18 },
	{ -9, -20 },
	{ -15, -20 }
};

short int figure3[][2] = {
	{ -20, -5 },
	{ 0, 10 },
	{ 20, -5 },
	{ 0, 0 }
};

int absint(int val){
	return val < 0 ? -val : val;
}

void setPixel(int x, int y){
	if (x >= 0 && y >= 0 && x < 320 && y < 240){
		unsigned int adress = x/8 + y*40;
		unsigned char pixel = spritemask[adress];
		pixel = pixel | (0x80 >> (x%8));
		spritemask[adress] = pixel;
	}
}

void drawLine(int x0, int y0, int x1, int y1){
	int dx = absint(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = absint(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
    setPixel(x0, y0);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

void drawFigure(short int figure[][2], int points, int x, int y, float rotation){
	float sinVal = sin(rotation);
	float cosVal = cos(rotation);
	float x0, x1, y0, y1;
	
	x0=figure[points-1][0]*cosVal+figure[points-1][1]*sinVal; 
	y0=figure[points-1][1]*cosVal-figure[points-1][0]*sinVal;
	
	for (int i = 0; i < points; i++){
		x1=figure[i][0]*cosVal+figure[i][1]*sinVal; 
		y1=figure[i][1]*cosVal-figure[i][0]*sinVal; 
		
		drawLine(x0+x, y0+y, x1+x, y1+y);
		
		x0 = x1;
		y0 = y1;
	}
}

void runTest3(Engine *engine, Display *display){
	char string[16];
	float rotator = 0;
	
	while(1){
		memset(spritemask, 0, 40*240);
		
		rotator += 0.01;
		
		drawFigure(figure1, 4, 40, 40, rotator);
		drawFigure(figure1, 4, 200, 150, -rotator);
		drawFigure(figure1, 4, 140, 50, rotator*2);
		drawFigure(figure1, 4, 300, 200, -rotator*2);
		drawFigure(figure2, 16, 160, 120, rotator*0.5);
		drawFigure(figure3, 4, 40, 200, rotator*-2.5);
		drawFigure(figure3, 4, 60, 180, rotator*4.0);
		drawFigure(figure3, 4, 80, 160, rotator*3.0);
		
		engine->displaySpriteMask(spritemask, 4, 0, 0, 40, 240, false);
		
		// Draw fps information
		itoa(display->getFPS(), string);
		Text::displayString(engine, string, 4, 0, 0);
		
		display->draw();
	}
}
