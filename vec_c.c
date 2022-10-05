#include <stdio.h>
#include "stdlib.h"
#include "string.h"

typedef void(*fun_vvi)(void* vec, int val);
typedef void(*fun_vv)(void* vec);

typedef struct {
	int* ptr;
	int cur_index, max_index;
	fun_vvi push_back;
	fun_vv display_vec;
	fun_vv destroy_vec;
} vecInt;

void destroy(void* vec) {
	vecInt* vec_ptr = (vecInt*)vec;
	free(vec_ptr->ptr);
	vec_ptr = NULL;
	printf("free the vec's memory.\n");
}

void push(void* vec, int val) {
	vecInt* vec_ptr = (vecInt*)vec;
	if (vec_ptr->cur_index == vec_ptr->max_index) {
		int* new_ptr = (int*)malloc(sizeof(int) * 2 * (vec_ptr->max_index ));
		memcpy(new_ptr, vec_ptr->ptr, sizeof(int) * (vec_ptr->max_index));
		free(vec_ptr->ptr);
		vec_ptr->ptr = new_ptr;
		vec_ptr->max_index = 2 * (vec_ptr->max_index);
	}
	int index = (vec_ptr->cur_index)++;
	*(vec_ptr->ptr + index) = val;
}
void display(void* vec) {
	vecInt* vec_ptr = (vecInt*)vec;
	for (int i = 0; i < vec_ptr->cur_index; i++) {
		printf("%d,", vec_ptr->ptr[i]);
	}
}
 
void initVecInt(vecInt* vec, int vec_size) {
	vec->ptr = (int*)malloc(sizeof(int) * vec_size);
	memset(vec->ptr, 0, sizeof(int) * vec_size);
	vec->max_index = vec_size;
	vec->cur_index = 0;
	vec->push_back = push;
	vec->display_vec = display;
	vec->destroy_vec = destroy;
}


int main() {
	vecInt vec;
	initVecInt(&vec, 10);
	for (int i = 0; i < 21; i++) {
		vec.push_back(&vec, i);
	}
	vec.display_vec(&vec);
	vec.destroy_vec(&vec);

	return 0;
}