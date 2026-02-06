#pragma once
#include <iostream>
#include <format>
#include <ctime>
#include <string_view>

namespace woodchuck {

    inline bool g_Verbose = true;

    // =========================
    // ANSI enable
    // =========================
    #ifdef _WIN32
    inline void enable_ansi() {
        // Only attempt to enable ANSI if stdout is a console
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return;

        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) return;

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
    #else
    void enable_ansi() {}
    #endif

    // =========================
    // ANSI colors
    // =========================
    namespace ansi {
        std::string_view reset() {
            if (dynamic_cast<FileSink*>(g_ActiveSink.get())) return "";
            return "\x1b[0m";
        }

        std::string_view red() {
            if (dynamic_cast<FileSink*>(g_ActiveSink.get())) return "";
            return "\x1b[31m";
        }

        std::string_view green() {
            if (dynamic_cast<FileSink*>(g_ActiveSink.get())) return "";
            return "\x1b[32m";
        }

        std::string_view yellow() {
            if (dynamic_cast<FileSink*>(g_ActiveSink.get())) return "";
            return "\x1b[33m";
        }

        std::string_view blue() {
            if (dynamic_cast<FileSink*>(g_ActiveSink.get())) return "";
            return "\x1b[34m";
        }

        std::string_view magenta() {
            if (dynamic_cast<FileSink*>(g_ActiveSink.get())) return "";
            return "\x1b[35m";
        }

        std::string_view cyan() {
            if (dynamic_cast<FileSink*>(g_ActiveSink.get())) return "";
            return "\x1b[36m";
        }

        std::string_view gray() {
            if (dynamic_cast<FileSink*>(g_ActiveSink.get())) return "";
            return "\x1b[90m";
        }
    }

    // =========================
    // Utilities
    // =========================
    void print(std::string_view line)
    {
        std::cout << line;
    }

    void println(std::string_view line)
    {
        std::cout << line << '\n';
    }

    std::string timestamp()
    {
        using namespace std::chrono;

        const auto now = system_clock::now();
        const auto sec = time_point_cast<seconds>(now);
        const auto ms = duration_cast<milliseconds>(now - sec).count();

        std::time_t tt = system_clock::to_time_t(sec);

        std::tm tm{};
        #if defined(_WIN32)
        localtime_s(&tm, &tt);
        #else
        localtime_r(&tt, &tm);
        #endif

        return std::format(
            "{:04}-{:02}-{:02} {:02}:{:02}:{:02}.{:03}",
            tm.tm_year + 1900,
            tm.tm_mon + 1,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec,
            ms
        );
    }

    // =========================
    // Logging functions
    // =========================

    template <class... Args>
    void log(std::string_view fmt, Args&&... args)
    {
        std::string msg = std::format(
            "{}",
            std::vformat(fmt, std::make_format_args(args...))
        );

        if (g_ActiveSink) g_ActiveSink->put(msg);
        else println(msg);
    }

    template <class... Args>
    void warn(std::string_view fmt, Args&&... args)
    {
        // build the message first
        std::string body = std::vformat(fmt, std::make_format_args(args...));
        std::string msg = std::format(
            "{}[WARNING] [{}] {}{}",
            ansi::yellow(),
            timestamp(),
            body,
            ansi::reset()
        );
        log("{}", msg);
    }

    template <class... Args>
    void error(std::string_view fmt, Args&&... args)
    {
        std::string body = std::vformat(fmt, std::make_format_args(args...));
        std::string msg = std::format(
            "{}[ERROR] [{}] {}{}",
            ansi::red(),
            timestamp(),
            body,
            ansi::reset()
        );
        log("{}", msg);
    }

    template <class... Args>
    void fatal(std::string_view fmt, Args&&... args)
    {
        std::string body = std::vformat(fmt, std::make_format_args(args...));
        std::string msg = std::format(
            "{}[FATAL] [{}] {}{}",
            ansi::magenta(),
            timestamp(),
            body,
            ansi::reset()
        );
        log("{}", msg);
    }

    template <class... Args>
    void info(std::string_view fmt, Args&&... args)
    {
        std::string body = std::vformat(fmt, std::make_format_args(args...));
        std::string msg = std::format(
            "{}[INFO] [{}] {}{}",
            ansi::green(),
            timestamp(),
            body,
            ansi::reset()
        );
        log("{}", msg);
    }

    template <class... Args>
    void debug(std::string_view fmt, Args&&... args)
    {
        #ifdef _DEBUG
        std::string body = std::vformat(fmt, std::make_format_args(args...));
        std::string msg = std::format(
            "{}[DEBUG] [{}] {}{}",
            ansi::cyan(),
            timestamp(),
            body,
            ansi::reset()
        );
        log("{}", msg);
        #endif
    }

    template <class... Args>
    void verbose(std::string_view fmt, Args&&... args)
    {
        if (!g_Verbose) return;
        std::string body = std::vformat(fmt, std::make_format_args(args...));
        std::string msg = std::format(
            "{}[INFO] [{}] {}{}",
            ansi::gray(),
            timestamp(),
            body,
            ansi::reset()
        );
        log("{}", msg);
    }

    template <class... Args>
    void perf(std::string_view fmt, std::chrono::microseconds ms, Args&&... args)
    {
        std::string body = std::vformat(fmt, std::make_format_args(args...));
        std::string msg = std::format(
            "{}[PERF] [{}] {} {} μs{}",
            ansi::blue(),
            timestamp(),
            body,
            ms.count(),
            ansi::reset()
        );
        log("{}", msg);
    }

    template <typename SinkType, typename... Args>
    void init(Args&&... args) {
        static_assert(std::is_base_of_v<Sink, SinkType>,
            "SinkType must derive from woodchuck::Sink");

        g_ActiveSink = std::make_unique<SinkType>(std::forward<Args>(args)...);

        #ifdef _DEBUG
            setVerboseMode(true);
        #endif

        // Only enable ANSI if using CLI sink
        if constexpr (std::is_same_v<SinkType, CLISink>) {
            enable_ansi();
        }


        woodchuck::debug("Initialized Woodchuck");
    }

    void setVerboseMode(bool mode)
    {
        g_Verbose = mode;
    }
    bool getVerboseMode() {
        return g_Verbose;
    }


} // namespace woodchuck
