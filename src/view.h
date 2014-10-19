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

#ifndef _VIEW_H
#define _VIEW_H

gint get_current_keyval(void);
void clear_current_keyval(void);
void scroll_to_cursor(GtkTextBuffer *buffer, gdouble within_margin);
void force_call_cb_modified_changed(GtkWidget *view);
void force_block_cb_modified_changed(GtkWidget *view);
void force_unblock_cb_modified_changed(GtkWidget *view);
void set_view_scroll(void);
gint check_text_modification(void);
GtkWidget *create_text_view(void);

typedef struct SingleCellStruct {
	GtkWidget*	vbox;
	GtkWidget*	text;
	GtkTextBuffer*	buffer;
	struct SingleCellStruct*	prev;
	struct SingleCellStruct*	next;
} SingleCell;

typedef struct RowStruct {
	SingleCell*		first;
	struct RowStruct*		prev;
	struct RowStruct*		next;
} Row;

SingleCell* create_cell();
Row* create_row(GtkAdjustment* adj, int count);

#endif /* _VIEW_H */
