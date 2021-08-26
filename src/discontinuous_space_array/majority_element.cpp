#include <functional>

#include <glog/logging.h>
#include <gtest/gtest.h>

int GetMajorityElement(const std::vector<int>& input) {
  if (input.size() < 1) return -1;
  int ans = input.front();
  int count = 1;
  for (int i = 1; i < input.size(); ++i) {
    if (count == 0) {
      ans = input[i];
      count = 1;
      continue;
    }
    if (input[i] == ans) {
      ++count;
    } else {
      --count;
    }
  }
  return ans;
}

TEST(MajorityElement, LC169) {
  std::vector<int> input1{2, 2, 1, 1, 1, 2, 2};
  auto ans = GetMajorityElement(input1);
  std::cout << "ans " << ans << std::endl;
}

int main(int arc, char** argv) {
  testing::InitGoogleTest(&arc, argv);
  return RUN_ALL_TESTS();

  return 0;
}