#pragma once
#include "Hazel/Core/Layer.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

class ImGuiLayer
{
public:
    ImGuiLayer();
    ~ImGuiLayer() = default;
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Event &e) override;
    void Begin();
    void End();
    void BlockEvents(bool block) { m_BlockEvents = block; }
    void SetDarkThemeColors();

private:
    bool m_BlockEvents = true;
    float m_Time = 0.0f;
}