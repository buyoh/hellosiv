# include <Siv3D.hpp>
#include "Field.h"
#include "Car.h"

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
    Car carBody{ world.createPolygons({0, 0}, carPolygon, P2Material(0.1, 0.0, 1.0)) };
    Texture carTex = Texture(Emoji(U"⬇"));


    Field field{ {0.0,0.0}, {100.0, 0.0}, {100.0, 100.0}, {-100.0, 100.0}, {-100.0, 0.0} };
    field.generatePolygonFromPath();

    while (System::Update())
    {
        ClearPrint();
        // 2D カメラを更新
        camera.update();
        {
            // 2D カメラの設定から Transformer2D を作成・適用
            const auto t = camera.createTransformer();


            {
                carBody.setAccsel(KeyUp.pressed() ? 1 : KeyDown.pressed() ? -1 : 0);
                carBody.setSteer(KeyLeft.pressed() ? -1 : KeyRight.pressed() ? 1 : 0);
            }
            carBody.apply();

            // 物理演算のワールドを更新
            world.update(Scene::DeltaTime(), velocityIterations, positionIterations);

            // carTex.scaled(0.04).rotated(carBody.getAngle()).drawAt(carBody.getPos());

            field.polygon().draw(Palette::Gray);

            carBody.body().draw();

            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    Print << carBody.getSensor(field, { i, j }) << U" ";
                }
            }
        }

        // 2D カメラ操作の UI を表示
        camera.draw(Palette::Orange);
    }
}
