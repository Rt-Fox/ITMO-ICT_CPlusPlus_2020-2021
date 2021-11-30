#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <ostream>
#include <istream>

class number_t {
public:
  int64_t number;
  number_t(int64_t i = 0);
  number_t& operator=(number_t i);

  explicit operator bool() const;
  explicit operator int64_t() const;
  explicit operator std::string() const;
  bool operator==(int64_t const& i) const;
  bool operator!=(int64_t const& i) const;
  bool operator<(int64_t const& i) const;
  bool operator>(int64_t const& i) const;
  bool operator<=(int64_t const& i) const;
  bool operator>=(int64_t const& i) const;
  bool operator==(number_t const& i) const;
  bool operator!=(number_t const& i) const;
  bool operator<(number_t const& i) const;
  bool operator>(number_t const& i) const;
  bool operator<=(number_t const& i) const;
  bool operator>=(number_t const& i) const;

  number_t operator+() const;
  number_t &operator++();
  number_t operator++(int);
  number_t operator-() const;
  number_t &operator--();
  number_t operator--(int);
  bool operator!() const;
  number_t operator~() const;
  number_t operator+(number_t const& b) const;
  number_t operator-(number_t const& b) const;
  number_t operator*(number_t const& b) const;
  number_t operator/(number_t const& b) const;
  number_t operator%(number_t const& b) const;
  number_t operator^(number_t const& b) const;
  number_t operator&(number_t const& b) const;
  number_t operator|(number_t const& b) const;
  number_t operator+(int64_t const& b) const;
  number_t operator-(int64_t const& b) const;
  number_t operator*(int64_t const& b) const;
  number_t operator/(int64_t const& b) const;
  number_t operator%(int64_t const& b) const;
  number_t operator^(int64_t const& b) const;
  number_t operator&(int64_t const& b) const;
  number_t operator|(int64_t const& b) const;
  number_t &operator+=(const number_t &i);
  number_t &operator-=(const number_t &i);
  number_t &operator/=(const number_t &i);
  number_t &operator*=(const number_t &i);
  number_t &operator|=(const number_t &i);
  number_t &operator&=(const number_t &i);
  number_t &operator<<=(const number_t &i);
  number_t &operator>>=(const number_t &i);
  number_t &operator^=(const number_t &i);
  number_t &operator%=(const number_t &i);
};

bool operator==(int64_t const& a,number_t const& b);
bool operator!=(int64_t const& a,number_t const& b);
bool operator<(int64_t const& a,number_t const& b);
bool operator>(int64_t const& a,number_t const& b);
bool operator>=(int64_t const& a,number_t const& b);
bool operator<=(int64_t const& a,number_t const& b);

number_t operator<<(const number_t &a,const int64_t &i);
number_t operator>>(const number_t &a,const int64_t &i);

std::ostream &operator<<(std::ostream &stream, const number_t &i);
std::istream &operator>>(std::istream &stream, number_t &i);


number_t operator+(int64_t const& a,number_t const& b);
number_t operator-(int64_t const& a,number_t const& b);
number_t operator*(int64_t const& a,number_t const& b);
number_t operator/(int64_t const& a,number_t const& b);
number_t operator%(int64_t const& a,number_t const& b);
number_t operator^(int64_t const& a,number_t const& b);
number_t operator&(int64_t const& a,number_t const& b);
number_t operator|(int64_t const& a,number_t const& b);

