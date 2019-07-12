#pragma comment(lib, "Winmm.lib")
#include "sort.h"
#include <Windows.h>
#include <Mmsystem.h>

void wait();
void wait(int x);
void display_array(Block_Array & blocks);
void selection_sort(Block_Array & blocks);
void bubble_sort(Block_Array & blocks);
void quick_sort(int start, int end, Block_Array & blocks);
void refresh(Block_Array & blocks, Block_Array & reference);
void play_sound(const char * filename);
void merge_sort(Block_Array & blocks);
void merge_sort_main(int start, int stop, int current_block, Block_Array & block1, Block_Array & block2);
void merge_sort_main(int start, int stop,  Block_Array & block1, Block_Array & block2);
void draw_two_block(Block_Array & block1, Block_Array & block2);
void draw_two_block(Block_Array & block1, Block_Array & block2);
void swap_stick(Block_Array & a, int index_a, Block_Array & b, double index_b, double cycle, bool music);
void clear_and_draw_backgorund();