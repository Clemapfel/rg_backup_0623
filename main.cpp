#include <mousetrap.hpp>

#include <deque>
#include <iostream>
#include <thread>
#include <memory>

using namespace mousetrap;

///
inline struct State {
    Window window;
}* state = nullptr;

int main()
{
    auto app = Application("mousetrap.debug");

    app.connect_signal_activate([&](Application* app) -> void
    {
        state = new State {
            Window(*app)
        };

        log::set_surpress_debug(MOUSETRAP_DOMAIN, false);

        static auto spin = SpinButton(0, 1, 0.001);
        spin.set_value_to_text_function([](const SpinButton* instance, float value) -> std::string{
            return std::to_string(value) + "%";
        });

        static auto scale = Scale(0, 1, 0.01);

        auto column_view = ColumnView();
        column_view.push_back_column("01");
        column_view.push_back_column("02");

        auto label = Label("test");
        column_view.append_row(label);

        /*
        for (size_t i = 0; i < n_rows; ++i)
        {
            std::vector<Widget*> row;


            column_view.push_back_row(row);
            std::cout << i << std::endl;
        }
         */

        state->window.set_child(column_view);
        state->window.present();
    });

    app.connect_signal_shutdown([](Application* app) -> void{
        delete state;
    });

    return app.run();
}