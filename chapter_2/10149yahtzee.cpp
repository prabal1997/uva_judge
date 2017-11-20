#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
#include<iomanip>

//global constants
const int DICE_COUNT = 5;
const int THROW_COUNT = 13;
const int MIN_NUM = -100;

//pre-declared functions
int calc_result(std::array<int, DICE_COUNT>&, int);
int process_data(std::vector<std::array<int, DICE_COUNT>>&);
void print_binary(unsigned int);
std::vector<unsigned int> give_longer_set(unsigned int);
unsigned int give_bits(unsigned int ones_count);

int main() {

     std::vector<std::array<int,DICE_COUNT>> dice_throws(THROW_COUNT);     
     for(int counter(0); true; ++counter) {
          //read in the input die throws for a line
          for (int die_counter(0); die_counter < DICE_COUNT; ++die_counter)
               std::cin >> dice_throws[counter][die_counter];
          
          //check if the input is ready for processing
          if ( (counter+1)%THROW_COUNT == 0 ) {
               //process the data to pre-caclulate results          
               process_data(dice_throws);
          }
     
     }
     
     return 0;
}

//returns a vector of all possible bit patterns with an additional one
std::vector<unsigned int> give_longer_set(unsigned int input_set) {
     //count number of '1's in the sequence
     const int SUIT_SIZE(13);
     int one_counter(0);
     for (int idx(0); idx < SUIT_SIZE; ++idx)
          one_counter += (input_set >> idx) & 0x01;
     
     //create new bit-patterns
     std::vector<unsigned int> perms(SUIT_SIZE-one_counter);
     for (int idx(0), pos(0); idx < SUIT_SIZE; ++idx) {
          //check if the position is already occupied
          if ((input_set >> idx) & 0x01)
               continue;
               
          //add the additional bit
          unsigned int new_bit_pattern = input_set | (0x01 << idx);
          perms[pos++] = new_bit_pattern;
     }
     
     //return the bit-patterns
     return perms;
}

//returns a bit-sequence with 'ones_count' number of bits
unsigned int give_bits(unsigned int ones_count) {
     unsigned int output(0);
     for (int idx(0); idx < ones_count; ++idx) {
          output = output << 1;
          output = output | 0x01;
     }
     
     return output;
}

//prints the input number in binary
void print_binary(unsigned int input) {
     const int SUIT_SIZE(13);
     //print each bit to the 'cout' buffer
     for (int idx(SUIT_SIZE-1); idx > -1; --idx)
          std::cout << ( ( (0x01<<idx) & input ) >> idx );
}

//support functions
int calc_result(std::array<int, DICE_COUNT>& input_seq, int test_request) {
     
     int total_point_count = 0;
     
     //consider all test cases
     for (int counter = 0; test_request <= 6 && counter < DICE_COUNT; ++counter)
          total_point_count += ( (input_seq[counter] == test_request) ? test_request : 0 );
     
     if (test_request == 7) {
          for (int counter = 0; counter < DICE_COUNT; ++counter)
               total_point_count += input_seq[counter];
     }
     if (test_request == 8) {
          for (int counter = 0; counter < DICE_COUNT; ++counter) {
               int count_val = std::count(input_seq.begin(), input_seq.end(), input_seq[counter]);
               if (count_val >= 3) {
                    total_point_count += std::accumulate(input_seq.begin(), input_seq.end(), 0);
                    break;
               }
          }
     }
     if (test_request == 9) {
          for (int counter = 0; counter < DICE_COUNT; ++counter) {
               int count_val = std::count(input_seq.begin(), input_seq.end(), input_seq[counter]);
               if (count_val >= 4) {
                    total_point_count += std::accumulate(input_seq.begin(), input_seq.end(), 0);
                    break;
               }
          }
     }
     if (test_request == 10) {
          //check if all the die values are same
          int counter(0);
          for (counter = 0; counter < DICE_COUNT; ++counter)
               if (input_seq[0] != input_seq[counter])
                    break;
                    
          if (counter == 5)
               total_point_count += 50;
     }
     if (test_request == 11) {
          //see if the array contains a sequence of length DICE_COUNT-1
          //we add the outsides of the sequence, and we move to the middle of it repeating the process - the sum should ALWAYS be the same
          int seq_num_count(0);
          bool seq_detected(false);
          for (int shift = 0; shift < 1+1; ++shift) {
               for (int counter = shift; seq_num_count < 3 && counter < DICE_COUNT-1+shift; ++counter) {
                    if ( input_seq[counter+1] - input_seq[counter] == 1 ) {
                         seq_num_count += 1;
                         seq_detected = true;
                    }
                    else {
                         seq_num_count = 0;
                         seq_detected = false;
                         break;
                    }
               }
          }
          
          if (seq_detected)
               total_point_count += 25;
     }
     if (test_request == 12) {
          //see if the entire array is a sequence
          bool seq_detected(true);
          for (int counter = 0; seq_detected && counter < DICE_COUNT-1; ++counter) {
               if ( input_seq[counter+1] - input_seq[counter] != 1 )
                    seq_detected = false;
          }
          
          if (seq_detected)
               total_point_count += 35;
     }
     
     if (test_request == 13) {
          std::array<int, 6> variety = {0, 0, 0, 0, 0, 0};
          for (int counter = 0; counter < DICE_COUNT; ++counter)
               variety[input_seq[counter]-1] += 1; 
          
          int count_3 = std::count(variety.begin(), variety.end(), 3);
          int count_2 = std::count(variety.begin(), variety.end(), 2);
          if (count_3 == 1 && count_2 == 1)
               total_point_count += 40;
     }
     
     return total_point_count;
     
}

int process_data(std::vector<std::array<int, DICE_COUNT>>& input_requests) {
     //make a 2D array, populate
     std::array<int, THROW_COUNT*THROW_COUNT> matrix_data;
     std::array<bool, THROW_COUNT*THROW_COUNT> matrix_bool;
     for (int counter = 0; counter < THROW_COUNT*THROW_COUNT; ++counter) {
          matrix_data[counter] = 0;
          matrix_bool[counter] = true;
     }
     for (int test_num = 0; test_num < THROW_COUNT; ++test_num) {
          for (int throw_num = 0; throw_num < THROW_COUNT; ++throw_num)
               matrix_data[test_num*THROW_COUNT+throw_num] = calc_result(input_requests[throw_num], test_num+1);
     }

/*
1 2 3 4 5
1 1 1 1 1
2 2 2 2 2
1 2 3 4 5
1 2 3 4 5
5 4 3 2 1 
1 2 3 4 5
5 4 3 2 1
1 2 3 4 5
1 2 3 4 5
2 2 2 2 2
1 2 3 4 5
6 6 6 6 6
*/

     //we use dynamic programming - iterate through all SETS of 'tests' of varying sizes (1, 2, 3, ..., 13)
     std::vector<int> max_val_holder(THROW_COUNT+1, 0);
     std::vector<unsigned int> max_bit_pattern_holder(THROW_COUNT+1, 0);
     std::vector<std::pair<int, int>> throw_test_pair;
     
     int bonus_req_calculate(0);
     for (int set_size(1); set_size < THROW_COUNT+1; ++set_size) {
          //get 'set_size' number of test cases in bit-pattern form
          unsigned int prev_bit_pattern = max_bit_pattern_holder[set_size-1];
          std::vector<unsigned int> bit_patterns = give_longer_set(prev_bit_pattern);
          
          //calculate the MAXIMUM ADDITIONAL value found
          int max_val(-1), max_test_num(1);
          unsigned int max_bit_pattern(0);
          for (int set_type(0); set_type < bit_patterns.size(); ++set_type) {
               //calculate test number of the additional test we are adding to the set
               unsigned int additional_bit = bit_patterns[set_type] ^ prev_bit_pattern;
               int test_num = 0;
               while(additional_bit) {
                    additional_bit = additional_bit >> 1;
                    test_num += 1;
               }
               test_num = THROW_COUNT-test_num+1;
               
               //calculate the value imparted by additional test, and additional throw
               int new_value = matrix_data[(test_num-1)*THROW_COUNT+(set_size-1)];
               if (new_value > max_val) {
                    max_val = new_value;
                    max_bit_pattern = bit_patterns[set_type];
                    max_test_num = test_num;
               }
          }
          
          //finally storing the calculated values
          max_val_holder[set_size] = max_val + max_val_holder[set_size-1]; 
          max_bit_pattern_holder[set_size] = max_bit_pattern;
          
          //push the throw, test pair to the vector
          throw_test_pair.push_back(std::make_pair(set_size, max_test_num));
          if (max_test_num <= 6)
               bonus_req_calculate += max_val;
     }
     //add bonus if sum of first siz categories is >= 63
     if (bonus_req_calculate >= 63)
          max_val_holder[max_val_holder.size()-1] += 35;
     
     //print stuff
     std::cout << "\nTOTAL SUM: " << max_val_holder[max_val_holder.size()-1] << "\n";
     std::cout << "THROW, TEST SEQ.:\n";
     for (int idx = 0; idx < throw_test_pair.size(); ++idx) {
          std::cout << "(" << throw_test_pair[idx].first << ", " << throw_test_pair[idx].second << ")\n";
          print_binary(max_bit_pattern_holder[idx+1]);
          std::cout << "\n";
          //std::cout << max_val_arr[idx] << "\n\n";
     }

     return 0;
}