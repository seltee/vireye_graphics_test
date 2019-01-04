#include <math.h>
#include "test3.h"
#include "string.h"
#include "sprites.h"

#define SHIFT_FACROT 14
#define FACTOR (1<<SHIFT_FACROT)
#define HEIGHT 90

unsigned char displaySprite[160*HEIGHT];


void drawRotatedSprite(const unsigned char *data, int x, int y, float rotation){
	int sinVal = sin(rotation)*FACTOR;
	int cosVal = cos(rotation)*FACTOR;
	int targetX, targetY;
	unsigned char color;
	
	for (int iy = -24; iy < 24; iy++){
		for (int ix = -24; ix < 24; ix++){
			int Xsource = ((ix*cosVal)>>SHIFT_FACROT)+((iy*sinVal)>>SHIFT_FACROT)+16;
			int Ysource = -((ix*sinVal)>>SHIFT_FACROT)+((iy*cosVal)>>SHIFT_FACROT)+16;

			if (Xsource >= 0 && Xsource < 32 && Ysource >= 0 && Ysource < 32){
				color = data[Xsource+(Ysource<<5)];
				if (color){
					targetX = ix+x-24; 
					targetY = iy+y-24;
					if (targetX >= 0 && targetX < 160 && targetY >= 0 && targetY < HEIGHT){
						displaySprite[targetX + targetY*160] = color;
					}
				}
			}
		}
	}
}


void runTest4(Engine *engine, Display *display){
	char string[16];
	int cameraX = 0, cameraY = 0;
	float rotator = 0;
	int iterator = 0;
	int precY;
	while(1){
		rotator += 0.01f;
		iterator++;
		
		// Draw our abstract waves
		for (int iy=0;iy<HEIGHT;iy++){
			precY = iy*160;
			for (int ix=0;ix<160;ix++){
				displaySprite[ix+precY] = (ix+iy+(iterator)+cameraX+cameraY)%40 < 20 ? 6 : 7;
			}
		}

		// Update camera position
		cameraX += Input::getXAxis()>>8;
		cameraY -= Input::getYAxis()>>8;
		
		drawRotatedSprite(tank, 10-cameraX, 10-cameraY, rotator);
		drawRotatedSprite(tank, 60-cameraX, 10-cameraY, rotator);
		drawRotatedSprite(tank, 40-cameraX, 80-cameraY, rotator);
		drawRotatedSprite(tank, 100-cameraX, 70-cameraY, rotator);
		
		engine->displaySprite(displaySprite, 0, 120-HEIGHT, 160, HEIGHT);
		
		// Draw fps information
		itoa(display->getFPS(), string);
		Text::displayString(engine, string, 4, 0, 0);
		
		display->draw();
	}
}
