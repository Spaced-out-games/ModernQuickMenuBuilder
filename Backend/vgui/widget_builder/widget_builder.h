#pragma once
#include "thirdparty/json/json_fwd.hpp"
#include "../vgui_background.h"
#include "../vgui_button.h"
#include <memory>
namespace vgui::build {
	std::string strip_jsonc(const std::string& input);


	std::unique_ptr<vgui::Widget> make_background(const std::string& name, json j);
}