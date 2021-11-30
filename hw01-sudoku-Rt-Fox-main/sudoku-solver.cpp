#include "sudoku-solver.h"
#include <vector>
#define LENGTH_OF_SUDOKU 9

using solution = std::vector<std::vector<int>>;
using sudoku = std::vector<std::vector<int>>;

std::vector<solution> res;

std::vector<int> get_row(sudoku field, std::vector<int> pos);
std::vector<int> get_col(sudoku field, std::vector<int> pos);
std::vector<int> get_block(sudoku field, std::vector<int> pos);
std::vector<int> find_empty_positions(sudoku field);
std::vector<int> find_possible_values(sudoku field, std::vector<int> pos);
std::vector<std::vector<int>> solve(sudoku field);
void add_solution_to_res(std::vector<std::vector<int>> field);

std::vector<int> get_row(sudoku field, std::vector<int> pos) {
  //Возвращает все значения для номера строки, указанного в pos
  // i = pos[0]  - координата строки
  // j = pos[1] - координата столбца
  return field[pos[0]]; //строка вывода;
}

std::vector<int> get_col(sudoku field, std::vector<int> pos) {
  //Возвращает все значения для номера столбца, указанного в pos
  // i = pos[0]  - координата строки
  // j = pos[1] - координата столбца
  std::vector<int> result(LENGTH_OF_SUDOKU); //блок вывода
  for (int i = 0; i < LENGTH_OF_SUDOKU; i++) {
    result[i] = field[i][pos[1]];
  }
  return result;
}

std::vector<int> get_block(sudoku field, std::vector<int> pos) {
  //Возвращает все значения из квадрата, в который попадает позиция pos
  int i = pos[0]; //- координата строки
  int j = pos[1]; //- координата столбца
  int blrow =
      3 * (i / 3); //определяю в каком блоке находятся координаты позиции
  int blcol =
      3 * (j / 3); //определяю в каком блоке находятся координаты позиции
  std::vector<int> result = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //блок вывода
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      result[3 * row + col] = field[blrow + row][blcol + col]; //заполняю блок
    }
  }
  return result;
}

std::vector<int> find_empty_positions(sudoku field) {
  //Найти первую свободную позицию в судоку
  std::vector<int> pos = {};
  for (int row = 0; row < LENGTH_OF_SUDOKU; row++) {
    for (int col = 0; col < LENGTH_OF_SUDOKU; col++) {
      if (field[row][col] == 0) {
        pos.push_back(row);
        pos.push_back(col);
        return pos;
      }
    }
  }
  return pos;
}

std::vector<int> find_possible_values(sudoku field, std::vector<int> pos) {
  //Вернуть множество возможных значения для указанной позиции
  std::vector<int> possible_values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> row = get_row(field, pos);
  std::vector<int> col = get_col(field, pos);
  std::vector<int> block = get_block(field, pos);

  for (int i = 0; i < LENGTH_OF_SUDOKU; i++) {
    for (int k = 0; k < LENGTH_OF_SUDOKU; k++) {
      if (possible_values[i] == row[k] || possible_values[i] == col[k] ||
          possible_values[i] == block[k]) {
        possible_values[i] = 0;
        break;
      }
    }
  }
  return possible_values;
}

std::vector<std::vector<int>> solve(sudoku field) {
  //решение судоку
  std::vector<int> pos = find_empty_positions(field);
  if (pos.empty()) {
    add_solution_to_res(field); //больше нет свободных мест, судоку решен
    return {{-1}};
  }
  std::vector<int> possible_values = find_possible_values(
      field, pos); //поиск возможных значений, если функция не пустая
  for (int i = 0; i < possible_values.size(); i++) {
    int value = possible_values[i]; //одно из возможных значений
    if (value == 0) {
      continue; //заглушка, на случай 0 в возможном значении
    };
    field[pos[0]][pos[1]] = value;
    //подставляю новое значение и вызываю снова функцию solve, для
    //нового пазла, где свободная позиция уже не может быть такой же
    solve(field);

  } //если свободная  позиция есть, а возможных значений нет, то решения нет, и
  //мы возвращаем {{-1}}
  // возвращаем ноль в исходное место решений нет
  return {{-1}};
}

void add_solution_to_res(sudoku field) {
  res.push_back(field);
}

std::pair<size_t, solution>
sudoku_solve(const std::vector<std::vector<int>>& field) {
  std::vector<std::vector<int>> working_field = field;
  solve(working_field);
  return std::make_pair(res.size(), res[0]);
}

// for tests
// int main(){
//  std::vector<std::vector<int>> working_field = {{5, 9, 6, 1, 3, 8, 4, 7, 2 },
//                                                 {3, 8, 1, 2, 4, 0, 5, 9, 6},
//                                                 {4, 7, 2, 6, 5, 9, 3, 8, 1},
//                                                 {1, 4, 7, 9, 2, 5, 6, 3, 8},
//                                                 {6, 3, 8, 7, 1, 4, 2, 5, 9},
//                                                 {2, 5, 9, 8, 6, 3, 1, 4, 7},
//                                                 {7, 2, 5, 3, 9, 6, 8, 1, 4},
//                                                 {9, 6, 3, 4, 8, 1, 7, 2, 5},
//                                                 {8, 1, 4, 5, 7, 2, 9, 6, 3}};
//  solve(working_field);
//  std::vector<solution> res_end = res;
//  return 1;
//}