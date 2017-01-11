#ifndef ANIMATION_H
#define ANIMATION_HPP

#include <curses.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

#define DELAY 265000

class Animation
{
	private:
		int width;
		int height;
		
	public:
		Animation();
		void title();
		void addCore();
		void putOutFire();
		void end();
};

#endif