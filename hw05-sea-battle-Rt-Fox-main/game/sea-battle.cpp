#include "game/sea-battle.h"

sea_battle_t::turn_t sea_battle_t::change_turn(turn_t current_turn) {
  return current_turn == FIRST_PLAYER ? SECOND_PLAYER : FIRST_PLAYER;
}

std::string sea_battle_t::get_player_name(turn_t turn) {
  return turn == FIRST_PLAYER ? "First" : "Second";
}
sea_battle_t::sea_battle_t(std::shared_ptr<player_interface_t> player1, field_t field1,
                           std::shared_ptr<player_interface_t> player2, field_t field2)
    : field1(field1), field2(field2), player1(player1), player2(player2) {}
void sea_battle_t::play() {
  //первый игрок первый
  turn_t current_turn_player = FIRST_PLAYER;
  //ссылка на ттекущего игрока
  std::shared_ptr<player_interface_t> current_player = player1;
  //поле текущего игрока
  field_t *current_field = &field1;
  //варжеское поле для текущего игрока
  field_t *enemy_field = &field2;
  //пустое вражеское поле, дабы без подсказок
  field_t empty_field = field2;

  //очистим вражеское поле от подсказок, а также посчитаем количесвто кораблей.
  for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
    for (int j = 0; j < field_t::FIELD_SIZE; ++j) {
      if ((*enemy_field)[i][j] == field_t::SHIP_CELL) {
        empty_field[i][j] = field_t::EMPTY_CELL;
      }
    }
  }
  while (true) {
    //передаем два поля, вызываем функцию хода
    std::pair<int, int> move = current_player->make_move(*current_field, empty_field);
    int x = move.first;
    int y = move.second;
    //проверяем ход
    if (!field_t::is_cell_valid(x, y)) {
      //ты вернул какую-то фигню, давай ты попробуешь еще раз)
      current_player->on_incorrect_move(x, y);
      continue;
    }
    //проверим, что во вражеском поле это точка не является вновь атакуемой.
    if ((*enemy_field)[x][y] == field_t::HIT_CELL || (*enemy_field)[x][y] == field_t::MISS_CELL) {
      //ты "выстрелил" туда, куда уже "стрелял", давай ты попробуешь еще раз
      current_player->on_duplicate_move(x, y);
      continue;
    } else if ((*enemy_field)[x][y] == field_t::EMPTY_CELL) {
      //чел не попал в корабль.
      (*enemy_field)[x][y] = field_t::MISS_CELL;
      current_player->on_miss(x, y);

      //передаем ход другому игроку
      current_turn_player = change_turn(current_turn_player);
      if (get_player_name(current_turn_player) == "First") {
        //ссылка на первого игрока
        current_player = player1;
        //передаем новые ссылки в поля
        current_field = &field1; //поле текущего игрока
        enemy_field = &field2;   //варжеское поле для текущего игрока
        //пустое вражеское поле, дабы без подсказок
        empty_field = field2;
        for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
          for (int j = 0; j < field_t::FIELD_SIZE; ++j) {
            if (empty_field[i][j] == field_t::SHIP_CELL) {
              empty_field[i][j] = field_t::EMPTY_CELL;
            }
          }
        }
      } else {
        //ссылка на ттекущего игрока
        current_player = player2;
        //передаем новые ссылки в поля
        current_field = &field2; //поле текущего игрока
        enemy_field = &field1;   //варжеское поле для текущего игрока
        //пустое вражеское поле, дабы без подсказок
        empty_field = field1;
        for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
          for (int j = 0; j < field_t::FIELD_SIZE; ++j) {
            if (empty_field[i][j] == field_t::SHIP_CELL) {
              empty_field[i][j] = field_t::EMPTY_CELL;
            }
          }
        }
      }
      //следующая итерация цыкла с новым игроком
      continue;
    } else {
      //попал в корабль.
      (*enemy_field)[x][y] = field_t::HIT_CELL; //закрасим точку.
      empty_field[x][y] = field_t::HIT_CELL; //закрасим точку.
      //проверим, что он не убил или же убил корабль;
      bool flag = false;
      for (std::pair<int, int> pair : field_t::DIRECTIONS) {
        // 4 направления
        int dir_x = pair.first;
        int dir_y = pair.second;
        //для одного направления пройдемся в одну сторону
        int k = 1;
        while (field_t::is_cell_valid(x + k * dir_x, y + k * dir_y)) {
          //встретилось пустое поле в этом направлении, переходим в следующее.
          if ((*enemy_field)[x + k * dir_x][y + k * dir_y] == field_t::MISS_CELL ||
              (*enemy_field)[x + k * dir_x][y + k * dir_y] == field_t::EMPTY_CELL) {
            break;
          }
          if ((*enemy_field)[x + k * dir_x][y + k * dir_y] == field_t::SHIP_CELL) {
            //есть куда стрелять
            flag = true;
            break;
          }
          k++;
        }
        if (flag) {
          break;
        }
      }
      //выходя из цикла мы получили одно значение флага, либо false, если корабль убит, либо true, если не убит
      if (flag) {
        current_player->on_hit(x, y);
      } else {
        current_player->on_kill(x, y);

        //проверим, что еще есть корабли.
        bool flag_game = false;
        for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
          for (int j = 0; j < field_t::FIELD_SIZE; ++j) {
            if ((*enemy_field)[i][j] == field_t::SHIP_CELL) {
              //корабль есть
              flag_game = true;
              break;
            }
          }
          //так как корабль есть выхожу и из второго цыкла. (меотда выйти из неаскольких циклов не нашел)
          if (flag_game) {
            break;
          }
        }
        //вновь выйдя из циклов получаем два значения. Если корабль отсался, просто выхываем следующую итерацию
        //бесконечного цыкла
        if (flag_game) {
          continue;
        } else {
          //елси же это не так, то пора вызывать метод он вин у текущего игрока
          current_player->on_win();
          if (get_player_name(current_turn_player) == "First") {
            player2->on_lose();
          } else {
            player1->on_lose();
          }
          return; //конец цикла
        }
      }
    }
  }
}
