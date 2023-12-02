#include <iostream>
#include <vector>
#include <chrono>

class Object_1
{
 public:
        Object_1() = default;
        ~Object_1() = default;
        Object_1(const Object_1&) = default;
        Object_1& operator=(const Object_1&) = default;

 private:
        int m_member;
};

template<typename T>
double object_ctor_speed()
{
   const auto start{std::chrono::steady_clock::now()};
   T object;
   const auto end{std::chrono::steady_clock::now()};
   const std::chrono::duration<double> timer{end - start};
   return timer.count();
}

template <typename T>
double rvaule_pback_speed(const T& object)
{
 std::vector<T> container;
 const auto start{std::chrono::steady_clock::now()};
 container.push_back(object);
 const auto end{std::chrono::steady_clock::now()};
 const std::chrono::duration<double> timer{end - start};
 return timer.count();
}

template <typename T>
double lvaule_pback_speed(T&& object)
{
    std::vector<T> container;
    const auto start{std::chrono::steady_clock::now()};
    container.push_back(std::forward<T>(object)); 
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> timer{end - start};
    return timer.count();
}

int main()
{
    try
    {
        int test_object_1{13} ;
        Object_1 test_object_2;
    std::cout << "Object creating speed" << '\n' << "1: " 
              << object_ctor_speed<int>() << "2: "
              << object_ctor_speed<Object_1>() << std::endl ;
    std::cout << "Rvalue object  push_back() speed" << '\n' << "1: "
              << rvaule_pback_speed(test_object_1) << '\n' << "2: "
              << rvaule_pback_speed(test_object_2) << std:: endl ;
    std::cout << "Lvalue object push_back() speed" << '\n' << "1: "
              << lvaule_pback_speed(13) << '\n' << "2: "
              << lvaule_pback_speed(std::move(test_object_2)) << std:: endl ;
    return 0 ;
    }
    catch(...) 
                {
                    std::cerr << "Cannot check speed" ; 
                    exit(1) ;
                }
}
