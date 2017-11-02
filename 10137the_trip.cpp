#include<iostream>
#include<cstdint>
#include<cstdio>
#include<sstream>
#include<string>
#include<algorithm>

int main() {
	
	int student_count(0);
	bool cont_work(true), first_exec(true);
	std::stringstream output_data;
	
	while(cont_work) {
		//receive student cound
		std::cin >> student_count;
		
		//continue only if the student count is non-zero
		if (!student_count) {
			cont_work = false;
		}
		else {
		
			//receive input, convert to integer (in cents)
			int* int_vals = new int[student_count];
			int total_sum(0);
			double input_val;
			for (int counter = 0; counter < student_count; ++counter) {
				std::cin >> input_val;
				int_vals[counter] = (int)(input_val*100+0.5);
				
				total_sum += int_vals[counter];
			}
			
			//calculating the difference
			int low_avg(total_sum/student_count), high_avg(low_avg + 1), mod_val(total_sum%student_count);
			int solution(0);

			//ALGORITHM:
			//1.) Find the LOWEST POSSIBLE amount that the 'richer' people need to give
			//2.) Add up all the amount that the 'richer' people had to give, and output			
			for (int counter = 0; counter < student_count; ++counter) {
				if (mod_val-- && int_vals[counter] >= high_avg) {
					solution += (int_vals[counter] - high_avg);
				}
				else if (int_vals[counter] >= low_avg) {
					solution += (int_vals[counter] - low_avg);
				}
			}
			
			//creating output
			output_data << "$" << solution/100 << ".";
			output_data << ((solution%100)-(solution%10))/10 << (solution%10) << "\n";
		}
	}
	
	//dumping output on console
	std::cout << output_data.str();
	
	return 0;
}
