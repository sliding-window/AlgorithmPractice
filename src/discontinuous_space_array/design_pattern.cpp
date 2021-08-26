#include <functional>
#include <memory>
#include <glog/logging.h>
#include <gtest/gtest.h>

class Investment {
 public:
  virtual ~Investment() {}
};

class Stock : public Investment {
 public:
  Stock() = default;
  Stock(int a, int b) {}
  virtual ~Stock() {}
};

class Bond : public Investment {
 public:
  Bond() = default;
  Bond(int a, int b, int c) {}

  virtual ~Bond() {}
};

class RealEstate : public Investment {
 public:
  RealEstate() = default;
  RealEstate(int a, int b, int c, int d) {}
  virtual ~RealEstate() {}
};


void DoSomethingBeforeDelete(){};

auto DelInvestment = [](Investment* ptr) {
  DoSomethingBeforeDelete();
  delete ptr;
};

enum class InvestMentType { STOCK, BOND, REALESTATE };

template <typename T, typename... Ts>
std::unique_ptr<T> ClassFactory(Ts&&... params) {
  std::unique_ptr<T> ptr(new T(std::forward<Ts>(params)...));
  return ptr;
}

TEST(FactoryMode, fm) {
  auto real_estate_ptr = ClassFactory<RealEstate>(1, 2, 3, 4);
  auto bond_ptr = ClassFactory<Bond>(1, 2, 3);
}

int main(int arc, char** argv) {
  testing::InitGoogleTest(&arc, argv);
  return RUN_ALL_TESTS();

  return 0;
}