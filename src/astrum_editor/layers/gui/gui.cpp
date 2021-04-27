#include "gui.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "elements/dockspace/dockspace.h"
#include "elements/scene/scene.h"
#include "elements/viewport/viewport.h"
#include "elements/inspector/inspector.h"

#include "core/window/window.h"

GUI::GUI()
{
    A_DEBUG_LOG_OUT("[Call] GUI constructor");
}

GUI::~GUI()
{
    A_DEBUG_LOG_OUT("[Call] GUI destructor");
}

void GUI::init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplGlfw_InitForOpenGL(Window::getGlfwWindow(), true);
	ImGui_ImplOpenGL3_Init();

    guiElements.emplace_back(std::make_unique<Dockspace>());
    guiElements.emplace_back(std::make_unique<Scene>());
    guiElements.emplace_back(std::make_unique<Viewport>());
    guiElements.emplace_back(std::make_unique<Inspector>());
}

void GUI::newFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUI::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();

		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();

		glfwMakeContextCurrent(backup_current_context);
	}
}

void GUI::update()
{
    newFrame();

    for (auto& element : guiElements)
    {
        element->render();
    }

    render();   
}