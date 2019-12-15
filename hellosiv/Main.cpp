# include <Siv3D.hpp>
#include <fstream>
#include "Interfaces.h"
#include "PathField.h"
#include "Siv3DCar.h"
#include "KeyController.h"
#include "HandAiController.h"

void Main() {

    Graphics::SetTargetFrameRateHz(60);


    P2World world(0);

    // PathField field{ {0.0,0.0}, {100.0, 0.0}, {100.0, 100.0}, {-100.0, 100.0}, {-100.0, 0.0} };
    std::ifstream courseFile("./course.txt");
    PathField field(courseFile);
    courseFile.close();


    Car car(world);
    car.setPos(field.getStartPos());
    car.setAngle(field.getStartAngle());
    car.setController(std::make_unique<HandAiController>());

    Camera2D camera(field.getStartPos(), 10.0, Camera2DParameters::MouseOnly());


    Array<const IDrawable*> drawables;
    drawables.push_back(&field);
    drawables.push_back(&car);
    {
        auto p = dynamic_cast<const IDrawable*>(&car.getController());
        if (p) drawables.push_back(p);
    }


    while (System::Update()) {

        ClearPrint();
        camera.update();
        {
            const auto t = camera.createTransformer();

            
            car.apply(field);

            world.update(Scene::DeltaTime(), 12, 4);

            for (const IDrawable* d : drawables)
                d->draw();

        }

        // 2D カメラ操作の UI を表示
        camera.draw(Palette::Orange);
    }
}
