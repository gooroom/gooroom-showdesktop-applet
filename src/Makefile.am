gooroomappletdir = $(GNOME_PANEL_MODULES_DIR)
gooroomapplet_LTLIBRARIES = libgooroom-showdesktop-applet.la

libgooroom_showdesktop_applet_la_CPPFLAGS = \
	-I$(srcdir) \
	-I$(top_srcdir) \
	-DGNOMELOCALEDIR=\""$(localedir)"\" \
	-DPKGDATADIR=\"$(pkgdatadir)\" \
	-DWNCK_I_KNOW_THIS_IS_UNSTABLE \
	-DGDK_DISABLE_DEPRECATED

libgooroom_showdesktop_applet_la_SOURCES = \
	showdesktop-applet-module.c \
	showdesktop-applet.h \
	showdesktop-applet.c

libgooroom_showdesktop_applet_la_CFLAGS = \
	$(GLIB_CFLAGS) \
	$(GTK_CFLAGS) \
	$(LIBWNCK_CFLAGS) \
	$(LIBGNOMEPANEL_CFLAGS) \
	$(AM_CFLAGS)

libgooroom_showdesktop_applet_la_LDFLAGS = \
	-avoid-version \
	$(AM_LDFLAGS)

libgooroom_showdesktop_applet_la_LIBADD = \
	$(GLIB_LIBS) \
	$(GTK_LIBS) \
	$(LIBWNCK_LIBS)	\
	$(LIBGNOMEPANEL_LIBS)
