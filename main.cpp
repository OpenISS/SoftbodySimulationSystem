
#include "global.h"
#include "ViewSpace.h"
#include "Object1D.h"
#include "Object2D.h"
#include "Object3D.h"

int main()
{
    // ****************** initialization process ****************************************
    // initialize glfw
    glfwInit();
    
    // set the window version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // for mac only, for crossplatform purpose
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // prevent the window from resizing itself
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    // create a window
    GLFWwindow *window = glfwCreateWindow(Width, Height, "COMP371 PA3", nullptr, nullptr);
    
    // for mac to adjust the window size
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    // check if the window has been created correctly
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    // initialize glew
    glewExperimental = true;
    if(GLEW_OK != glewInit())
    {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Compile and link shaders here ...
    Shader shader("resources/shaders/core.vs", "resources/shaders/core.fs");
    shader.use();
    // ******************** end of system initializatoin ***************************************

    
    // *****************Variables declarations*******************
    float lastFrameTime = glfwGetTime();    // time is in seconds
    float movementSpeed = 1.0f;
    float initialEyeX = 0.0f;
    float initialEyeY = 0.0f;
    float initialEyeZ = 7.0f;
    glm::vec3 initialEye(initialEyeX, initialEyeY, initialEyeZ);
    
    int mousedown = 0;
    float xMouse, yMouse;
    // ******************* end of variable declaration***********


    // ******************* set initial camera position *****************
    glm::vec3 eye = initialEye;
    glm::vec3 center(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(70.0f), float(Width) / float(Height), 0.01f, 100.0f);
    GLuint projectionMatrixLocation = glGetUniformLocation(shader.program, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    glm::mat4 viewMatrix = glm::lookAt(eye,  // eye
        center,  // center
        cameraUp);
    GLuint viewMatrixLocation = glGetUniformLocation(shader.program, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    
    //**************** end of initial camera position *******************************************
    

    // enable backface culling and depth test
//    glEnable(GL_CULL_FACE);
//    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);                                // transparent
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    ViewSpace box;
    Object1D object1D;
    Object2D object2D;
    Object3D object3D;
    
    // set integrator type
    object1D.setIntegratorType(RK4);
    object2D.setIntegratorType(RK4);
    object3D.setIntegratorType(RK4);
    // main game loop
    while(!glfwWindowShouldClose(window))
    {
        // detect inputs from keyboard
        glfwPollEvents();
        
        // set background color (r, g, b, alpha)
        // can either do this inside the loop or outside the loop
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
        // Each frame, reset color of each pixel to glClearColor and clear depth buffer bit
        glClear(GL_COLOR_BUFFER_BIT);
        
        // compute the rotational angle every loop.
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;
        

        
        //============== updating ===========
        // update mouse position
        double x = Width / 2.0, y = Height / 2.0;
        glfwGetCursorPos(window, &x, &y);
        xMouse = (4 * ((float)x / (float)Width)) - 2;
        yMouse = -((4 * ((float)y / (float)Height)) - 2);
        // update object
        object1D.Update(DT, mousedown != 0, xMouse, yMouse);
        object2D.Update(DT, mousedown != 0, xMouse, yMouse);
        object3D.Update(DT, mousedown != 0, xMouse, yMouse);
        
        // ============ drawing =======================
        glm::mat4 sbMatrix = glm::mat4(1.0f);   //  can possibly apply glm::translate(), glm::rotate(), and glm::scale() here
        box.Draw(shader.program);
        object1D.Draw(shader.program, sbMatrix);
        object2D.Draw(shader.program, sbMatrix);
        object3D.Draw(shader.program, sbMatrix);

        // End of frame, used 2 buffers for displaying, this is swapping the buffer
        glfwSwapBuffers(window);
        
        // ************** handle inputs *************************
        
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            mousedown = 1;
        }
        else{
            mousedown = 0;
        }
        
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
        
        
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            glm::vec3 direction(0.0f, 2.0f, 0.0f);
            eye = eye + direction * movementSpeed * dt;
            center = center + direction * movementSpeed * dt;

        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            glm::vec3 direction(0.0f, -2.0f, 0.0f);
            eye = eye + direction * movementSpeed * dt;
            center = center + direction * movementSpeed * dt;
        }

        // update the view matrix
        glm::mat4 viewMatrix = glm::lookAt(eye,  // eye
            center,  // center
            cameraUp);
        GLuint viewMatrixLocation = glGetUniformLocation(shader.program, "viewMatrix");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);

    }
    
    
    glfwTerminate();
    return 0;
}








