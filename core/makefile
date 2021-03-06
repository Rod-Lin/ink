LIB_NAME=$(GLOBAL_CORE_LIB_SONAME)
STATIC_LIB_NAME=$(GLOBAL_CORE_STATIC_LIB_NAME)
TARGET=$(LIB_NAME)
REQUIRE=\
	gc/gc.o \
	native/native.o \
	thread/thread.o \
	coroutine/coroutine.o \
	package/package.o \
	msg/msg.o \
	interface/interface.o \
	syntax/syntax.o \
	hash.o \
	object.o \
	slot.o \
	clone.o\
	array.o\
	function.o \
	explist.o \
	coroutine.o \
	expression.o \
	context.o \
	general.o \
	debug.o \
	error.o \
	protocol.o \
	utf8.o \
	exception.o \
	constant.o \
	numeric.o

LDFLAGS=-shared -static-libgcc -static-libstdc++ -lm
STATIC_LDFLAGS=

ifeq ($(GLOBAL_PLATFORM), windows)
	LDFLAGS+= -Wl,-Bstatic -lwinpthread
	# -fPIC is default on Windows
	CPPFLAGS=-I$(GLOBAL_ROOT_PATH) $(GLOBAL_CPPFLAGS)
else
	LDFLAGS+= -ldl -pthread
	CPPFLAGS=-I$(GLOBAL_ROOT_PATH) -fPIC $(GLOBAL_CPPFLAGS)
endif

$(TARGET): $(REQUIRE)
	$(CC) -o $@ $(REQUIRE) $(LDFLAGS)

static: $(REQUIRE)
	$(LD) -r -o $(STATIC_LIB_NAME) $(REQUIRE) $(STATIC_LDFLAGS)

gc/gc.o:
	cd gc; $(MAKE)

native/native.o:
	cd native; $(MAKE)

thread/thread.o:
	cd thread; $(MAKE)

coroutine/coroutine.o:
	cd coroutine; $(MAKE)

package/package.o:
	cd package; $(MAKE)

msg/msg.o:
	cd msg; $(MAKE)

interface/interface.o:
	cd interface; $(MAKE)

syntax/syntax.o:
	cd syntax; $(MAKE)

%.o: %.cpp
	$(CC) -c $^ $(CPPFLAGS)

clean:
	cd gc; $(MAKE) clean
	cd native; $(MAKE) clean
	cd thread; $(MAKE) clean
	cd coroutine; $(MAKE) clean
	cd package; $(MAKE) clean
	cd msg; $(MAKE) clean
	cd interface; $(MAKE) clean
	cd syntax; $(MAKE) clean
	$(RM) *.o *.so *.dll

FORCE: