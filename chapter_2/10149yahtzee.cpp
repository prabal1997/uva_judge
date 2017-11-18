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
     
     std::cout << "START!\n";
     //print
     //print stuff
     for (int i = 0; i < THROW_COUNT*THROW_COUNT; ++i) {
          //print data
          std::cout << std::setw(4);
          std::cout << matrix_data[i] <<  " (" << matrix_bool[i] << ") ";
          if ( i%THROW_COUNT == THROW_COUNT-1 )
               std::cout << "\n";
     }
     std::cout << "\n";
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
     std::vector<std::pair<int, int>> throw_test_pair;
     while(true) {
          //find maximum value that a throw seq. can obtain
          std::array<std::pair<int, int>, THROW_COUNT> test_max_val;  //keeps max_value, dice_seq. that gives max_value
          for (int counter = 0; counter < THROW_COUNT; ++counter) {
               test_max_val[counter] = std::make_pair(MIN_NUM, MIN_NUM);
               std::cout << "<" << test_max_val[counter].first << "," << test_max_val[counter].second << "> | LOL\n";
          }
          
          for (int throw_num = 0; throw_num < THROW_COUNT; ++throw_num) {
               //find test that maximizes value of a dice-seq.
               int max_val(MIN_NUM), max_idx(MIN_NUM);
               for (int test_num = 0; test_num < THROW_COUNT; ++test_num) {
                    if (matrix_bool[test_num*THROW_COUNT+throw_num] && matrix_data[test_num*THROW_COUNT+throw_num] > max_val) {
                         max_val = matrix_data[test_num*THROW_COUNT+throw_num];
                         max_idx = test_num;
                    }
               }
               
               std::cout << "<" << test_max_val[max_idx].first << "," << test_max_val[max_idx].second << "> | ";               
               //mark the above-found dice-seq.
               if (test_max_val[max_idx].first < max_val) {
                    test_max_val[max_idx].first = max_val;
                    test_max_val[max_idx].second = throw_num;
               }
               std::cout << "< (for " << max_idx << ") " << test_max_val[max_idx].first << "," << test_max_val[max_idx].second << ">\n";

          }
          
          
          //calculate the maximum
          for (int test_num = THROW_COUNT-1; test_num > -1; --test_num) {
               int throw_idx = test_max_val[test_num].second;
               int test_idx = test_num;
               if (throw_idx!=MIN_NUM) {
                    
                    throw_test_pair.push_back(std::make_pair(throw_idx, test_idx));
                    
                    for (int counter = 0; counter < THROW_COUNT; ++counter)
                         matrix_bool[counter*THROW_COUNT+throw_idx] = false; 
                    for (int counter = 0; counter < THROW_COUNT; ++counter)
                         matrix_bool[test_idx*THROW_COUNT+counter] = false;
                         
                    //print
                    //print stuff
                    std::cout << "<" << test_idx << "," << test_idx << ">\n";
                    for (int i = 0; i < THROW_COUNT*THROW_COUNT; ++i) {
                         //print data
                         std::cout << std::setw(4);
                         std::cout << matrix_data[i] <<  " (" << matrix_bool[i] << ") ";
                         if ( i%THROW_COUNT == THROW_COUNT-1 )
                              std::cout << "\n";
                    }
                    std::cout << "\n";
               }
          }
          
          
          //see if we should terminate
          int false_count(0);
          for (int counter = 0; counter < THROW_COUNT*THROW_COUNT; ++counter) {
               if (matrix_bool[counter] == false)
                    ++false_count;
          }                            
          if (false_count == THROW_COUNT*THROW_COUNT)
               break;
               
     }
     std::cout << "DONE!\n";
     
     //print stuff
     for (int i = 0; i < THROW_COUNT*THROW_COUNT; ++i) {
          //print data
          std::cout << std::setw(4);
          std::cout << matrix_data[i] <<  " (" << matrix_bool[i] << ") ";
          if ( i%THROW_COUNT == THROW_COUNT-1 )
               std::cout << "\n";
     }
     
     for (int i = 0 ; i < throw_test_pair.size(); ++i) {
          std::pair<int, int> temp = throw_test_pair[throw_test_pair[i].first];
          throw_test_pair[throw_test_pair[i].first] = throw_test_pair[i]; 
          throw_test_pair[i] = temp;
     }
     int val_sum(0);
     for (int i = 0 ; i < throw_test_pair.size(); ++i) {
          std::cout << "(" << throw_test_pair[i].first << ", "  << throw_test_pair[i].second << ")\n"; 
          val_sum += matrix_data[throw_test_pair[i].second*THROW_COUNT + i];
     }
     std::cout << "SUM: " << val_sum << "\n";

     return 0;
}