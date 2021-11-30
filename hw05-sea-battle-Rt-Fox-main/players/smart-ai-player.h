#pragma once

#include <cstdlib>
#include "players/player-interface.h"
#include <vector>

class smart_ai_player_t : public player_interface_t {
public:
  smart_ai_player_t() = default;
  std::pair<int, int> make_move(const field_t &my_field, const field_t &enemy_field) override;
  std::pair<int, int> possible_move();
  void on_miss(int x, int y) override;
  void on_hit(int x, int y) override;
  void on_kill(int x, int y) override;

  void on_incorrect_move(int x, int y) override;
  void on_duplicate_move(int x, int y) override;
  void on_win() override;
  void on_lose() override;
private:
  int pos_x = -1;
  int pos_y = -1;
  std::pair<int, int> direction = {0,0};//все ходы, в оптимальном варианте

  field_t empty_field = {
      "..........",
      "..........",
      "..........",
      "..........",
      "..........",
      "..........",
      "..........",
      "..........",
      "..........",
      ".........."
  };
};
