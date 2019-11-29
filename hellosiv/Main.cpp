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

    // 物理演算の精度
    constexpr int32 velocityIterations = 12;
    constexpr int32 positionIterations = 4;

    // 物理演算用のワールド
    P2World world(0);


    Car car(world);


    Field field{ {0.0,0.0}, {100.0, 0.0}, {100.0, 100.0}, {-100.0, 100.0}, {-100.0, 0.0} };
    field.generatePolygonFromPath();

    car.setPos(field.getStartPos());
    car.setAngle(field.getStartAngle());

    std::unique_ptr<IController> ctrl{ new HandAiController() };

    while (System::Update())
    {
        ClearPrint();
        // 2D カメラを更新
        camera.update();
        {
            // 2D カメラの設定から Transformer2D を作成・適用
            const auto t = camera.createTransformer();

            car.manipulate(ctrl->apply(car, field)); // TODO: carの中で。
            car.apply();

            // 物理演算のワールドを更新
            world.update(Scene::DeltaTime(), velocityIterations, positionIterations);


            field.draw();
            car.draw();
        }

        // 2D カメラ操作の UI を表示
        camera.draw(Palette::Orange);
    }
}
