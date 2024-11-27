使用自定义类型时需要特化hash模版，还需要重载==运算符

```
class MyClass
{
  public:
    int x;
    int y;

    bool operator==(const MyClass &a) const
    {
        return x == a.x && y == a.y;
    }
};

template <>
class std::hash<MyClass>
{
  public:
    size_t operator()(const MyClass &a) const
    {
        return a.x ^ a.y << 1;
    }
};
```
