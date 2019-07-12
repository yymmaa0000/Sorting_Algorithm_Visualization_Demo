#include "sort.h"
#include "process.h"
#include <iostream>

using namespace std;

Block::Block()
{
	value = 1;
	r = g = b = r_original = g_original = b_original = 255;
	fr = fg = fb = 0;
}

void Block::set_color(int r2, int g2, int b2)
{
	r = r2;
	b = b2;
	g = g2;
}

void Block::set_default_color()
{
	r_original = r;
	g_original = g;
	b_original = b;
}

void Block::restore_color()
{
	r = r_original;
	g = g_original;
	b = b_original;
}

Block::Block(int value2, int r2, int g2, int b2, int fr2, int fg2, int fb2)
{
	value = value2;
	r = r_original = r2;
	g = g_original = g2;
	b = b_original = b2;
	fr = fr2;
	fg = fg2;
	fb = fb2;
}

void Block::draw(int xmin, int xmax, int ymin, int ymax, int size, double index)
{
	if (value == 0) return;
	int xrange = xmax - xmin;
	double xborder = xrange / 20.;
	double xwidth = (xrange - 2 * xborder) / size;
	int yrange = ymax - ymin;
	double yborder = yrange / 20.;
	double ywidth = (yrange - 2 * yborder) / size;

	glColor3ub(r, g, b);
	glBegin(GL_QUADS);
	glVertex2d(index * xwidth + xborder, ymax - yborder);
	glVertex2d(index * xwidth + xwidth + xborder, ymax - yborder);
	glVertex2d(index * xwidth + xwidth + xborder, ymax - value * ywidth - yborder);
	glVertex2d(index * xwidth + xborder, ymax - value * ywidth - yborder);
	glEnd();

	glColor3ub(fr, fg, fb);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(index * xwidth + xborder, ymin + yrange - yborder);
	glVertex2d(index * xwidth + xwidth + xborder, ymin + yrange - yborder);
	glVertex2d(index * xwidth + xwidth + xborder, ymin + yrange - value * ywidth - yborder);
	glVertex2d(index * xwidth + xborder, ymin + yrange - value * ywidth - yborder);
	glEnd();
}

Block_Array::Block_Array(Block_Array & sample)
{
	size = sample.size;
	xmax = sample.xmax;
	xmin = sample.xmin;
	ymax = sample.ymax;
	ymin = sample.ymin;

	data = new Block[size];
	for (int i = 0; i < size; i++) {
		data[i] = sample.data[i];
	}
}

Block_Array::Block_Array(int number, int r, int g, int b, int xmin2, int xmax2, int ymin2, int ymax2)
{
	data = new Block[number];
	size = number;
	xmin = xmin2;
	xmax = xmax2;
	ymin = ymin2;
	ymax = ymax2;


	for (int i = 0; i < number; i++) {
		data[i].value = i + 1;
		data[i].r = double(r) / number * (i + 1);
		data[i].g = double(g) / number * (i + 1);
		data[i].b = double(b) / number * (i + 1);
		data[i].set_default_color();
	}
}

Block_Array & Block_Array::operator==(Block_Array & sample)
{
	size = sample.size;
	xmax = sample.xmax;
	xmin = sample.xmin;
	ymax = sample.ymax;
	ymin = sample.ymin;

	data = new Block[size];
	for (int i = 0; i < size; i++) {
		data[i] = sample.data[i];
	}
	return *this;
}

Block_Array::~Block_Array()
{
	delete[] data;
}

void Block_Array::swap(int a, int b)
{
	Block temp;
	temp = data[a];
	data[a] = data[b];
	data[b] = temp;
}

void Block_Array::swap_with_animation(double a, double b, int cycle_per_swap, int ra, int ga, int ba, int rb, int gb, int bb)
{
	YsSoundPlayer player;
	YsSoundPlayer::SoundData wav;

	if (cycle_per_swap >= 8) {
		char filename[] = "Resource/bottle_pop.wav";
		if (YSOK != wav.LoadWav(filename))
		{
			printf("Failed to read %s\n", filename);
			return;
		}
		player.Start();
		player.PlayOneShot(wav);
	}

	int animation_clcye = cycle_per_swap;
	double step = double(b - a) / animation_clcye;

	while (animation_clcye--) {

		clear_and_draw_backgorund();

		if (text.size() != 0) {
			glColor3ub(0, 0, 0);
			glRasterPos2i(350, 50);  // sets position
			YsGlDrawFontBitmap20x32(text.c_str());
			glLineWidth(3.0);
			glBegin(GL_LINES);
			glVertex2d(300, 55);
			glVertex2d(850, 55);
			glEnd();
		}

		FsPollDevice();
		int key = FsInkey();
		if (FSKEY_ESC == key) break;

		for (int i = 0; i < size; i++) {
			if (i == a || i == b) continue;
			data[i].draw(xmin, xmax, ymin, ymax, size, i);
		}
		data[int(a)].set_color(ra, ga, ba);
		data[int(b)].set_color(rb, gb, bb);
		data[int(a)].draw(xmin, xmax, ymin, ymax, size, b - step * animation_clcye);
		data[int(b)].draw(xmin, xmax, ymin, ymax, size, a + step * animation_clcye);
		data[int(a)].restore_color();
		data[int(b)].restore_color();


		FsSwapBuffers();

		if (YSTRUE == player.IsPlaying(wav))player.KeepPlaying();

		FsSleep(20);
	}
	swap(a, b);
	player.End();
}

void Block_Array::swap_with_animation_constant_speed(double a, double b, int cycle_per_index, int ra, int ga, int ba, int rb, int gb, int bb)
{
	int cycle_per_swap = cycle_per_index * abs(b - a);
	swap_with_animation(a, b, cycle_per_swap, ra, ga, ba, rb, gb, bb);
}

void Block_Array::shuffle()
{
	int randLoc;
	srand((int)time(NULL));
	for (int i = 0; i < size; i++) {
		randLoc = rand() % size;
		swap(i, randLoc);
	}
}

void Block_Array::shuffle_with_animation(int cycle_per_swap)
{
	int randLoc;
	srand((int)time(NULL));
	for (int i = 0; i < size; i++) {
		randLoc = rand() % size;
		swap_with_animation(i, randLoc,cycle_per_swap,255,255,0,255,0,0);
	}
	draw_now();
}

void Block_Array::draw()
{
	if (text.size() != 0) {
		glColor3ub(0, 0, 0);
		glRasterPos2i(350, 50);  // sets position
		YsGlDrawFontBitmap20x32(text.c_str());
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex2d(300,55);
		glVertex2d(850,55);
		glEnd();
	}

	for (int i = 0; i < size; i++) {
		data[i].draw(xmin, xmax, ymin, ymax, size, i);
	}
}

void Block_Array::draw_now()
{
	clear_and_draw_backgorund();
	draw();
	FsSwapBuffers();
	FsSleep(20);
}

void Block_Array::move_to_upper_half(int cycle)
{
	double step = (double(ymax - ymin)) / 2 / cycle;
	int counter = cycle;
	double ymax_double = double(ymax);
	while (counter--) {
		ymax_double -= step;
		ymax = ymax_double;
		draw_now();
	}
}

void Block_Array::move_back_down(int cycle,int ymax2)
{
	double step = (double(ymax2 - ymax))/ cycle;
	int counter = cycle;
	double ymax_double = double(ymax);
	while (counter--) {
		ymax_double += step;
		ymax = ymax_double;
		draw_now();
	}
}

void Block_Array::move_to_lower_half()
{
	ymin += (double(ymax - ymin)) / 2;
}

