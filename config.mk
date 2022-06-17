# paths
PREFIX = /usr/local
MANDIR = $(PREFIX)/share/man
DESKTOP = /usr/share/wayland-sessions

# Default compile flags (overridable by environment)
CFLAGS ?= -march=native -Ofast -pipe -fomit-frame-pointer -Wall -Wextra -Werror -Wno-unused-parameter -Wno-sign-compare -Wno-unused-function -Wno-unused-variable -Wno-unused-result -Wdeclaration-after-statement

# Uncomment to build XWayland support
#CFLAGS += -DXWAYLAND
