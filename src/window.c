/*
 *  L3afpad - GTK+ based simple text editor
 *  Copyright (C) 2004-2005 Tarot Osuji
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "l3afpad.h"
/*
static void cb_scroll_event(GtkAdjustment *adj, GtkWidget *view)
{
	gtk_text_view_place_cursor_onscreen(GTK_TEXT_VIEW(view));
}
*/
MainWin *create_main_window(void)
{
	GtkWidget	*vbox;
	GtkWidget	*sw;
	GtkWidget	*space;
	GtkWidget	*grid;
	int			count = 3;

	MainWin *mw = g_malloc(sizeof(MainWin));

	mw->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(mw->window, PACKAGE_NAME);

	gtk_window_set_icon_from_file(GTK_WINDOW(mw->window), ICONDIR"/l3afpad.png", NULL);
	gtk_window_set_default_icon_name(PACKAGE);

	g_signal_connect(G_OBJECT(mw->window), "delete-event",
		G_CALLBACK(on_file_quit), NULL);
	g_signal_connect_after(G_OBJECT(mw->window), "delete-event",
		G_CALLBACK(gtk_widget_hide_on_delete), NULL);

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(mw->window), vbox);

	mw->menubar = create_menu_bar(mw->window);
	gtk_box_pack_start(GTK_BOX(vbox), gtk_ui_manager_get_widget(mw->menubar, "/M"), FALSE, FALSE, 0);

	sw = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_hexpand (sw, TRUE);
	gtk_widget_set_vexpand (sw, TRUE);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw),
		GTK_SHADOW_IN);
	gtk_box_pack_start(GTK_BOX(vbox), sw, TRUE, TRUE, 0);

//	mw->view = create_text_view();
//	gtk_container_add(GTK_CONTAINER(sw), mw->view);
//	mw->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mw->view));

	// Outer Container
	GtkWidget* viewport = gtk_viewport_new( NULL, NULL );
	gtk_container_add( GTK_CONTAINER( sw ), viewport );


	// Create the grid
	grid = gtk_grid_new();
	gtk_grid_set_column_homogeneous(grid, TRUE);
//	gtk_grid_set_row_homogeneous(grid, TRUE);
	gtk_grid_set_column_spacing(grid, 2);
//	gtk_box_pack_start(GTK_BOX(sw), grid, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(viewport), grid);

	// Create filler
/*	GtkWidget* filler = gtk_widget_new(GTK_TYPE_LABEL, "label", "Hello World 1");
//	gtk_table_attach(GTK_TABLE (table), filler, 0, count, 1, 2, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
	gtk_container_add(GTK_CONTAINER(space), grid);
*/
//	GtkWidget* filler1 = gtk_label_new("Filler");
//	gtk_box_pack_end(GTK_BOX(sw), filler1, TRUE, TRUE, 0);
//	gtk_container_add(GTK_CONTAINER(sw), filler1);
//	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(sw), filler1);
//	gtk_container_add(GTK_CONTAINER(viewport), filler1);

//	GtkWidget* filler2 = gtk_label_new("Filler");
//	gtk_box_pack_end(GTK_BOX(sw), filler2, TRUE, TRUE, 0);
//	gtk_container_add(GTK_CONTAINER(sw), filler2);
//	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(sw), filler2);
//	gtk_container_add(GTK_CONTAINER(viewport), filler2);

	// Adjustment
	GtkAdjustment* adj = gtk_adjustment_new(0,0,0,0,0,0);

	// Create a row
	Row* first = create_row(adj, count);

	// Place it
	gtk_grid_insert_row(grid, 0);
	{
		int i;
		SingleCell* iv = first->first;
		for(i=0;i<count;i++) {
			gtk_grid_attach(grid, iv->vbox, i, 0, 1, 1);
			iv = iv->next;
		}
	}

	// Create a row
	Row* second = create_row(adj, count);
	second->prev = first;
	second->next = NULL;
	first->next = second;

	// Place it
	gtk_grid_insert_row(grid, 1);
	{
		int i;
		SingleCell* iv = second->first;
		for(i=0;i<count;i++) {
			gtk_grid_attach(grid, iv->vbox, i, 1, 1, 1);
			iv = iv->next;
		}
	}

	// GTK VSCROLLBAR
//	GtkWidget* scrollbar = gtk_vscrollbar_new(GTK_ADJUSTMENT(adj));
//	gtk_table_attach(GTK_TABLE (table), scrollbar, count, count+1, 0, 2, GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);

/*	GtkWidget* grid = gtk_grid_new ();
	gtk_container_add(GTK_CONTAINER(sw), grid);
	gtk_grid_attach (GTK_GRID (grid), view1, 0, 0, 1, 1);
	gtk_grid_attach_next_to (GTK_GRID (grid), view2, view1, GTK_POS_RIGHT, 1, 1);
*/
/*
	hadj = gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(sw));
	vadj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(sw));
	g_signal_connect_after(G_OBJECT(hadj), "value-changed",
		G_CALLBACK(cb_scroll_event), view);
	g_signal_connect_after(G_OBJECT(vadj), "value-changed",
		G_CALLBACK(cb_scroll_event), view);
*/

	mw->table = grid;
	mw->count = count;
	mw->rows = first;

	//gtk_scrolled_window_set_vadjustment(msw, gtk_scrolled_window_get_vadjustment(ec));
	//gtk_set_hadjustment(self.textviewer.mainview.get_hadjustment())

	return mw;
}

void set_main_window_title(void)
{
	gchar *title;

	title = get_file_basename(pub->fi->filename, TRUE);
	gtk_window_set_title(GTK_WINDOW(pub->mw->window), title);
	g_free(title);
}

int window_get_focused_view()
{
	GtkWidget* focused = gtk_window_get_focus(GTK_WINDOW(pub->mw->window));
	Row* i = pub->mw->rows;
	int counter = 0;
	do {
		counter++;
		if(focused == i->first)
			break;
	} while( (i = i->next) != NULL );

	return counter;
}
