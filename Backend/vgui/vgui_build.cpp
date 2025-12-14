#include "vgui_build.h"

#include "vgui.h"
#include "vgui_page.h"
#include "vgui_button.h"
#include "vgui_error.h"

#include <fstream>
#include <sstream>
#include <regex>
#include <format>

namespace vgui
{
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

    json load_jsonc(const std::string& path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            exit(std::format("[ERROR]: Failed to open jsonc file at path: {}", path),
                Error::FILE_NOT_FOUND_ERROR);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        std::string cleaned = strip_jsonc(buffer.str());

        try
        {
            return json::parse(cleaned);
        }
        catch (const json::parse_error& e)
        {
            exit(std::format("{}\n", e.what()), Error::JSON_PARSE_ERROR);
        }
    }

    std::unique_ptr<Widget> build_widget(const std::string& name, json widget)
    {
        using enum vgui::Error;

        std::string type;
        json bounds;
        json action;

        if (widget.contains("type") && widget.at("type").is_string())
        {
            type = widget.at("type").get<std::string>();
        }
        else
        {
            exit(std::format("Widget '{}' has no type defined!", name),
                JSON_PARSE_ERROR);
        }

        if (widget.contains("bounds") &&
            widget.at("bounds").is_array() &&
            widget.at("bounds").size() == 4)
        {
            bounds = widget.at("bounds");
        }
        else
        {
            exit(std::format("Widget '{}' has no bounding box defined!", name),
                JSON_PARSE_ERROR);
        }

        // optional
        if (widget.contains("action"))
        {
            action = widget.at("action");
        }

        if (type == "button")
        {
            return std::make_unique<VButton>(bounds, action);
        }

        exit(std::format("[ERROR]: Unknown widget type '{}' for widget '{}'",
            type, name),
            INVALID_WIDGET_TYPE_ERROR);

        return nullptr;
    }

    std::unique_ptr<Page> load_page(json widgets)
    {
        auto page = std::make_unique<Page>();
        if (!page)
            return nullptr;

        for (auto& [name, widget] : widgets.items())
        {
            page->add(name, build_widget(name, widget));
        }

        return page;
    }

    std::unique_ptr<Book> load_book(json pages)
    {
        exit("load_book Not implemented!",
            Error::NO_IMPLEMENTATION_ERROR);
        return nullptr;
    }
}
