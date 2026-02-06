#pragma once
#include <string_view>
#include <cstdio>

namespace woodchuck {

    struct Sink {
        virtual ~Sink() = default;
        virtual void put(std::string_view msg) = 0;
    };

    struct DebugSink final : Sink {
        DebugSink();
        void put(std::string_view msg) override;
    };

    struct CLISink final : Sink {
        CLISink();
        void put(std::string_view msg) override;
    };

    struct FileSink final : Sink {
        explicit FileSink(const char* path);
        ~FileSink() override;
        void put(std::string_view msg) override;

    private:
        FILE* file = nullptr;
    };

} // namespace woodchuck
