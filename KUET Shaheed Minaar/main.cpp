//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "directional.h"
#include "spotlight.h"

#include "curve.h"
#include "cube.h"
#include "stb_image.h"
#include "sphere.h"
#include "cylinder.h"

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void drawCube2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float, float alpha);
void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);


//alif
long long nCr(int n, int r);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
unsigned int hollowBezier(GLfloat ctrlpoints[], int L);

// settings



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;





//points
vector<float> jhopchauni
{
-0.1063, 1.6252, 5.1000,
-0.1917, 1.6222, 5.1000,
-0.3063, 1.6131, 5.1000,
-0.4792, 1.5556, 5.1000,
-0.6104, 1.4829, 5.1000,
-0.7250, 1.4224, 5.1000,
-0.8479, 1.3588, 5.1000,
-0.9125, 1.3074, 5.1000,
-0.9563, 1.2741, 5.1000,
};
vector<float> gachchauni
{
-0.0146, 2.1399, 5.1000,
-0.0438, 2.1066, 5.1000,
-0.0708, 2.0763, 5.1000,
-0.1042, 2.0006, 5.1000,
-0.1625, 1.9219, 5.1000,
-0.2000, 1.8402, 5.1000,
-0.2708, 1.6949, 5.1000,
-0.3479, 1.5768, 5.1000,
-0.4417, 1.4224, 5.1000,
-0.5292, 1.2589, 5.1000,
-0.6042, 1.1106, 5.1000,
-0.6792, 0.9047, 5.1000,
-0.6708, 0.7746, 5.1000,
-0.5167, 0.7534, 5.1000,
};




vector<float> gachcurve
{
-0.1542, 1.9703, 5.1000,
-0.1542, 1.9068, 5.1000,
-0.1583, 1.8341, 5.1000,
-0.1583, 1.7705, 5.1000,
-0.1542, 1.6827, 5.1000,
-0.1583, 1.5980, 5.1000,
-0.1583, 1.5344, 5.1000,
-0.1604, 1.4103, 5.1000,
-0.1604, 1.3013, 5.1000,
-0.1563, 1.2044, 5.1000,
-0.1563, 1.0773, 5.1000,
-0.1583, 0.9683, 5.1000,
-0.1604, 0.8714, 5.1000,
-0.1583, 0.7715, 5.1000,
-0.1625, 0.6928, 5.1000,
-0.1625, 0.5717, 5.1000,
-0.1625, 0.4870, 5.1000,
-0.1708, 0.3871, 5.1000,
-0.1854, 0.3114, 5.1000,
-0.2104, 0.2509, 5.1000,
-0.2188, 0.2085, 5.1000,
-0.2521, 0.1570, 5.1000,
-0.2958, 0.0813, 5.1000,
-0.3042, 0.0723, 5.1000,
-0.3438, 0.0450, 5.1000,
-0.3854, 0.0178, 5.1000,
-0.3917, 0.0178, 5.1000
};




//bezier curve
vector <float> coordinates;
vector <float> normals;
vector <int> indices;
vector <float> vertices;
class point
{
public:
    point()
    {
        x = 0;
        y = 0;
    }
    int x;
    int y;
} clkpt[2];
int mouseButtonFlag = 0;
FILE* fp;
const double pi = 3.14159265389;
const int nt = 40;
const int ntheta = 20;
bool showControlPoints = true;
bool loadBezierCurvePoints = false;
bool showHollowBezier = false;
bool lineMode = false;
unsigned int bezierVAO;
unsigned int gachcurveVAO;
unsigned int gachchauniVAO;
unsigned int jhopchauniVAO;



// camera
Camera camera(glm::vec3(0.0f, 4.1f, 40.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = -1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);


// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(2.50f,  2.50f,  0.0f),
    glm::vec3(2.5f,  -2.5f,  0.0f),
    glm::vec3(-2.5f,  2.5f,  0.0f),
    glm::vec3(-22.0f, 25.05f, 5.5f)
    //glm::vec3(-2.5f,  -2.5f,  0.0f)
    //grass
    //
};


//glm::vec3(-0.5, 1, -0.5)


PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.01f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.01f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.01f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.0001f,   //k_c
    0.009f, //0.09f,  //k_l
    0.0009f, //0.032f, //k_q
    4       // light number
);
PointLight pointlight5(
    -9.5f, -1.15f, 16.0f,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.1f,   //k_c
    0.9f,  //k_l
    0.32f, //k_q
    5       // light number
);
PointLight pointlight6(
    -9.5f, -1.15f, 23.0f,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.1f,   //k_c
    0.9f,  //k_l
    0.32f, //k_q
    6       // light number
);
PointLight pointlight7(
    -9.5f, -1.75f, 25.50f,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.1f,   //k_c
    0.9f,  //k_l
    0.32f, //k_q
    7       // light number
);
PointLight pointlight8(
    -9.5f, -1.75f, 29.50f,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.1f,   //k_c
    0.9f,  //k_l
    0.32f, //k_q
    8       // light number
);
PointLight pointlight9(
    9.2f, -1.15f, 16.0f,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.1f,   //k_c
    0.9f,  //k_l
    0.32f, //k_q
    9       // light number
);
PointLight pointlight10(
    9.2f, -1.15f, 23.0f,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.1f,   //k_c
    0.9f,  //k_l
    0.32f, //k_q
    10       // light number
);
PointLight pointlight11(
    9.2f, -1.75f, 25.50f,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.01f,   //k_c
    0.09f,  //k_l
    0.32f, //k_q
    11       // light number
);
PointLight pointlight12(
    9.2f, -1.75f, 29.50f,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.1f,   //k_c
    0.9f,  //k_l
    0.32f, //k_q
    12       // light number
);
PointLight pointlight13(
    14.2f, 1.0f, 25.50f,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    0.001f,   //k_c
    0.009f,  //k_l
    0.032f, //k_q
    13       // light number
);


DirectionalLight directionalLight(0.0f, 100.0f, 3000.0f,
    0.4f, 0.4f, 0.4f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f);

SpotLight spotLight(0.0, 1, -0.5,0,
    -1, 0, 0.2f,
    0.2f, 0.2f,
    1.0f, 1, 1,
    1.0f, 1.0f, 1.0f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(21.50f)));

// light settings
bool onOffToggle = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;
bool directionalLightOn = true;
bool pointLightFirstHalf = true;
bool pointLightSecondHalf = true;
bool spotLightOn = true;

float FwaterY = 0.0f;
// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;


glm::mat4 transformation(float transform_x, float transform_y, float transform_z, float rotate_x, float rotate_y,
    float rotate_z, float scale_x, float scale_y, float scale_z) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(transform_x, transform_y, transform_z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotate_x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotate_y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotate_z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_x, scale_y, scale_z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    return model;
}




int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);
    

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);




    //bazierVAO

    gachcurveVAO = hollowBezier(gachcurve.data(), ((unsigned int)gachcurve.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    gachchauniVAO = hollowBezier(gachchauni.data(), ((unsigned int)gachchauni.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    jhopchauniVAO = hollowBezier(jhopchauni.data(), ((unsigned int)jhopchauni.size() / 3) - 1);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    ///////////////grass
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");

    string diffuseMapPath = "grasslarge.png";
    string specularMapPath = "grasslarge.png";


    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 5.0f, 5.0f);

    //nodi
    //Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");

    string diffuseMapPath2 = "waterlarge.png";
    string specularMapPath2 = "waterlarge.png";


    unsigned int diffMap2 = loadTexture(diffuseMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    unsigned int specMap2 = loadTexture(specularMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube cube2 = Cube(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //road
    string diffuseMapPath3 = "roadtex.png";
    string specularMapPath3 = "roadtex.png";


    unsigned int diffMap3 = loadTexture(diffuseMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    unsigned int specMap3 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube cube3 = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 5.0f, 5.0f);
    //BezierCurve gachwood = BezierCurve(gachcurve,27,specMap3,diffMap3);

    //mandala
    string diffuseMapPath4 = "mandalaf.png";
    string specularMapPath4 = "mandalaf.png";


    unsigned int diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    unsigned int specMap4 = loadTexture(specularMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube cube4 = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //brick
    string diffuseMapPath5 = "brick2.png";
    string specularMapPath5 = "brick2.png";
    unsigned int diffMap5 = loadTexture(diffuseMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    unsigned int specMap5 = loadTexture(specularMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube cube5 = Cube(diffMap5, specMap5, 32.0f, 0.0f, 0.0f, 4.0f, 4.0f);
    Cube cube6 = Cube(diffMap5, specMap5, 32.0f, 0.0f, 0.0f, 5.0f, 5.0f);

    string ww = "waterFall/1.png";
    unsigned int diffMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    unsigned int specMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube waterD1 = Cube(diffMapW, specMapW, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    
    ww = "waterFall/2.png";
    diffMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    specMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube waterD2 = Cube(diffMapW, specMapW, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    ww = "waterFall/3.png";
    diffMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    specMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube waterD3 = Cube(diffMapW, specMapW, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    

    ww = "waterFall/4.png";
    diffMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    specMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube waterD4 = Cube(diffMapW, specMapW, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    ww = "waterFall/5.png";
    diffMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    specMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube waterD5 = Cube(diffMapW, specMapW, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    ww = "waterFall/6.png";
    diffMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    specMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube waterD6 = Cube(diffMapW, specMapW, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    ww = "waterFall/7.png";
    diffMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    specMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube waterD7 = Cube(diffMapW, specMapW, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    ww = "waterFall/8.png";
    diffMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    specMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube waterD8 = Cube(diffMapW, specMapW, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    ww = "waterFall/9.png";
    diffMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    specMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube waterD9 = Cube(diffMapW, specMapW, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    ww = "waterFall/10.png";
    diffMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    specMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube waterD10 = Cube(diffMapW, specMapW, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    ww = "waterFall/11.png";
    diffMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    specMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube waterD11 = Cube(diffMapW, specMapW, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    ww = "waterFall/12.png";
    diffMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    specMapW = loadTexture(ww.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube waterD12 = Cube(diffMapW, specMapW, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    Cube waterrr[] = { waterD1,waterD2,waterD3,waterD4,waterD5,waterD6,waterD7,waterD8,waterD9,waterD10,waterD11,waterD12 };
    

    float waterDropY[20];
    float yyy = 1.8;
    for (int i = 0; i < 16; i++)
    {
        waterDropY[i] = yyy;
        yyy -= 0.3;
    }
    float waterDropSpeed = 0.05;

    float time = 0.0f;
    int indd = 0;

    //stage
    /*string diffuseMapPath3 = "bricksmall.png";
    string specularMapPath3 = "bricksmall.png";


    unsigned int diffMap3 = loadTexture(diffuseMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    unsigned int specMap3 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_REPEAT, GL_REPEAT);
    Cube cube3 = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);*/


    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
        pointlight4.setUpPointLight(lightingShader);
        pointlight5.setUpPointLight(lightingShader);
        pointlight6.setUpPointLight(lightingShader);
        pointlight7.setUpPointLight(lightingShader);
        pointlight8.setUpPointLight(lightingShader);
        pointlight9.setUpPointLight(lightingShader);
        pointlight10.setUpPointLight(lightingShader);
        pointlight11.setUpPointLight(lightingShader);
        pointlight12.setUpPointLight(lightingShader);
        pointlight13.setUpPointLight(lightingShader);


        directionalLight.setUpDirectionalLight(lightingShader);

        spotLight.setUpSpotLight(lightingShader);

        /*lightingShader.setVec3("diectionalLight.directiaon", 0.0f, 3.0f, 0.0f);
        lightingShader.setVec3("diectionalLight.ambient", .2, .2, .2);
        lightingShader.setVec3("diectionalLight.diffuse", .8f, .8f, .8f);
        lightingShader.setVec3("diectionalLight.specular", 1.0f, 1.0f, 1.0f);




        lightingShader.setBool("dlighton", false);*/


        /*lightingShader.setVec3("spotlight.position", -0.5, 1, -0.5);
        lightingShader.setVec3("spotlight.direction", 0, -1, 0);
        lightingShader.setVec3("spotlight.ambient", .2, .2, .2);
        lightingShader.setVec3("spotlight.diffuse", .8f, .8f, .8f);
        lightingShader.setVec3("spotlight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("spotlight.k_c", 1.0f);
        lightingShader.setFloat("spotlight.k_l", 0.09);
        lightingShader.setFloat("spotlight.k_q", 0.032);
        lightingShader.setFloat("cos_theta", glm::cos(glm::radians(5.5f)));
        lightingShader.setBool("spotlighton", true);*/


        //pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
        //    1.0f, 1.0f, 1.0f,     // ambient
        //    1.0f, 1.0f, 1.0f,      // diffuse
        //    1.0f, 1.0f, 1.0f,        // specular
        //    1.0f,   //k_c
        //    0.09f,  //k_l
        //    0.032f, //k_q
        //    1,       // light number
        //    glm::cos(glm::radians(20.5f)),
        //    glm::cos(glm::radians(25.0f)),
        //    0, -1, 0
        // activate shader
        lightingShader.use();











        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);

        //glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        bed(cubeVAO, lightingShader, model);

        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.directional
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        ///////texture
        // 
        // 
        // 
        // 
        // 
        // 
        // 
        // 
        // 
        // be sure to activate shader when setting uniforms/drawing objects
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
        //glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShaderWithTexture.setMat4("projection", projection);

        // camera/view transformation
        //glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view);


        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight4.setUpPointLight(lightingShaderWithTexture);
        



        //sphere//sphere
        Sphere spheresigG3 = Sphere();
        Sphere spheresigG4 = Sphere();
        //glm::mat4 alTogether;

        spheresigG3.ambient = glm::vec3(1.0f, 0.0f, 0.0f);
        spheresigG3.diffuse = glm::vec3(1.0f, 0.0f, 0.0f);
        spheresigG3.specular = glm::vec3(1.0f, 0.0f, 0.0f);
        spheresigG4.ambient = glm::vec3(1.0f, 1.0f, 1.0f);
        spheresigG4.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
        spheresigG4.specular = glm::vec3(1.0f, 1.0f, 1.0f);

        glm::mat4 modelForSphere = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 3.5f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(13.0f, 13.0f, 0.5f));
        modelForSphere = translateMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);
        spheresigG3.drawSphere(lightingShader, modelForSphere);
        //reverse
        glm::mat4 modelForSphererev = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, -9.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(13.0f, 13.0f, 0.5f));
        modelForSphererev = translateMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);
        spheresigG3.drawSphere(lightingShader, modelForSphererev);
        glm::mat4 modelspherecylinderlight1 = transformation(-9.5f, -1.15f, 16.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
        spheresigG4.drawSphere(ourShader, modelspherecylinderlight1);
        glm::mat4 modelspherecylinderlight2 = transformation(-9.5f, -1.15f, 23.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
        spheresigG4.drawSphere(ourShader, modelspherecylinderlight2);
        glm::mat4 modelspherecylinderlight3 = transformation(-9.5f, -1.75f, 25.50f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
        spheresigG4.drawSphere(ourShader, modelspherecylinderlight3);
        glm::mat4 modelspherecylinderlight4 = transformation(-9.5f, -1.75f, 29.50f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
        spheresigG4.drawSphere(ourShader, modelspherecylinderlight4);

        glm::mat4 modelspherecylinderlight11 = transformation(9.2f, -1.15f, 16.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
        spheresigG4.drawSphere(ourShader, modelspherecylinderlight11);
        glm::mat4 modelspherecylinderlight22 = transformation(9.2f, -1.15f, 23.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
        spheresigG4.drawSphere(ourShader, modelspherecylinderlight22);
        glm::mat4 modelspherecylinderlight33 = transformation(9.2f, -1.75f, 25.50f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
        spheresigG4.drawSphere(ourShader, modelspherecylinderlight33);
        glm::mat4 modelspherecylinderlight44 = transformation(9.2f, -1.75f, 29.50f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
        spheresigG4.drawSphere(ourShader, modelspherecylinderlight44);


        //chad
        //glm::mat4 modelchad = transformation(0.0f, 10.5f, -50.0f, 0.0f, 0.0f, 0.0f, 13.0f, 13.0f, 0.5f);
        //spheresigG4.drawSphere(ourShader, modelspherecylinderlight1);






        //cylinder
        //cylinder initialization
        Cylinder myCylinder = Cylinder();
        myCylinder.setRadius(0.1);
        glm::mat4 modelcylinderlightstand = transformation(-9.5f, -1.85f, 16.0f, 0.0f, 0.0f, 0.0f, 0.4f, 0.7f, 0.4f);
        myCylinder.drawCylinder(lightingShader, modelcylinderlightstand, 0.1, 0.2, 0.3);
        glm::mat4 modelcylinderlightstand2 = transformation(-9.5f, -1.85f, 23.0f, 0.0f, 0.0f, 0.0f, 0.4f, 0.7f, 0.4f);
        myCylinder.drawCylinder(lightingShader, modelcylinderlightstand2, 0.1, 0.2, 0.3);
        glm::mat4 modelcylinderlightstand3 = transformation(-9.5f, -2.45f, 25.50f, 0.0f, 0.0f, 0.0f, 0.4f, 0.7f, 0.4f);
        myCylinder.drawCylinder(lightingShader, modelcylinderlightstand3, 0.1, 0.2, 0.3);
        glm::mat4 modelcylinderlightstand4 = transformation(-9.5f, -2.45f, 29.50f, 0.0f, 0.0f, 0.0f, 0.4f, 0.7f, 0.4f);
        myCylinder.drawCylinder(lightingShader, modelcylinderlightstand4, 0.1, 0.2, 0.3);

        glm::mat4 modelcylinderlightstand11 = transformation(9.2f, -1.85f, 16.0f, 0.0f, 0.0f, 0.0f, 0.4f, 0.7f, 0.4f);
        myCylinder.drawCylinder(lightingShader, modelcylinderlightstand11, 0.1, 0.2, 0.3);
        glm::mat4 modelcylinderlightstand22 = transformation(9.2f, -1.85f, 23.0f, 0.0f, 0.0f, 0.0f, 0.4f, 0.7f, 0.4f);
        myCylinder.drawCylinder(lightingShader, modelcylinderlightstand22, 0.1, 0.2, 0.3);
        glm::mat4 modelcylinderlightstand33 = transformation(9.2f, -2.45f, 25.50f, 0.0f, 0.0f, 0.0f, 0.4f, 0.7f, 0.4f);
        myCylinder.drawCylinder(lightingShader, modelcylinderlightstand33, 0.1, 0.2, 0.3);
        glm::mat4 modelcylinderlightstand44 = transformation(9.2f, -2.45f, 29.50f, 0.0f, 0.0f, 0.0f, 0.4f, 0.7f, 0.4f);
        myCylinder.drawCylinder(lightingShader, modelcylinderlightstand44, 0.1, 0.2, 0.3);
        
        //roadside light

        






        //gachtexture
        //glm::mat4 modelgachcurve = transformation(13.0f, -3.0f, 15.0f, 0.0f, 0.0f, 0.0f, 2.0f, 3.0f, 2.0f);
        //gachwood.drawBezierCurve(lightingShaderWithTexture,modelgachcurve);
        //basew texture
        //first stage
        glm::mat4 modelFirstStage = transformation(-10.0f, -1.25f, -0.501f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 9.0f);
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelFirstStage);
        glm::mat4 modelFirstStage2 = transformation(-10.0f, -1.45f, -0.501f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 9.5f);
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelFirstStage2);
        glm::mat4 modelFirstStage3 = transformation(-10.0f, -1.65f, -0.501f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 10.0f);
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelFirstStage3);
        glm::mat4 modelFirstStage3rev = transformation(-10.0f, -3.05f, -0.501f, 0.0f, 0.0f, 0.0f, 20.0f, -1.75f, 10.0f);
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelFirstStage3rev);

        //second stage
        glm::mat4 modelSecondStage = transformation(-12.50f, -1.85f, -0.501f, 0.0f, 0.0f, 0.0f, 25.0f, 0.2f, 14.5f);
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelSecondStage);
        glm::mat4 modelSecondStage2 = transformation(-12.50f, -2.05f, -0.501f, 0.0f, 0.0f, 0.0f, 25.0f, 0.2f, 15.0f);
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelSecondStage2);
        glm::mat4 modelSecondStage3 = transformation(-12.50f, -4.25f, -0.501f, 0.0f, 0.0f, 0.0f, 25.0f, 2.2f, 15.5f);
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelSecondStage3);
        glm::mat4 modelSecondStage4 = transformation(-12.50f, -2.25f, -0.501f, 0.0f, 0.0f, 0.0f, 25.0f, -0.6f, 15.5f);
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelSecondStage4);

        //third stage
        glm::mat4 modelThirdStage = transformation(-10.0f, -2.45f, -0.5f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 24.5f);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, modelThirdStage);
        glm::mat4 modelThirdStage2 = transformation(-10.0f, -2.65f, -0.5f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 25.0f);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, modelThirdStage2);
        glm::mat4 modelThirdStage3 = transformation(-10.0f, -3.05f, -0.5f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 31.0f);
        cube6.drawCubeWithTexture(lightingShaderWithTexture, modelThirdStage3);

        //third stage mandala 1
        //glm::mat4 modelThirdStagemandala1 = transformation(-10.0f, -2.45f, 15.0f, 0.0f, 0.0f, 0.0f, 9.0f, 0.21f, 9.0f);
        //cube4.drawCubeWithTexture(lightingShaderWithTexture, modelThirdStagemandala1);






        //roadtex
        glm::mat4 modelroad = transformation(40.5f, -3.05f, 33.0f, 0.0f, 40.0f, 0.0f, 7.5f, 0.4f, -240.0f);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, modelroad);
        glm::mat4 modelroadrev = transformation(40.5f, -3.05f, 33.0f, 0.0f, 40.0f, 0.0f, 7.5f, 0.4f, 20.0f);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, modelroadrev);
        //front road
        glm::mat4 modelfrontroad = transformation(-40.5f, -3.05f, 31.0f, 0.0f, 0.0f, 0.0f, 90.5f, 0.4f, 10.0f);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, modelfrontroad);
        modelfrontroad = transformation(-40.5f, -3.05f, 31.0f, 0.0f, 0.0f, 0.0f, -20.5f, 0.4f, 10.0f);
        cube3.drawCubeWithTexture(lightingShaderWithTexture, modelfrontroad);


        //grasstexture
        //glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        //cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);
        glm::mat4 modelgrasstexture = transformation(-10.0f, -3.04f, 31.0f, 0.0f, 0.0f, 0.0f, -50.0f, 0.2f, -30.0f);
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelgrasstexture);
        //drawCube(cubeVAO, lightingShader, modelgrasstexture, 0.0, 1.0, 0.0);
        glm::mat4 modelgrasstexture2 = transformation(-11.0f, -3.05f, 0.5f, 0.0f, 40.0f, 0.0f, -50.5f, 0.2f, -100.0f);
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelgrasstexture2);
        //drawCube(cubeVAO, lightingShader, modelgrasstexture2, 0.0, 1.0, 0.0);

        

        //stage
        //glm::mat4 modelThirdStage = transformation(-10.0f, -2.45f, -0.5f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 18.5f);
        ////drawCube(cubeVAO, lightingShader, modelThirdStage, 0.8, 0.4, 0.2);
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, modelThirdStage);
        //glm::mat4 modelThirdStage2 = transformation(-10.0f, -2.65f, -0.5f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 19.0f);
        ////drawCube(cubeVAO, lightingShader, modelThirdStage2, 0.8, 0.4, 0.2);
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, modelThirdStage2);
        //glm::mat4 modelThirdStage3 = transformation(-10.0f, -2.85f, -0.5f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 24.0f);
        ////drawCube(cubeVAO, lightingShader, modelThirdStage3, 0.8, 0.4, 0.2);
        //cube3.drawCubeWithTexture(lightingShaderWithTexture, modelThirdStage3);

        //large tree  base
        glm::mat4 modelmaintreebasetexture = transformation(-15.0f, -4.05f, 12.51f, 0.0f, 0.0f, 0.0f, 5.0f, 2.8f, 5.0f);
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelmaintreebasetexture);
        //left tree bases
        glm::mat4 modelsmallleft1treebasetexture = transformation(-14.0f, -4.05f, 19.51f, 0.0f, 0.0f, 0.0f, 3.0f, 1.4f, 2.0f);
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelsmallleft1treebasetexture);
        glm::mat4 modelsmallleft2treebasetexture = transformation(-14.0f, -4.05f, 23.01f, 0.0f, 0.0f, 0.0f, 3.0f, 1.4f, 2.0f);
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelsmallleft2treebasetexture);
        glm::mat4 modelsmallleft3treebasetexture = transformation(-14.0f, -4.05f, 26.51f, 0.0f, 0.0f, 0.0f, 3.0f, 1.4f, 2.0f);
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelsmallleft3treebasetexture);
        //middle
        //tree base middle texture 1
        glm::mat4 modelmiddle1treebasetexture = transformation(-0.751f, -4.05f, 18.001f, 0.0f, 0.0f, 0.0f, 1.5f, 2.0f-0.18f, 1.49f);
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelmiddle1treebasetexture);
        
        //tree base middle texture 2
        glm::mat4 modelmiddle2treebasetexture = transformation(-0.751f, -4.05f, 21.501f, 0.0f, 0.0f, 0.0f, 1.5f, 2.0f-0.18f, 1.49f);
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelmiddle2treebasetexture);
        
        //tree base middle texture 3
        glm::mat4 modelmiddle3treebasetexture = transformation(-0.751f, -3.05f, 25.001f, 0.0f, 0.0f, 0.0f, 1.5f, 0.6f-0.18f, 1.49f);
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelmiddle3treebasetexture);
        
        //tree base middle texture 4
        glm::mat4 modelmiddle4treebasetexture = transformation(-0.751f, -3.05f, 28.001f, 0.0f, 0.0f, 0.0f, 1.5f, 0.6f-0.18f, 1.49f);
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelmiddle4treebasetexture);
        
        






        //fountain
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));

        glm::mat4 modelForFountain = transformation(13.01f, -3.0f, 25.01f, 0.0f, 0.0f, 0.0f, 0.4f, 5.0f, 0.4f);
        myCylinder.drawCylinder(lightingShader, modelForFountain, 0.0, 0.0, 0.0);

        spheresigG3.ambient = glm::vec3(1.0f, 0.0f, 0.0f);
        spheresigG3.diffuse = glm::vec3(1.0f, 0.0f, 0.0f);
        spheresigG3.specular = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::mat4 modelForFountainTop = transformation(13.01f, 2.0f, 25.01f, 0.0f, 0.0f, 0.0f, 5.0f, 0.2f, 5.0f);
        spheresigG3.drawSphere(lightingShader, modelForFountainTop);


        /*glm::mat4 modelForWat = transformation(13.01f, 1.8f, 25.9f, 0.0f, 0.0f, 0.0f, 0.05f, 0.2f, 0.05f);
        drawCube(cubeVAO, lightingShader, modelForWat, 0.0, 0.0, 1.0);*/
        //FwaterY += 0.01f;
        for (int i = 0; i < 16; i++)
        {
            waterDropY[i] -= waterDropSpeed;
            if (waterDropY[i] <= -3.0)
                waterDropY[i] = 1.8;
            glm::mat4 modelForWat = transformation(13.01f, waterDropY[i], 25.9f, 0.0f, 0.0f, 0.0f, 0.05f, 0.2f, 0.05f);
            drawCube(cubeVAO, lightingShader, modelForWat, 1.0, 1.0, 1.0);

            modelForWat = transformation(13.01f, waterDropY[i], 23.9f, 0.0f, 0.0f, 0.0f, 0.05f, 0.2f, 0.05f);
            drawCube(cubeVAO, lightingShader, modelForWat, 1.0, 1.0, 1.0);

            modelForWat = transformation(13.5f, waterDropY[i], 25.5f, 0.0f, 0.0f, 0.0f, 0.05f, 0.2f, 0.05f);
            drawCube(cubeVAO, lightingShader, modelForWat, 1.0, 1.0, 1.0);

            modelForWat = transformation(13.5f, waterDropY[i], 24.3f, 0.0f, 0.0f, 0.0f, 0.05f, 0.2f, 0.05f);
            drawCube(cubeVAO, lightingShader, modelForWat, 1.0, 1.0, 1.0);

            modelForWat = transformation(12.5f, waterDropY[i], 25.5f, 0.0f, 0.0f, 0.0f, 0.05f, 0.2f, 0.05f);
            drawCube(cubeVAO, lightingShader, modelForWat, 1.0, 1.0, 1.0);

            modelForWat = transformation(12.5f, waterDropY[i], 24.3f, 0.0f, 0.0f, 0.0f, 0.05f, 0.2f, 0.05f);
            drawCube(cubeVAO, lightingShader, modelForWat, 1.0, 1.0, 1.0);


            modelForWat = transformation(12.0f, waterDropY[i], 24.9f, 0.0f, 0.0f, 0.0f, 0.05f, 0.2f, 0.05f);
            drawCube(cubeVAO, lightingShader, modelForWat, 1.0, 1.0, 1.0);

            modelForWat = transformation(14.01f, waterDropY[i], 24.9f, 0.0f, 0.0f, 0.0f, 0.05f, 0.2f, 0.05f);
            drawCube(cubeVAO, lightingShader, modelForWat, 1.0, 1.0, 1.0);
        }




        

        

        //for (int i = 0; i < 10; i++)
        //{

        //}




        //glm::mat4 modelrightjhobasetexture = transformation(10.01f, -3.0f, 15.01f, 0.0f, 0.0f, 0.0f, 8.1f, 0.1, 15.4f);
        //waterFlow[0].drawCubeWithTexture(lightingShaderWithTexture, modelrightjhobasetexture);

        if (currentFrame - time>0.1)
        {
            time = currentFrame;
            if (indd == 11)
                indd = 0;
            else
                indd++;
        }
        glm::mat4 modelrightjhobasetexture = transformation(17.3f, -3.0f, 32.5f, 0.0f, 180.0f, 0.0f, 8.1f, 0.1, 17.4f);
        waterrr[indd].drawCubeWithTexture(lightingShaderWithTexture, modelrightjhobasetexture);
        


        //rightjhobase texture
        


        
        //cube.drawCubeWithTexture(lightingShaderWithTexture, modelrightjhobasetexture);
        //drawCube2(cubeVAO, ourShader, modelrightjhobasetexture, 0.2, 0.2, 0.6, 0.5);
        //rightjhobase erpasher faka jaiga
        glm::mat4 modelrightjhopashetexture = transformation(18.4f, -3.0f, 30.5f, 0.0f, 20.0f, 0.0f, 16.4f, 0.125, -30.4f);
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelrightjhopashetexture);


        //pond
        glm::mat4 modelnodi = transformation(13.5f, -3.08f, 0.5f, 0.0f, 40.0f, 0.0f, -19.5f, 0.2f, -240.0f);
        drawCube2(cubeVAO, ourShader, modelnodi, 0.1, 0.1, 0.4, 0.5);

        glm::mat4 modelsadamaker = transformation(12.5f, -3000.08f, 0.5f, 0.0f, 40.0f, 0.0f, 0.01f, 0.01f, 0.01f);
        drawCube2(cubeVAO, ourShader, modelsadamaker, 1.0, 1.0, 1.0, 0.5);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(r, g, b));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
void drawCube2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f, float alpha = 1.0f)
{
    lightingShader.use();

    // Set material properties
    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 22.0f);

    // Set model matrix
    lightingShader.setMat4("model", model);

    // Set the color with alpha (transparency)
    lightingShader.setVec4("color", glm::vec4(r, g, b, alpha));

    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Bind VAO and draw the cube
    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Disable blending after drawing
    glDisable(GL_BLEND);
}

void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float baseHeight = 0.1;
    float width = 10;
    float length = 5;
    float pillowWidth = 0.3;
    float pillowLength = 0.15;
    float blanketWidth = 0.8;
    float blanketLength = 0.7;
    float headHeight = 0.6;




    //firstbase
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    /*scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.5, -8.5, -0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);*/
    glm::mat4 modelFirstBase = transformation(-7.5f, -1.05f, -0.5f, 0.0f, 0.0f, 0.0f, 15.0f, 0.3f, 5.0f);
    drawCube(cubeVAO, lightingShader, modelFirstBase, 0.0, 0.0, 0.0);
    glm::mat4 modelFirstBaserev = transformation(-7.5f, -4.8f, -0.5f, 0.0f, 0.0f, 0.0f, 15.0f, -0.3f, 5.0f);
    drawCube(cubeVAO, lightingShader, modelFirstBaserev, 0.0, 0.0, 0.0);

    //basepillar
    //main
    glm::mat4 modelBasePillar = transformation(-1.9f, -0.8f, 0.2f, 0.0f, 0.0f, 0.0f, 4.0f, 0.2f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelBasePillar, 1.0, 1.0, 1.0);
    glm::mat4 modelBasePillarrev = transformation(-1.9f, -5.1f, 0.2f, 0.0f, 0.0f, 0.0f, 4.0f, -0.2f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelBasePillarrev, 1.0, 1.0, 1.0);
    //basepillar 1st left
    glm::mat4 modelBasePillar2 = transformation(-4.7f, -0.8f, 1.7f, 0.0f, 30.0f, 0.0f, 2.2f, 0.2f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelBasePillar2, 1.0, 1.0, 1.0);
    glm::mat4 modelBasePillar2r = transformation(-4.7f, -5.1f, 1.7f, 0.0f, 30.0f, 0.0f, 2.2f, -0.2f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelBasePillar2r, 1.0, 1.0, 1.0);
    ////basepillar 1st right
    glm::mat4 modelBasePillar3 = transformation(4.7f, -0.8f, 1.7f, 0.0f, 150.0f, 0.0f, 2.2f, 0.2f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelBasePillar3, 1.0, 1.0, 1.0);
    glm::mat4 modelBasePillar3rev = transformation(4.7f, -5.1f, 1.7f, 0.0f, 150.0f, 0.0f, 2.2f, -0.2f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelBasePillar3rev, 1.0, 1.0, 1.0);
    //basepillar 2nd left
    glm::mat4 modelBasePillar4 = transformation(-6.8f, -0.8f, 3.4f, 0.0f, 35.0f, 0.0f, 2.2f, 0.2f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelBasePillar4, 1.0, 1.0, 1.0);
    glm::mat4 modelBasePillar4r = transformation(-6.8f, -5.1f, 3.4f, 0.0f, 35.0f, 0.0f, 2.2f, -0.2f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelBasePillar4r, 1.0, 1.0, 1.0);
    ////basepillar 2nd right
    glm::mat4 modelBasePillar5 = transformation(6.8f, -0.8f, 3.4f, 0.0f, 145.0f, 0.0f, 2.2f, 0.2f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelBasePillar5, 1.0, 1.0, 1.0);
    glm::mat4 modelBasePillar5r = transformation(6.8f, -5.1f, 3.4f, 0.0f, 145.0f, 0.0f, 2.2f, -0.2f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelBasePillar5r, 1.0, 1.0, 1.0);

    //lombapillar
    //main-left
    glm::mat4 modelUpPillar = transformation(-1.7f, -0.8f, 0.2f, 0.0f, 0.0f, 0.0f, 0.5f, 9.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillarrev = transformation(-1.7f, -5.3f, 0.2f, 0.0f, 0.0f, 0.0f, 0.5f, -9.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillarrev, 1.0, 1.0, 1.0);
    //main-mid
    glm::mat4 modelUpPillar2 = transformation(-0.15f, -0.8f, 0.2f, 0.0f, 0.0f, 0.0f, 0.5f, 9.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar2, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillar2rev = transformation(-0.15f, -5.3f, 0.2f, 0.0f, 0.0f, 0.0f, 0.5f, -9.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar2rev, 1.0, 1.0, 1.0);
    //main-right
    glm::mat4 modelUpPillar3 = transformation(1.4f, -0.8f, 0.2f, 0.0f, 0.0f, 0.0f, 0.5f, 9.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar3, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillar3rev = transformation(1.4f, -5.3f, 0.2f, 0.0f, 0.0f, 0.0f, 0.5f, -9.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar3rev, 1.0, 1.0, 1.0);
    //lombapillar 1st left pair left-right
    glm::mat4 modelUpPillar4 = transformation(-4.6f, -0.8f, 1.65f, 0.0f, 30.0f, 0.0f, 0.4f, 7.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar4, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillar4rev = transformation(-4.6f, -5.3f, 1.65f, 0.0f, 30.0f, 0.0f, 0.4f, -7.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar4rev, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillar5 = transformation(-3.25f, -0.8f, 0.85f, 0.0f, 30.0f, 0.0f, 0.4f, 7.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar5, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillar5rev = transformation(-3.25f, -5.3f, 0.85f, 0.0f, 30.0f, 0.0f, 0.4f, -7.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar5rev, 1.0, 1.0, 1.0);
    //lombapillar 2nd left pair left-right
    glm::mat4 modelUpPillar6 = transformation(-6.65f, -0.8f, 3.3f, 0.0f, 35.0f, 0.0f, 0.4f, 5.5f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar6, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillar6rev = transformation(-6.65f, -5.3f, 3.3f, 0.0f, 35.0f, 0.0f, 0.4f, -5.5f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar6rev, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillar7 = transformation(-5.45f, -0.8f, 2.45f, 0.0f, 35.0f, 0.0f, 0.4f, 5.5f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar7, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillar7rev = transformation(-5.45f, -5.3f, 2.45f, 0.0f, 35.0f, 0.0f, 0.4f, -5.5f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar7rev, 1.0, 1.0, 1.0);
    //lombapillar 1st right pair left-right
    glm::mat4 modelUpPillar8 = transformation(4.6f, -0.8f, 1.65f, 0.0f, 150.0f, 0.0f, 0.4f, 7.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar8, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillar8rev = transformation(4.6f, -5.3f, 1.65f, 0.0f, 150.0f, 0.0f, 0.4f, -7.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar8rev, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillar9 = transformation(3.25f, -0.8f, 0.85f, 0.0f, 150.0f, 0.0f, 0.4f, 7.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar9, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillar9rev = transformation(3.25f, -5.3f, 0.85f, 0.0f, 150.0f, 0.0f, 0.4f, -7.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar9rev, 1.0, 1.0, 1.0);
    //lombapillar 2nd right pair left-right
    glm::mat4 modelUpPillar10 = transformation(6.65f, -0.8f, 3.3f, 0.0f, 145.0f, 0.0f, 0.4f, 5.5f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar10, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillar10rev = transformation(6.65f, -5.3f, 3.3f, 0.0f, 145.0f, 0.0f, 0.4f, -5.5f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar10rev, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillar11 = transformation(5.45f, -0.8f, 2.45f, 0.0f, 145.0f, 0.0f, 0.4f, 5.5f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar11, 1.0, 1.0, 1.0);
    glm::mat4 modelUpPillar11rev = transformation(5.45f, -5.3f, 2.45f, 0.0f, 145.0f, 0.0f, 0.4f, -5.5f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpPillar11rev, 1.0, 1.0, 1.0);

    //upper block left side 1st 2nd
    glm::mat4 modelUpblock = transformation(-4.6f, 6.2f, 1.65f, 0.0f, 30.0f, 0.0f, 1.96f, 0.3f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpblock, 1.0, 1.0, 1.0);
    glm::mat4 modelUpblockrev = transformation(-4.6f, -12.3f, 1.65f, 0.0f, 30.0f, 0.0f, 1.96f, -0.3f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpblockrev, 1.0, 1.0, 1.0);
    glm::mat4 modelUpblock2 = transformation(-6.65f, 4.7f, 3.3f, 0.0f, 35.0f, 0.0f, 1.87f, 0.3f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpblock2, 1.0, 1.0, 1.0);
    glm::mat4 modelUpblock2rev = transformation(-6.65f, -10.8f, 3.3f, 0.0f, 35.0f, 0.0f, 1.87f, -0.3f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpblock2rev, 1.0, 1.0, 1.0);

    //upper block right side 1st 2nd
    glm::mat4 modelUpblock3 = transformation(4.6f, 6.2f, 1.65f, 0.0f, 150.0f, 0.0f, 1.96f, 0.3f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpblock3, 1.0, 1.0, 1.0);
    glm::mat4 modelUpblock3rev = transformation(4.6f, -12.3f, 1.65f, 0.0f, 150.0f, 0.0f, 1.96f, -0.3f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpblock3rev, 1.0, 1.0, 1.0);
    glm::mat4 modelUpblock4 = transformation(6.65f, 4.7f, 3.3f, 0.0f, 145.0f, 0.0f, 1.87f, 0.3f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpblock4, 1.0, 1.0, 1.0);
    glm::mat4 modelUpblock4rev = transformation(6.65f, -10.8f, 3.3f, 0.0f, 145.0f, 0.0f, 1.87f, -0.3f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelUpblock4rev, 1.0, 1.0, 1.0);

    //mainbakablock
    //main-left
    glm::mat4 modelmainbakaPillar = transformation(-1.7f, 8.2f, 0.2f, 30.0f, 0.0f, 0.0f, 0.5f, 2.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelmainbakaPillar, 1.0, 1.0, 1.0);
    glm::mat4 modelmainbakaPillarrev = transformation(-1.7f, -14.2f, 0.2f, -30.0f, 0.0f, 0.0f, 0.5f, -2.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelmainbakaPillarrev, 1.0, 1.0, 1.0);
    //main-mid
    glm::mat4 modelmainbakaPillar2 = transformation(-0.15f, 8.2f, 0.2f, 30.0f, 0.0f, 0.0f, 0.5f, 2.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelmainbakaPillar2, 1.0, 1.0, 1.0);
    glm::mat4 modelmainbakaPillar2rev = transformation(-0.15f, -14.2f, 0.2f, -30.0f, 0.0f, 0.0f, 0.5f, -2.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelmainbakaPillar2rev, 1.0, 1.0, 1.0);
    //main-right
    glm::mat4 modelmainbakaPillar3 = transformation(1.4f, 8.2f, 0.2f, 30.0f, 0.0f, 0.0f, 0.5f, 2.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelmainbakaPillar3, 1.0, 1.0, 1.0);
    glm::mat4 modelmainbakaPillar3rev = transformation(1.4f, -14.2f, 0.2f, -30.0f, 0.0f, 0.0f, 0.5f, -2.0f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelmainbakaPillar3rev, 1.0, 1.0, 1.0);
    //mainupper
    glm::mat4 modelmainup = transformation(-1.7f, 9.6f, 1.157f, 0.0f, 0.0f, 0.0f, 3.6f, 0.35f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelmainup, 1.0, 1.0, 1.0);
    glm::mat4 modelmainuprev = transformation(-1.7f, -15.6f, 1.157f, 0.0f, 0.0f, 0.0f, 3.6f, -0.35f, 0.3f);
    drawCube(cubeVAO, lightingShader, modelmainuprev, 1.0, 1.0, 1.0);

    ////first stage
    //glm::mat4 modelFirstStage = transformation(-10.0f, -1.25f, -0.5f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 9.0f);
    //drawCube(cubeVAO, lightingShader, modelFirstStage, 0.8, 0.4, 0.2);
    //glm::mat4 modelFirstStage2 = transformation(-10.0f, -1.45f, -0.5f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 9.5f);
    //drawCube(cubeVAO, lightingShader, modelFirstStage2, 0.8, 0.4, 0.2);
    //glm::mat4 modelFirstStage3 = transformation(-10.0f, -1.65f, -0.5f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 10.0f);
    //drawCube(cubeVAO, lightingShader, modelFirstStage3, 0.8, 0.4, 0.2);
    //glm::mat4 modelFirstStage3rev = transformation(-10.0f, -3.05f, -0.5f, 0.0f, 0.0f, 0.0f, 20.0f, -1.75f, 10.0f);
    //drawCube(cubeVAO, lightingShader, modelFirstStage3rev, 0.8, 0.4, 0.2);

    ////second stage
    //glm::mat4 modelSecondStage = transformation(-12.50f, -1.85f, -0.5f, 0.0f, 0.0f, 0.0f, 25.0f, 0.2f, 14.5f);
    //drawCube(cubeVAO, lightingShader, modelSecondStage, 0.8, 0.4, 0.2);
    //glm::mat4 modelSecondStage2 = transformation(-12.50f, -2.05f, -0.5f, 0.0f, 0.0f, 0.0f, 25.0f, 0.2f, 15.0f);
    //drawCube(cubeVAO, lightingShader, modelSecondStage2, 0.8, 0.4, 0.2);
    //glm::mat4 modelSecondStage3 = transformation(-12.50f, -4.25f, -0.5f, 0.0f, 0.0f, 0.0f, 25.0f, 2.2f, 15.5f);
    //drawCube(cubeVAO, lightingShader, modelSecondStage3, 0.8, 0.4, 0.2);
    //glm::mat4 modelSecondStage4 = transformation(-12.50f, -2.25f, -0.5f, 0.0f, 0.0f, 0.0f, 25.0f, -0.6f, 15.5f);
    //drawCube(cubeVAO, lightingShader, modelSecondStage4, 0.8, 0.4, 0.2);

    ////third stage
    //glm::mat4 modelThirdStage = transformation(-10.0f, -2.45f, -0.5f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 24.5f);
    //drawCube(cubeVAO, lightingShader, modelThirdStage, 0.8, 0.4, 0.2);
    //glm::mat4 modelThirdStage2 = transformation(-10.0f, -2.65f, -0.5f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 25.0f);
    //drawCube(cubeVAO, lightingShader, modelThirdStage2, 0.8, 0.4, 0.2);
    //glm::mat4 modelThirdStage3 = transformation(-10.0f, -3.05f, -0.5f, 0.0f, 0.0f, 0.0f, 20.0f, 0.2f, 31.0f);
    //drawCube(cubeVAO, lightingShader, modelThirdStage3, 0.8, 0.4, 0.2);

    //grass
    /*glm::mat4 modelgrass = transformation(-10.0f, -3.05f, 23.5f, 0.0f, 0.0f, 0.0f, -200.0f, 0.2f, -24.0f);
    drawCube(cubeVAO, lightingShader, modelgrass, 1.0, 1.0, 1.0);
    glm::mat4 modelgrass2 = transformation(-11.0f, -3.05f, 0.5f, 0.0f, 40.0f, 0.0f, -180.5f, 0.2f, -240.0f);
    drawCube(cubeVAO, lightingShader, modelgrass2, 1.0, 1.0, 1.0);*/

    //nodi
    /*glm::mat4 modelnodi = transformation(12.5f, -3.08f, 0.5f, 0.0f, 40.0f, 0.0f, -18.5f, 0.2f, -240.0f);
    drawCube(cubeVAO, lightingShader, modelnodi, 0.0, 0.6, 1.0);*/
    

    //road
    //glm::mat4 modelroad = transformation(40.5f, -3.05f, 33.0f, 0.0f, 40.0f, 0.0f, 7.5f, 0.2f, -240.0f);
    //drawCube(cubeVAO, lightingShader, modelroad, 0.6, 0.9, 0.6);

    //wall
    glm::mat4 modelwall = transformation(21.0f, -3.05f, 0.0f, 0.0f, 40.0f, 0.0f, 0.4f, 6.0f, -240.0f);
    drawCube(cubeVAO, lightingShader, modelwall, 0.8, 0.8, 0.9);


    //large tree base
    glm::mat4 modelmaintreebasenorth = transformation(-15.0f, -4.05f, 12.5f, 0.0f, 0.0f, 0.0f, 5.0f, 3.0f, 0.4f);
    drawCube(cubeVAO, lightingShader, modelmaintreebasenorth, 1.0, 1.0, 1.0);
    glm::mat4 modelmaintreebaseeast = transformation(-15.0f, -4.05f, 12.5f, 0.0f, -90.0f, 0.0f, 5.4f, 3.0f, 0.4f);
    drawCube(cubeVAO, lightingShader, modelmaintreebaseeast, 1.0, 1.0, 1.0);
    glm::mat4 modelmaintreebasesouth = transformation(-15.0f, -4.05f, 17.5f, 0.0f, 0.0f, 0.0f, 5.0f, 3.0f, 0.4f);
    drawCube(cubeVAO, lightingShader, modelmaintreebasesouth, 1.0, 1.0, 1.0);
    glm::mat4 modelmaintreebasewest = transformation(-10.0f-0.39f, -4.05f, 17.9f, 0.0f, 90.0f, 0.0f, 5.4f, 3.0f, 0.4f);
    drawCube(cubeVAO, lightingShader, modelmaintreebasewest, 1.0, 1.0, 1.0);
    //tree base small left 1
    glm::mat4 modelsmallleft1treebasenorth = transformation(-14.0f, -4.05f, 19.5f, 0.0f, 0.0f, 0.0f, 3.0f, 1.5f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelsmallleft1treebasenorth, 1.0, 1.0, 1.0);
    glm::mat4 modelsmallleft1treebaseeast = transformation(-14.0f, -4.05f, 19.5f, 0.0f, -90.0f, 0.0f, 2.2f, 1.5f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelsmallleft1treebaseeast, 1.0, 1.0, 1.0);
    glm::mat4 modelsmallleft1treebasesouth = transformation(-14.0f, -4.05f, 21.5f, 0.0f, 0.0f, 0.0f, 3.0f, 1.5f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelsmallleft1treebasesouth, 1.0, 1.0, 1.0);
    glm::mat4 modelsmallleft1treebasewest = transformation(-11.0f-0.198f, -4.05f, 21.5f, 0.0f, 90.0f, 0.0f, 2.0f, 1.5f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelsmallleft1treebasewest, 1.0, 1.0, 1.0);
    //tree base small left 2
    glm::mat4 modelsmallleft2treebasenorth = transformation(-14.0f, -4.05f, 23.0f, 0.0f, 0.0f, 0.0f, 3.0f, 1.5f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelsmallleft2treebasenorth, 1.0, 1.0, 1.0);
    glm::mat4 modelsmallleft2treebaseeast = transformation(-14.0f, -4.05f, 23.0f, 0.0f, -90.0f, 0.0f, 2.2f, 1.5f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelsmallleft2treebaseeast, 1.0, 1.0, 1.0);
    glm::mat4 modelsmallleft2treebasesouth = transformation(-14.0f, -4.05f, 25.0f, 0.0f, 0.0f, 0.0f, 3.0f, 1.5f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelsmallleft2treebasesouth, 1.0, 1.0, 1.0);
    glm::mat4 modelsmallleft2treebasewest = transformation(-11.0f - 0.198f, -4.05f, 25.0f, 0.0f, 90.0f, 0.0f, 2.0f, 1.5f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelsmallleft2treebasewest, 1.0, 1.0, 1.0);
    //tree base small left 3
    glm::mat4 modelsmallleft3treebasenorth = transformation(-14.0f, -4.05f, 26.5f, 0.0f, 0.0f, 0.0f, 3.0f, 1.5f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelsmallleft3treebasenorth, 1.0, 1.0, 1.0);
    glm::mat4 modelsmallleft3treebaseeast = transformation(-14.0f, -4.05f, 26.5f, 0.0f, -90.0f, 0.0f, 2.2f, 1.5f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelsmallleft3treebaseeast, 1.0, 1.0, 1.0);
    glm::mat4 modelsmallleft3treebasesouth = transformation(-14.0f, -4.05f, 28.5f, 0.0f, 0.0f, 0.0f, 3.0f, 1.5f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelsmallleft3treebasesouth, 1.0, 1.0, 1.0);
    glm::mat4 modelsmallleft3treebasewest = transformation(-11.0f - 0.198f, -4.05f, 28.5f, 0.0f, 90.0f, 0.0f, 2.0f, 1.5f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelsmallleft3treebasewest, 1.0, 1.0, 1.0);

    //tree base middle 1
    glm::mat4 modelmiddle1treebasenorth = transformation(-0.75f, -4.05f, 18.0f, 0.0f, 0.0f, 0.0f, 1.5f, 2.0f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle1treebasenorth, 1.0, 1.0, 1.0);
    glm::mat4 modelmiddle1treebaseeast = transformation(-0.75f, -4.05f, 18.0f, 0.0f, -90.0f, 0.0f, 1.7f, 2.0f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle1treebaseeast, 1.0, 1.0, 1.0);
    glm::mat4 modelmiddle1treebasesouth = transformation(-0.75f, -4.05f, 19.5f, 0.0f, 0.0f, 0.0f, 1.5f, 2.0f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle1treebasesouth, 1.0, 1.0, 1.0);
    glm::mat4 modelmiddle1treebasewest = transformation(0.75f - 0.198f, -4.05f, 19.5f, 0.0f, 90.0f, 0.0f, 1.5f, 2.0f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle1treebasewest, 1.0, 1.0, 1.0);
    //tree base middle 2
    glm::mat4 modelmiddle2treebasenorth = transformation(-0.75f, -4.05f, 21.5f, 0.0f, 0.0f, 0.0f, 1.5f, 2.0f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle2treebasenorth, 1.0, 1.0, 1.0);
    glm::mat4 modelmiddle2treebaseeast = transformation(-0.75f, -4.05f, 21.5f, 0.0f, -90.0f, 0.0f, 1.7f, 2.0f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle2treebaseeast, 1.0, 1.0, 1.0);
    glm::mat4 modelmiddle2treebasesouth = transformation(-0.75f, -4.05f, 23.0f, 0.0f, 0.0f, 0.0f, 1.5f, 2.0f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle2treebasesouth, 1.0, 1.0, 1.0);
    glm::mat4 modelmiddle2treebasewest = transformation(0.75f - 0.198f, -4.05f, 23.0f, 0.0f, 90.0f, 0.0f, 1.5f, 2.0f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle2treebasewest, 1.0, 1.0, 1.0);
    //tree base middle 3
    glm::mat4 modelmiddle3treebasenorth = transformation(-0.75f, -3.05f, 25.0f, 0.0f, 0.0f, 0.0f, 1.5f, 0.6f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle3treebasenorth, 1.0, 1.0, 1.0);
    glm::mat4 modelmiddle3treebaseeast = transformation(-0.75f, -3.05f, 25.0f, 0.0f, -90.0f, 0.0f, 1.7f, 0.6f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle3treebaseeast, 1.0, 1.0, 1.0);
    glm::mat4 modelmiddle3treebasesouth = transformation(-0.75f, -3.05f, 26.5f, 0.0f, 0.0f, 0.0f, 1.5f, 0.6f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle3treebasesouth, 1.0, 1.0, 1.0);
    glm::mat4 modelmiddle3treebasewest = transformation(0.75f - 0.198f, -3.05f, 26.5f, 0.0f, 90.0f, 0.0f, 1.5f, 0.6f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle3treebasewest, 1.0, 1.0, 1.0);
    //tree base middle 4
    glm::mat4 modelmiddle4treebasenorth = transformation(-0.75f, -3.05f, 28.0f, 0.0f, 0.0f, 0.0f, 1.5f, 0.6f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle4treebasenorth, 1.0, 1.0, 1.0);
    glm::mat4 modelmiddle4treebaseeast = transformation(-0.75f, -3.05f, 28.0f, 0.0f, -90.0f, 0.0f, 1.7f, 0.6f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle4treebaseeast, 1.0, 1.0, 1.0);
    glm::mat4 modelmiddle4treebasesouth = transformation(-0.75f, -3.05f, 29.5f, 0.0f, 0.0f, 0.0f, 1.5f, 0.6f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle4treebasesouth, 1.0, 1.0, 1.0);
    glm::mat4 modelmiddle4treebasewest = transformation(0.75f - 0.198f, -3.05f, 29.5f, 0.0f, 90.0f, 0.0f, 1.5f, 0.6f, 0.2f);
    drawCube(cubeVAO, lightingShader, modelmiddle4treebasewest, 1.0, 1.0, 1.0);
    //rightjhobase
    glm::mat4 modelrightjhobasenorth = transformation(10.0f, -3.0f, 15.0f, 0.0f, 0.0f, 0.0f, 3.0f, 1.1f, 0.4f);
    drawCube(cubeVAO, lightingShader, modelrightjhobasenorth, 1.0, 1.0, 1.0);
    glm::mat4 modelrightjhobaseeast = transformation(10.001f, -3.0f, 15.0f, 0.0f, -90.0f, 0.0f, 15.499f, 1.1f, 0.4f);
    drawCube(cubeVAO, lightingShader, modelrightjhobaseeast, 1.0, 1.0, 1.0);
    glm::mat4 modelrightjhobasesouth = transformation(10.0f, -3.0f, 30.1f, 0.0f, 0.0f, 0.0f, 8.2f, 1.1f, 0.4f);
    drawCube(cubeVAO, lightingShader, modelrightjhobasesouth, 1.0, 1.0, 1.0);
    glm::mat4 modelrightjhobasewest = transformation(13.0f, -3.0f, 15.0f, 0.0f, -70.0f, 0.0f, 16.3f, 1.1f, 0.4f);
    drawCube(cubeVAO, lightingShader, modelrightjhobasewest, 1.0, 1.0, 1.0);

























 //   //draw curve
 //   glm::mat4 identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
 //   glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
 //   translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(0, 10, 10));
 //   rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
 //   rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
 //   rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
 //   scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3, 2.5, 3));
 //   modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
 //   lightingShader.setMat4("model", modelforCurve);
 //   lightingShader.use();
 //   lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
 //   lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
 //   lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
 //   lightingShader.setFloat("material.shininess", 32.0f);
 //   glBindVertexArray(bezierVAO);
 //   glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
 //// glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
 //   glBindVertexArray(0);


   


    //draw gach with curve
    glm::mat4 modelgachcurve= transformation(22.0f, -3.0f, 20.0f, 0.0f, 0.0f, 0.0f, 2.0f, 3.0f, 2.0f);
    lightingShader.setMat4("model", modelgachcurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    glm::mat4 modelgachchaunicurve = transformation(22.0f, 0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 5.0f, 3.0f, 5.0f);
    lightingShader.setMat4("model", modelgachchaunicurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.2f, 0.6f, 0.1f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.2f, 0.6f, 0.1f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachchauniVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    //gach, math side
    glm::mat4 modelgachcurve2 = transformation(-18.0f, -3.05f, -5.0f, 0.0f, 0.0f, 0.0f, 2.0f, 1.0f, 2.0f);
    lightingShader.setMat4("model", modelgachcurve2);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    glm::mat4 modelgachchaunicurve2 = transformation(-18.0f, -3.05f, -5.0f, 0.0f, 0.0f, 0.0f, 5.0f, 3.0f, 5.0f);
    lightingShader.setMat4("model", modelgachchaunicurve2);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.2f, 0.6f, 0.1f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.2f, 0.6f, 0.1f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    glm::mat4 modelgachcurve2mirror = transformation(-18.0f, -3.05f, -5.0f, 0.0f, 0.0f, 0.0f, 2.0f, -1.0f, 2.0f);
    lightingShader.setMat4("model", modelgachcurve2mirror);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    glm::mat4 modelgachchaunicurve2mirror = transformation(-18.0f, -3.05f, -5.0f, 0.0f, 0.0f, 0.0f, 5.0f, -3.0f, 5.0f);
    lightingShader.setMat4("model", modelgachchaunicurve2mirror);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.2f, 0.6f, 0.1f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.2f, 0.6f, 0.1f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    //gach 3, math side
    glm::mat4 modelgachcurve3 = transformation(-25.0f, -3.05f, -13.0f, 0.0f, 0.0f, 0.0f, 2.0f, 1.0f, 2.0f);
    lightingShader.setMat4("model", modelgachcurve3);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    glm::mat4 modelgachchaunicurve3 = transformation(-25.0f, -3.05f, -13.0f, 0.0f, 0.0f, 0.0f, 5.0f, 3.0f, 5.0f);
    lightingShader.setMat4("model", modelgachchaunicurve3);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.2f, 0.6f, 0.1f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.2f, 0.6f, 0.1f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    glm::mat4 modelgachcurve3mirror = transformation(-25.0f, -3.05f, -13.0f, 0.0f, 0.0f, 0.0f, 2.0f, -1.0f, 2.0f);
    lightingShader.setMat4("model", modelgachcurve3mirror);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    glm::mat4 modelgachchaunicurve3mirror = transformation(-25.0f, -3.05f, -13.0f, 0.0f, 0.0f, 0.0f, 5.0f, -3.0f, 5.0f);
    lightingShader.setMat4("model", modelgachchaunicurve3mirror);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.2f, 0.6f, 0.1f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.2f, 0.6f, 0.1f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);








    //jhopgach transformation(-15.0f, -4.05f, 12.51f, 0.0f, 0.0f, 0.0f, 5.0f, 2.8f, 5.0f);
    glm::mat4 modeljhopmaincurve = transformation(-12.5f, -1.3f, 15.0f, 0.0f, 0.0f, -20.0f, 0.5f, 0.7f, 0.5f);
    lightingShader.setMat4("model", modeljhopmaincurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmaincurve = transformation(-12.5 + .02f, -1.3f, 15.0f, 0.0f, 0.0f, -5.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmaincurve);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmaincurve = transformation(-12.5 - .02f, -1.3f, 15.0f, 0.0f, 0.0f, 10.0f, 0.5f, 0.6f, 0.5f);
    lightingShader.setMat4("model", modeljhopmaincurve);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    glm::mat4 modeljhopmainchaunicurve = transformation(-12.4f, -1.0f, 15.0f, 0.0f, 0.0f, -20.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmainchaunicurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.9f, 0.1f, 0.1f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.9f, 0.1f, 0.1f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(jhopchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    modeljhopmainchaunicurve = transformation(-12.5 + .02f, -0.8f, 15.0f, 0.0f, 0.0f, -5.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmainchaunicurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(jhopchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmainchaunicurve = transformation(-12.5 - .02f, -1.2f, 15.0f, 0.0f, 0.0f, 10.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmainchaunicurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 0.0f, 1.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 0.0f, 1.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(jhopchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    //jhop left 1 transformation(-14.0f, -4.05f, 19.51f, 0.0f, 0.0f, 0.0f, 3.0f, 1.4f, 2.0f);
    modeljhopmaincurve = transformation(-12.5f, -2.65f, 20.51f, 0.0f, 0.0f, -20.0f, 0.5f, 0.7f, 0.5f);
    lightingShader.setMat4("model", modeljhopmaincurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmaincurve = transformation(-12.5 + .02f, -2.65f, 20.51f, 0.0f, 0.0f, -5.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmaincurve);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmaincurve = transformation(-12.5 - .02f, -2.65f, 20.51f, 0.0f, 0.0f, 10.0f, 0.5f, 0.6f, 0.5f);
    lightingShader.setMat4("model", modeljhopmaincurve);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmainchaunicurve = transformation(-12.5f, -2.35f, 20.51f, 0.0f, 0.0f, -20.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmainchaunicurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.9f, 0.1f, 0.1f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.9f, 0.1f, 0.1f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(jhopchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    modeljhopmainchaunicurve = transformation(-12.5 + .02f, -2.15f, 20.51f, 0.0f, 0.0f, -5.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmainchaunicurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(jhopchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmainchaunicurve = transformation(-12.5 - .02f, -2.55f, 20.51f, 0.0f, 0.0f, 10.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmainchaunicurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 0.0f, 1.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 0.0f, 1.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(jhopchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    //jhop left 2 transformation(-14.0f, -4.05f, 19.51f, 0.0f, 0.0f, 0.0f, 3.0f, 1.4f, 2.0f);
    modeljhopmaincurve = transformation(-12.5f, -2.65f, 24.00f, 0.0f, 0.0f, -20.0f, 0.5f, 0.7f, 0.5f);
    lightingShader.setMat4("model", modeljhopmaincurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmaincurve = transformation(-12.5 + .02f, -2.65f, 24.00f, 0.0f, 0.0f, -5.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmaincurve);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmaincurve = transformation(-12.5 - .02f, -2.65f, 24.00f, 0.0f, 0.0f, 10.0f, 0.5f, 0.6f, 0.5f);
    lightingShader.setMat4("model", modeljhopmaincurve);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmainchaunicurve = transformation(-12.5f, -2.35f, 24.00f, 0.0f, 0.0f, -20.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmainchaunicurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.9f, 0.1f, 0.1f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.9f, 0.1f, 0.1f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(jhopchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    modeljhopmainchaunicurve = transformation(-12.5 + .02f, -2.15f, 24.00f, 0.0f, 0.0f, -5.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmainchaunicurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(jhopchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmainchaunicurve = transformation(-12.5 - .02f, -2.55f, 24.00f, 0.0f, 0.0f, 10.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmainchaunicurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 0.0f, 1.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 0.0f, 1.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(jhopchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    //jhop left 3
    modeljhopmaincurve = transformation(-12.5f, -2.65f, 27.50f, 0.0f, 0.0f, -20.0f, 0.5f, 0.7f, 0.5f);
    lightingShader.setMat4("model", modeljhopmaincurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmaincurve = transformation(-12.5 + .02f, -2.65f, 27.50f, 0.0f, 0.0f, -5.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmaincurve);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmaincurve = transformation(-12.5 - .02f, -2.65f, 27.50f, 0.0f, 0.0f, 10.0f, 0.5f, 0.6f, 0.5f);
    lightingShader.setMat4("model", modeljhopmaincurve);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmainchaunicurve = transformation(-12.5f, -2.35f, 27.50f, 0.0f, 0.0f, -20.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmainchaunicurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.9f, 0.1f, 0.1f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.9f, 0.1f, 0.1f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(jhopchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    modeljhopmainchaunicurve = transformation(-12.5 + .02f, -2.15f, 27.50f, 0.0f, 0.0f, -5.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmainchaunicurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(jhopchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    modeljhopmainchaunicurve = transformation(-12.5 - .02f, -2.55f, 27.50f, 0.0f, 0.0f, 10.0f, 0.5f, 0.8f, 0.5f);
    lightingShader.setMat4("model", modeljhopmainchaunicurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 0.0f, 1.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 0.0f, 1.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(jhopchauniVAO);
    glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);


    //jhop majher -0.75f, -4.05f, 18.0f, 0.0f, 0.0f, 0.0f, 1.5f, 2.0f, 0.2f
    /*modeljhopmaincurve = transformation(0.0f, -2.23f, 18.75f, 0.0f, 0.0f, 0.0f, 0.2f, 0.7f, 0.2f);
    lightingShader.setMat4("model", modeljhopmaincurve);
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.5f, 0.2f, 0.0f));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(gachcurveVAO);
    glDrawElements(GL_TRIANGLE_STRIP, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);*/


















    ////foam
    //model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //translate2 = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //translate2 = glm::translate(model, glm::vec3(0, baseHeight, 0));
    //scale = glm::scale(model, glm::vec3(width, 0.06, length));
    //translate = glm::translate(model, glm::vec3(-0.5, -14.0, -0.55));
    //model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);

    ////foam2
    //model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //translate2 = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //translate2 = glm::translate(model, glm::vec3(0, baseHeight, 0));
    //scale = glm::scale(model, glm::vec3(width, 0.06, length));
    //translate = glm::translate(model, glm::vec3(-0.5, -13.0, -0.60));
    //model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);

    ////right tower
    //model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //translate2 = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //translate2 = glm::translate(model, glm::vec3(3.7, baseHeight + 1 * 0.06-1, -0.2));
    //scale = glm::scale(model, glm::vec3(1.5, 5, 0.2));
    //translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    //model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 1.0f, 1.0f, 1.0f);

    ////left tower
    //model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //translate2 = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //translate2 = glm::translate(model, glm::vec3(-3.7, baseHeight + 1 * 0.06 - 1, -0.2));
    //scale = glm::scale(model, glm::vec3(1.5, 5, 0.2));
    //translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    //model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 1.0f, 1.0f, 1.0f);

    //model = glm::mat4(1.0f);
    //translate = glm::translate(model, glm::vec3(-4.0, 3.0, -5.0));
    //model = alTogether * translate;
    //drawCube(cubeVAO, lightingShader, model, 1.0, 1.0,1.0);

    ////ekti bostu
    //glm::mat4 modelEktiBostu = transformation(2.29 * 2.80f, -0.30f, 6.0f, 0.0f, 90.0f, 0.0f, 14.0f, 4.8f, 0.0f);
    //drawCube(cubeVAO,lightingShader, modelEktiBostu, 0,0.7,0);


    ////middle tower
    //model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //translate2 = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //translate2 = glm::translate(model, glm::vec3(0, baseHeight + 1 * 0.06-1, -(length / 2 - 0.025) + blanketLength / 2));
    //scale = glm::scale(model, glm::vec3(2.5, 6, 0.2));
    //translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    //model = alTogether * translate2 * scale * translate;
    ////drawCube(cubeVAO, lightingShader, model, 1.0, 0.5, 0.0);
    //drawCube(cubeVAO, lightingShader, model, 0.541, 0.169, 0.886);

    //head
    /*model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, 0, (length / 2 - 0.02 / 2) + 0.02));
    scale = glm::scale(model, glm::vec3(width, headHeight, 0.02));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);*/



    


}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    //dlighton
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        if (directionalLightOn)
        {
            directionalLight.turnOff();

            directionalLightOn = !directionalLightOn;
        }
        else
        {
            directionalLight.turnOn();

            directionalLightOn = !directionalLightOn;
        }
    }
    //bool pointLightFirstHalf = true;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        if (pointLightFirstHalf)
        {

            pointlight1.turnOff();
            pointlight2.turnOff();
            //pointlight3.turnDiffuseOff();
            //pointlight4.turnDiffuseOff();
            pointLightFirstHalf = !pointLightFirstHalf;
        }
        else
        {

            pointlight1.turnOn();
            pointlight2.turnOn();
            //pointlight3.turnDiffuseOn();
            //pointlight4.turnDiffuseOn();
            pointLightFirstHalf = !pointLightFirstHalf;
        }

    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        if (pointLightFirstHalf)
        {

            pointlight3.turnOff();
            pointlight4.turnOff();
            //pointlight3.turnDiffuseOff();
            //pointlight4.turnDiffuseOff();
            pointLightFirstHalf = !pointLightFirstHalf;
        }
        else
        {

            pointlight3.turnOn();
            pointlight4.turnOn();
            //pointlight3.turnDiffuseOn();
            //pointlight4.turnDiffuseOn();
            pointLightFirstHalf = !pointLightFirstHalf;
        }

    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        if (spotLightOn)
        {
            spotLight.turnOff();

            spotLightOn = !spotLightOn;
        }
        else
        {
            spotLight.turnOn();

            spotLightOn = !spotLightOn;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        if (ambientToggle)
        {

            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            pointlight3.turnAmbientOff();
            pointlight4.turnAmbientOff();
            directionalLight.turnAmbientOff();
            spotLight.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {

            pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
            pointlight3.turnAmbientOn();
            pointlight4.turnAmbientOn();
            directionalLight.turnAmbientOn();
            spotLight.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        if (diffuseToggle)
        {
            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            directionalLight.turnDiffuseOff();
            spotLight.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {
            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            pointlight4.turnDiffuseOn();
            directionalLight.turnDiffuseOn();
            spotLight.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        if (specularToggle)
        {
            
            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            pointlight3.turnSpecularOff();
            pointlight4.turnSpecularOff();
            directionalLight.turnSpecularOff();
            spotLight.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {
            
            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            pointlight3.turnSpecularOn();
            pointlight4.turnSpecularOn();
            directionalLight.turnSpecularOn();
            spotLight.turnSpecularOn();
            specularToggle = !specularToggle;
        }


        
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        pointlight1.turnAmbientOn();
        pointlight2.turnAmbientOn();
        pointlight3.turnAmbientOn();
        pointlight4.turnAmbientOn();
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        pointlight1.turnDiffuseOn();
        pointlight2.turnDiffuseOn();
        pointlight3.turnDiffuseOn();
        pointlight4.turnDiffuseOn();
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        pointlight1.turnSpecularOn();
        pointlight2.turnSpecularOn();
        pointlight3.turnSpecularOn();
        pointlight4.turnSpecularOn();
    }

    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        pointlight1.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight1.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight1.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight2.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight2.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight2.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight3.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight3.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight3.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight4.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight4.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight4.specular = glm::vec3(0.0, 1.0, 0.0);

    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(YAW_R, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(YAW_L, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(Pitch_U, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(Pitch_D, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(Roll_L, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(Roll_R, deltaTime);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}






unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}




//Bezier Curve Header Function

long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}

unsigned int hollowBezier(GLfloat ctrlpoints[], int L)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal


    const float dtheta = 2 * pi / ntheta;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = (x - 0) * lengthInv;
            ny = (y - y) * lengthInv;
            nz = (z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            theta += dtheta;
        }
    }

    // generate index list of triangles
    // k1--k1+1
    // |  / |
    // | /  |
    // k2--k2+1

    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // k1 => k2 => k1+1
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            // k1+1 => k2 => k2+1
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);
    }

    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // create VBO to copy vertex data to VBO
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
        (unsigned int)vertices.size() * sizeof(float), // data size, # of bytes
        vertices.data(),   // ptr to vertex data
        GL_STATIC_DRAW);                   // usage

    // create EBO to copy index data
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
        (unsigned int)indices.size() * sizeof(unsigned int),             // data size, # of bytes
        indices.data(),               // ptr to index data
        GL_STATIC_DRAW);                   // usage

    // activate attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // set attrib arrays with stride and offset
    int stride = 24;     // should be 24 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

    // unbind VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
    
    
}