#include "sink.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

namespace woodchuck {

    // =========================
    // DebugSink
    // =========================
    DebugSink::DebugSink() {}

    void DebugSink::put(std::string_view msg) {
        #ifdef _WIN32
        std::string tmp(msg);
        OutputDebugStringA(tmp.c_str());
        OutputDebugStringA("\n");
        #endif
    }

    // =========================
    // CLISink
    // =========================
    CLISink::CLISink() {
        #ifdef _WIN32
        AllocConsole();
        FILE* f;
        freopen_s(&f, "CONOUT$", "w", stdout);
        freopen_s(&f, "CONOUT$", "w", stderr);
        #endif
    }

    void CLISink::put(std::string_view msg) {
        std::fwrite(msg.data(), 1, msg.size(), stdout);
        std::fputc('\n', stdout);
    }

    // =========================
    // FileSink
    // =========================
    FileSink::FileSink(const char* path) {
        #ifdef _WIN32
        errno_t err = fopen_s(&file, path, "w");
        if (err != 0) file = nullptr;
        #else
        file = std::fopen(path, "w");
        #endif
    }

    FileSink::~FileSink() {
        if (file) std::fclose(file);
    }

    void FileSink::put(std::string_view msg) {
        if (!file) return;
        std::fwrite(msg.data(), 1, msg.size(), file);
        std::fputc('\n', file);
        std::fflush(file);
    }

} // namespace woodchuck
