//
// Copyright 2022 Clemens Cords
// Created on 9/1/22 by clem (mail@clemens-cords.com)
//

#pragma once

#include <gtk/gtk.h>
#include <vector>

#include <include/widget.hpp>
#include <include/orientable.hpp>
#include <include/selection_model.hpp>

namespace mousetrap
{
    namespace detail { struct _ListViewItem; }

    class ListView : public WidgetImplementation<GtkListView>, public Orientable,
        HAS_SIGNAL(ListView, activate)
    {
        public:
            using Iterator = detail::_ListViewItem*;

            ListView(Orientation = Orientation::HORIZONTAL, SelectionMode = SelectionMode::NONE);
            ~ListView();

            Iterator push_back(Widget* widget, Iterator = nullptr);
            Iterator push_front(Widget* widget, Iterator = nullptr);
            Iterator insert(size_t, Widget*, Iterator = nullptr);
            void remove(size_t, Iterator = nullptr);
            void clear(Iterator = nullptr);

            Widget* get_widget_at(size_t i, Iterator = nullptr);
            void set_widget_at(size_t i, Widget*, Iterator = nullptr);

            void set_enable_rubberband_selection(bool);
            bool get_enable_rubberband_selection() const;

            void set_show_separators(bool);
            bool get_show_separators() const;

            void set_single_click_activate(bool);
            bool get_single_click_activate() const;

            SelectionModel* get_selection_model();
            size_t get_n_items() const;

            void set_orientation(Orientation) override;
            Orientation get_orientation() const override;

        private:
            static void on_list_item_factory_setup(GtkSignalListItemFactory* self, void* object, void*);
            static void on_list_item_factory_teardown(GtkSignalListItemFactory* self, void* object, void*);
            static void on_list_item_factory_bind(GtkSignalListItemFactory* self, void* object, void*);
            static void on_list_item_factory_unbind(GtkSignalListItemFactory* self, void* object, void*);

            static GListModel* on_tree_list_model_create(void* item, void* user_data);
            static void on_tree_list_model_destroy(void* item);

            GtkSignalListItemFactory* _factory;

            GtkListView* _list_view;
            GListStore* _root;
            GtkTreeListModel* _tree_list_model;

            SelectionModel* _selection_model;
            GtkSelectionMode _selection_mode;
            GtkOrientation _orientation;
    };

    using TreeListView = ListView;
}
