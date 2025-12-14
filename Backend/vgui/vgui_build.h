#pragma once

#include <memory>
#include <string>
#include <thirdparty/json/json.hpp>
using json = nlohmann::json;

namespace vgui
{
    class Page;
    struct Widget;

    using Book = std::unordered_map<std::string, std::unique_ptr<Page>>;

    // JSONC utilities
    std::string strip_jsonc(const std::string& input);
    json load_jsonc(const std::string& path);

    // widget / page / book construction
    std::unique_ptr<Widget> build_widget(const std::string& name, json widget);
    std::unique_ptr<Page>   load_page(json widgets);
    std::unique_ptr<Book>   load_book(json pages);
}
