/**
 * @file main.cpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief main file for tests
 * @date 2022-08-29
 */

#include <GL/glew.h>
#include <GL/glut.h>
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    // init glut
    glutInit(&argc, argv);
    glutCreateWindow("dummy windows");
    // setup glew
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Cannot init glew library: " << glewGetErrorString(err) << std::endl;
        exit(1); // or handle the error in a nicer way
    }
    return RUN_ALL_TESTS();
}