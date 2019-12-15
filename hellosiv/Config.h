#pragma once

class Config {
private:
    Config() = default;
    ~Config() = default;

public:
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    Config(Config&&) = delete;
    Config& operator=(Config&&) = delete;
    
    static Config& get_instance() {
        static Config instance;
        return instance;
    }
};