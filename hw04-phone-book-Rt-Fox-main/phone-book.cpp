#include "phone-book.h"

bool Comp_name::operator()(const user_info_t &a, const user_info_t &b) const {
  if (a.user.name != b.user.name) {
    return a.user.name < b.user.name;
  } else if (a.total_call_duration_s != b.total_call_duration_s) {
    return a.total_call_duration_s > b.total_call_duration_s;
  } else {
    return a.user.number < b.user.number; //при полном равенстве вывдеет false.
  }
}
bool Comp_total::operator()(const user_info_t &a, const user_info_t &b) const {
  if (a.total_call_duration_s != b.total_call_duration_s) {
    return a.total_call_duration_s > b.total_call_duration_s;
  } else if (a.user.name != b.user.name) {
    return a.user.name < b.user.name;
  } else  {
    return a.user.number < b.user.number;
  }
}
bool phone_book_t::create_user(const std::string &number, const std::string &name) {
  if (users.find(number) != users.end()) {
    //такой юзер уже есть
    return false;
  }
  //если его нет, вставим во все массивы массива.
  //создадим структуру такого юзера
  user_info_t u {{number,name}};
  //новый контакт
  users[number] = u;
  //новый контакт в сете сортированном по имени
  users_by_name.insert(u);
  //новый контакт с каждым префиксом.
  for (int i = 0; i <= number.size(); ++i) {
    //вставим в каждый сет
    users_by_total[number.substr(0,  i)].insert(u);
  }
  return true;
}
bool phone_book_t::add_call(const call_t &call) {
  if (users.find(call.number) == users.end()) {
    //такого номера нет
    return false;
  }
  //такой юзер есть
  //удалим из сетов данного юзера
  auto it = users_by_name.find(users[call.number]);
  users_by_name.erase(users_by_name.lower_bound(users[call.number]));
  for (int i = 0; i <= call.number.size(); ++i) {
    users_by_total[call.number.substr(0, 0 + i - 1)].erase(
        users_by_total[call.number.substr(0, 0 + i - 1)].lower_bound(users[call.number]));
  }
  //изменим длинну звонка в основном массиве
  users[call.number].total_call_duration_s += call.duration_s;
  //вставим его обратно с новыми значениями
  users_by_name.insert(users[call.number]);
  for (int i = 0; i <= call.number.size(); ++i) {
    //вставим в каждый сет юзера
    users_by_total[call.number.substr(0, 0 + i)].insert(users[call.number]);
  }
  //добавим звонок в историю
  calls.push_back(call);
  return true;
}
std::vector<call_t> phone_book_t::get_calls(size_t start_pos, size_t count) const {
  //берем минимум из старотовой позиции и размеров вектора на случай старта больше чем вектор
  //берем минимум из стартовой позииции плюс число запросов, если конченая позиция больше, то вновь будет размер вектора
  return {calls.begin() + std::min(start_pos, calls.size()),calls.begin() + std::min(start_pos + count, calls.size())};

}
std::vector<user_info_t> phone_book_t::search_users_by_number(const std::string &number_prefix, size_t count) const {
  std::vector<user_info_t> answer = {};
  if (users_by_total.find(number_prefix)==users_by_total.end()) {
    return answer;
  }
  auto it = users_by_total.at(number_prefix).begin();
  while (count && it != users_by_total.at(number_prefix).end()) {
    answer.push_back(*it);
    count--;
    it++;
  }
  return answer;
}

std::vector<user_info_t> phone_book_t::search_users_by_name(const std::string &name_prefix, size_t count) const {
  std::vector<user_info_t> answer = {};
  //фиктивный юзер
  user_info_t u {{ "number", name_prefix},std::numeric_limits<int>::max()};
  auto it = users_by_name.lower_bound(u);
  while (count && it != users_by_name.end()) {
    if((*it).user.name.find(name_prefix, 0) != 0) {
      break;
    }
    answer.push_back(*it);
    count--;
    it++;
  }
  return answer;
}
void phone_book_t::clear() {
  calls.clear();
  users.clear();
  users_by_name.clear();
  users_by_total.clear();
}

size_t phone_book_t::size() const {
  return users.size();
}
bool phone_book_t::empty() const {
  return users.empty();
}
