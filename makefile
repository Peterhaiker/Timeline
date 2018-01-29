#file search path
VPATH=header:func_model:input_model
source=*.c func_model/*.c input_model/*.c
install:$(source) header/timeline.h
	gcc $(source) -o timeline -lmysqlclient
.PHONY:uninstall
uninstall:
	-rm *.o timeline
