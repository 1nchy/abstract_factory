# USAGE

## 需求分析

在羽毛球领域，有许多厂家生产球拍与球。因此我们可以抽象出球拍 `bat` 和球 `ball` 作为物品的基类。而各厂家生产出来的球拍和球作为实际的物品，都将分别派生于这两个基类。

## 物品定义

下面是物品基类的定义：

~~~cpp
struct bat {
    virtual const std::string label() const = 0;
};
struct ball {
    virtual const std::string label() const = 0;
};
~~~

下面是 球 类实例的定义（这里仅给出一个例子）：

~~~cpp
struct yonex_ball : public ball {
    const std::string label() const override { return "yonex"; }
};
~~~

## 工厂使用

~~~cpp
auto* const _ball_merchant = icy::factory<ball>::instance(); // 获取工厂单例
_ball_merchant->enroll<yonex_ball>("YONEX"); // 类型注册
ball* _y = _ball_merchant->get("yonex");
cout << _y->label() << endl;
delete _y;
~~~