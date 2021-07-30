    #include <glad/glad.h>
    #include <GLFW/glfw3.h>
    #include <stb/stb_image.h>
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #include <glm/gtc/type_ptr.hpp>
    #include <iostream>
    #include <math.h>
    #include "Header/shaderClass.h"
    #include "Header/VAO.h"
    #include "Header/VBO.h"
    #include "Header/EBO.h"
    #include "Header/Texture.h"
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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //uncomment this statement to fix compilation on OS X
    #endif

        //Vertices coordinates
        GLfloat vertices[] = 
        {//     COORDINATES         /       COLORS        /     TexCoord//
            -0.5f,    0.0f,  0.5f,   0.83f, 0.70f, 0.44f,  0.0f, 0.0f,// Lower left corner
            -0.5f,    0.0f, -0.5f,   0.83f, 0.70f, 0.44f,  5.0f, 0.0f,// Lower right corner
             0.5f,    0.0f, -0.5f,   0.83f, 0.70f, 0.44f,  0.0f, 0.0f,// Upper corner
             0.5f,    0.0f,  0.5f,   0.83f, 0.70f, 0.44f,  5.0f, 0.0f,//Inner left
             0.0f,    0.8f,  0.0f,   0.92f, 0.86f, 0.76f,  2.5f, 5.0f
        };

        GLuint indices[] = 
        {
            0, 1, 2, // Lower left triangle
            0, 2, 3, // LowerRight triangle
            0, 1, 4, // Upper triangle
            1, 2, 4,
            2, 3, 4,
            3, 0, 4
        };

        // glfw window creation
        // --------------------
        GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,"OpenGL", NULL, NULL);
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

        Shader shaderProgram("src/Shaders/VertexShader.vs", "src/Shaders/FragmentShader.fs");

        VAO VAO1;
        VAO1.Bind();

        VBO VBO1(vertices, sizeof(vertices));
        EBO EBO1(indices, sizeof(indices));

        VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
        VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        VAO1.Unbind();
        VBO1.Unbind();
        EBO1.Unbind();

        //Gets ID of uniiform called "scaled"
        GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

        //Texture

        Texture popCat("resource/pyramid.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
        popCat.texUnit(shaderProgram, "tex0", 0);

        // render loop
        // -----------
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);

        //Variables that help the rotation of the pyramid
        float rotation = 0.0f;
        double prevTime = glfwGetTime();

        //Enables the Depth Buffer
        glEnable(GL_DEPTH_TEST);

        while (!glfwWindowShouldClose(window))
        {
            //Specify the color of the background
            glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
            //Clean the back buffer and depth buffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            //Tell OpenGL which Shader Program we want to use
            shaderProgram.Activate();

            //Simple timer
            double crnTime = glfwGetTime();
            if(crnTime - prevTime >= 1 / 60)
            {
                rotation += 0.5f;
                prevTime = crnTime;
            }

            //Initializes matrices so they are not the null matrix
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 proj = glm::mat4(1.0f);

            //Assigns different transformations to each matrix
            model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
            proj = glm::perspective(glm::radians(45.0f), (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);

            // Outputs the matrices into the Vertex Shader
            int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

            //Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
            glUniform1f(uniID, 0.5f);
            // Binds texture so that is appears in render
            popCat.Bind();
            //Bind the VAO so OpenGL knows to use it
            VAO1.Bind();
            //Draw the triangle using the GL_TRIANGLES primitive
            glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
            // glfw: swap buffers and poll IO events (keyspressed/released, mouse moved etc.)
            // ---------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        //Delete all the object we've created
       VAO1.Delete();
       VBO1.Delete();
       EBO1.Delete();
       popCat.Delete();
       shaderProgram.Delete();

        // glfw: terminate, clearing all previously allocated GLFWresources.
        //---------------------------------------------------------------
        glfwTerminate();
        return 0;
    }