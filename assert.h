#ifndef ASSERT_H
#define ASSERT_H

#define ASSERT_TRUE(predict) do { \
  if (!(predict)) { \
    std::cout << "FAILED: " << #predict << std::endl; \
  } else { \
    std::cout << "PASSED: " << #predict << std::endl; \
  } \
} while(false);

#define EXPECT_EQ(a, b) do { \
  if ((a) != (b)) { \
    std::cout << "FAILED: " << #a << " != " << #b << std::endl; \
  } else { \
    std::cout << "PASSED: " << #a << " == " << #b << std::endl; \
  } \
} while(false);

#endif  // ASSERT_H
