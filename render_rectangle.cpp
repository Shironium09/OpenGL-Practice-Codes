#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";
    
void processInput(GLFWwindow*);
void framebuffer_size_callback(GLFWwindow*, int, int);

int main(){
    
    //Initiating the GLFW window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //Create the window {glfwCreateWindow(Width, Height, Window Name, Can ignore, Can ignore)}
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLTesting", NULL, NULL);

    //Set the current window as the window context (the size, name, etc)
    glfwMakeContextCurrent(window);
 
    //Set the callback to resize the window ecerytime we resize it
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Check if GLAD is initalized
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        
        std::cout<<"Failed to initlize GLAD";
        return -1;
        
    }

    //Check if the window failed to initiate / create
    if(window == NULL){

        std::cout<<"Failed to create GLFW window";
        glfwTerminate();
        return -1;

    }
    
    //Vertices of the rectangle
    /*
    float vertices[] = {

        x, y, z,
        x, y, z,
        x, y, z,
        x, y, z,
    
    }
    */
    float vertices[] = {

        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f

    };

    //"Map" the 2 sets of vertices to the vertices
    unsigned int indices[] = {

        0, 1, 3,
        1, 2, 3

    };

    //The VAO (Vertex Array Object)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    //The VBO (Vertex Buffer Objects)
    //VBO allows it to store large number of vertices in the GPU's memory
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    //Bind the vertex araray to the VAO
    glBindVertexArray(VAO);

    //Bind the newlcy created buffer to GL_ARRAY_BUFFER
    //glBindBuffer(target, buffer)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
 
    //Copies the defined verterx data into the buffer's memory
    //glBufferData(mode, size, data, usage)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Element Buffer Objects
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    //Binds the EBO to the buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Create the shader object
    unsigned int vertexShader;
    //glCreateShader(shader Type)
    vertexShader  = glCreateShader(GL_VERTEX_SHADER);

    //Attach the sahder source code to the shader object and compile it
    //glShaderSource(shader, count, string, length)
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Checking if the compilation was successful
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){

        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED/n"<<infoLog<<std::endl;

    }

    //The fragment shader for rendering a triangle, calculating thew color output of the pixels, will always have an orange-ish color
    unsigned int fragmentShader;
    //glCreateShader(ShaderType)
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(shader, count, string, length)
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //glCompileShader(shader)
    glCompileShader(fragmentShader);

    //combines multiple shaders
    unsigned int shaderProgram;
    //create the shader program
    shaderProgram = glCreateProgram();

    //attach the compiled shaders to a shader program
    //glAttachShader(program, shader)
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    //glLinkProgram(program)
    glLinkProgram(shaderProgram);

    //Checking if the shader compilation is successful or not
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){

        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED/n"<<infoLog<<std::endl;

    }

    //Delete the shaders that we no longer need
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //Tell OpenGL how it should interpret the vertex data
    //glVertexAttribPointer(index, size, type, normalized, stride (byte offset), pointer)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    //glEnableVertexAttribArray(index)
    glEnableVertexAttribArray(0);

    //Activate the program obejct by calling it
    glUseProgram(shaderProgram);

    //Tells OpenGL the size of the rendering window
    //glViewport(location of the lower left cornder, location of the lower left corder, width, height)
    glViewport(0, 0, 800, 600);

    //Continuously run the program (so it doesn't close immediately after opening)
    while(!glfwWindowShouldClose(window)){

        processInput(window);

        //This changes the color of the background from black to something green-ish
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Change from draw array to draw elements
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
glfwTerminate();
return 0;
}


void processInput(GLFWwindow* window){

    //Check if escape is entered, if entered, close the window
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){

        glfwSetWindowShouldClose(window, true);

    }

}

//This function makes it so that it will resize when resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    glViewport(0, 0, width, height);

}