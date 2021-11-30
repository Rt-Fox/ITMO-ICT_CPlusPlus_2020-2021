#include "players/smart-ai-player.h"

//нет смысла проверять ход на валидность, так как если не валидный, то ход снова нащ.
std::pair<int, int> smart_ai_player_t::make_move(const field_t &my_field, const field_t &enemy_field) {
  std::pair<int, int> move;
  if (pos_x == -1) {
    //значит, что мы просто ищем корабли в поле, найдем возможный ход
    return possible_move();
  }
  //если  это не так, то значит в прошлый ход мы попали в координаты: pos-x,pos-y
  if (direction.first == 0 && direction.second == 0) {
    //если направление не выбрано, то значит, нужно выбрать его
    //проверим, было ли направление.
    for(std::pair<int, int> dir : field_t::DIRECTIONS) {
      direction = dir;
      if (!field_t::is_cell_valid(pos_x + direction.first, pos_y + direction.second)) {
        continue;
      }
      //проверим, обратное направление.
      if (empty_field[pos_x + direction.first][pos_y + direction.second] == field_t::HIT_CELL) {
        int k = 2;
        while (empty_field[pos_x + direction.first][pos_y + direction.second] == field_t::EMPTY_CELL) {
          k++;
        }
        return std::make_pair(pos_x + k*direction.first, pos_y + k*direction.second);
      }
    }
    for(std::pair<int, int> dir : field_t::DIRECTIONS) {
      direction = dir;
      if (!field_t::is_cell_valid(pos_x + direction.first, pos_y + direction.second)) {
        continue;
      }
      if (empty_field[pos_x + direction.first][pos_y + direction.second] == field_t::EMPTY_CELL) {
        return std::make_pair(pos_x + direction.first, pos_y + direction.second);
      }
    }
  } else {
      //направление выбрано
      return std::make_pair(pos_x + direction.first, pos_y + direction.second);
  }

  return move;
}
void smart_ai_player_t::on_duplicate_move(int x, int y) {
}

void smart_ai_player_t::on_hit(int x, int y) {
  //запоминаем новую позицию попадания.
  empty_field[x][y] = field_t::HIT_CELL;
  pos_x = x;
  pos_y = y;

}
void smart_ai_player_t::on_kill(int x, int y) {
  //убили цель
  empty_field[x][y] = field_t::HIT_CELL;//поменяем значения в поле.
  pos_x = x;
  pos_y = y;
  while (field_t::is_cell_valid(pos_x, pos_y) && empty_field[pos_x][pos_y] == field_t::HIT_CELL) {
    for(std::pair<int, int> dir : field_t::DIRECTIONS) {
      if (!field_t::is_cell_valid(pos_x + dir.first, pos_y + dir.second)) {
        continue;
      }
      if (empty_field[pos_x + dir.first][pos_y + dir.second] == field_t::EMPTY_CELL) {
        empty_field[pos_x + dir.first][pos_y + dir.second] = field_t::MISS_CELL;
      }
    }
    if (direction.first == 0 && direction.second == 0) {
      break;
    }
    pos_x = pos_x - direction.first;
    pos_y = pos_y - direction.second;
  }
  //вновь ищем корабль среди возможных ходов
  direction = {0,0};
  pos_x = -1;
  pos_y = -1;

}

void smart_ai_player_t::on_miss(int x, int y) {
  empty_field[x][y] = field_t::MISS_CELL;
  direction = {0,0};
}
std::pair<int, int> smart_ai_player_t::possible_move() {
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (empty_field[i][j] == field_t::EMPTY_CELL) {
        return std::make_pair(i,j);
      }
    }
  }
  return std::make_pair(-1,-1);
}
void smart_ai_player_t::on_incorrect_move(int x, int y) {}
void smart_ai_player_t::on_win() {}
void smart_ai_player_t::on_lose() {}
