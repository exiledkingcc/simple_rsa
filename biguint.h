#ifndef _BIGUINT_H__
#define _BIGUINT_H__ 1

#include <cstdint>
#include <string>
#include <vector>


namespace simple_rsa {

using std::uint32_t;
typedef unsigned int uint;

class BigUint {
public:
  BigUint():_data{0} {}
  BigUint(uint32_t n):_data{n} {}
  BigUint(const BigUint& other):_data{other._data} {}
  BigUint(BigUint&& rhs):_data{std::move(rhs._data)} {}
  ~BigUint() = default;

  bigint& operator=(const BigUint& other) {
    if (this != &other) {
      _data = other._data;
    }
    return *this;
  }
  bigint& operator=(BigUint&& rhs) {
    if (this != &rhs) {
      _data = std::move(rhs._data);
    }
    return *this;
  }

  // hexadecimal format
  std::string to_string() const;

  // not exactly, multiple of 32
  uint bits_length() const;

  // not exactly, multiple of 32
  void shrink_to_fit();

  // not exactly, multiple of 32
  void random_bits(uint bits);

  bool operator<(const BigUint& b) const { return _compare_(b) < 0; }
  bool operator>(const BigUint& b) const { return _compare_(b) > 0; }
  bool operator==(const BigUint& b) const { return _compare_(b) == 0; }
  bool operator<=(const BigUint& b) const { return _compare_(b) <= 0; }
  bool operator>=(const BigUint& b) const { return _compare_(b) >= 0; }

  BigUint& operator+=(uint32_t n);
  BigUint& operator-=(uint32_t n);
  BigUint& operator*=(uint32_t n);
  BigUint& operator/=(uint32_t n);
  BigUint& operator+=(const BigUint& b);
  BigUint& operator-=(const BigUint& b);
  BigUint& operator*=(const BigUint& b);
  BigUint& operator/=(const BigUint& b);

private:
  int _compare_(const const BigUint& b) const;

private:
  std::vector<uint32_t> _data;
};

} // namespace simple_rsa

#endif // _BIGUINT_H__