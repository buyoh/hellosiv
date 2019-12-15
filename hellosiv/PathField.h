#pragma once
#include <Siv3D.hpp>
#include "Interfaces.h"

class PathField : public IFieldPresenter, public IDrawable {
    using Path = Array<Vec2>;

    bool cyclic_ = true;
    double width_ = 20;
    Path path_;
    Polygon polygon_;

    //

    static Polygon createRect(Vec2 v1, Vec2 v2, double width) {
        auto n12 = (v2 - v1).normalize();
        auto l12 = n12.yx(); l12.x = -l12.x;
        auto w2 = width / 2;
        return Polygon(Array<Vec2>{ v1 + w2 * l12, v1 - w2 * l12, v2 - w2 * l12, v2 + w2 * l12 }, {});
    }

    void inputPath(std::istream& is) {
        int nVertex;
        is >> nVertex;
        assert(nVertex > 2);
        for (int i = 0; i < nVertex; ++i) {
            double x, y;
            is >> x >> y;
            path_.push_back(Vec2{ x, y });
        }
    }

    void generatePolygonFromPath() {
        auto lastv = path_.back();
        bool ignoreFirst = !cyclic_;
        polygon_ = Polygon();
        for (auto v : path_) {
            if (ignoreFirst) {
                ignoreFirst = false;
                lastv = v;
                continue;
            }
            polygon_.append(createRect(lastv, v, width_));
            polygon_.append(Circle(v, width_ / 2).asPolygon());
            lastv = v;
        }
    }

public:
    // inline const Polygon& polygon() const noexcept { return polygon_; }

    inline Vec2 getStartPos() const override {
        return path_.front();
    }
    inline double getStartAngle() const override {
        return -Math::HalfPi; // path_[0].getAngle(path_[1]);
    }
    inline bool isOnRoad(const Vec2& vec) const override {
        return polygon_.contains(vec);
    }

    void draw() const override {
        polygon_.draw(Palette::Gray);
    }



    inline PathField(std::initializer_list<Vec2>&& _path) :path_(_path) {
        generatePolygonFromPath();
    }
    inline PathField(std::istream& is) {
        inputPath(is);
        generatePolygonFromPath();
    }
};