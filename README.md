# HIT-Circle-Backend

## How to use

```
./bin/hit-circle-backend --help
```

## How to build

### Environment

- cmake 3.20+
- C++17
- Ninja-build(recommend) / makefile
- sqlite3
- [Poco](https://github.com/pocoproject/poco)

### Quick Start

```
# clone code
mkdir hit-circle-backend
git clone https://github.com/leebdscoding/HITSQL_Back.git .
cmake -B build -G Ninja
cmake --build build

# compile sqlite3
cd ~
mkdir sqlite
cd sqlite
wget https://www.sqlite.org/2024/sqlite-autoconf-3460000.tar.gz
tar xzvf sqlite-autoconf-3460000.tar.gz
cd sqlite-autoconf-3460000/
./configure
make && sudo make install

# compile and install poco
cd ~
git clone -b main https://github.com/pocoproject/poco.git --depth=1
cd poco
mkdir cmake-build
cd cmake-build
cmake .. -G Ninja
cmake --build . --config Release
sudo cmake --build . --target install
```

## File structure

- Project/
    - include/
    - module/
        - cmdParser/
        - http/
        - log/
        - sql/
        - CMakeLists.txt
    - .gitignore
    - CMakeLists.txt
    - main.cpp
    - README.md
    - TODO.md

## Configure the server

The config file is in `path/to/bin/config/config.json`.
It's a JSON with comment file.

An example is here:

```
{
    "website": {
        "name": "HIT_Circle"
    },
    "server": {
        "port": 8080,
        "root": "webroot/",
        "site-root": "www/",
        "handlers": [
            {
                // the handler's name, defined by backend.
                "type": "handler name",
                // what template this handler use, designed by web designer.
                "template": "template/index.html",
                "use": "what this handler do"
            }
            // can be more handlers
        ]
    }
}
```

- `website` is required, the `name` is the server's name, which decides how the log files are named.
- `port` in `server` is optional, the default value is 8080.
- `root` is the website's root direction. Actually, this software is a file parser.
- `site-root` is the website's file direction, which always includes `.html`, `.css` and template files.
- `handlers` is about how the server run. Handlers point to the `HTTPRequestHandler()` object.