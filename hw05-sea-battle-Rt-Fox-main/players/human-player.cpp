#include "players/human-player.h"

human_player_t::human_player_t(std::istream &input_stream, std::ostream &output_stream)
    : input_stream(input_stream), output_stream(output_stream), len(field_t::FIELD_SIZE) {
  for (int y = 0; y < len; y++) {
    for (char x = 'A'; x < char('A'+len); x++) {
      all_pos[std::to_string(y+1) + x] = {y, int(x -'A')};
      all_pos_reverse[{y,int(x - 'A')}] = std::to_string(y+1) + x;
    }
  }
}
std::pair<int, int> human_player_t::make_move(const field_t &my_field, const field_t &enemy_field) {
  output_stream << "Your field:" << std::endl;
  output_stream << my_field << std::endl;
  output_stream << "Enemy's field" << std::endl;
  output_stream << enemy_field << std::endl;
  output_stream << "Input you turn! [Example 1A or 10B or 6J]" << std::endl;
  while (true) {
    std::getline(input_stream, s);
    if (all_pos.find(s) != all_pos.end()) {
      //такой ход существует
      return all_pos.find(s)->second;
    } else {
      output_stream << "Incorrect move! [Correct example 1A or 10B or 6J]" << std::endl;
    }
  }
}
void human_player_t::on_incorrect_move(int x, int y) {
  assert(false);
}

void human_player_t::on_duplicate_move(int x, int y) {
  const std::pair<int, int> move_pos = {x,y};
  output_stream << all_pos_reverse.find(move_pos)->second  << " DUPLICATE! Repeat move!" << std::endl;
}

void human_player_t::on_miss(int x, int y) {
  const std::pair<int, int> move_pos = {x,y};
  output_stream << all_pos_reverse.find(move_pos)->second  << " MISS! Enemy's turn!" << std::endl;
}
void human_player_t::on_hit(int x, int y) {
  const std::pair<int, int> move_pos = {x,y};
  output_stream << all_pos_reverse.find(move_pos)->second  << " HIT! Your next move!" << std::endl;
}
void human_player_t::on_kill(int x, int y) {
  const std::pair<int, int> move_pos = {x,y};
  output_stream << all_pos_reverse.find(move_pos)->second  << " KILL! Your next move!" << std::endl;

}
void human_player_t::on_win() {
  output_stream << "You WIN!" << std::endl;
}
void human_player_t::on_lose() {
  output_stream << "You LOSE!" << std::endl;
}
