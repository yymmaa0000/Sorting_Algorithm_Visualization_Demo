#include "process.h"

void wait() {
	while (1) {
		FsPollDevice();
		int key = FsInkey();
		if (FSKEY_ESC == key) return;
		FsSleep(20);
	}
}

void wait(int cycles)
{
	while (cycles--) {
		FsPollDevice();
		int key = FsInkey();
		if (FSKEY_ESC == key) return;
		FsSleep(20);
	}
}

void display_array(Block_Array & data) {
	int cycle = 200;

	while (cycle--) {

		clear_and_draw_backgorund();

		FsPollDevice();
		int key = FsInkey();
		if (FSKEY_ESC == key) return;
		glColor3ub(0, 0, 0);
		glRasterPos2i(80, 100);  // sets position
		YsGlDrawFontBitmap20x32("Sort Algorithm Visualization");

		glRasterPos2i(85, 150);  // sets position
		YsGlDrawFontBitmap20x32("24-780 Engineering Computation");

		glRasterPos2i(85, 190);  // sets position
		YsGlDrawFontBitmap20x32("Individual Project");

		glRasterPos2i(87, 230);  // sets position
		YsGlDrawFontBitmap20x32("XingYu Wang");

		data.draw();
		FsSwapBuffers();
		FsSleep(20);
	}
}

void selection_sort(Block_Array & blocks) {
	int min, min_index;
	for (int i = 0; i < blocks.size; i++) {
		min = 10000; min_index = 0;
		for (int j = i; j < blocks.size; j++) {

			clear_and_draw_backgorund();
			FsPollDevice();
			int key = FsInkey();
			if (FSKEY_ESC == key) return;

			if (blocks.text.size() != 0) {
				glColor3ub(0, 0, 0);
				glRasterPos2i(350, 50);  // sets position
				YsGlDrawFontBitmap20x32(blocks.text.c_str());
				glLineWidth(3.0);
				glBegin(GL_LINES);
				glVertex2d(300, 55);
				glVertex2d(850, 55);
				glEnd();
			}

			for (int k = 0; k < blocks.size; k++) {
				if (k == j) continue;
				blocks.data[k].draw(blocks.xmin, blocks.xmax, blocks.ymin, blocks.ymax, blocks.size, k);
			}
			if (blocks.data[j].value < min) {
				blocks.data[min_index].restore_color();

				min = blocks.data[j].value;
				min_index = j;

				blocks.data[j].set_color(255, 0, 0);
				blocks.data[j].draw(blocks.xmin, blocks.xmax, blocks.ymin, blocks.ymax, blocks.size, j);
			}
			else {
				blocks.data[j].set_color(255, 255, 0);
				blocks.data[j].draw(blocks.xmin, blocks.xmax, blocks.ymin, blocks.ymax, blocks.size, j);
				blocks.data[j].restore_color();
			}

			FsSwapBuffers();
			if (i < 5) FsSleep(40);
			else if (i < 10) FsSleep(20);
			else FsSleep(10);
		}
		int cycle;
		if (i < 5) cycle = 20;
		else if (i < 10) cycle = 10;
		else cycle = 5;
		blocks.swap_with_animation(min_index,i, cycle,255,0,0, blocks.data[i].r_original,
			blocks.data[i].g_original, blocks.data[i].b_original);
	}
	blocks.data[min_index].restore_color();
	blocks.draw_now();
}

void bubble_sort(Block_Array & blocks) {
	YsSoundPlayer player;
	YsSoundPlayer::SoundData wav;

	for (int i = blocks.size - 1; i > 0; i--) {
		
		if (i < blocks.size - 1) {
			char filename[] = "Resource/correct.wav";
			if (YSOK != wav.LoadWav(filename))
			{
				printf("Failed to read %s\n", filename);
				return;
			}
			player.Start();
			player.PlayOneShot(wav);
		}

		for (int j = 0; j < i; j++) {
			if (YSTRUE == player.IsPlaying(wav))player.KeepPlaying();

			clear_and_draw_backgorund();
			FsPollDevice();
			int key = FsInkey();
			if (FSKEY_ESC == key) return;

			if (blocks.text.size() != 0) {
				glColor3ub(0, 0, 0);
				glRasterPos2i(350, 50);  // sets position
				YsGlDrawFontBitmap20x32(blocks.text.c_str());
				glLineWidth(3.0);
				glBegin(GL_LINES);
				glVertex2d(300, 55);
				glVertex2d(850, 55);
				glEnd();
			}

			for (int k = 0; k < blocks.size; k++) {
				if (k == j) continue;
				blocks.data[k].draw(blocks.xmin, blocks.xmax, blocks.ymin, blocks.ymax, blocks.size, k);
			}
			blocks.data[j].set_color(255, 255, 0);
			blocks.data[j].draw(blocks.xmin, blocks.xmax, blocks.ymin, blocks.ymax, blocks.size, j);
			blocks.data[j].restore_color();

			FsSwapBuffers();
			if (i > blocks.size - 2) FsSleep(200);
			else if (i > blocks.size - 3) FsSleep(100);
			else FsSleep(25);

			if (blocks.data[j].value > blocks.data[j + 1].value) {
				int cycle;
				if (i > blocks.size - 2) cycle = 8;
				else if (i > blocks.size - 3) cycle = 5;
				else cycle = 3;
				blocks.swap_with_animation(j+1, j, cycle,255,0,0,255,255,0);
			}
		}
		if (i < blocks.size - 1) player.End();
	}
	blocks.draw_now();

}

void quick_sort(int start, int end, Block_Array & blocks) {
	if (start >= end) { // root condition
		return;
	}
	/*
	else if (start == end) {
		blocks.data[start].set_color(255, 255, 0);
		blocks.draw_now();
		blocks.data[start].restore_color();
		blocks.draw_now();
		return;
	}
	*/

	int length = end + 1;
	int pivit = start;
	int r = blocks.data[pivit].r;
	int g = blocks.data[pivit].g;
	int b = blocks.data[pivit].b;
	blocks.data[pivit].set_color(255, 0, 0);
	blocks.data[pivit].set_default_color();
	blocks.draw_now();

	for (int i = start + 1; i < length; i++) {
		//blocks.data[i].set_color(255, 255, 0);
		//blocks.draw_now();

		if (blocks.data[i].value < blocks.data[pivit].value) {
			blocks.swap_with_animation(pivit, i,8,255,0,0, blocks.data[i].r_original,
				blocks.data[i].g_original, blocks.data[i].b_original);
			pivit = i;
			continue;
		}
		while (blocks.data[i].value > blocks.data[pivit].value) {
			if (i == length - 1) {
				//blocks.data[i].restore_color();
				//blocks.draw_now();
				break;
			}
			else {
				blocks.swap_with_animation(length - 1, i,8, blocks.data[length - 1].r,
					blocks.data[length - 1].g, blocks.data[length - 1].b, blocks.data[i].r_original,
					blocks.data[i].g_original, blocks.data[i].b_original);
				length--;
			}
			//blocks.data[i].set_color(255, 255, 0);
			//blocks.draw_now();
		}
		if (blocks.data[i].value < blocks.data[pivit].value) {
			blocks.swap_with_animation(pivit, i, 8, 255, 0, 0, blocks.data[i].r_original,
				blocks.data[i].g_original, blocks.data[i].b_original);
			pivit = i;
		}
	}

	blocks.draw_now();

	//blocks.data[pivit].set_color(r, g, b);
	//blocks.data[pivit].set_default_color();

	quick_sort(start, pivit -1, blocks);
	quick_sort(pivit + 1, end, blocks);
}

void refresh(Block_Array & blocks, Block_Array & reference)
{
	YsSoundPlayer player;
	YsSoundPlayer::SoundData wav;
	char filename[] = "Resource/Up_fast.wav";



	if (YSOK != wav.LoadWav(filename))
	{
		printf("Failed to read %s\n", filename);
		return;
	}

	player.Start();
	player.PlayOneShot(wav);

	for (int i = 0; i <= blocks.size; i++) {
		if (YSTRUE == player.IsPlaying(wav))player.KeepPlaying();
		if (i < blocks.size) blocks.data[i].set_color(255, 255, 0);
		if (i > 0) blocks.data[i - 1].set_color(reference.data[i - 1].r,
			reference.data[i - 1].g, reference.data[i - 1].b);
		blocks.draw_now();
		FsSleep(20);
	}
	player.End();
}

void play_sound(const char * filename)
{
	YsSoundPlayer player;
	YsSoundPlayer::SoundData wav;

	if (YSOK != wav.LoadWav(filename))
	{
		printf("Failed to read %s\n", filename);
		return;
	}

	player.Start();
	player.PlayOneShot(wav);

	while (YSTRUE == player.IsPlaying(wav))
	{
		player.KeepPlaying();
	}

	/*
	int cycle = 50;
	while (cycle--)
	{
		if (YSTRUE == player.IsPlaying(wav)) player.KeepPlaying();
	}
	*/

	player.End();

	return;
}

void merge_sort(Block_Array & block1)
{
	block1.draw_now();
	FsSleep(1000);

	Block_Array block2 = block1;
	int ymax = block1.ymax;

	for (int i = 0; i < block2.size; i++) {
		block2.data[i].value = 0;
	}
	
	block1.move_to_upper_half(20);
	block2.move_to_lower_half();
	draw_two_block(block1, block2);
	

	//merge_sort_main(0, block1.size - 1, 1, block1, block2);
	merge_sort_main(0, block1.size - 1,block1, block2);

	block1.move_back_down(20, ymax);
}

void merge_sort_main(int start, int stop, Block_Array & block1, Block_Array & block2)
{
	if (start >= stop) return;
	int half = (stop - start) / 2 + start;
	merge_sort_main(start, half,block1, block2);
	merge_sort_main(half + 1, stop,block1, block2);


	int a = 0, b = 0;
	for (int i = start; i <= stop; i++) {
		if (a + start > half) {
			swap_stick(block1, b + half + 1, block2, i, 5, false);
			//block2.data[i] = block1.data[b + half + 1];
			//block1.data[b + half + 1].value = 0;
			b++;
		}
		else if (b + half+1 > stop) {
			swap_stick(block1, a + start, block2, i, 5, false);
			//block2.data[i] = block1.data[a + start];
			//block1.data[a + start].value = 0;
			a++;
		}
		else if (block1.data[a+start].value < block1.data[b + half + 1].value) {
			swap_stick(block1, a + start, block2, i, 5,false);
			//block2.data[i] = block1.data[a + start];
			//block1.data[a + start].value = 0;
			a++;
		}
		else {
			swap_stick( block1, b + half + 1, block2, i,5, false);
			//block2.data[i] = block1.data[b + half + 1];
			//block1.data[b + half + 1].value = 0;
			b++;
		}
		draw_two_block(block1, block2);
		FsSleep(20);
	}

	//play_sound("Resource/correct.wav");

	for (int i = start; i <= stop; i++) {
		if (i == start) swap_stick(block1, i, block2, i, 10, true);
		else swap_stick(block1, i, block2, i, 5, false);
		/*block1.data[i] = block2.data[i];
		block2.data[i].value = 0;
		draw_two_block(block1, block2);
		FsSleep(20);*/
	}
}

//void merge_sort_main(int start, int stop, int current_block, Block_Array & block1, Block_Array & block2)
//{
//	if (start >= stop) return;
//	int half = (stop - start) / 2 + start;
//	if (current_block == 1) {
//		if (block1.data[start].value == 0) return;
//		merge_sort_main(start, half, 2, block1, block2);
//		merge_sort_main(half + 1, stop, 2, block1, block2);
//	}
//	else if (current_block == 2) {
//		if (block2.data[start].value == 0) return;
//		merge_sort_main(start, half, 1, block1, block2);
//		merge_sort_main(half + 1, stop, 1, block1, block2);
//	}
//	
//	int a = 0, b = 0;
//	if (current_block == 2) {
//		for (int i = start; i <= stop; i ++) {
//			if (a + start > half) {
//				swap_stick(block1, i, block2, b + half + 1, 10);
//				b++;
//			}
//			else if (b + half + 1 > stop) {
//				swap_stick(block1, i, block2, a + start, 10);
//				a++;
//			}
//			else if (block2.data[a + start].value < block2.data[b + half + 1].value) {
//				swap_stick(block1, i, block2, a + start, 10);
//				a++;
//			}
//			else {
//				swap_stick(block1, i, block2, b + half + 1, 10);
//				b++;
//			}
//			draw_two_block(block1, block2);
//			FsSleep(20);
//		}
//	}
//	else if (current_block == 1) {
//		for (int i = start; i <= stop; i++) {
//			if (a + start > half) {
//				swap_stick(block2, i, block1, b + half + 1, 10);
//				b++;
//			}
//			else if (b + half + 1 > stop) {
//				swap_stick(block2, i, block1, a + start, 10);
//				a++;
//			}
//			else if (block1.data[a + start].value < block1.data[b + half + 1].value) {
//				swap_stick(block2, i, block1, a + start, 10);
//				a++;
//			}
//			else {
//				swap_stick(block2, i, block1, b + half + 1, 10);
//				b++;
//			}
//			draw_two_block(block1, block2);
//			FsSleep(20);
//		}
//	}
//}

void draw_two_block(Block_Array & block1, Block_Array & block2)
{
	clear_and_draw_backgorund();
	block1.draw();
	block2.draw();
	FsSwapBuffers();
	FsSleep(20);
}

void swap_stick(Block_Array & a, int index_a, Block_Array & b, double index_b, double cycle, bool music)
{
	double distance = (b.ymax - a.ymax);
	double ystep = distance / cycle;
	double xstep = double(index_b - index_a) / cycle;

	YsSoundPlayer player;
	YsSoundPlayer::SoundData wav;

	if (music) {
		char filename[] = "Resource/bottle_pop.wav";
		if (YSOK != wav.LoadWav(filename))
		{
			printf("Failed to read %s\n", filename);
			return;
		}
		player.Start();
		player.PlayOneShot(wav);
	}

	int animation_clcye = cycle;
	while (animation_clcye--) {

		clear_and_draw_backgorund();

		if (music) {
			if (YSTRUE == player.IsPlaying(wav))player.KeepPlaying();
		}

		if (a.text.size() != 0) {
			glColor3ub(0, 0, 0);
			glRasterPos2i(350, 50);  // sets position
			YsGlDrawFontBitmap20x32(a.text.c_str());
			glLineWidth(3.0);
			glBegin(GL_LINES);
			glVertex2d(300, 55);
			glVertex2d(850, 55);
			glEnd();
		}

		FsPollDevice();
		int key = FsInkey();
		if (FSKEY_ESC == key) break;

		for (int i = 0; i < a.size; i++) {
			if (i == index_a) continue;
			a.data[i].draw(a.xmin, a.xmax, a.ymin, a.ymax, a.size, i);
		}
		for (int i = 0; i < b.size; i++) {
			if (i == index_b) continue;
			b.data[i].draw(b.xmin, b.xmax, b.ymin, b.ymax, b.size, i);
		}
		a.data[int(index_a)].draw(a.xmin, a.xmax, b.ymin - ystep * animation_clcye, b.ymax - ystep * 
			animation_clcye, a.size, index_b - xstep * animation_clcye);
		b.data[int(index_b)].draw(b.xmin, b.xmax, a.ymin + ystep * animation_clcye, a.ymax + ystep *
			animation_clcye, a.size, index_a + xstep * animation_clcye);

		FsSwapBuffers();

		FsSleep(20);
	}
	
	if (music) {
		player.End();
	}

	Block temp = a.data[int(index_a)];
	a.data[int(index_a)] = b.data[int(index_b)];
	b.data[int(index_b)] = temp;

}

void clear_and_draw_backgorund()//YsRawPngDecoder png, GLuint texId
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	
	glShadeModel(GL_SMOOTH);

	glBegin(GL_QUADS);

	glColor3ub(55, 186, 60);
	glVertex2i(0, 0);

	glColor3ub(0, 100, 20);
	glVertex2i(WINDOW_X, 0);

	glColor3ub(89, 237, 21);
	glVertex2i(WINDOW_X, WINDOW_Y);

	glColor3ub(0, 224, 160);
	glVertex2i(0, WINDOW_Y);

	glEnd();
	
	/*
	int wid, hei;
	FsGetWindowSize(wid, hei);

	// in order for textures to show, you must create a projection
	glViewport(0, 0, wid, hei);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	// enable texture mapping
	glEnable(GL_TEXTURE_2D);

	// bind a texture to OpenGL primitives
	glBindTexture(GL_TEXTURE_2D, texId);

	glBegin(GL_QUADS);

	// For each vertex, assign texture coordinate before vertex coordinate.
	glTexCoord2d(0.0, 0.0);
	glVertex2i(0, 0);

	glTexCoord2d(1.0, 0.0);
	glVertex2i(WINDOW_X, 0);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(WINDOW_X, WINDOW_Y);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(0, WINDOW_Y);

	glEnd();
	*/

}
