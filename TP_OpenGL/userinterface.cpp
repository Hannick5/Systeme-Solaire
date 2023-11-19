#include "userinterface.h"

UserInterface::UserInterface(GLFWwindow* window) : window(window) {
    // Initialiser ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // Style ImGui (facultatif)
    ImGui::StyleColorsDark();
}

UserInterface::~UserInterface() {
    // Nettoyer ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UserInterface::render() {
    // Nouveau frame ImGui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Définir la position de la fenêtre ImGui en haut à gauche
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);

    // Commencer à créer la fenêtre ImGui avec le flag pour un redimensionnement automatique en fonction du contenu
    ImGui::Begin("Interface", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    // Ajouter un slider pour ajuster la vitesse des planètes
    ImGui::SliderFloat("Vitesse de rotation", &rotationSpeedMultiplier, 0.0f, 30.0f);

    // Terminer la création de la fenêtre ImGui
    ImGui::End();

    // Rendre l'interface ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
