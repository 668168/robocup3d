AM_CPPFLAGS = -DBATS_NO_DEBUG -DDATADIR="$(pkgdatadir)" -I../..
AM_LDFLAGS = ../../libbats.la -lxml2

noinst_PROGRAMS = helloworldagent
noinst_HEADERS = HelloWorldAgent/helloworldagent.hh HelloWorldAgent/helloworldagent.ih
helloworldagent_SOURCES = HelloWorldAgent/init.cc HelloWorldAgent/think.cc helloworldagent.cc
#helloworldagent_LDADD = ../../libbats.la
