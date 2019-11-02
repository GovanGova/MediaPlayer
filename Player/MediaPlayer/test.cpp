

#include <test.h>
#include <ScreenManager.h>
#include <Engine.h>
#include <Script.h>
#include <Element.h>
#include <Shape.h>
#include <PointSprite.h>
#include <Player.h>
#include <Image.h>
#include <Text.h>
#include <ThreeDModel.h>
#include<Camera.h>

std::shared_ptr<screenManager> scm = nullptr;
std::shared_ptr<Player> player = nullptr;
std::shared_ptr<Script> script = nullptr;
std::shared_ptr<Engine> engine = nullptr;

GLuint width = 1920, height = 1080;
float eyex = 0, eyey = 0, eyez = 100, angleY=0;

void setup()
{

    scm = std::shared_ptr<screenManager>(new screenManager());

    scm->setRes(width, height);

    engine = std::shared_ptr<Engine>(new Engine(scm));

    player = std::shared_ptr<Player>(new Player());
    player->attachMediaEngine(engine);

    //Element *shape = new Shape(scm);

    // shape->setPosX(20);
    // shape->setPosY(20);
    // shape->setColor(0.0,0.0,0.5,0.5);
    script = std::shared_ptr<Script>(new Script(scm));
    // script->addAsset(std::shared_ptr<Element>(shape));

    Element *shape1 = new Shape(scm);

    shape1->setPosX(-800);
    shape1->setPosY(-500);
    //shape1->setPosZ()
    shape1->setColor(1.0, 0.0, 0.0, 0.5);
    script->addAsset(std::shared_ptr<Element>(shape1));

    // Point sprite
    PointSprite *point = new PointSprite(scm, 50);

    point->setPosX(0);
    point->setPosY(0);
    point->setPosZ(0);
    point->setWidth((float)400);
    point->setBreadth(0);
    point->setVelocityRanges(-.5, 0.5, -.5, 0.5, 0.0, 0.05);
    //point->setAcceleration(0, -0.1, 0);
    point->setHeight((float)400);
    //point->setColor(1.0, 1.0, 1.0, 0.9);
    point->setFilename("./assets/star.tga");

    engine->attachScript(script);

    //jpg
    Image *gova = new Image(scm);
    gova->setPosX(-800);
    //gova->setWidth(500);

    gova->showOriginal(true);
    gova->setColor(0, 0, 0, 0);
    gova->setFilename("./assets/sample.jpg");
    gova->setPosY(-300);
    gova->setPosZ(-1.0);
    script->addAsset(std::shared_ptr<Element>(gova));

    Image *imgae = new Image(scm);
    imgae->setFilename("./assets/star.tga");
    imgae->setColor(0,0,0,0);
    imgae->setPosX(0);
    imgae->setPosY(0);
    imgae->setHeight(150);
    imgae->setWidth(150);
    imgae->setPosZ(10);

    Image *image = new Image(scm);
    image->setFilename("./assets/star.tga");
    image->setPosX(700);
    image->setColor(0, 0, 0, 0);
    image->setPosY(0);
    image->setHeight(60);
    image->setVelocity(0, -1.5, 0);
    image->setWidth(60);
    image->setPosZ(10);
    image->setSunAndMass(0, 0.0, 10.0, 1700.0);
    script->addAsset(std::shared_ptr<Element>(image));
    script->addAsset(std::shared_ptr<Element>(imgae));
    script->addAsset(std::shared_ptr<Element>(point));

    Text *text = new Text(scm);
    text->setPosX(-400);
    text->setPosY(-400);
    text->setPosZ(10.0);
    text->setFontFilename("./assets/Roboto-Black.ttf");
    text->setFontSize(100);
    text->setText(std::string("Gova"));
    text->setColor(1, 0, 0, 1);
    script->addAsset(std::shared_ptr<Element>(text));

    for (int i = 0; i < 10; i++)
    {
        ThreeDModel *model = new ThreeDModel(scm);
        //model->setFilename(std::string("./assets/house/house_plant.obj"));
        model->setFilename(std::string("./assets/tree1_3ds/Tree1.3ds"));
        //model->setFilename(std::string("./assets/grass-block.3DS"));
        //model->setFilename(std::string("./assets/sunflower/SunFlower.obj"));
        model->setPosX(-100+(i*20));
        model->setPosY(0);
        model->setPosZ(50.0);
        model->setColor(0.0, 0.0, 0.0, 0.0);
        script->addAsset(std::shared_ptr<Element>(model));
    }
}

void RenderScene()
{
    player->render();
    glutSwapBuffers();
    glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    scm->setRes(w, h);
}
///////////////////////////////////////////////////
// Respond to arrow keys, move the viewpoint back
// and forth
void SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        eyez -= 5.0;
        scm->getCamera()->setEyePos(eyex, eyey, eyez);
        scm->setUpMatrices();
    }

    if (key == GLUT_KEY_DOWN)
    {
        eyez += 5.0;
        scm->getCamera()->setEyePos(eyex, eyey, eyez);
        scm->setUpMatrices();
    }

    if (key == GLUT_KEY_LEFT)
    {
        angleY += 0.5;
        scm->getCamera()->rotateCameraY(angleY);
        scm->setUpMatrices();
    }

    if (key == GLUT_KEY_RIGHT)
    {
        angleY -= 0.5;
        scm->getCamera()->rotateCameraY(angleY);
        scm->setUpMatrices();
    }

    // Refresh the Window
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    //glutInitContextVersion(3,3);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(width, height);
    glutCreateWindow("Triangle");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    if (!glewInit())
        std::cout << "hello";

    setup();
    //player->startRenderingThread();
    glutMainLoop();
    std::cout << "end";
}
