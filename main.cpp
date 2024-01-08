#include <iostream>
#include "Wahadlo2Niezal.h"

using namespace std;




int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    if (Args(argc, argv) == GL_FALSE) {
        exit(1);
    }

    windW = 300;
    windH = 300;
    glutInitWindowPosition(0, 0);
    glutInitWindowSize( windW, windH);

    windType = (rgb) ? GLUT_RGB : GLUT_INDEX;
    windType |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
    glutInitDisplayMode(windType);

    if (glutCreateWindow("Wahadło") == GL_FALSE) {
        exit(1);
}

//InitMap();

    Init();

    glutReshapeFunc(Reshape);
    glutDisplayFunc(Draw);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}
