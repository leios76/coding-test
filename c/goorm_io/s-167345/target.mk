TARGET := $(notdir $(shell dirname $(realpath $(shell dirname $(lastword $(MAKEFILE_LIST))))))/$(notdir $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))
WORKDIR := ${BASE_DIR}
WORKDIR := $(WORKDIR)/$(notdir $(shell dirname $(realpath $(shell dirname $(lastword $(MAKEFILE_LIST))))))
WORKDIR := $(WORKDIR)/$(notdir $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))
SOURCES += $(patsubst $(WORKDIR)/%.c, %.c, $(wildcard $(WORKDIR)/*.c))

TGT_CFLAGS := -DDEBUG_RUN -DDEBUG_OUTPUT
TGT_LDFLAGS := -L${BASE_DIR}/output/lib
TGT_LDLIBS  :=
