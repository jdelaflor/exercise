CFLAGS = --pedantic -Wall -std=c99 -g -pthread
LDFLAGS = -lm 

bin_PROGRAMS =  $(top_builddir)/bin/doggy $(top_builddir)/bin/doggy_watcher
__top_builddir__bin_doggy_SOURCES = doggy.c doggy.h doggy_wrapper_constants.h
__top_builddir__bin_doggy_LDADD = 
__top_builddir__bin_doggy_watcher_SOURCES = doggy_watcher.c doggy_watcher.h doggy_watcher_params.c doggy_watcher_params.h doggy_wrapper_constants.h doggy_process.c doggy_process.h doggy_watcher_log.c doggy_watcher_log.h
__top_builddir__bin_doggy_watcher_LDADD = 
