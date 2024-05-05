#pragma once

#include <string>

struct bat;
struct ball;

struct bat {
    bat(int _w = 3) : _weight(_w) {}
    virtual const std::string label() const = 0;
    virtual int weight() const = 0;
    int _weight;
};
struct ball {
    virtual const std::string label() const = 0;
};

struct yonex_bat : public bat {
    yonex_bat(int _w = 3) : bat(_w) {}
    const std::string label() const override;
    int weight() const override;
};
struct lining_bat : public bat {
    lining_bat(int _w = 3) : bat(_w) {}
    const std::string label() const override;
    int weight() const override;
};
struct victor_bat : public bat {
    victor_bat(int _w = 3) : bat(_w) {}
    const std::string label() const override;
    int weight() const override;
};
struct dhs_bat : public bat {
    dhs_bat(int _w = 3) : bat(_w) {}
    const std::string label() const override;
    int weight() const override;
};


struct yonex_ball : public ball {
    const std::string label() const override;
};
struct lining_ball : public ball {
    const std::string label() const override;
};
struct victor_ball : public ball {
    const std::string label() const override;
};
struct ysl_ball : public ball {
    const std::string label() const override;
};
struct jianyu_ball : public ball {
    const std::string label() const override;
};