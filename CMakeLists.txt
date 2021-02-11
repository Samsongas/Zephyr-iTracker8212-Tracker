# Find Zephyr. This also loads Zephyr's build system.
cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr)
project(Zephyr-iTracker8212-Tracker)

# Add your source file to the "app" target. This must come after
# find_package(Zephyr) which defines the target.
target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/bg-96-uart.c)
target_sources(app PRIVATE src/bg-96-gps.c)
target_sources(app PRIVATE src/bg-96-gprs.c)