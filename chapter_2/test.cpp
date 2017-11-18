#include<iostream>
#include<vector>
#include<array>
#include<deque>
#include<string>
#include<algorithm>


const int DICE_COUNT = 5;

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

int main() {
     std::array<int, DICE_COUNT> test = {1, 2, 2, 3, 3};
     std::cout << calc_result(test, 13) << "\n";
     
     return 0;
}