#include <gtest/gtest.h>

#include <random>
#include <unordered_map>

#include "ignition/utils/NeverDestroyed.hh"

class Boom : public std::exception { };
struct DtorGoesBoom {
#ifdef _WIN32
// Disable warning C4722 which is triggered by the exception thrown in the dtor
#pragma warning(push)
#pragma warning(disable : 4722)
#endif
  ~DtorGoesBoom() noexcept(false) { throw Boom(); }
#ifdef _WIN32
#pragma warning(pop)
#endif
};

// Confirm that we see booms by default.
GTEST_TEST(NeverDestroyed, BoomTest) {
  try {
    { DtorGoesBoom foo; }
    GTEST_FAIL();
  } catch (const Boom&) {
    ASSERT_TRUE(true);
  }
}

// Confirm that our wrapper stops the booms.
GTEST_TEST(NeverDestroyed, NoBoomTest) {
  try {
    { ignition::utils::NeverDestroyed<DtorGoesBoom> foo; }
    ASSERT_TRUE(true);
  } catch (const Boom& e) {
    GTEST_FAIL();
  }
}

// This is an example from the class overview API docs; we repeat it here to
// ensure it remains valid.
class Singleton {
 public:
  Singleton(const Singleton&) = delete;
  void operator=(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  void operator=(Singleton&&) = delete;

  static Singleton& getInstance() {
    static ignition::utils::NeverDestroyed<Singleton> instance;
    return instance.Access();
  }
 private:
  friend ignition::utils::NeverDestroyed<Singleton>;
  Singleton() = default;
};

GTEST_TEST(NeverDestroyedExample, Singleton) {
  const Singleton* get1 = &Singleton::getInstance();
  const Singleton* get2 = &Singleton::getInstance();
  EXPECT_EQ(get1, get2);
}

// This is an example from the class overview API docs; we repeat it here to
// ensure it remains valid.
enum class Foo { kBar, kBaz };
Foo ParseFoo(const std::string& foo_string) {
  using Dict = std::unordered_map<std::string, Foo>;
  static const ignition::utils::NeverDestroyed<Dict> string_to_enum{
    std::initializer_list<Dict::value_type>{
      {"bar", Foo::kBar},
      {"baz", Foo::kBaz},
    }
  };
  return string_to_enum.Access().at(foo_string);
}

GTEST_TEST(NeverDestroyedExample, ParseFoo) {
  EXPECT_EQ(ParseFoo("bar"), Foo::kBar);
  EXPECT_EQ(ParseFoo("baz"), Foo::kBaz);
}

// This is an example from the class overview API docs; we repeat it here to
// ensure it remains valid.
const std::vector<double>& GetConstantMagicNumbers() {
  static const
  ignition::utils::NeverDestroyed<std::vector<double>> result{[]() {
    std::vector<double> prototype;
    std::mt19937 random_generator;
    for (int i = 0; i < 10; ++i) {
      double new_value = random_generator();
      prototype.push_back(new_value);
    }
    return prototype;
  }()};
  return result.Access();
}

GTEST_TEST(NeverDestroyedExample, GetConstantMagicNumbers) {
  const auto& numbers = GetConstantMagicNumbers();
  EXPECT_EQ(numbers.size(), 10u);
}
