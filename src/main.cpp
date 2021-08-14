#include "Header/Model.h"
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

//Vertex Shader source code.

//Fragment Shader source code

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern function
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //uncomment this statement to fix compilation on OS X
#endif

   

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Load GLAD so it configures OpenGL
    gladLoadGL();

    //Specify the viewport of OpenGL in the Window
    //In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // Generates Shader object using shaders VertexShader.vs and FragmentShader.fs
    Shader shaderProgram("src/Shaders/VertexShader.vs", "src/Shaders/FragmentShader.fs");

    
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightColor.x, lightColor.y, lightColor.z);

    //Texture

    

    // render loop
    // -----------
    // glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);
    // glfwSwapBuffers(window);

    //Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);

    //Creates camera onject
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    Model model("resource/models/sword/scene.gltf");

    while (!glfwWindowShouldClose(window))
    {
        //Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        //Clean the back buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       

        //Handles camera inputs
        camera.Inputs(window);
        //Updates and exports the camera matrix to the Vertex Shader
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        model.Draw(shaderProgram, camera);
        
        // glfw: swap buffers and poll IO events (keyspressed/released, mouse moved etc.)
        // ---------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Delete all the object we've created
   
    shaderProgram.Delete();

    // glfw: terminate, clearing all previously allocated GLFWresources.
    //---------------------------------------------------------------
    glfwTerminate();
    return 0;
}