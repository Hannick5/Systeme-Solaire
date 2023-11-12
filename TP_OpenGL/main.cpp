#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>
#include <math.h>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"
#include "navigationcontrols.h"
#include "ambientlight.h"
#include "pointlight.h"


using namespace std;

int main()
{
    string path = "/home/hannick/Téléchargements/TP_OpenGL";
    const char* pathObj = "/home/hannick/Téléchargements/TP_OpenGL/obj";
/////////////////////////Initialisation de GLFW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }


    glfwWindowHint(GLFW_SAMPLES, 4); //antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //version core

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);


/////////////////////////Ouverture de la fenêtre/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //définition de la taille de la fenêtre
    int width=600;
    int height=600;

    //On récupère les dimensions de l'écran pour créer la fenètre
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(primary,nullptr,nullptr, &width, &height);

    //Enfin on crée la fenêtre
    GLFWwindow* window = glfwCreateWindow(width,height,"OpenGL_API",NULL,NULL);
    glfwSwapInterval(1);
    //On vérifie que l'initialisation a bien marché
    if (window==NULL){
        fprintf(stderr, "Erreur lors de la création de la fénêtre\n");
        glfwTerminate();
        return -1;
    }

    //Enfin on définit la fenêtre créée comme la fenêtre sur laquelle on va dessiner
    glfwMakeContextCurrent(window);



/////////////////////////Initialisation de GLEW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Initialisation de GLEW
    glewExperimental=true;
    if (glewInit() != GLEW_OK){
        fprintf(stderr, "Erreur lors de l'initialisation de GLEW\n");
        return -1;
    }

/////////////////////////On crée un Renderer/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Renderer renderer;

/////////////////////////On crée un Shader/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Shader shader(path+"/shaders/SimpleVertexShader.vertexshader", path+"/shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();
    Shader shaderSun(path+"/shaders/SunVertexShader.vertexshader", path+"/shaders/SunFragmentShader.fragmentshader");
/////////////////////////On crée un vertex array/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VertexArray va;
    va.Bind();

/////////////////////////On crée la camera et les contrôles/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Camera cam(width, height);
    NavigationControls controls(window, &cam);
    controls.setSpeed(30.f);

/////////////////////////Création des formes à afficher/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Échelles des planètes
    float scaleSun = 3.0f;
    float scaleMercury = 0.383f;
    float scaleVenus = 0.949f;
    float scaleEarth = 1.0f;
    float scaleMoon = 0.3f;
    float scaleMars = 0.532f;
    float scaleJupiter = 11.209f;
    float scaleSaturn = 9.449f;
    float scaleUranus = 4.007f;
    float scaleNeptune = 3.883f;

    Object espace("/home/hannick/Téléchargements/TP_OpenGL/obj/sphere.obj", path + "/textures/2k_stars_milky_way.jpg", glm::vec3(900.0f));
    // Objets pour les planètes
    Object soleil("/home/hannick/Téléchargements/TP_OpenGL/obj/sphere.obj", path + "/textures/2k_sun.jpg", glm::vec3(scaleSun));
    Object mercure("/home/hannick/Téléchargements/TP_OpenGL/obj/sphere.obj", path + "/textures/2k_mercury.jpg", glm::vec3(scaleMercury));
    Object venus("/home/hannick/Téléchargements/TP_OpenGL/obj/sphere.obj", path + "/textures/2k_venus_atmosphere.jpg", glm::vec3(scaleVenus));
    Object terre("/home/hannick/Téléchargements/TP_OpenGL/obj/sphere.obj", path + "/textures/2k_earth_daymap.jpg", glm::vec3(scaleEarth));
    Object mars("/home/hannick/Téléchargements/TP_OpenGL/obj/sphere.obj", path + "/textures/2k_mars.jpg", glm::vec3(scaleMars));
    Object jupiter("/home/hannick/Téléchargements/TP_OpenGL/obj/sphere.obj", path + "/textures/2k_jupiter.jpg", glm::vec3(scaleJupiter));
    Object saturne("/home/hannick/Téléchargements/TP_OpenGL/obj/sphere.obj", path + "/textures/2k_saturn.jpg", glm::vec3(scaleSaturn));
    Object saturneRing("/home/hannick/Téléchargements/TP_OpenGL/obj/ring.obj", path + "/textures/2k_saturn.jpg", glm::vec3(scaleSaturn));
    Object uranus("/home/hannick/Téléchargements/TP_OpenGL/obj/sphere.obj", path + "/textures/2k_uranus.jpg", glm::vec3(scaleUranus));
    Object neptune("/home/hannick/Téléchargements/TP_OpenGL/obj/sphere.obj", path + "/textures/2k_neptune.jpg", glm::vec3(scaleNeptune));
    Object lune("/home/hannick/Téléchargements/TP_OpenGL/obj/sphere.obj", path + "/textures/2k_moon.jpg", glm::vec3(scaleMoon));
    
/////////////////////////Création de la matrice MVP/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cam.computeMatrices(width, height);
    glm::mat4 m = soleil.getModelMatrix();
    glm::mat4 v = cam.getViewMatrix();
    glm::mat4 p = cam.getProjectionMatrix();

    glm::mat4 mvp = p*v*m;

    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);
/////////////////////////Lumière/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PointLight pointLight(soleil.position, glm::vec3(1.0f, 1.0f, 1.0f), 50.0f);


/////////////////////////Boucle de rendu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Assure que l'on peut capturer les touche de clavier
glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

//On indique la couleur de fond
glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

//On autorise les tests de profondeur
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);

float lastTime = glfwGetTime();
float currentTime, deltaTime;

// Définir la distance entre o et o2
float distanceSoleilMercure = 0.39f;   // 0.39 UA
float distanceSoleilVenus = 0.72f;     // 0.72 UA
float distanceSoleilTerre = 1.0f;      // 1.0 UA
float distanceTerreLune = 0.2f;
float distanceSoleilMars = 1.52f;      // 1.52 UA
float distanceSoleilJupiter = 5.2f;    // 5.2 UA
float distanceSoleilSaturne = 9.58f;   // 9.58 UA
float distanceSoleilUranus = 19.22f;   // 19.22 UA
float distanceSoleilNeptune = 30.05f;  // 30.05 UA

float scale = 10.0f;  // Échelle : 1 unité = 1000 km

float distanceSoleilMercureScaled = distanceSoleilMercure * scale;
float distanceSoleilVenusScaled = distanceSoleilVenus * scale;
float distanceSoleilTerreScaled = distanceSoleilTerre * scale;
float distanceSoleilMarsScaled = distanceSoleilMars * scale;
float distanceSoleilJupiterScaled = distanceSoleilJupiter * scale;
float distanceSoleilSaturneScaled = distanceSoleilSaturne * scale;
float distanceSoleilUranusScaled = distanceSoleilUranus * scale;
float distanceSoleilNeptuneScaled = distanceSoleilNeptune * scale;
float distanceTerreLuneScaled = distanceTerreLune * scale;

float rotationSpeedTerre = 1.0f; // Facteur de vitesse de rotation pour la Terre
float rotationSpeedMercure = 1.5f; // Facteur de vitesse de rotation pour Mercure
float rotationSpeedVenus = 0.7f; // Facteur de vitesse de rotation pour Vénus
float rotationSpeedMars = 0.9f; // Facteur de vitesse de rotation pour Mars
float rotationSpeedJupiter = 0.3f; // Facteur de vitesse de rotation pour Jupiter
float rotationSpeedSaturne = 0.2f; // Facteur de vitesse de rotation pour Saturne
float rotationSpeedUranus = 0.1f; // Facteur de vitesse de rotation pour Uranus
float rotationSpeedNeptune = 0.1f; // Facteur de vitesse de rotation pour Neptune
float rotationSpeedLune = 2.0f; // Facteur de vitesse de rotation pour la Lune

Object circleMercure("/home/hannick/Téléchargements/TP_OpenGL/obj/circle.obj", path + "/textures/circle.jpg", glm::vec3(distanceSoleilMercureScaled - 0.1f * distanceSoleilMercureScaled));
circleMercure.position = soleil.position;

Object circleVenus("/home/hannick/Téléchargements/TP_OpenGL/obj/circle.obj", path + "/textures/circle.jpg", glm::vec3(distanceSoleilVenusScaled - 0.1f * distanceSoleilVenusScaled));
circleVenus.position = soleil.position;

Object circleTerre("/home/hannick/Téléchargements/TP_OpenGL/obj/circle.obj", path + "/textures/circle.jpg", glm::vec3(distanceSoleilTerreScaled - 0.1f * distanceSoleilTerreScaled));
circleTerre.position = soleil.position;

Object circleMars("/home/hannick/Téléchargements/TP_OpenGL/obj/circle.obj", path + "/textures/circle.jpg", glm::vec3(distanceSoleilMarsScaled - 0.1f * distanceSoleilMarsScaled));
circleMars.position = soleil.position;

Object circleJupiter("/home/hannick/Téléchargements/TP_OpenGL/obj/circle.obj", path + "/textures/circle.jpg", glm::vec3(distanceSoleilJupiterScaled - 0.1f * distanceSoleilJupiterScaled));
circleJupiter.position = soleil.position;

Object circleSaturne("/home/hannick/Téléchargements/TP_OpenGL/obj/circle.obj", path + "/textures/circle.jpg", glm::vec3(distanceSoleilSaturneScaled - 0.1f * distanceSoleilSaturneScaled));
circleSaturne.position = soleil.position;

Object circleUranus("/home/hannick/Téléchargements/TP_OpenGL/obj/circle.obj", path + "/textures/circle.jpg", glm::vec3(distanceSoleilUranusScaled - 0.1f * distanceSoleilUranusScaled));
circleUranus.position = soleil.position;

Object circleNeptune("/home/hannick/Téléchargements/TP_OpenGL/obj/circle.obj", path + "/textures/circle.jpg", glm::vec3(distanceSoleilNeptuneScaled - 0.1f * distanceSoleilNeptuneScaled));
circleNeptune.position = soleil.position;


while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)){

    currentTime = glfwGetTime();
    deltaTime = currentTime-lastTime;
    lastTime = currentTime;

    //soleil.rotationAngles.y=currentTime;

    // Faire tourner o2 autour de o
    
    terre.rotateAround(soleil, currentTime * rotationSpeedTerre, distanceSoleilTerreScaled);
    mercure.rotateAround(soleil, currentTime * rotationSpeedMercure, distanceSoleilMercureScaled);
    venus.rotateAround(soleil, currentTime * rotationSpeedVenus, distanceSoleilVenusScaled);
    mars.rotateAround(soleil, currentTime * rotationSpeedMars, distanceSoleilMarsScaled);
    jupiter.rotateAround(soleil, currentTime * rotationSpeedJupiter, distanceSoleilJupiterScaled);
    saturne.rotateAround(soleil, currentTime * rotationSpeedSaturne, distanceSoleilSaturneScaled);
    uranus.rotateAround(soleil, currentTime * rotationSpeedUranus, distanceSoleilUranusScaled);
    neptune.rotateAround(soleil, currentTime * rotationSpeedNeptune, distanceSoleilNeptuneScaled);
    saturneRing.rotateAround(saturne, 0, 0);
    lune.rotateAround(terre, currentTime * rotationSpeedLune, distanceTerreLuneScaled);

    controls.update(deltaTime, &shader);
    cam.computeMatrices(width, height);

    
    v = cam.getViewMatrix();
    p = cam.getProjectionMatrix();

    renderer.Clear();

    shader.Bind();

    shader.setUniform3fv("cameraPosition_worldspace", cam.position);

    pointLight.Bind(&shader);
    
    m = terre.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);

    renderer.Draw(va, terre, shader);

    // Pour Mercure
    m = circleMercure.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);
    renderer.Draw(va, circleMercure, shader);

    // Pour Venus
    m = circleVenus.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);
    renderer.Draw(va, circleVenus, shader);

    // Pour Terre
    m = circleTerre.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);
    renderer.Draw(va, circleTerre, shader);

    // Pour Mars
    m = circleMars.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);
    renderer.Draw(va, circleMars, shader);

    // Pour Jupiter
    m = circleJupiter.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);
    renderer.Draw(va, circleJupiter, shader);

    // Pour Saturne
    m = circleSaturne.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);
    renderer.Draw(va, circleSaturne, shader);

    // Pour Uranus
    m = circleUranus.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);
    renderer.Draw(va, circleUranus, shader);

    // Pour Neptune
    m = circleNeptune.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);
    renderer.Draw(va, circleNeptune, shader);


    m = lune.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);

    renderer.Draw(va, lune, shader);

    m = venus.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);

    renderer.Draw(va, venus, shader);

    m = mercure.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);

    renderer.Draw(va, mercure, shader);

    m = jupiter.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);

    renderer.Draw(va, jupiter, shader);

    m = neptune.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);

    renderer.Draw(va, neptune, shader);

    m = mars.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);

    renderer.Draw(va, mars, shader);

    m = saturne.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);

    renderer.Draw(va, saturne, shader);

    m = saturneRing.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);

    renderer.Draw(va, saturneRing, shader);

    m = uranus.getModelMatrix();
    mvp = p * v * m;
    shader.setUniformMat4f("MVP", mvp);
    shader.setUniformMat4f("M", m);

    renderer.Draw(va, uranus, shader);

    shader.Unbind();

    shaderSun.Bind();

    m = soleil.getModelMatrix();
    mvp = p*v*m;
    shaderSun.setUniformMat4f("MVP", mvp);
    shaderSun.setUniform3fv("pointLightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    renderer.Draw(va, soleil, shaderSun);

    m = espace.getModelMatrix();
    mvp = p * v * m;
    shaderSun.setUniformMat4f("MVP", mvp);
    shaderSun.setUniform3fv("pointLightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    renderer.Draw(va, espace, shaderSun);

    shaderSun.Unbind();

    //Swap buffers : frame refresh
    glfwSwapBuffers(window);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << error << std::endl;
    }
    //get the events
    glfwPollEvents();
}
glfwTerminate();

return 0;
}



