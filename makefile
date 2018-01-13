#file search path
VPATH=header:func_model
install:timeline.c login.c
	gcc timeline.c func_model/login.c -o timeline -lmysqlclient
.PHONY:uninstall
uninstall:
	-rm *.o timeline
