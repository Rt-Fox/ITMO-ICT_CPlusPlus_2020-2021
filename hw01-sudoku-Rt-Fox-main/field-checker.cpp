#include "field-checker.h"
#define LENGTH_OF_SUDOKU 9

bool check_field(const std::vector<std::vector<int>>& init_field,
                 const std::vector<std::vector<int>>& solution) {
  for (int i = 0; i < LENGTH_OF_SUDOKU; i++) {
    for (int j = 0; j < LENGTH_OF_SUDOKU; j++) {
      if (init_field[i][j] != 0 && init_field[i][j] == solution[i][j]) {
        continue; //поле не пустое и значения одинаковы.
      } else {
        if (init_field[i][j] != 0) {
          //значит значения не равны, хотя обязына быть равны.
          return false;
        }
        //поле пустое, проверим на валидность координату ij для решения
        int count_block = 0;
        for (int k = 0; k < LENGTH_OF_SUDOKU; k++) {
          if ( (k!=j && solution[i][k] == solution[i][j]) || (k!=i && solution[k][j] == solution[i][j]) ) {
            return false;
          }
        }
        int blrow =3 * (i / 3);
        int blcol = 3 * (j / 3);
        //определяю в каком блоке находятся пустой элемент
        for (int row = 0; row < 3; row++) {
          for (int col = 0; col < 3; col++) {
            if  ((blrow + row == i)&&(blcol + col == j)) {
              continue;
            }
            if (solution[blrow + row][blcol + col] == solution[i][j]){
              return false;
            }
          }
        }
      }
    }
  }
  return true;
}
