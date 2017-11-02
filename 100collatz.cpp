#include<iostream>
#include<cstdlib>
#include<cstdint>

//forward declaration
uint32_t give_path_length(int32_t);

int main() {
	
	int32_t i(0), j(0), swap(0);
	while(std::cin >> i >> j) {
		//print input data
		std::cout << i << " " << j << " ";
		
		//swap numbers if neccesary
		if (i > j) {
			swap = i;
			i = j;
			j = swap;
		}
		
		//iterate through each number
		uint32_t max(0);
		for (int32_t counter = i; counter < j+1; ++counter) {
			uint32_t cycle_len = give_path_length(counter);
			max = ( (max<cycle_len) ? cycle_len : max );
		}
		
		//print output
		std::cout << max << "\n";
	}

	return 0;
}

uint32_t give_path_length(int32_t start) {
	uint32_t counter = 1;
	while(start != 1) {
		start = ( (start % 2) ?  3*start+1 : start/2  );
		++counter;
	}

	return counter;
}
