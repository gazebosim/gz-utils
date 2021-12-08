#ifndef IGNITION_UTILS_NEVERDESTROYED_HH_
#define IGNITION_UTILS_NEVERDESTROYED_HH_

#include <new>
#include <type_traits>
#include <utility>

namespace ignition
{
namespace utils
{

/// Originally copied from https://github.com/RobotLocomotion/drake/blob/v0.36.0/common/never_destroyed.h
/// Originally licensed BSD 3-Clause (https://github.com/RobotLocomotion/drake/blob/v0.36.0/LICENSE.TXT)

/// Wraps an underlying type T such that its storage is a direct member field
/// of this object (i.e., without any indirection into the heap), but *unlike*
/// most member fields T's destructor is never invoked.
///
/// This is especially useful for function-local static variables that are not
/// trivially destructable.  We shouldn't call their destructor at program exit
/// because of the "indeterminate order of ... destruction" as mentioned in
/// cppguide's
/// <a href="https://drake.mit.edu/styleguide/cppguide.html#Static_and_Global_Variables">Static
/// and Global Variables</a> section, but other solutions to this problem place
///  the objects on the heap through an indirection.
///
/// Compared with other approaches, this mechanism more clearly describes the
/// intent to readers, avoids "possible leak" warnings from memory-checking
/// tools, and is probably slightly faster.
template <typename T>
class NeverDestroyed {
 public:
  /// Passes the constructor arguments along to T using perfect forwarding.
  template <typename... Args>
  explicit NeverDestroyed(Args&&... args) {
    // Uses "placement new" to construct a `T` in `storage_`.
    new (&storage_) T(std::forward<Args>(args)...);
  }

  /// Does nothing.  Guaranteed!
  ~NeverDestroyed() = default;

  /// \brief Deleted copy constructor
  NeverDestroyed(const NeverDestroyed&) = delete;

  /// \brief Deleted move constructor
  NeverDestroyed(NeverDestroyed&&) = delete;

  /// \brief Deleted copy assignment constructor
  NeverDestroyed& operator=(const NeverDestroyed&) = delete;

  /// \brief Deleted move assignment constructor
  NeverDestroyed& operator=(NeverDestroyed&&) noexcept = delete;

  /// Returns the underlying T reference.
  T& access() { return *reinterpret_cast<T*>(&storage_); }
  const T& access() const { return *reinterpret_cast<const T*>(&storage_); }

 private:
  typename std::aligned_storage<sizeof(T), alignof(T)>::type storage_;
};

}  // namespace utils
}  // namespace ignition

#endif  // IGNITION_UTILS_NEVERDESTROYED_HH_

