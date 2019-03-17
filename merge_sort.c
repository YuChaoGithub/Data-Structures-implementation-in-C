#include <stdio.h>
#include <stdlib.h>

void merge_sort(int*, int*, int, int);
void merge(int*, int*, int, int, int);

void sort(int* arr, int len) {
	int* temp_arr = (int*) malloc(sizeof(int) * len);
	merge_sort(arr, temp_arr, 0, len - 1);
	free(temp_arr);
}

void merge_sort(int* arr, int* temp_arr, int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		merge_sort(arr, temp_arr, left, mid);
		merge_sort(arr, temp_arr, mid + 1, right);
		merge(arr, temp_arr, left, mid, right);
	}
}

void merge(int* arr, int* temp_arr, int left, int mid, int right) {
	int size = right - left + 1;
	int left_ptr = left;
	int right_ptr = mid + 1;
	int merge_ptr = left;
	while (left_ptr <= mid && right_ptr <= right) {
		if (arr[left_ptr] <= arr[right_ptr]) {
			temp_arr[merge_ptr] = arr[left_ptr];
			merge_ptr++;
			left_ptr++;
		} else {
			temp_arr[merge_ptr] = arr[right_ptr];
			merge_ptr++;
			right_ptr++;
		}
	}

	while (left_ptr <= mid) {
		temp_arr[merge_ptr] = arr[left_ptr];
		merge_ptr++;
		left_ptr++;
	}

	while (right_ptr <= right) {
		temp_arr[merge_ptr] = arr[right_ptr];
		merge_ptr++;
		right_ptr++;
	}

	for (int i = 0; i < size; i++, right--) {
		arr[right] = temp_arr[right];
	}
}

int main(void) {
	int arr[10] = {1, -4, 50, 9, 39, 95, 13, 49, 43, 0};
	sort(arr, 10);
	
	for (int i = 0; i < 10; i++) {
		printf("%d ", arr[i]);
	}
	
	putchar('\n');
	return 0;
}
