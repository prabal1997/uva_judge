#include<iostream>
#include<deque>
#include<string>
#include<algorithm>
#define DEBUG_MODE


namespace card {
     
     //define the 'CARD' data-type
     const int DECK_SIZE = 52;
     const int ERROR_CARD = -1;

     const char type[] = "23456789TJQKA";
     const char suit[] = "cdhs";
     
     int rank_card(std::string input_card) {
          int type_val(0), suit_val(0);

          //create a ranking for the input card
          for (type_val = 0; (type_val < sizeof(type)-1); ++type_val)
               if (type[type_val] == input_card[0])
                    for (suit_val = 0; (suit_val < sizeof(suit) - 1); ++suit_val)
                         if (suit[suit_val] == input_card[1])
                              //return output when a match occurs
                              return (suit_val*(DECK_SIZE/4) + type_val);

          //indicate error otherwise
          return ERROR_CARD;
     }
     
     //convert the card rank to a card
     std::string unrank_card(int card_rank) {
          std::string output_string = "00";
          output_string[0] = type[card_rank%(DECK_SIZE/4)];
          output_string[1] = suit[card_rank/13];
     }
}

int main() {
     while(true) {
          //receive input card data
          std::deque<int> player_1(card::DECK_SIZE/2, card::ERROR_CARD), player_2(card::DECK_SIZE/2, card::ERROR_CARD), desk;
          for(int count_input(0); count_input < card::DECK_SIZE; ++count_input) {
          //for(int count_input(0); count_input < 4; ++count_input) {
               std::string temp_input;
               std::cin >> temp_input;
     
               if (count_input <= card::DECK_SIZE/2-1)
                    player_1.at(count_input) = card::rank_card(temp_input);
               else
                    player_2.at(count_input-card::DECK_SIZE/2) = card::rank_card(temp_input);               
          }
     
          //start the game
          bool in_war(false);
          int iteration_count(0);
          const int UPPER_LIMIT = 10000;
          while( (iteration_count++ < UPPER_LIMIT) && !player_1.empty() && !player_2.empty() ) {
               //getting the cards on top of the deck
               int player_1_move(player_1.back()), player_2_move(player_2.back());
               player_1.pop_back();           player_2.pop_back();
               desk.push_back(player_1_move); desk.push_back(player_2_move);
               
               //comparing the cards
               if (in_war) {
                    if (player_1_move%13 > player_2_move%13) {
                         while(!desk.empty()) {
                              player_1.push_front(desk.back());
                              desk.pop_back();
                         }
                    }
                    else if (player_1_move%13 <  player_2_move%13) {
                         while(!desk.empty()) {
                              player_2.push_front(desk.back());
                              desk.pop_back();
                         }
                    }
                    else {
                         in_war = true;
                    }
               }
               else 
                    in_war = false;
          }
     
          if (!player_1.empty() && player_2.empty()) {
               std::cout << "Player 1 wins!\n";
          }
          if (player_1.empty() && !player_2.empty()) {
               std::cout << "Player 2 wins!\n";
          }
          if (player_1.empty() && player_2.empty()) {
               std::cout << "Tie!\n";
          }
     }
     
     
     return 0;
}