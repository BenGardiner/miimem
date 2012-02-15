targets = miimem
sources = miimem.c mii.c
objs = $(sources:.c=.o)
deps = $(sources:.c=.d)
.PHONY =  all clean

override CFLAGS := -Wall $(CFLAGS)

all : $(targets)

clean :
	rm -rf $(objs)
	rm -rf $(targets)

miimem : miimem.o mii.o

%.d : %.c
	@$(SHELL) -ec '$(CC) -MM $(CPPFLAGS) $< \
	| sed '\''s/\($*\)\.o[ :]*/\1.o $@ : /g'\'' > $@; \
	[ -s $@ ] || rm -f $@'

-include $(deps)
