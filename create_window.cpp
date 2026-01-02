#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(){

    //Initiating the GLFW window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create the window {glfwCreateWindow(Width, Height, Window Name, Can ignore, Can ignore)}
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLTest", NULL, NULL);

    //Check if the window failed to initiate / create
    if(window == NULL){

        std::cout<<"Failed to create GLFW window";
        glfwTerminate();
        return -1;

    }

    glfwMakeContextCurrent(window);

    //Check if GLAD is initalized
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){

        std::cout<<"Failed to initlize GLAD";
        return -1;

    }

    //Tells OpenGL the size of the rendering window
    //glViewport(location of the lower left cornder, location of the lower left corder, width, height)
    glViewport(0, 0, 800, 600);

    //Check if the window should close or not
    while(!glfwWindowShouldClose(window)){

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

glfwTerminate();
return 0;
}