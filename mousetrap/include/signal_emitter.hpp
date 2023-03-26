//
// Copyright 2022 Clemens Cords
// Created on 8/26/22 by clem (mail@clemens-cords.com)
//

#pragma once

#include <gtk/gtk.h>

#include <string>
#include <map>
#include <vector>

namespace mousetrap
{
    /// @brief object that can emit GLib signals, for internal use only
    class SignalEmitter
    {
        public:
            /// @brief block a signal by id
            /// @param b true if signal handler should not be invoked, false otherwise
            void set_signal_blocked(const std::string& signal_id, bool);

            /// @brief get list of possible signal ids
            /// @param vector of signals names
            std::vector<std::string> get_all_signal_names();

            /// @brief connect static function to signal, does not work with lambdas, for internal use only
            /// @tparam Function_t static function pointer, the user is responsible for asserting that the function has the correct signature
            /// @param signal_id glib id of the signal
            /// @param data void-pointer to arbitrary data
            template<typename Function_t>
            void connect_signal(const std::string& signal_id, Function_t*, void* data = nullptr);

            /// @brief disconnect signal, it may not be invoked until reconnected, if signal is not registered, does nothing. For internal use only
            /// @param signal_id
            void disconnect_signal(const std::string& signal_id);

            /// @brief expose as GObject, for internal use only
            virtual operator GObject*() = 0;

        private:
            struct SignalHandler
            {
                size_t id;
                bool is_blocked = false;
            };

            std::map<std::string, SignalHandler> _signal_handlers = {};
    };
}

#include <src/signal_emitter.inl>