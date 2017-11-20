#include<iostream>
#include<vector>
#include<array>
#include<deque>
#include<string>
#include<algorithm>

unsigned int give_bits(unsigned int ones_count) {
     unsigned int output(0);
     for (int idx(0); idx < ones_count; ++idx) {
          output = output << 1;
          output = output | 0x01;
     }
     
     return output;
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

void print_binary(unsigned int input) {
     const int SUIT_SIZE(13);
     //print each bit to the 'cout' buffer
     for (int idx(SUIT_SIZE-1); idx > -1; --idx)
          std::cout << ( ( (0x01<<idx) & input ) >> idx );
}

int main() {
     std::vector<unsigned int> output_bitpattern = give_longer_set(104);
     
     for (int i = 0; i < output_bitpattern.size(); ++i) {
          print_binary(output_bitpattern[i]);
          std::cout << "\n";
     }
     std::cout << "\n";
     
     for (int idx(0); idx < 13 + 1; ++idx) {
          print_binary(give_bits(idx));
          std::cout << "\n";
     }
     return 0;
}