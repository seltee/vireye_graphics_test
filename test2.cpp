#include <math.h>
#include "test2.h"

void runTest2(Engine *engine, Display *display){
	unsigned int guyCount = 3;
	float angle = 0;
	float counter;
	char string[16];
	bool clicked = false;
	
	while(1){
		if (!Input::getState(INPUT_A) && !Input::getState(INPUT_B)){
			clicked = false;
		}
		
		if (Input::getState(INPUT_A) && !clicked && guyCount > 3){
			clicked = true;
			guyCount--;
		}
		
		if (Input::getState(INPUT_B) && !clicked && guyCount < 33){
			clicked = true;
			guyCount++;
		}
		
		angle = 6.28f / guyCount;
		counter+=0.02f;
		
		for (int i = 0; i < guyCount; i++){
			engine->displaySprite(guy, 160 + sin(angle*i - counter)*24 - 16, 120 + cos(angle*i - counter)*24 - 16, 16, 16);
		}
		
		for (int i = 0; i < guyCount; i++){
			engine->displaySprite(guy, 160 + sin(angle*i + counter*2)*56 - 16, 120 + cos(angle*i + counter)*56 - 16, 16, 16);
		}
		
		for (int i = 0; i < guyCount; i++){
			engine->displaySprite(guy, 160 + sin(angle*i - counter*3)*88 - 16, 120 + cos(angle*i - counter)*88 - 16, 16, 16);
		}
		
		// Draw fps information
		itoa(display->getFPS(), string);
		Text::displayString(engine, string, 4, 0, 0);
		
		// Draw guys information
		itoa(guyCount*3, string);
		Text::displayString(engine, string, 4, 0, 24);
		
		display->draw();
	}
}
