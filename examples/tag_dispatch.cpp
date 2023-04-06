#include <iostream>
#include <string>
#include <type_traits>

namespace dispatch_by_tag {
// Tags
struct int_tag {};
struct string_tag {};
struct float_tag {};
struct bool_tag {};
struct enum_tag {};

void print_type(auto value, enum_tag) {
    std::cout << "Type: enum with: " << (int)value << std::endl;
}

void print_type(auto value, int_tag) {
    std::cout << "Type: int with: " << value << std::endl;
}

void print_type(const auto& value, string_tag) {
    std::cout << "Type: string with " << value << std::endl;
}

void print_type(auto value, float_tag) {
    std::cout << "Type: float with " << value << std::endl;
}

void print_type(auto value, bool_tag) {
    std::cout << "Type: bool with " << value << std::endl;
}

template <typename T>
void print_type(const T& value) {
    // The draw back of this approach is that we need to add a new tag for each new type
    using tag = typename std::conditional<std::is_same<T, int>::value, int_tag,
                 typename std::conditional<std::is_same<T, std::string>::value, string_tag,
                 typename std::conditional<std::is_same<T, float>::value, float_tag,
                 typename std::conditional<std::is_same<T, bool>::value, bool_tag,
                 typename std::conditional<std::is_enum<T>::value, enum_tag,
                 void>::type>::type>::type>::type>::type;
    print_type(value, tag{});
}

} // namespace dispatch_by_tag

namespace dispatch_by_specialization {

// Base template for print_type_traits
template <typename T, typename = void>
struct print_type_traits;

// Specialization for enum class
template <typename T>
struct print_type_traits<T, std::enable_if_t<std::is_enum_v<T>>> {
    static void print(T value) {
        std::cout << "Type: enum with " << (int)value << std::endl;
    }
};

// Specialization for int
template <>
struct print_type_traits<int> {
    static void print(auto value) {
        std::cout << "Type: int with " << value << std::endl;
    }
};

// Specialization for string
template <>
struct print_type_traits<std::string> {
    static void print(const auto& value) {
        std::cout << "Type: string with " << value << std::endl;
    }
};

// Specialization for float
template <>
struct print_type_traits<float> {
    static void print(auto value) {
        std::cout << "Type: float with " << value << std::endl;
    }
};

// Specialization for bool
template <>
struct print_type_traits<bool> {
    static void print(auto value) {
        std::cout << "Type: bool with " << value << std::endl;
    }
};

template <typename T>
void print_type(const T& value) {
    print_type_traits<T>::print(value);
}

} // namespace dispatch_by_specialization

int main() {
    int i = 42;
    std::string s = "hello";
    float f = 3.14f;
    bool b = true;
    enum class Color { red, green, blue };
    Color c = Color::red;

    dispatch_by_tag::print_type(i); // prints "Type: int"
    dispatch_by_tag::print_type(s); // prints "Type: string"
    dispatch_by_tag::print_type(f); // prints "Type: float"
    dispatch_by_tag::print_type(b); // prints "Type: bool"
    dispatch_by_tag::print_type(c); // prints "Type: Color"

    dispatch_by_specialization::print_type(i); // prints "Type: int"
    dispatch_by_specialization::print_type(s); // prints "Type: string"
    dispatch_by_specialization::print_type(f); // prints "Type: float"
    dispatch_by_specialization::print_type(b); // prints "Type: bool"
    dispatch_by_specialization::print_type(c); // prints "Type: Color"

    return 0;
}
