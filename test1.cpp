#include "test1.h"

void runTest1(Engine *engine, Display *display){
	// Initial position of player
	int positionX = 160-8;
	int positionY = 120-8;
	
	// Other parameters
	int counter = 0;
	int spaceMove = 0;
	short int bulletX = 0;
	short int bulletY = 0;
	bool bulletAlive = false;
	char string[16];
	
	// Our space (space is a matrix of sprites)
	const unsigned char *spaceMatrix1[90];
	const unsigned char *spaceMatrix2[90];
	for (int i = 0; i < 90; i++){
		spaceMatrix1[i] = space[i % 2];
		spaceMatrix2[i] = space2[i % 2];
	}
	
	// Game cycle
	while(1){			
		// Display space
		// See engine.h for all available drawing functions
		spaceMove++;
		engine->displaySpriteMatrix(spaceMatrix1, 16, 0, (spaceMove % 32) - 32, 10, 9);
		engine->displaySpriteMatrix(spaceMatrix2, 16, 0, ((spaceMove << 2) % 32) - 32, 10, 9);
				
		// Update player position
		positionX += Input::getXAxis()>>8;
		positionY -= Input::getYAxis()>>8;
						
		// Shoot bullet
		if (Input::getState(INPUT_A) && !bulletAlive){
			bulletX = positionX + 3;
			bulletY = positionY;
			bulletAlive = true;
		}

		// Draw player
		counter++;
		engine->displaySprite(shipSprite[counter%2], positionX, positionY, 8, 8);
						
		// Draw bullet
		if (bulletAlive){
			bulletY -= 6;
			bulletAlive = bulletY < 0 ? false : true;
			engine->displaySprite(bulletSprite, bulletX, bulletY, 4, 4);
		}
			
		// Draw axis information
		itoa(display->getFPS(), string);
		Text::displayString(engine, string, 4, 0, 0);

		// Draw sprites on real screen
		display->draw();
	}
}

