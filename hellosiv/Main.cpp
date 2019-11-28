# include <Siv3D.hpp>
#include "Field.h"
#include "Car.h"
#include "Controller.h"
#include "KeyController.h"
#include "HandAiController.h"

void Main()
{
    Graphics::SetTargetFrameRateHz(60);


    // 2D カメラ
    Camera2D camera(Vec2(0, -8), 10.0, Camera2DParameters::MouseOnly());

    // 物理演算の精度
    constexpr int32 velocityIterations = 12;
    constexpr int32 positionIterations = 4;

    // 物理演算用のワールド
    P2World world(0);

    const MultiPolygon carPolygon = Emoji::CreateImage(U"⬇").alphaToPolygonsCentered().simplified(0.8).scale(0.04);
    Car car{ world.createPolygons({0, 0}, carPolygon, P2Material(0.1, 0.0, 1.0)) };
    Texture carTex = Texture(Emoji(U"⬇"));


    Field field{ {0.0,0.0}, {100.0, 0.0}, {100.0, 100.0}, {-100.0, 100.0}, {-100.0, 0.0} };
    field.generatePolygonFromPath();

    car.setPos(field.getStartPos());
    car.setAngle(field.getStartAngle());

    std::unique_ptr<Controller> ctrl{ new HandAiController() };

    while (System::Update())
    {
        ClearPrint();
        // 2D カメラを更新
        camera.update();
        {
            // 2D カメラの設定から Transformer2D を作成・適用
            const auto t = camera.createTransformer();

            ctrl->apply(car, field);
            car.apply();

            // 物理演算のワールドを更新
            world.update(Scene::DeltaTime(), velocityIterations, positionIterations);


            field.polygon().draw(Palette::Gray);

            carTex.scaled(0.04).rotated(car.body().getAngle()).drawAt(car.body().getPos());
            // car.body().draw();

            // {
            //     const auto t = Transformer2D(car.transformer());
            //     for (int i = -1; i <= 1; ++i) {
            //         for (int j = -1; j <= 1; ++j) {
            //             Circle(i*5, j*5, 0.3).draw(car.getSensor(field, { i*2, j*2 }) ? Palette::White : Palette::Black);
            //         }
            //     }
            // }
        }

        // 2D カメラ操作の UI を表示
        camera.draw(Palette::Orange);
    }
}
