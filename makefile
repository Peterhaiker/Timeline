#file search path
VPATH=header:func_model
source=*.c func_model/*.c
install:$(source) header/timeline.h
	gcc $(source) -o timeline -lmysqlclient
.PHONY:uninstall
uninstall:
	-rm *.o timeline
