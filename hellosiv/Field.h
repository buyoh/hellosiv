#pragma once
#include <Siv3D.hpp>

class Field {
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

public:
    inline const Polygon& polygon() const noexcept { return polygon_; }

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

    inline Field() {}
    inline Field(std::initializer_list<Vec2>&& _path) :path_(_path) {}
};