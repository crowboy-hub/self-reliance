class Box
{
public:
    // Default constructor
    Box() {}

    // Initialize a Box with equal dimensions (i.e. a cube)
    // 使用 explicit 关键字修饰构造函数，表示该构造函数不能用于隐式类型转换。
    // 也就是说，编译器不会自动将一个 int 类型的值隐式转换为 Box 类型的对象。
    // 这是一个带有单个 int 参数的构造函数
    // 成员初始化列表用于在构造函数体执行之前初始化类的成员变量。
    explicit Box(int i) : m_width(i), m_length(i), m_height(i) // member init list
    {
    }

    // Initialize a Box with custom dimensions
    Box(int width, int length, int height)
        : m_width(width), m_length(length), m_height(height)
    {
    }

    int Volume() { return m_width * m_length * m_height; }

private:
    // Will have value of 0 when default constructor is called.
    // If we didn't zero-init here, default constructor would
    // leave them uninitialized with garbage values.
    int m_width{0};
    int m_length{0};
    int m_height{0};
};

int main()
{
    Box b; // Calls Box()

    // Using uniform initialization (preferred):
    Box b2{5};        // Calls Box(int)
    Box b3{5, 8, 12}; // Calls Box(int, int, int)

    // Using function-style notation:
    // 初始化的时候使用的是（）而不是{}，但{}更规范
    Box b4(2, 4, 6); // Calls Box(int, int, int)
}
