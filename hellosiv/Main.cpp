# include <Siv3D.hpp>
#include "Interfaces.h"
#include "Field.h"
#include "Car.h"
#include "KeyController.h"
#include "HandAiController.h"

void Main()
{
    Graphics::SetTargetFrameRateHz(60);

    // 2D カメラ
    Camera2D camera(Vec2(0, -8), 10.0, Camera2DParameters::MouseOnly());

    // 物理演算用のワールド
    P2World world(0);


    Car car(world);


    Field field{ {0.0,0.0}, {100.0, 0.0}, {100.0, 100.0}, {-100.0, 100.0}, {-100.0, 0.0} };
    field.generatePolygonFromPath();

    car.setPos(field.getStartPos());
    car.setAngle(field.getStartAngle());

    car.setController(std::make_unique<KeyController>());


    Array<const IDrawable*> drawables;
    drawables.push_back(&field);
    drawables.push_back(&car);
    {
        auto p = dynamic_cast<const IDrawable*>(&car.getController());
        if (p) drawables.push_back(p);
    }

    while (System::Update())
    {
        ClearPrint();
        // 2D カメラを更新
        camera.update();
        {
            // 2D カメラの設定から Transformer2D を作成・適用
            const auto t = camera.createTransformer();

            car.apply(field);

            // 物理演算のワールドを更新
            world.update(Scene::DeltaTime(), 12, 4);

            for (const IDrawable* d : drawables)
                d->draw();

        }

        // 2D カメラ操作の UI を表示
        camera.draw(Palette::Orange);
    }
}
