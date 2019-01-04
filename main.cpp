#include "display_ili9341.h"
#include "engine.h"
#include "input.h"
#include "text.h"
#include "helpers.h"
#include "hardware.h"
#include "sprites.h"
#include "test1.h"
#include "test2.h"
#include "test3.h"
#include "test4.h"

//#define RUN_TEST_1
//#define RUN_TEST_2
//#define RUN_TEST_3
#define RUN_TEST_4

int main(void)
{
	// Init all of the cpu hardware. Note: display has it's own hardware initialization
	if (initHardware()){	
		// initialization
		Engine engine;
		Display_ILI9341 display;
		engine.init();
		display.init(&engine);

		#ifdef RUN_TEST_1
			runTest1(&engine, &display);
		#endif
		
		#ifdef RUN_TEST_2
			runTest2(&engine, &display);
		#endif
		
		#ifdef RUN_TEST_3
			runTest3(&engine, &display);
		#endif
		
		#ifdef RUN_TEST_4
			runTest4(&engine, &display);
		#endif
		
		while(1);
	}
}
