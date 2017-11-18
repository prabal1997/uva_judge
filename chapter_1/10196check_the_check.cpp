#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<sstream>

//CONSTANTS
const int BOARD_SIZE(8);
const int PIECE_COUNT(32);

//PRE-DECLARED FUNCTIONS
bool is_empty(std::vector<std::string>);
void check_board(std::vector<std::string>, int);
std::pair<int, int> fix_idx(std::pair<int, int>, std::pair<int, int>);
bool check_if_blocked(std::pair<int, int>, std::pair<int, int>, std::pair<int, int>);

//output buffer
std::stringstream output_buffer;
int main() {
     
     //receive input
     int game_count(0);
     bool cont_read(true);
     int line_count(0);
     std::string temp_line = std::string();
     std::vector<std::string> temp_board;
     //read, process board
     while(cont_read) {
          std::getline(std::cin, temp_line);

          if (!temp_line.empty()) {
               //build the board if the line isn't empty
               temp_board.push_back(temp_line);
               line_count++;

               //process board after receiving it
               if ( !(line_count%BOARD_SIZE) ) {
                    if (!is_empty(temp_board)) {
                         check_board(temp_board, ++game_count);
                         temp_board.clear();
                    }
                    else
                         cont_read = false;
               } 
          }
     }
     
     //flush buffer
     std::cout << output_buffer.str();

     return 0;
}

//FUNCTIONS
//check if the king is blocked
bool check_if_blocked(std::pair<int, int> king_pos, std::pair<int, int> check_pos, std::pair<int, int> current_char, std::vector<std::string>& chess_board) {
     //mark 'incorrect' indices as blocked
     check_pos = fix_idx(check_pos, current_char);
     if (check_pos == current_char)
          return true;
          
     //check if its diagonally, horizontally, or vertically possible to reach another index
     std::pair<int, int> diff = std::make_pair(king_pos.first-check_pos.first,king_pos.second-check_pos.second);
     
     if ( (!diff.first && diff.second) || (!diff.first && diff.second) || (abs(diff.first) == abs(diff.second)) )
          return false;
     
     if ( !diff.first && diff.second ) {
          for (int idx = std::min(king_pos.second, check_pos.second)+1; idx < std::max(king_pos.second, check_pos.second); ++idx) {
               if ( chess_board[king_pos.first][idx] != '.')
                    return true;
          }
     }
     else if ( !diff.second && diff.first ) {
          for (int idx = std::min(king_pos.first, check_pos.first)+1; idx < std::max(king_pos.first, check_pos.first); ++idx) {
               if ( chess_board[idx][king_pos.second] != '.')
                    return true;
          }
     }
     else if (abs(diff.first) == abs(diff.second)) {
          int x_increment = ( (diff.second < 0) ? 1 : -1 );
          int y_increment = ( (diff.first < 0) ? 1 : -1 );          
          
          for (int y_idx = king_pos.first + x_increment; king_pos.first!=check_pos.first; y_idx += y_increment) {
               for (int x_idx = king_pos.second + y_increment; king_pos.second!=check_pos.second; x_idx += x_increment) {
                    if ( chess_board[y_idx][x_idx] != '.')
                         return true;
               }
          }
     }     
     
     
     return false;
}

//checks if the chessboard is empty
bool is_empty(std::vector<std::string> chess_board) {
     int dot_count = std::count(chess_board.begin(), chess_board.end(), "........");
     if (dot_count != BOARD_SIZE)
          return false;
     return true;
}

//fixes an out-of-bounds index
std::pair<int, int> fix_idx(std::pair<int, int> input_data, std::pair<int, int> current_idx) {
     //replace input index with the index of the element being tested for its ability to attack the king incase the input index is invalid
     if (input_data.first < 0 || input_data.first > BOARD_SIZE || input_data.second < 0 || input_data.second > BOARD_SIZE)
          input_data = current_idx;
     return input_data;
}

//checks if a king is in 'check'
void check_board(std::vector<std::string> input_board, int game_count) {
     //find bothg kings' index
     std::pair<int, int> small_king, large_king;
     
     bool small_found(false), large_found(false);
     for (int y_coord(0); y_coord < BOARD_SIZE && (!small_found || !large_found) ; ++y_coord) {
          for (int x_coord(0); x_coord < BOARD_SIZE && (!small_found || !large_found); ++x_coord) {
               if (!small_found && input_board[y_coord][x_coord] == 'k') {
                    small_king = std::make_pair(y_coord, x_coord);
                    small_found = true;
               }
               else if (!large_found && input_board[y_coord][x_coord] == 'K') {
                    large_king = std::make_pair(y_coord, x_coord);
                    large_found = true;
               }
          }
     }
     
     //indicator for whether the king was found
     enum KING_FOUND {NONE = 0, WHITE, BLACK};
     int king_found(NONE);
     
     //iterate through each element, see if they can affect king
     for (int y_coord(0); y_coord < BOARD_SIZE; ++y_coord) {
          for (int x_coord(0); x_coord < BOARD_SIZE; ++x_coord) {
                              
               //element code depending upon character type
               char current_char = input_board[y_coord][x_coord];
               //determine king to be searched
               std::pair<int, int> local_king = ( (std::isupper(current_char)) ? large_king : small_king );
               std::pair<int, int> current_pos = std::make_pair(y_coord, x_coord); 
               switch(std::tolower(current_char)) {
                    case 'p': {
                         //calculate if opponent king is reachable
                         int search_radius(3), black_or_white( (std::isupper(current_char)) ? -1 : 1 );
                         for (int idx = -search_radius/2; !king_found && (idx < search_radius/2 + 1); ++idx)
                              if (local_king == std::make_pair(y_coord + black_or_white, x_coord + idx))
                                   king_found = ( (std::isupper(current_char)) ? BLACK : WHITE );
                         
                         break;
                    }
                    case 'r': {
                         
                         //calculate if opponent king is reachable
                         for (int search_radius(2); !king_found && (search_radius < 2*BOARD_SIZE+1); search_radius = search_radius + 2) {
                              for (int y_offset = -search_radius/2; !king_found && (y_offset < search_radius/2 + 1); ++y_offset) {
                                   for (int x_exp = 0; !king_found && (x_exp < (int)(!y_offset) + 1); ++x_exp) {
                                        int x_offset =  ( (!y_offset) ? (search_radius/2) : 0 ) * ( (x_exp) ? -1 : 1 );
                                        
                                        std::pair<int, int> local_pos_pair = std::make_pair(y_coord + y_offset, x_coord + x_offset);
                                        if ( local_king == local_pos_pair && check_if_blocked(local_king, local_pos_pair, current_pos, input_board) )
                                             king_found = ( (std::isupper(current_char)) ? BLACK : WHITE );
                                   }
                              }
                          }
                         
                         break;
                    }                    
                    case 'b': {
                         
                         //calculate if opponent king is reachable
                         for (int search_radius(2); !king_found && (search_radius < 2*BOARD_SIZE+1); search_radius = search_radius + 2) {
                              for (int y_exp = 0; !king_found && (y_exp < 1 + 1); ++y_exp) {
                                   for (int x_exp = 0; !king_found && (x_exp < 1 + 1); ++x_exp) {
                                        int x_multiplier(1), y_multiplier(1);
                                        x_multiplier *= ( (x_exp) ? -1 : 1 );
                                        y_multiplier *= ( (y_exp) ? -1 : 1 );
     
                                        std::pair<int, int> local_pos_pair = std::make_pair(y_coord + y_multiplier*search_radius, x_coord + x_multiplier*search_radius);
                                        if (local_king == local_pos_pair && check_if_blocked(local_king, local_pos_pair, current_pos, input_board))
                                             king_found = ( (std::isupper(current_char)) ? BLACK : WHITE );
                                   }
                              }
                         }
                          
                         break;
                    }
                    case 'q': {
                         
                         //calculate if opponent king is reachable
                         for (int search_radius(2); !king_found && (search_radius < 2*BOARD_SIZE+1); search_radius = search_radius + 2) {
                              
                              for (int y_exp = -1; !king_found && (y_exp < 1 + 1); ++y_exp) {
                                   for (int x_exp = -1; !king_found && (x_exp < 1 + 1); ++x_exp) {
                                        int x_offset = (search_radius/2) * x_exp;
                                        int y_offset = (search_radius/2) * y_exp;
                                        
                                        std::pair<int, int> local_pos_pair = std::make_pair(y_coord + y_offset, x_coord + x_offset);
                                        if ( local_king == local_pos_pair && check_if_blocked(local_king, local_pos_pair, current_pos, input_board) )
                                             king_found = ( (std::isupper(current_char)) ? BLACK : WHITE );
                                   }
                              }
                              
                         }
                         
                         break;
                    }
                    case 'k': {
                              
                         //calculate if opponent king is reachable                         
                         for (int y_offset = -1; !king_found && (y_offset < 1 + 1); ++y_offset) {
                              for (int x_offset = -1; !king_found && (x_offset < 1 + 1); ++x_offset) {
                                   if (local_king == std::make_pair(y_coord + y_offset, x_coord + x_offset))
                                        king_found = ( (std::isupper(current_char)) ? BLACK : WHITE );
                              }
                         }
                         
                         break;
                    }
                    case 'n': {
                         
                         //calculate if opponent king is reachable
                         for (int y_offset(1); !king_found && y_offset < 2 + 1; ++y_offset)
                              for (int y_exp(0); !king_found && y_exp < 1 + 1; ++y_exp)
                                   for (int x_offset(1); !king_found && x_offset < 2 + 1; ++x_offset)                         
                                        for (int x_exp(0); !king_found && x_offset < 1 + 1; ++x_offset) {
                                             int y_diff = y_offset * ( (y_exp) ? 1 : -1 );
                                             int x_diff = x_offset * ( (x_exp) ? 1 : -1 );
                                             
                                             if (local_king == std::make_pair(y_coord + y_diff, x_coord + x_diff))
                                                  king_found = ( (std::isupper(current_char)) ? BLACK : WHITE );
                                        }
                         break;
                    }
                    default:
                         //do nothing when we are reading a '.' character
                         break;
               }
          }    
     }
     
     //print data on screen
     if (king_found == WHITE) {
          output_buffer << "Game #" << game_count << ": " << "black king is in check.\n";
     }
     else if (king_found == BLACK) {
          output_buffer << "Game #" << game_count << ": " << "white king is in check.\n";
     }
     else {
          output_buffer << "Game #" << game_count << ": " << "no king is in check.\n";          
     }
}