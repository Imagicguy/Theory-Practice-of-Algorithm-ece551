#include <cstdlib>
#include <cstring>
#include <iostream>
template<typename T>
class MyClass
{
 private:
  T data;

 public:
  template<typename A>
  T setData(const A & input) {
    data = (T)input;
    return data;
  }
  ~MyClass() {}
};

int main() {
  MyClass<std::string> * a1 = new MyClass<std::string>;
  std::cout << a1->setData<std::string>("ok") << std::endl;
  MyClass<std::string> a2;
  std::cout << a2.setData<std::string>("all right") << std::endl;
  delete a1;
}
