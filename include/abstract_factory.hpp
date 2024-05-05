#ifndef _ABSTRACT_FACTORY_HPP_
#define _ABSTRACT_FACTORY_HPP_

#include <type_traits>

#include <string>
#include <unordered_map>

namespace icy {

template <typename _Bt> class factory;

namespace __details__ {
template <typename _Bt> struct virtual_producer;
template <typename _Bt, typename _Dt> requires std::is_base_of<_Bt, _Dt>::value
struct producer;

template <typename _Bt> struct virtual_producer {
private:
    virtual_producer(const virtual_producer<_Bt>&) = delete;
    virtual_producer<_Bt>& operator=(const virtual_producer<_Bt>&) = delete;
protected:
    virtual_producer() = default;
public:
    virtual ~virtual_producer() = default;
    typedef _Bt base_type;
    virtual base_type* get() const = 0;
    // template <typename... _Args> base_type* get(_Args&&... _args) const { return nullptr; }
};
template <typename _Bt, typename _Dt> requires std::is_base_of<_Bt, _Dt>::value
struct producer : public virtual_producer<_Bt> {
    using typename virtual_producer<_Bt>::base_type;
    base_type* get() const override { return new _Dt(); }
    // template <typename... _Args> base_type* get(_Args&&... _args) const {
    //     return new _Dt(std::forward<_Args>(_args)...);
    // }
};
}

/**
 * @brief 抽象工厂类
 * @tparam _Bt 创造实例的基类
*/
template <typename _Bt> class factory {
private:
    factory() = default;
public:
    ~factory();
    typedef _Bt base_type;
    typedef factory<_Bt> self;
    static self* instance();
    template <typename _Dt>
        requires std::is_base_of<base_type, _Dt>::value
        void enroll(const std::string&);
    void expel(const std::string&);
    bool contains(const std::string&) const;
    base_type* get(const std::string&) const;
    // template <typename... _Args> base_type* get(const std::string&, _Args&&... _args) const;
private:
    std::unordered_map<std::string, __details__::virtual_producer<base_type>*> _enrollment;
};


template <typename _Bt>
factory<_Bt>::~factory() {
    for (const auto& _p : _enrollment) {
        delete _p.second;
    }
}
template <typename _Bt> auto
factory<_Bt>::instance() -> self* {
    static self _s;
    return &_s;
}
/**
 * @brief 注册实例类型
 * @tparam _Dt 实例类型（需继承自 @c _Bt ）
 * @param _s 类型的字符串键
*/
template <typename _Bt> template <typename _Dt>
requires std::is_base_of<typename factory<_Bt>::base_type, _Dt>::value auto
factory<_Bt>::enroll(const std::string& _s) -> void {
    auto* const _p = new __details__::producer<base_type, _Dt>();
    expel(_s);
    _enrollment.insert(std::make_pair(_s, _p));
}
/**
 * @brief 注销实例类型
 * @param _s 类型的字符串键
*/
template <typename _Bt> auto
factory<_Bt>::expel(const std::string& _s) -> void {
    if (!contains(_s)) return;
    delete _enrollment.at(_s);
    _enrollment.erase(_s);
}
/**
 * @brief 是否已用该字符串键注册类型
*/
template <typename _Bt> auto
factory<_Bt>::contains(const std::string& _s) const -> bool {
    return _enrollment.contains(_s);
}
/**
 * @brief 根据字符串键获取类型实例
 * @return 类型实例，若未注册则返回 @c nullptr
*/
template <typename _Bt> auto
factory<_Bt>::get(const std::string& _s) const -> base_type* {
    if (!contains(_s)) return nullptr;
    return _enrollment.at(_s)->get();
}
// template <typename _Bt> template <typename... _Args> auto
// factory<_Bt>::get(const std::string& _s, _Args&&... _args) const -> base_type* {
//     if (!contains(_s)) return nullptr;
//     return _enrollment.at(_s)->get(std::forward<_Args>(_args)...);
// }
}

#endif // _ABSTRACT_FACTORY_HPP_