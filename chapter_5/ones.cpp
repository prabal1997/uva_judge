#include <iostream>
#include <cstdint>
#include <string>
#include <climits>

//returns the length of an integer
int num_len(uint64_t input) {
     int len(0);
     for (uint64_t copy(input); copy; copy/=10)
          ++len;
          
     return len;
}

//returns the mod of powers of '10'
uint64_t give_mod(uint64_t ten_multiple, uint64_t repeat_ten_multiple, uint64_t input_int) {
     uint64_t final_mod = 1;
     for (int counter = 0; counter < repeat_ten_multiple; ++counter) {
          final_mod *= ten_multiple%input_int;
          final_mod = final_mod%input_int;
     }
     return final_mod;
}

//returns a power of 10
uint64_t give_ten_power(int exponent) {
     uint64_t ans = 1;
     for (int counter = 0; counter < exponent; ++counter)
          ans *= 10;
     return ans;
}

int main() {
     
     const uint64_t MAX_VAL = ~((uint64_t)0);
     uint64_t MAX_LEN = num_len(MAX_VAL);
     uint64_t LARGEST_TEN_MULTIPLE = 1;
          
     std::cout << MAX_VAL << " " << MAX_LEN << "\n";
     
     while(true) {
          //receive an integer as input
          uint64_t input_num;          
          std::cin >> input_num;
          
          //check length of the input int
          int num_len_calc(num_len(input_num));
          
          uint64_t total_mod(0);
          uint64_t counter(0), exp_val(1), one_seq(0);
          bool match_done(false);

          while(!match_done) {
               //create a sequence of '1's
               one_seq += 1*exp_val;
          
               //check divisibility
               uint64_t temp_val = give_mod(give_ten_power(MAX_LEN/2), counter/MAX_LEN, input_num); temp_val *= temp_val;
               temp_val = temp_val%input_num;
               
               uint64_t mod_val = (one_seq%input_num)*temp_val;
               mod_val = mod_val%input_num;
                         
               uint64_t local_total_mod = (mod_val + total_mod)%input_num;
               match_done = !local_total_mod;
               
               //increment the counter
               if (counter%MAX_LEN == MAX_LEN-1) {
                    total_mod = local_total_mod;
                    exp_val = 1;
                    one_seq = 0;
               }
               else
                    exp_val *= 10;

               ++counter;
          }
          
          //print the sequence of '1's that's been calculated
          std::cout << counter << "\n";
     }
     
     return 0;
}