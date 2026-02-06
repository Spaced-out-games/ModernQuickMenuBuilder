#include "widget_builder.h"
#include <regex>
#include "../../woodchuck/woodchuck.h"

namespace vgui::build {
    std::string strip_jsonc(const std::string& input)
    {
        std::string output = input;

        // Remove single-line comments
        output = std::regex_replace(output, std::regex(R"(//.*)"), "");

        // Remove multi-line comments
        output = std::regex_replace(
            output,
            std::regex(R"(/\*[\s\S]*?\*/)", std::regex_constants::ECMAScript),
            ""
        );

        return output;
    }

    std::unique_ptr<vgui::Widget> make_background(native::WidgetBase& owner, const std::string& name, json j) {
        std::unique_ptr<vgui::Widget> result = nullptr;

        if (!j.contains("image")) {
            woodchuck::warn("Widget '{}' has no image defined. This will cause it to not draw.", name);
            return std::move(std::make_unique<VBackground>(owner, ""));
        }
        else {
            // NOTE TO SELF: this *might* somehow be open to exploits.
            if (!j["image"].is_string() || j["image"] == "") return nullptr;

            std::string path = j["image"];

            result = std::make_unique<VBackground>(owner, path);

            
            

        }

        return result;


    }
}