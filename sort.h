#pragma once
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "yssimplesound.h"
#include <time.h>
#include <string>

#define WINDOW_X 1024
#define WINDOW_Y 768
//#define PI 3.1415927


struct Block {
	int value;
	int r, g, b; // fill color
	int fr, fg, fb; // frame color
	int r_original, g_original, b_original; // original fill color
	
	Block();
	void set_color(int r2, int g2, int b2);
	void set_default_color();
	void restore_color();
	Block(int value2, int r2, int g2, int b2, int fr2, int fg2, int fb2);
	void draw(int xmin, int xmax, int ymin, int ymax, int size, double index);
};

struct Block_Array{
	int size;
	Block * data;
	int xmax, xmin, ymax, ymin;
	std::string text;

	Block_Array() {};
	Block_Array(Block_Array & sample);
	Block_Array(int number, int r, int g, int b, int xmin2, int xmax2, int ymin2, int ymax2);
	Block_Array & operator==(Block_Array & sample);
	~Block_Array();
	void swap(int a,int b);
	void swap_with_animation(double a, double b, int cycle_per_swap, int ra, int ga, int ba, int rb, int gb ,int bb);
	void swap_with_animation_constant_speed(double a, double b, int cycle_per_index, int ra, int ga, int ba, int rb, int gb, int bb);
	void shuffle();
	void shuffle_with_animation(int cycle_per_swap);
	void draw();
	void draw_now();
	void move_to_upper_half(int cycle);
	void move_back_down(int cycle, int ymax2);
	void move_to_lower_half();
};
