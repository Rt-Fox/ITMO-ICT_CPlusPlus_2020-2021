#include "number.h"

number_t::number_t(int64_t number) : number(number) {
}
number_t &number_t::operator=(number_t another_class_number) {
  number = another_class_number.number;
  return *this;
}
number_t::operator bool() const {
  return number != 0;
}
number_t::operator std::string() const {
  return std::to_string(number);
}
number_t::operator int64_t() const {
  return number;
}

bool number_t::operator==(int64_t const& given_number) const {
  return number==given_number;
}
bool number_t::operator!=(int64_t const& given_number) const {
  return number!=given_number;
}
bool number_t::operator<(int64_t const& given_number) const {
  return number<given_number;
}
bool number_t::operator>(int64_t const& given_number) const {
  return number>given_number;
}
bool number_t::operator<=(int64_t const& given_number) const {
  return number<=given_number;
}
bool number_t::operator>=(int64_t const& given_number) const {
  return number>=given_number;
}
bool number_t::operator==(number_t const& another_class_number) const {
  return number==another_class_number.number;
}
bool number_t::operator!=(number_t const& another_class_number) const {
  return number!=another_class_number.number;
}
bool number_t::operator<(number_t const& another_class_number) const {
  return number<another_class_number.number;
}
bool number_t::operator>(number_t const& another_class_number) const {
  return number>another_class_number.number;
}
bool number_t::operator<=(number_t const& another_class_number) const {
  return number<=another_class_number.number;
}
bool number_t::operator>=(number_t const& another_class_number) const {
  return number>=another_class_number.number;
}
bool operator==(int64_t const& given_number, number_t const& another_class_number) {
    return given_number==another_class_number.number;
}
bool operator!=(int64_t const& given_number, number_t const& another_class_number) {
    return given_number!=another_class_number.number;
}
bool operator<(int64_t const& given_number, number_t const& another_class_number) {
    return given_number<another_class_number.number;
}
bool operator>(int64_t const& given_number, number_t const& another_class_number) {
    return given_number>another_class_number.number;
}
bool operator<=(int64_t const& given_number, number_t const& another_class_number) {
    return given_number<=another_class_number.number;
}
bool operator>=(int64_t const& given_number, number_t const& another_class_number) {
    return given_number>=another_class_number.number;
}
//унарный +
number_t number_t::operator+() const {
  return number_t(number);
}
//унарный минус
number_t number_t::operator-() const {
  return number_t(-number);
}
//логическое не
bool number_t::operator!() const {
  return number==0;
}
//побитовое не
number_t number_t::operator~() const {
  return number_t(~number);
}
//префиксный инкремент
number_t &number_t::operator++() {
  ++number;
  return *this;
}
//постфиксный инкремент
number_t number_t::operator++(int) {
  number_t temp(number);
  ++(*this);
  return  temp;
}
//префиксный декремент
number_t &number_t::operator--() {
  --number;
  return *this;
}
//постфиксный декремент
number_t number_t::operator--(int) {
  number_t temp(number);
  --(*this);
  return  temp;
}

number_t &number_t::operator+=(const number_t &class_number) {
  number += class_number.number;
  return *this;
}
number_t &number_t::operator-=(const number_t &class_number) {
  number -= class_number.number;
  return *this;
}
number_t &number_t::operator/=(const number_t &class_number) {
  number /= class_number.number;
  return *this;
}
number_t &number_t::operator*=(const number_t &class_number) {
  number *= class_number.number;
  return *this;
}
number_t &number_t::operator|=(const number_t &class_number) {
  number |= class_number.number;
  return *this;
}
number_t &number_t::operator&=(const number_t &class_number) {
  number &= class_number.number;
  return *this;
}
number_t &number_t::operator<<=(const number_t &class_number) {
  number <<= class_number.number;
  return *this;
}
number_t &number_t::operator>>=(const number_t &class_number) {
  number >>= class_number.number;
  return *this;
}
number_t &number_t::operator^=(const number_t &class_number) {
  number ^= class_number.number;
  return *this;
}
number_t &number_t::operator%=(const number_t &class_number) {
  number %= class_number.number;
  return *this;
}

number_t number_t::operator+(const number_t &class_number) const{
  number_t temp(number + class_number.number);
  return temp;
}
number_t number_t::operator+(const int64_t &given_int) const{
  number_t temp(number + given_int);
  return temp;
}
number_t number_t::operator-(const number_t &class_number) const{
  number_t temp(number - class_number.number);
  return temp;
}
number_t number_t::operator-(const int64_t &given_int) const{
  number_t temp(number - given_int);
  return temp;
}
number_t number_t::operator*(const number_t &class_number) const{
  number_t temp(number * class_number.number);
  return temp;
}
number_t number_t::operator*(const int64_t &given_int) const{
  number_t temp(number * given_int);
  return temp;
}
number_t number_t::operator/(const number_t &class_number) const{
  number_t temp(number / class_number.number);
  return temp;
}
number_t number_t::operator/(const int64_t &given_int) const{
  number_t temp(number / given_int);
  return temp;
}
number_t number_t::operator%(const number_t &class_number) const{
  number_t temp(number % class_number.number);
  return temp;
}
number_t number_t::operator%(const int64_t &given_int) const{
  number_t temp(number % given_int);
  return temp;
}
number_t number_t::operator^(const number_t &class_number) const{
  number_t temp(number ^ class_number.number);
  return temp;
}
number_t number_t::operator^(const int64_t &given_int) const{
  number_t temp(number ^ given_int);
  return temp;
}
number_t number_t::operator&(const number_t &class_number) const{
  number_t temp(number & class_number.number);
  return temp;
}
number_t number_t::operator&(const int64_t &given_int) const{
  number_t temp(number & given_int);
  return temp;
}
number_t number_t::operator|(const number_t &class_number) const{
  number_t temp(number | class_number.number);
  return temp;
}
number_t number_t::operator|(const int64_t &given_int) const{
  number_t temp(number | given_int);
  return temp;
}

number_t operator<<(const number_t &class_number,const int64_t &given_int) {
  return number_t(class_number.number << given_int);
}
number_t operator>>(const number_t &class_number, const int64_t &given_int) {
  return number_t(class_number.number >> given_int);
}


std::ostream &operator<<(std::ostream &stream, const number_t &another_class_number) {
  stream << another_class_number.number;
  return stream;
}
std::istream &operator>>(std::istream &stream, number_t &another_class_number) {
  stream >> another_class_number.number;
  return stream;
}

number_t operator+(int64_t const& given_number, const number_t &class_number) {
  return number_t(given_number + class_number.number);
}
number_t operator-(int64_t const& given_number, const number_t &class_number) {
  return number_t(given_number - class_number.number);
}
number_t operator*(int64_t const& given_number, const number_t &class_number) {
  return number_t(given_number * class_number.number);
}
number_t operator/(int64_t const& given_number, const number_t &class_number) {
  return number_t(given_number / class_number.number);
}
number_t operator%(int64_t const& given_number, const number_t &class_number) {
  return number_t(given_number % class_number.number);
}
number_t operator^(int64_t const& given_number, const number_t &class_number) {
  return number_t(given_number ^ class_number.number);
}
number_t operator&(int64_t const& given_number, const number_t &class_number) {
  return number_t(given_number & class_number.number);
}
number_t operator|(int64_t const& given_number, const number_t &class_number) {
  return number_t(given_number | class_number.number);
}
