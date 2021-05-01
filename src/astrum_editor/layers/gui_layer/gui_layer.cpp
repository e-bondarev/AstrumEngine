#include "gui_layer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "core/window/window.h"

#include "../graphics_layer/graphics_layer.h"

#include "assets/asset.h"

GUILayer::GUILayer(Layers* layers) : m_Layers { layers }
{
    A_DEBUG_LOG_OUT("[Call] GUI constructor");
}

GUILayer::~GUILayer()
{
    A_DEBUG_LOG_OUT("[Call] GUI destructor");
}

void GUILayer::OnAttach()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;

    io.IniFilename = ASTRUM_ROOT "imgui.ini";

	ImGui_ImplGlfw_InitForOpenGL(Window::GetGlfwWindow(), true);
	ImGui_ImplOpenGL3_Init();

    m_Dockspace = std::make_unique<Dockspace>();
    m_Scene     = std::make_unique<Scene>();
    m_Viewport  = std::make_unique<Viewport>();
    m_Inspector = std::make_unique<Inspector>();
    m_Assets    = std::make_unique<Assets>();
}

void GUILayer::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUILayer::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backupCurrentContext = glfwGetCurrentContext();

		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();

		glfwMakeContextCurrent(backupCurrentContext);
	}
}

void GUILayer::OnUpdate()
{
    NewFrame();
    
    m_Dockspace->Render();
    m_Scene->Render();
    m_Viewport->Render(m_Layers->Graphics->GetRenderTarget());
    m_Inspector->Render();
    m_Assets->Render();

    Render();   
}