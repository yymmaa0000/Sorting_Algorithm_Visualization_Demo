#include "process.h"

int main() {
	FsOpenWindow(16, 16, WINDOW_X, WINDOW_Y, 1);

	PlaySound("bgmusic.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	Block_Array blocks(20, 0, 0, 255, 0, WINDOW_X, 50, WINDOW_Y);
	Block_Array reference = blocks;

	display_array(blocks);

	//blocks.shuffle();

	blocks.text = "Random Shuffling";
	blocks.shuffle_with_animation(8);
	wait(50);
	
	Block_Array blocks2 = blocks;
	Block_Array blocks3 = blocks;
	Block_Array blocks4 = blocks;

	blocks.text = "Selection Sort - O(n^2)";
	selection_sort(blocks);
	refresh(blocks, reference);
	wait(50);

	blocks2.text = "Bubble Sort - O(n^2)";
	bubble_sort(blocks2);
	refresh(blocks2, reference);
	wait(50);

	blocks3.text = "Quick Sort - O(nlog(n))";
	quick_sort(0, blocks3.size-1,blocks3);
	refresh(blocks3, reference);
	wait(50);

	blocks4.text = "Merge Sort - O(nlog(n))";
	merge_sort(blocks4);
	refresh(blocks4, reference);
	wait(50);

	wait(50);
	return 0;
}