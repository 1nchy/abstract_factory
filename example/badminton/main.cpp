#include <iostream>

#include "badminton.hpp"
#include "abstract_factory.hpp"

using std::cout;
using std::cin;
using std::endl;

int main() {
    auto* const _bat_merchant = icy::factory<bat>::instance();
    auto* const _ball_merchant = icy::factory<ball>::instance();
    _bat_merchant->enroll<yonex_bat>("YONEX");
    _bat_merchant->enroll<lining_bat>("LINING");
    _bat_merchant->enroll<victor_bat>("VICTOR");
    _bat_merchant->enroll<dhs_bat>("DHS");
    _ball_merchant->enroll<yonex_ball>("YONEX");
    _ball_merchant->enroll<lining_ball>("LINING");
    _ball_merchant->enroll<victor_ball>("VICTOR");
    _ball_merchant->enroll<ysl_ball>("YSL");
    _ball_merchant->enroll<jianyu_ball>("JIANYU");

    bat* _x = nullptr; ball* _y = nullptr;

    _x = _bat_merchant->get("LINING");
    cout << _x->label() << endl;
    cout << _x->weight() << endl;
    delete _x;

    // _x = _bat_merchant->get("VICTOR", 5);
    _x = _bat_merchant->get("VICTOR");
    cout << _x->label() << endl;
    cout << _x->weight() << endl;
    delete _x;

    _y = _ball_merchant->get("YSL");
    cout << _y->label() << endl;
    delete _y;

    return 0;
}