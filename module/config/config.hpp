#pragma once

#include "toml.hpp"
#include <cassert>
#include <memory>

class Config final {
private:
  toml::table tbl;

public:
  void configParse(std::string);
  toml::table getConfig();

  // Singleton
private:
  static std::unique_ptr<Config> instance_;

private:
  Config(){};

public:
  static void configInit() { instance_.reset(new Config); }
  static void configQuit() { instance_.reset(); }
  static Config &getInstance() {
    assert(instance_);
    return *instance_;
  }

  ~Config(){};
};