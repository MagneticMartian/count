#include <iostream>
#include <functional>

/*
 * auto takes the declared objects and gives it the return type of the 
 * initializer.
 *
 * auto main() -> int is a postfixed return type equivalent to int main().
 *
 * std::function<std::string(int)> f; says that the function f takes a varible
 * of type int and returns type std::string.
 *
 * [&f] is the lambda introducer. It is storing a reference to f and is called
 * a capture list. In order for the lambdas below to be able to use f they need
 * to capture it. The reason we need a reference is so that it is not trying to 
 * use a copy of the function f. Using a copy capture will result in a run time
 * error:
 *          std::bad_function_call
 *          Aborted: (core dump)
 *
 * <typename... Ts>(Ts... n) is a function parameter pack. It is similar to
 * building a tuple out of the list fed into it. The elements are not linked in
 * any way. The pack is iterated over one-by-one.
*/

auto main() -> int {
    std::function<std::string(int)> f;
    f = [&f] (int n) {
        return (n == 1) ? "1" : f(n - 1) + " " + std::to_string(n);
    };
    auto fun = [&f] <typename... Ts>(Ts... n){
        return ((f(n) + "\n") + ...);
    };
    std::cout << fun(5,4,3,2,1);
}
/*
Bellow is a procedural version of the program to elucidate how and what the
program is doing.
std::string f(int n) {
    if(n == 1){
        return "1";
    } else {
        return f(n - 1) + " " + std::to_string(n);
    }
}

template<typename... Ts>
std::string fun(Ts... n) {
    return ((f(n) + "\n") + ...);
}

int main() {
    std::cout << fun(5,4,3,2,1);
}
*/
