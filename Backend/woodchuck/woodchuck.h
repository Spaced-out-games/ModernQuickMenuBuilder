#pragma once

#include <string>
#include <string_view>
#include <chrono>
#include <cstdio>
#include "sink.h"
#include <memory>


namespace woodchuck {
    inline std::unique_ptr<Sink> g_ActiveSink = nullptr;

    // =========================
    // Sink interface
    // =========================
    



    // =========================
    // ANSI helpers
    // =========================
    inline void enable_ansi();

    namespace ansi {
        inline std::string_view reset();
        inline std::string_view red();

        inline std::string_view green();

        inline std::string_view yellow();

        inline std::string_view blue();

        inline std::string_view magenta();

        inline std::string_view cyan();

        inline std::string_view gray();
    }

    // =========================
    // Utilities
    // =========================
    template <typename SinkType, typename... Args>
    inline void init(Args&&... args);
    inline void print(std::string_view line);
    inline void println(std::string_view line);
    inline std::string timestamp();

    // =========================
    // Logging API
    // =========================
    template <class... Args>
    inline void log(std::string_view fmt, Args&&... args);

    template <class... Args>
    inline void warn(std::string_view fmt, Args&&... args);

    template <class... Args>
    inline void error(std::string_view fmt, Args&&... args);

    template <class... Args>
    inline void fatal(std::string_view fmt, Args&&... args);

    template <class... Args>
    inline void info(std::string_view fmt, Args&&... args);

    template <class... Args>
    inline void debug(std::string_view fmt, Args&&... args);

    template <class... Args>
    inline void verbose(std::string_view fmt, Args&&... args);

    template <class... Args>
    inline void perf(
        std::string_view fmt,
        std::chrono::microseconds ms,
        Args&&... args);

    inline void setVerboseMode(bool mode);
    inline bool getVerboseMode();


} // namespace woodchuck

#include "woodchuck.inl"
