OBJECTS = linkedlist.o hashmap.o

%.o : src/%.c include/essentials/%.h
	$(CC) $(CFLAGS) -c -Iinclude/ $<

libessentials.a : $(OBJECTS)
	$(AR) rcs lib/libessentials.a $(OBJECTS)

all: libessentials.a
	
clean:
	$(RM) $(OBJECTS)
