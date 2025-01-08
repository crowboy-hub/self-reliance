# 类对象的构造析构
```cpp
#include <iostream>
#include <vector>
#include <string>

class MyClass {
public:
    MyClass(int a, std::string b) : num(a), str(b) {
        std::cout << "Constructing MyClass with num=" << num << " and str=" << str << std::endl;
    }

    ~MyClass() {
        std::cout << "Destroying MyClass with num=" << num << " and str=" << str << std::endl;
    }

private:
    int num;
    std::string str;
};

int main() {
    std::vector<MyClass> vec;

    // 使用 emplace_back 直接在向量末尾构造 MyClass 对象
    vec.emplace_back(1, "Hello");
    vec.emplace_back(2, "World");

    return 0;
}
```
运行结果
```xml
Constructing MyClass with num=1 and str=Hello
Constructing MyClass with num=2 and str=World
Destroying MyClass with num=2 and str=World
Destroying MyClass with num=1 and str=Hello
```
1. emplace_back 是 C++ 标准库中 std::vector 类的一个成员函数，用于在向量的末尾直接构造一个元素，而不是先创建一个临时对象然后再将其复制或移动到向量中。这种方式可以避免不必要的复制或移动操作，从而提高性能。
2. 创建的class对象可以直接放在`std::vector<MyClass> vec;`里

## 构造函数与析构函数
在C++中，构造函数（Constructor）和析构函数（Destructor）是类的特殊成员函数，分别用于对象的初始化和清理。它们在对象的生命周期中扮演着重要的角色，确保对象在创建时正确初始化，在销毁时释放资源。

构造函数
构造函数在对象创建时自动调用，用于初始化对象的数据成员。构造函数有以下特点：

名称与类名相同：构造函数的名称必须与类名相同。
没有返回类型：构造函数没有返回类型，甚至没有void。
可以重载：一个类可以有多个构造函数，通过不同的参数列表进行重载。
默认构造函数：如果没有显式定义任何构造函数，编译器会提供一个默认构造函数。
构造函数的常见形式包括：

默认构造函数：不带参数的构造函数。
参数化构造函数：带参数的构造函数，用于初始化对象的数据成员。
拷贝构造函数：用于从一个已有对象创建新对象。
移动构造函数：用于从临时对象“移动”资源到新对象。
以下是一个示例，展示了不同类型的构造函数：
```cpp
#include <iostream>
#include <string>

class MyClass {
public:
    // 默认构造函数
    MyClass() {
        std::cout << "Default constructor called." << std::endl;
    }

    // 参数化构造函数
    MyClass(int a, std::string b) : num(a), str(b) {
        std::cout << "Parameterized constructor called with num=" << num << " and str=" << str << std::endl;
    }

    // 拷贝构造函数
    MyClass(const MyClass& other) : num(other.num), str(other.str) {
        std::cout << "Copy constructor called." << std::endl;
    }

    // 移动构造函数
    MyClass(MyClass&& other) noexcept : num(other.num), str(std::move(other.str)) {
        std::cout << "Move constructor called." << std::endl;
    }

private:
    int num;
    std::string str;
};

int main() {
    MyClass obj1; // 调用默认构造函数
    MyClass obj2(1, "Hello"); // 调用参数化构造函数
    MyClass obj3 = obj2; // 调用拷贝构造函数
    MyClass obj4 = std::move(obj2); // 调用移动构造函数

    return 0;
}
```
析构函数
析构函数在对象销毁时自动调用，用于清理对象的资源。析构函数有以下特点：

名称与类名相同，前面加上波浪号（~）：析构函数的名称是类名前面加上波浪号（~）。
没有返回类型：析构函数没有返回类型，甚至没有void。
不带参数：析构函数不能带参数，因此不能重载。
默认析构函数：如果没有显式定义析构函数，编译器会提供一个默认析构函数。
以下是一个示例，展示了析构函数的用法：
```cpp
#include <iostream>
#include <string>

class MyClass {
public:
    // 构造函数
    MyClass(int a, std::string b) : num(a), str(b) {
        std::cout << "Constructor called with num=" << num << " and str=" << str << std::endl;
    }
    //

    // 析构函数
    ~MyClass() {
        std::cout << "Destructor called with num=" << num << " and str=" << str << std::endl;
    }

private:
    int num;
    std::string str;
};

int main() {
    MyClass obj(1, "Hello"); // 调用构造函数
    return 0; // 程序结束时，调用析构函数
}
```
**其中在构造函数中使用初始化列表的理解：**
```cpp
类名(参数列表) : 成员变量1(初始值1), 成员变量2(初始值2), ... {
    // 构造函数体
}

```


在这个示例中，当obj对象在main函数结束时被销毁，析构函数会被自动调用，用于清理对象的资源。

总结来说，构造函数和析构函数是C++中非常重要的概念，它们确保对象在创建时正确初始化，在销毁时释放资源，从而避免内存泄漏和其他资源管理问题。

## 函数重载
函数重载（Function Overloading）是C++中的一项特性，允许在同一个作用域内定义多个具有相同名称但参数列表不同的函数。通过函数重载，可以实现类似功能的多个版本，从而提高代码的可读性和可维护性。

函数重载的规则
函数名称相同：重载的函数必须具有相同的名称。
参数列表不同：重载的函数必须在参数的数量、类型或顺序上有所不同。返回类型不同不足以构成函数重载。
返回类型可以不同：函数的返回类型可以不同，但这不是函数重载的依据。
示例
以下是一个简单的示例，展示了函数重载的用法：
```cpp
#include <iostream>

// 重载的函数：打印整数
void print(int x) {
    std::cout << "Integer: " << x << std::endl;
}

// 重载的函数：打印浮点数
void print(double x) {
    std::cout << "Double: " << x << std::endl;
}

// 重载的函数：打印字符串
void print(const std::string& x) {
    std::cout << "String: " << x << std::endl;
}

int main() {
    print(42);          // 调用第一个重载函数
    print(3.14);        // 调用第二个重载函数
    print("Hello");     // 调用第三个重载函数

    return 0;
}
```
在这个示例中，我们定义了三个名为print的函数，分别用于打印整数、浮点数和字符串。尽管它们的名称相同，但由于参数类型不同，编译器能够正确地选择调用哪个函数。

注意事项
默认参数：在函数重载中使用默认参数时需要小心，因为可能会导致歧义。例如：
```cpp
void func(int x) {
    std::cout << "Integer: " << x << std::endl;
}

void func(int x, int y = 0) {
    std::cout << "Integer with default: " << x << ", " << y << std::endl;
}

int main() {
    func(42); // 编译器无法确定调用哪个函数
    return 0;
}
```
在这个例子中，调用func(42)会导致编译错误，因为编译器无法确定是调用第一个函数还是第二个函数。

返回类型不同：仅返回类型不同的函数不能构成重载。例如：
```cpp
int func(int x) {
    return x;
}

double func(int x) { // 错误：仅返回类型不同
    return x;
}
```
这段代码会导致编译错误，因为编译器无法根据返回类型区分这两个函数。

总结
函数重载是C++中的一项强大特性，允许定义多个具有相同名称但参数列表不同的函数。通过合理使用函数重载，可以提高代码的可读性和可维护性，使代码更加简洁和易于理解。

## 运算符重载(没搞懂)
运算符重载（Operator Overloading）是C++中的一项特性，允许程序员重新定义或重载大部分内置运算符的行为。通过运算符重载，可以使得用户定义的类型（如类和结构体）使用起来更加直观和方便，就像内置类型一样。

运算符重载的规则
运算符符号不变：重载的运算符符号保持不变，例如+、-、*、/等。
不能创建新的运算符：只能重载现有的运算符，不能创建新的运算符。
不能改变运算符的优先级和结合性：重载运算符不会改变其原有的优先级和结合性。
至少有一个操作数是用户定义的类型：重载的运算符至少有一个操作数是用户定义的类型（类或结构体）。
不能重载的运算符：某些运算符不能重载，例如::、.*、.和?:。
运算符重载的语法
运算符重载可以通过成员函数或友元函数来实现。成员函数形式的语法如下
```cpp
返回类型 类名::operator运算符(参数列表) {
    // 函数体
}
```
友元函数形式的语法如下：
```cpp
friend 返回类型 operator运算符(参数列表) {
    // 函数体
}
```
示例
以下是一个简单的示例，展示了如何重载加法运算符+：
```cpp
#include <iostream>

class Complex {
public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // 重载加法运算符
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // 友元函数重载输出运算符
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real << ", " << c.imag << ")";
        return os;
    }

private:
    double real;
    double imag;
};

int main() {
    Complex c1(3.0, 4.0);
    Complex c2(1.0, 2.0);
    Complex c3 = c1 + c2; // 使用重载的加法运算符

    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;
    std::cout << "c3: " << c3 << std::endl;

    return 0;
}
```
在这个示例中，我们定义了一个表示复数的类Complex，并重载了加法运算符+。通过重载，我们可以直接使用+运算符来对两个Complex对象进行加法运算。此外，我们还重载了输出运算符<<，以便可以直接输出Complex对象的内容。

注意事项
合理使用运算符重载：运算符重载应该符合运算符的常规语义，避免让代码变得难以理解和维护。
避免滥用运算符重载：不要为了重载而重载，只有在确实能够提高代码可读性和易用性时才使用运算符重载。
成员函数与友元函数的选择：通常，对于需要访问私有成员的运算符，使用友元函数；对于只需要访问公有成员的运算符，使用成员函数。
总结
运算符重载是C++中的一项强大特性，允许程序员重新定义大部分内置运算符的行为。通过合理使用运算符重载，可以使自定义类型的操作更加直观和方便，提高代码的可读性和可维护性。

## 作用域
在C++中，作用域（Scope）是指程序中变量、函数、类等实体可以被访问的范围。作用域决定了变量和函数在程序中的可见性和生命周期。C++中有几种不同类型的作用域，包括块作用域、函数作用域、文件作用域和类作用域。

### 块作用域（Block Scope）
块作用域是指在代码块（由一对花括号{}包围的区域）内定义的变量，其作用域仅限于该代码块内部。块作用域的变量在进入代码块时创建，在离开代码块时销毁。

示例：
```cpp
#include <iostream>

int main() {
    int x = 10; // x 具有块作用域
    if (x > 5) {
        int y = 20; // y 具有块作用域
        std::cout << "x: " << x << ", y: " << y << std::endl;
    }
    // y 在这里不可见
    std::cout << "x: " << x << std::endl;
    return 0;
}
```
### 函数作用域（Function Scope）
函数作用域是指在函数内部定义的变量，其作用域仅限于该函数内部。函数作用域的变量在函数调用时创建，在函数返回时销毁。

示例：
```cpp
#include <iostream>

void myFunction() {
    int z = 30; // z 具有函数作用域
    std::cout << "z: " << z << std::endl;
}

int main() {
    myFunction();
    // z 在这里不可见
    return 0;
}
```
### 文件作用域（File Scope）
文件作用域是指在所有函数之外定义的变量或函数，其作用域从定义点开始，一直到文件的末尾。文件作用域的实体通常具有外部链接性（external linkage），可以被其他文件通过extern关键字访问。

示例：
```cpp
#include <iostream>

int globalVar = 40; // globalVar 具有文件作用域

void printGlobalVar() {
    std::cout << "globalVar: " << globalVar << std::endl;
}

int main() {
    printGlobalVar();
    return 0;
}
```
类作用域（Class Scope）
类作用域是指在类内部定义的成员变量和成员函数，其作用域仅限于该类内部。类作用域的成员可以通过对象或类名访问。

示例：
```cpp
#include <iostream>

class MyClass {
public:
    int memberVar; // memberVar 具有类作用域

    void setMemberVar(int value) {
        memberVar = value;
    }

    void printMemberVar() {
        std::cout << "memberVar: " << memberVar << std::endl;
    }
};

int main() {
    MyClass obj;
    obj.setMemberVar(50);
    obj.printMemberVar();
    return 0;
}
```
### 命名空间作用域（Namespace Scope）
命名空间作用域是指在命名空间内部定义的实体，其作用域仅限于该命名空间内部。命名空间作用域的实体可以通过命名空间名访问。

示例：
```cpp
#include <iostream>

namespace MyNamespace {
    int namespaceVar = 60; // namespaceVar 具有命名空间作用域

    void printNamespaceVar() {
        std::cout << "namespaceVar: " << namespaceVar << std::endl;
    }
}

int main() {
    MyNamespace::printNamespaceVar();
    return 0;
}
```
总结
作用域是C++中非常重要的概念，决定了变量和函数在程序中的可见性和生命周期。理解不同类型的作用域有助于编写更清晰、更易于维护的代码。常见的C++作用域包括块作用域、函数作用域、文件作用域、类作用域和命名空间作用域。

## 成员函数
在C++中，成员函数（Member Function）是指定义在类内部的函数。成员函数可以访问和操作类的成员变量，以及其他成员函数。成员函数是类的一部分，用于实现类的行为和功能。

成员函数的定义和声明
成员函数可以在类内部直接定义，也可以在类内部声明，然后在类外部定义。

特殊成员函数
C++中有一些特殊的成员函数，例如构造函数、析构函数、拷贝构造函数和赋值运算符重载函数。这些特殊成员函数在对象的创建、销毁和复制过程中起着重要作用。
构造函数在对象创建时自动调用，用于初始化对象的成员变量。

在C++中，成员函数指针与普通函数指针有所不同。成员函数指针不仅包含函数的地址，还包含一个隐含的指向对象的指针（即this指针）。因此，当我们将成员函数作为回调函数传递时，需要显式地传递对象指针（即this指针），以便在调用时能够正确地绑定到特定的对象实例。
```cpp
class PathSubscriber
{
public:
    PathSubscriber(const std::string &topic)
    {
        // 创建一个订阅者，订阅路径话题
        path_sub_ = nh_.subscribe(topic, 1000, &PathSubscriber::pathCallback, this);
    }
  private:  
      void pathCallback(const nav_msgs::Path::ConstPtr &path)
    {
        ROS_INFO("Received a path with %zu poses", path->poses.size());
        if (path->poses.size() > 1)
        {
            double length = calculatePathLength(*path);
            ROS_INFO("Path length: %f meters", length);
        }
        else
        {
            ROS_INFO("Path is too short to calculate length");
        }
    }  
```
## 友元函数和友元类
在C++中，友元（Friend）机制允许特定的函数或类访问另一个类的私有和保护成员。友元机制主要用于提高代码的灵活性和效率，但需要谨慎使用，以避免破坏封装原则。

友元函数（Friend Function）
友元函数是一个非成员函数，但它可以访问类的私有和保护成员。通过在类定义中使用friend关键字声明友元函数。

示例代码
```cpp
#include <iostream>

class MyClass {
private:
    int privateVar;

public:
    MyClass(int val) : privateVar(val) {}

    // 声明友元函数
    friend void display(const MyClass &obj);
};

// 友元函数的定义
void display(const MyClass &obj) {
    std::cout << "Private variable value: " << obj.privateVar << std::endl;
}

int main() {
    MyClass obj(10);
    display(obj);  // 调用友元函数
    return 0;
}
```
解释
友元声明：在MyClass类中，friend void display(const MyClass &obj);声明了display函数为友元函数。
友元函数定义：display函数是一个非成员函数，但它可以直接访问MyClass类的私有成员privateVar。
调用友元函数：在main函数中，通过调用display函数来访问MyClass对象的私有成员。
**友元类（Friend Class）**
友元类是一个类，它的所有成员函数都可以访问另一个类的私有和保护成员。通过在类定义中使用friend关键字声明友元类。

示例代码
```cpp
#include <iostream>

class MyClass {
private:
    int privateVar;

public:
    MyClass(int val) : privateVar(val) {}

    // 声明友元类
    friend class FriendClass;
};

class FriendClass {
public:
    void display(const MyClass &obj) {
        std::cout << "Private variable value: " << obj.privateVar << std::endl;
    }
};

int main() {
    MyClass obj(10);
    FriendClass friendObj;
    friendObj.display(obj);  // 调用友元类的成员函数
    return 0;
}

```
解释
友元类声明：在MyClass类中，friend class FriendClass;声明了FriendClass为友元类。
友元类成员函数：FriendClass的成员函数display可以直接访问MyClass类的私有成员privateVar。
调用友元类成员函数：在main函数中，通过FriendClass对象调用display函数来访问MyClass对象的私有成员。
注意事项
破坏封装：友元机制会破坏类的封装性，因此应谨慎使用。
单向关系：友元关系是单向的，即如果类A是类B的友元，并不意味着类B是类A的友元。
不可继承：友元关系不能继承，即如果类A是类B的友元，类A的派生类不会自动成为类B的友元。
总结
友元函数和友元类提供了一种灵活的机制，允许特定的函数或类访问另一个类的私有和保护成员。虽然这增加了代码的灵活性，但也可能破坏封装原则，因此在使用时应谨慎考虑。
## 引用
在C++中，引用（Reference）是一种特殊的变量类型，它提供了一种简便的方式来访问另一个变量的值。引用可以看作是某个变量的别名，对引用的操作实际上就是对原变量的操作。引用的主要用途包括函数参数传递和函数返回值。

引用的基本语法
引用的定义方式如下：

```cpp
数据类型 &引用名 = 变量名;
```
例如：
```cpp
int a = 10;
int &ref = a;  // ref是a的引用
```
引用的特点
初始化：引用必须在声明时进行初始化，且初始化后不能改变引用的对象。
别名：引用是目标变量的别名，对引用的操作就是对目标变量的操作。
不存在空引用：引用必须绑定到一个有效的对象上，不能像指针那样指向空（NULL）。
引用的使用场景
1. 函数参数传递
通过引用传递参数，可以避免复制大型对象，提高效率，并且可以在函数内部修改实参的值。
```cpp
//表示val是一个引用，它将引用传递给它的变量.在main函数中调用modifyValue时，传递了变量a。
//此时，val成为a的引用，对val的任何修改都会直接反映在a上。
void modifyValue(int &val) {
    val = 20;
}

int main() {
    int a = 10;
    modifyValue(a);
    //在modifyValue函数中，val被赋值为20，这实际上就是将a的值修改为20。最终，main函数中输出a的值时，结果是20。
    std::cout << a << std::endl;  // 输出20
    return 0;
}
```
2. 函数返回值
通过返回引用，可以实现对函数外部变量的修改.
```cpp
int globalVar = 10;
//getGlobalVar函数返回的是全局变量globalVar的引用
int& getGlobalVar() {
    return globalVar;
}

int main() {
	//对引用进行赋值
    getGlobalVar() = 20;
    std::cout << globalVar << std::endl;  // 输出20
    return 0;
}
```
注意事项
避免返回局部变量的引用：局部变量在函数返回后会被销毁，返回其引用会导致未定义行为。
常量引用：使用const修饰引用，可以避免在函数内部修改引用的值，同时可以绑定到临时对象或常量。
```cpp
void printValue(const int &val) {
    std::cout << val << std::endl;
}

int main() {
    int a = 10;
    printValue(a);  // 输出10
    return 0;
}
```
引用是C++中非常强大且灵活的特性，合理使用可以提高代码的效率和可读性。

## 封装  (不大理解)
在C++中，封装（Encapsulation）是面向对象编程（OOP）的核心概念之一。封装通过将数据（成员变量）和操作数据的方法（成员函数）绑定在一起，并隐藏对象的内部实现细节，从而提高代码的可维护性、安全性和可扩展性。

封装的基本概念
数据隐藏：将类的实现细节隐藏起来，只暴露必要的接口给外部使用。
访问控制：通过访问修饰符（如public、private、protected）来控制成员的访问权限。
访问修饰符
public：公有成员，可以被类的外部访问。
private：私有成员，只能被类的成员函数访问，不能被类的外部访问。
protected：受保护成员，只能被类的成员函数和派生类的成员函数访问，不能被类的外部访问。
封装的实现
示例代码
```cpp
#include <iostream>

class MyClass {
private:
    int privateVar;  // 私有成员变量

public:
    // 构造函数
    MyClass(int val) : privateVar(val) {}

    // 公有成员函数
    void setValue(int val) {
        privateVar = val;
    }

    int getValue() const {
        return privateVar;
    }
};

int main() {
    MyClass obj(10);  // 创建对象并初始化

    std::cout << "Initial value: " << obj.getValue() << std::endl;

    obj.setValue(20);  // 修改私有成员变量的值

    std::cout << "Modified value: " << obj.getValue() << std::endl;

    return 0;
}
```
解释
私有成员变量：privateVar是私有成员变量，只能在类的内部访问。
公有成员函数：setValue和getValue是公有成员函数，提供对私有成员变量的访问和修改接口。
构造函数：MyClass(int val)是构造函数，用于初始化对象。
main函数：在main函数中，通过公有成员函数来访问和修改私有成员变量的值。
封装的好处
数据保护：防止外部直接访问和修改类的内部数据，确保数据的完整性和一致性。
代码可维护性：隐藏实现细节，使得类的内部结构可以自由修改，而不影响外部代码。
代码安全性：通过接口控制访问权限，减少错误和安全漏洞。
代码可扩展性：方便添加新的功能和修改现有功能，而不影响类的使用者。
总结
封装是C++中实现数据隐藏和访问控制的重要手段，通过合理使用访问修饰符和成员函数，可以提高代码的模块化、可维护性和安全性。
## 继承与派生
在C++中，继承（Inheritance）是面向对象编程（OOP）的核心概念之一。继承允许一个类（派生类）从另一个类（基类）继承属性和方法，从而实现代码的重用和扩展。通过继承，派生类可以获得基类的所有成员（成员变量和成员函数），并且可以添加新的成员或重写基类的成员。

继承的基本概念
1. 基类（Base Class）：被继承的类，也称为父类或超类。
2. 派生类（Derived Class）：继承自基类的类，也称为子类。
3. 继承方式：C++支持多种继承方式，包括公有继承（public）、保护继承（protected）和私有继承（private）。
继承的语法
```cpp
class BaseClass {
    // 基类的成员变量和成员函数
};

class DerivedClass : 继承方式 BaseClass {
    // 派生类的成员变量和成员函数
};

```
继承方式
公有继承（public）：基类的公有成员在派生类中仍然是公有的，保护成员在派生类中仍然是保护的，私有成员在派生类中不可访问。
保护继承（protected）：基类的公有成员和保护成员在派生类中都变成保护的，私有成员在派生类中不可访问。
私有继承（private）：基类的公有成员和保护成员在派生类中都变成私有的，私有成员在派生类中不可访问。
示例代码
公有继承
```cpp
#include <iostream>

class Animal {
public:
    void eat() {
        std::cout << "Animal is eating." << std::endl;
    }
};

class Dog : public Animal {
public:
    void bark() {
        std::cout << "Dog is barking." << std::endl;
    }
};

int main() {
    Dog myDog;
    myDog.eat();  // 调用基类的成员函数
    myDog.bark(); // 调用派生类的成员函数
    return 0;
}
```
保护继承
```cpp
#include <iostream>

class Animal {
protected:
    void eat() {
        std::cout << "Animal is eating." << std::endl;
    }
};

class Dog : protected Animal {
public:
    void bark() {
        std::cout << "Dog is barking." << std::endl;
        eat();  // 在派生类中可以访问保护成员
    }
};

int main() {
    Dog myDog;
    // myDog.eat();  // 错误：eat()在Dog中是保护成员，不能在main中访问
    myDog.bark(); // 调用派生类的成员函数
    return 0;
}
```
私有继承
```cpp
#include <iostream>

class Animal {
public:
    void eat() {
        std::cout << "Animal is eating." << std::endl;
    }
};

class Dog : private Animal {
public:
    void bark() {
        std::cout << "Dog is barking." << std::endl;
        eat();  // 在派生类中可以访问私有成员
    }
};

int main() {
    Dog myDog;
    // myDog.eat();  // 错误：eat()在Dog中是私有成员，不能在main中访问
    myDog.bark(); // 调用派生类的成员函数
    return 0;
}
```
多重继承
C++还支持多重继承，即一个派生类可以继承多个基类。多重继承的语法如下：
```cpp
class BaseClass1 {
    // 基类1的成员变量和成员函数
};

class BaseClass2 {
    // 基类2的成员变量和成员函数
};

class DerivedClass : 继承方式 BaseClass1, 继承方式 BaseClass2 {
    // 派生类的成员变量和成员函数
};
```
示例代码
```cpp
#include <iostream>

class Animal {
public:
    void eat() {
        std::cout << "Animal is eating." << std::endl;
    }
};

class Mammal {
public:
    void breathe() {
        std::cout << "Mammal is breathing." << std::endl;
    }
};

class Dog : public Animal, public Mammal {
public:
    void bark() {
        std::cout << "Dog is barking." << std::endl;
    }
};

int main() {
    Dog myDog;
    myDog.eat();    // 调用Animal类的成员函数
    myDog.breathe();// 调用Mammal类的成员函数
    myDog.bark();   // 调用Dog类的成员函数
    return 0;
}
```
总结
继承是C++中实现代码重用和扩展的重要机制。通过继承，派生类可以获得基类的成员，并且可以添加新的成员或重写基类的成员。继承方式包括公有继承、保护继承和私有继承，每种方式有不同的访问控制特性。多重继承允许一个派生类继承多个基类，但需要小心处理潜在的复杂性和冲突。
## 多态


## 抽象
## 私有成员与保护成员的区别
私有成员只能在类的内部访问，不能被类的外部代码或派生类访问。
保护成员可以在类的内部和派生类中访问，但不能被类的外部代码访问。通常用于允许派生类访问基类的某些成员。
保护成员实现了一种平衡


## vector中的类，访问某个类的成员变量
创建一个vectot后push_back
如果std::vector ab[5]。这其实是五个vector。不是vector里面有五个

## emplace_back和push_back
emplace_back会导致后期使用类成员变量时产生“疑似覆盖的操作”，导致只有最后一个对象的成员变量有数值，而之前对象的均为0;

# Lambda函数（未懂）

# 回调函数传入其他参数

通过设置初始化列表来实现
```cpp
lass PathSubscriber
{
public:
    PathSubscriber(const std::string &topic,const int robot_num):robot_num(robot_num)
    {

        path_sub_ = nh_.subscribe(topic, 1000, &PathSubscriber::pathCallback, this);

    }

    double length=0;
    int robot_num;
    

private:
    ros::NodeHandle nh_;
    ros::Subscriber path_sub_;

void pathCallback(const nav_msgs::Path::ConstPtr &path)
    {
        path_get=1;
        ROS_INFO("Received a path with %zu poses", path->poses.size());
        if (path->poses.size() > 1)
        {
            this->length = calculatePathLength(*path);
            ROS_INFO("car %d Path length: %f meters", this->robot_num,this->length);

        }
        else
        {
            ROS_INFO("Path is too short to calculate length");
        }
    }

int main()
{
	std::vector<PathSubscriber> path_sub;
    PathSubscriber path_sub0(robot_namespaces[0] + "/move_base_node/GlobalPlanner/plan",1);
}
```

## 数组作为函数中的形参的写法