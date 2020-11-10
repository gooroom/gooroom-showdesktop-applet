/*
 * Copyright (C) 2018-2019 Gooroom <gooroom@gooroom.kr>
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib.h>
#include <gtk/gtk.h>
#include <glib/gi18n-lib.h>

#include <libgnome-panel/gp-applet.h>

#include <libwnck/libwnck.h>

#include "gooroom-showdesktop-applet.h"

#define	TRAY_ICON_SIZE	24

struct _GooroomShowDesktopAppletPrivate
{
	GtkWidget *button;

	WnckScreen *wnck_screen;
};



G_DEFINE_TYPE_WITH_PRIVATE (GooroomShowDesktopApplet, gooroom_showdesktop_applet, GP_TYPE_APPLET)


static void
on_showing_desktop_changed (WnckScreen *wnck_screen,
                            gpointer    data)
{
	GooroomShowDesktopApplet *applet;
	GooroomShowDesktopAppletPrivate *priv;

	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (priv->button),
			wnck_screen_get_showing_desktop (wnck_screen));
}

static void
on_applet_button_toggled (GtkToggleButton *button, gpointer data)
{
	gboolean a;
	GooroomShowDesktopApplet *applet;
	GooroomShowDesktopAppletPrivate *priv;

	applet = GOOROOM_SHOWDESKTOP_APPLET (data);
	priv = applet->priv;

	a = gtk_toggle_button_get_active (button);
	if (a != wnck_screen_get_showing_desktop (priv->wnck_screen)) {
		wnck_screen_toggle_showing_desktop (priv->wnck_screen, a);
	}
}

static void
gooroom_showdesktop_screen_changed (GtkWidget *widget,
                                    GdkScreen *prev_screen)
{
	GdkScreen *screen;
	WnckScreen *wnck_screen;
	GooroomShowDesktopApplet *applet;
	GooroomShowDesktopAppletPrivate *priv;

	applet = GOOROOM_SHOWDESKTOP_APPLET (widget);
	priv = applet->priv;

	screen = gtk_widget_get_screen (widget);

G_GNUC_BEGIN_IGNORE_DEPRECATIONS
	wnck_screen = wnck_screen_get (gdk_screen_get_number (screen));
G_GNUC_END_IGNORE_DEPRECATIONS

	if (priv->wnck_screen == wnck_screen)
		return;

	if (priv->wnck_screen) {
		g_signal_handlers_disconnect_by_func (G_OBJECT (priv->wnck_screen),on_showing_desktop_changed, applet);
	}

	priv->wnck_screen = wnck_screen;

	g_signal_connect (G_OBJECT (wnck_screen), "showing-desktop-changed",
		G_CALLBACK (on_showing_desktop_changed), applet);

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (priv->button)) != wnck_screen_get_showing_desktop (wnck_screen)) {
		on_showing_desktop_changed (priv->wnck_screen, applet);
	} else {
		on_applet_button_toggled (GTK_TOGGLE_BUTTON (priv->button), applet);
	}
}

static void
gooroom_showdesktop_applet_finalize (GObject *object)
{
	GooroomShowDesktopApplet *applet = GOOROOM_SHOWDESKTOP_APPLET (object);
	GooroomShowDesktopAppletPrivate *priv = applet->priv;

	g_signal_handlers_disconnect_by_func (G_OBJECT (priv->wnck_screen),gooroom_showdesktop_screen_changed, applet);

	if (priv->wnck_screen) {
		g_signal_handlers_disconnect_by_func (G_OBJECT (priv->wnck_screen),on_showing_desktop_changed, applet);
	}

	G_OBJECT_CLASS (gooroom_showdesktop_applet_parent_class)->finalize (object);
}


static gboolean
gooroom_showdesktop_applet_fill (GooroomShowDesktopApplet *applet)
{
	g_return_val_if_fail (GP_IS_APPLET (applet), FALSE);

	gtk_widget_show_all (GTK_WIDGET (applet));

	return TRUE;
}

static void
gooroom_showdesktop_applet_constructed (GObject *object)
{
	GooroomShowDesktopApplet *applet = GOOROOM_SHOWDESKTOP_APPLET (object);

	gooroom_showdesktop_applet_fill (applet);
}

static void
gooroom_showdesktop_applet_init (GooroomShowDesktopApplet *applet)
{
	GooroomShowDesktopAppletPrivate *priv;

	priv = applet->priv = gooroom_showdesktop_applet_get_instance_private (applet);

	gp_applet_set_flags (GP_APPLET (applet), GP_APPLET_FLAGS_EXPAND_MINOR);

	priv->wnck_screen = wnck_screen_get_default ();

	priv->button = gtk_toggle_button_new ();
	gtk_button_set_relief (GTK_BUTTON (priv->button), GTK_RELIEF_NONE);
	gtk_container_add (GTK_CONTAINER (applet), priv->button);

	GtkWidget *tray = gtk_image_new_from_icon_name ("show-desktop-symbolic", GTK_ICON_SIZE_BUTTON);
	gtk_image_set_pixel_size (GTK_IMAGE (tray), TRAY_ICON_SIZE);
	gtk_container_add (GTK_CONTAINER (priv->button), tray);

	g_signal_connect (G_OBJECT (priv->button), "toggled", G_CALLBACK (on_applet_button_toggled), applet);
}

static void
gooroom_showdesktop_applet_class_init (GooroomShowDesktopAppletClass *class)
{
	GObjectClass *object_class;
	GtkWidgetClass *widget_class;

	object_class = G_OBJECT_CLASS (class);
	widget_class = GTK_WIDGET_CLASS (class);

	object_class->constructed = gooroom_showdesktop_applet_constructed;
	object_class->finalize = gooroom_showdesktop_applet_finalize;
	widget_class->screen_changed = gooroom_showdesktop_screen_changed;
}
