#include "config.hpp"
#include <format>
#include <iostream>
#include <memory>

std::unique_ptr<Config> Config::instance_ = nullptr;

void Config::configParse(std::string configPath = "config/config.toml") {
  try {
    tbl = toml::parse_file(configPath);
    std::cout << std::format("[[INFO]] : Parse config file {}\n", configPath);
  } catch (const toml::parse_error &err) {
    std::cout << std::format("[[ERROR]] : toml-parse : {}\n", err.what());
  }
}

toml::table Config::getConfig() { return getInstance().tbl; }