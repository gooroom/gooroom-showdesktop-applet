/*
 * Copyright (C) 2018-2021 Gooroom <gooroom@gooroom.kr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __GOOROOM_SHOWDESKTOP_APPLET_H__
#define __GOOROOM_SHOWDESKTOP_APPLET_H__

G_BEGIN_DECLS

#include <libgnome-panel/gp-applet.h>

#define GOOROOM_TYPE_SHOWDESKTOP_APPLET           (gooroom_showdesktop_applet_get_type ())
#define GOOROOM_SHOWDESKTOP_APPLET(obj)           (G_TYPE_CHECK_INSTANCE_CAST ((obj), GOOROOM_TYPE_SHOWDESKTOP_APPLET, GooroomShowdesktopApplet))
#define GOOROOM_SHOWDESKTOP_APPLET_CLASS(obj)     (G_TYPE_CHECK_CLASS_CAST    ((obj), GOOROOM_TYPE_SHOWDESKTOP_APPLET, GooroomShowdesktopAppletClass))
#define GOOROOM_IS_SHOWDESKTOP_APPLET(obj)        (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GOOROOM_TYPE_SHOWDESKTOP_APPLET))
#define GOOROOM_IS_SHOWDESKTOP_APPLET_CLASS(obj)  (G_TYPE_CHECK_CLASS_TYPE    ((obj), GOOROOM_TYPE_SHOWDESKTOP_APPLET))
#define GOOROOM_SHOWDESKTOP_APPLET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS  ((obj), GOOROOM_TYPE_SHOWDESKTOP_APPLET, GooroomShowdesktopAppletClass))

typedef struct _GooroomShowdesktopApplet        GooroomShowdesktopApplet;
typedef struct _GooroomShowdesktopAppletClass   GooroomShowdesktopAppletClass;
typedef struct _GooroomShowdesktopAppletPrivate GooroomShowdesktopAppletPrivate;

struct _GooroomShowdesktopApplet {
	GpApplet parent;
	GooroomShowdesktopAppletPrivate *priv;
};

struct _GooroomShowdesktopAppletClass {
	GpAppletClass parent_class;
};

GType gooroom_showdesktop_applet_get_type (void);

G_END_DECLS

#endif /* __GOOROOM_SHOWDESKTOP_APPLET_H__*/
