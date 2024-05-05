# DESIGN

抽象工厂模式把对象的创建与使用分离开来，它显然应该被设计为单例。
在此基础之上，我们希望能够使用字符串键，让工厂单例返回特定类型的实例。

因此我们设计的工厂模式的使用大致是这样的：

~~~cpp
auto* const _f = factory<base_item>::instance();
_f->enroll<item1>("1");
_f->enroll<item2>("2");
auto* _x = _f->get("1"); // item1 object
~~~

## 工厂定义

我们首先明确抽象工厂类的定义与 API：

抽象工厂应该是个模板类，创建单例的时候将物品基类作为形参传入。

> 我们将工厂创建的实例称为物品

抽象工厂应该至少包含以下方法：

||enroll|expel|get|contains|
|:-:|:-:|:-:|:-:|:-:|
|功能|类型注册|类型注销|实例获取|键查询|

因此，我们下面给出抽象工厂方法的声明（API）：

~~~cpp
template <typename _Bt> class factory {
private:
    factory() = default;
public:
    typedef _Bt base_type;
    static factory<_Bt>* instance();
    template <typename _Dt>
        requires std::is_base_of<base_type, _Dt>::value
        void enroll(const std::string&);
    void expel(const std::string&);
    bool contains(const std::string&) const;
    base_type* get(const std::string&) const;
};
~~~

`factory` 中需要用 `unordered_map` 类型的成员变量 `_enrollment` 维护键值对的实例创造形式，以字符串为键，以能创造实例的**生产者类**作为值。

## 生产者定义

生产者作为直接创建实例的类，需要对工厂类提供统一的实例创建接口。
我们容易想到，设计一个生产者基类声明统一接口，再由各生产者子类实际创建实例。

因此生产者声明如下：

~~~cpp
template <typename _Bt> struct virtual_producer {
protected:
    virtual_producer() = default;
public:
    virtual ~virtual_producer() = default;
    typedef _Bt base_type;
    virtual base_type* get() const = 0;
};
template <typename _Bt, typename _Dt> requires std::is_base_of<_Bt, _Dt>::value
struct producer : public virtual_producer<_Bt> {
    using typename virtual_producer<_Bt>::base_type;
    base_type* get() const override { return new _Dt(); }
};
~~~

工厂类的 `_enrollment` 成员将保存生产者基类的指针，并在创建实例时，调用其 `get` 接口。

~~~cpp
template <typename _Bt> class factory {
private:
    std::unordered_map<std::string, __details__::virtual_producer<base_type>*> _enrollment;
};
~~~