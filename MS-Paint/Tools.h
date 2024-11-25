#pragma once
#include "Header.h"
class Tools
{
	/*much like Buttons, it stores various Tool objects. (this includes Brushes, a child class of the Tool class)
	Tools should include, among other things, the following (just examples doesnt need to be exactly this but yaknow)
	- Vector of type Tool that contains all tool objects
	- all declared Tool/Brush objects much like they are in Buttons
	- Definitions for the functions those Tool/Brush objects. Do you want to define them in Tools, 
	like I did in Buttons then store them as functions pointers in the Tool/Brush objects themselves, or keep those functions
	entirely in Tools and just use the Tool objects as storage locations for things like icons, textures, ink types (for brushes), etc?
	- Thats all I can think of for now, but if you have any other ideas for this please feel free to add them, just keep in mind the Tools object will be eventually
	defined in Buttons, and its various stored Tool/Brush objects called in their respective button functions.
	*/

};

