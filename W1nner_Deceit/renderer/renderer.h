#pragma once

ImFont* m_default_font;

void begin_frame()
{
	ImGuiIO io = ImGui::GetIO();
	ImGui_ImplDX11_NewFrame();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
	ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
	ImGui::Begin(xor_a("##frame"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);
	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);
}

void end_frame()
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->PushClipRectFullScreen();
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
}

inline void render_rect(const ImVec2& from, const ImVec2& to, float* color, float rounding, uint32_t roundingCornersFlags, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	float r = color[0];
	float g = color[1];
	float b = color[2];
	float a = color[3];

	window->DrawList->AddRect(from, to, ImGui::GetColorU32(ImVec4(r, g, b, a)), rounding, roundingCornersFlags, thickness);
}

inline void render_text_default(const ImVec2& from, const char* text, float* color)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	float r = color[0];
	float g = color[1];
	float b = color[2];
	float a = color[3];

	window->DrawList->AddText(from, ImGui::GetColorU32(ImVec4(r, g, b, a)), text);
}

void render_border(float x, float y, float w, float h, float* color)
{
	ImGuiWindow *windowDrawList = ImGui::GetCurrentWindow();

	float r = color[0];
	float g = color[1];
	float b = color[2];
	float a = color[3];

	windowDrawList->DrawList->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::GetColorU32(ImVec4(r, g, b, a)));
}

void render_box(float x, float y, float w, float h, float* color)
{
	ImGuiWindow *windowDrawList = ImGui::GetCurrentWindow();

	float r = color[0];
	float g = color[1];
	float b = color[2];
	float a = color[3];

	windowDrawList->DrawList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::GetColorU32(ImVec4(r, g, b, a)));
}

void __fastcall render_line(const ImVec2& from, const ImVec2& to, float* color, float thickness = 1.f)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	float r = color[0];
	float g = color[1];
	float b = color[2];
	float a = color[3];

	window->DrawList->AddLine(from, to, ImGui::GetColorU32(ImVec4(r, g, b, a)), thickness);
}

float render_text(const std::string& text, const ImVec2& pos, float size, float* color, bool center)
{
	ImGuiWindow *windowDrawList = ImGui::GetCurrentWindow();

	float a = color[3];
	float r = color[0];
	float g = color[1];
	float b = color[2];

	std::stringstream steam(text);
	std::string line;

	float y = 0.0f;
	int i = 0;

	while (std::getline(steam, line))
	{
		ImVec2 textSize = m_default_font->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());
		if (center)
		{
			windowDrawList->DrawList->AddText(m_default_font, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a)), line.c_str());
			windowDrawList->DrawList->AddText(m_default_font, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a)), line.c_str());
			windowDrawList->DrawList->AddText(m_default_font, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a)), line.c_str());
			windowDrawList->DrawList->AddText(m_default_font, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a)), line.c_str());
			windowDrawList->DrawList->AddText(m_default_font, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(r, g, b, a)), line.c_str());
		}
		else
		{
			windowDrawList->DrawList->AddText(m_default_font, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a)), line.c_str());
			windowDrawList->DrawList->AddText(m_default_font, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a)), line.c_str());
			windowDrawList->DrawList->AddText(m_default_font, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a)), line.c_str());
			windowDrawList->DrawList->AddText(m_default_font, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a)), line.c_str());
			windowDrawList->DrawList->AddText(m_default_font, size, ImVec2(pos.x, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(r, g, b, a)), line.c_str());
		}
		y = pos.y + textSize.y * (i + 1);
		i++;
	}
	return y;
}
void __fastcall render_health(float X, float Y, float W, float H, float Health, float MaxHealth)
{
	uint32_t backcolor = 0x55010101;
	float progress = Health / (MaxHealth / 100);
	if (W <= 20)	W = 20.1;
	float w = W / 100 * progress;

	uint32_t color = 0xFF0000FF;
	if (progress >= 20) color = 0xFF008CFF;
	if (progress >= 40) color = 0xFF00FFFF;
	if (progress >= 60) color = 0xFF00d090;
	if (progress >= 80) color = 0xFF00FF00;

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->AddRectFilled(ImVec2(X, Y), ImVec2(X + W, Y + H), backcolor, 5);
	window->DrawList->AddRectFilled(ImVec2(X - 1, Y), ImVec2(X + w, Y + H), color, 5);
}

void __fastcall render_multi_health(float X, float Y, float W, float H, float Health, float MaxHealth, uint32_t col_left, uint32_t col_right)
{
	if (H < 1.5) H = 1.5;

	uint32_t backcolor = 0xFF010101;
	float progress = Health / (MaxHealth / 100);
	if (W <= 20)	W = 21;

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->AddRectFilledMultiColor(ImVec2(X, Y), ImVec2(X + W, Y + H), col_left, col_right, col_right, col_left);
	window->DrawList->AddRectFilled(ImVec2((X + W) - (W - (W / 100 * progress)), Y), ImVec2(X + W, Y + H), backcolor);
}

void __fastcall render_circle(const ImVec2& position, float radius, float* color, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	float r = color[0];
	float g = color[1];
	float b = color[2];
	float a = color[3];

	window->DrawList->AddCircle(position, radius, ImGui::GetColorU32(ImVec4(r, g, b, a)), 24, thickness);
}

void rnder_circle_scale(const ImVec2& position, float radius, float* color, const ImVec2& scalepos, const ImVec2& scaleheadPosition, float thickness)
{
	float rad = (scaleheadPosition.y + 15 - scalepos.y) / 10.5f;
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	float r = color[0];
	float g = color[1];
	float b = color[2];
	float a = color[3];

	window->DrawList->AddCircle(position, rad, ImGui::GetColorU32(ImVec4(r, g, b, a)), 12, thickness);
}

void render_circle_filled(const ImVec2& position, float radius, float* color)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	float r = color[0];
	float g = color[1];
	float b = color[2];
	float a = color[3];

	window->DrawList->AddCircleFilled(position, radius, ImGui::GetColorU32(ImVec4(r, g, b, a)), 12);
}

void render_image(ImVec2 position, ImVec2 size, PVOID64 image_texture)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	if (!image_texture)
		return;

	window->DrawList->AddImage(image_texture, position, ImVec2(position.x + size.x, position.y + size.y), ImVec2(0, 0), ImVec2(1, 1));
}

