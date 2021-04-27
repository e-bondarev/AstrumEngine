#include "gui.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "core/window/window.h"

#include "../graphics/graphics.h"

GUI::GUI(Layers* _layers) : layers { _layers }
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

    dockspace = std::make_unique<Dockspace>();
    scene     = std::make_unique<Scene>();
    viewport  = std::make_unique<Viewport>();
    inspector = std::make_unique<Inspector>();
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
    
    dockspace->render();
    scene->render();
    viewport->render(layers->graphics->getRenderTargetTexture());
    inspector->render();

    render();   
}