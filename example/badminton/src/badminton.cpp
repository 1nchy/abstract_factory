#include "badminton.hpp"

auto yonex_bat::label() const -> const std::string {
    return "yonex";
}
auto yonex_bat::weight() const -> int {
    return _weight;
}
auto lining_bat::label() const -> const std::string {
    return "lining";
}
auto lining_bat::weight() const -> int {
    return _weight;
}
auto victor_bat::label() const -> const std::string {
    return "victor";
}
auto victor_bat::weight() const -> int {
    return _weight;
}
auto dhs_bat::label() const -> const std::string {
    return "dhs";
}
auto dhs_bat::weight() const -> int {
    return _weight;
}


auto yonex_ball::label() const -> const std::string {
    return "yonex";
}
auto lining_ball::label() const -> const std::string {
    return "lining";
}
auto victor_ball::label() const -> const std::string {
    return "victor";
}
auto ysl_ball::label() const -> const std::string {
    return "ysl";
}
auto jianyu_ball::label() const -> const std::string {
    return "jianyu";
}
