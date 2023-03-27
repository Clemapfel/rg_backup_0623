#include <SFML/Window.hpp>

#include <mousetrap/include/shape.hpp>
#include <mousetrap/include/render_task.hpp>
#include <mousetrap/include/image.hpp>
#include <mousetrap/include/sound.hpp>
#include <mousetrap/include/application.hpp>
#include <mousetrap/include/window.hpp>
#include <mousetrap/include/motion_event_controller.hpp>
#include <mousetrap/include/label.hpp>
#include <mousetrap/include/text_view.hpp>
#include <mousetrap/include/box.hpp>
#include <mousetrap/include/frame.hpp>
#include <mousetrap/include/button.hpp>
#include <mousetrap/include/list_view.hpp>
#include <mousetrap/include/column_view.hpp>
#include <mousetrap/include/popover_menu_button.hpp>
#include <mousetrap/include/stack.hpp>
#include <mousetrap/include/notebook.hpp>
#include <mousetrap/include/spin_button.hpp>
#include <mousetrap/include/drop_down.hpp>
#include <mousetrap/include/scale.hpp>
#include <mousetrap/include/file_system.hpp>
#include <mousetrap/include/spinner.hpp>
#include <mousetrap/include/grid_view.hpp>
#include <mousetrap/include/image_display.hpp>
#include <mousetrap/include/scrolled_window.hpp>
#include <mousetrap/include/icon.hpp>

#include <deque>
#include <iostream>

using namespace mousetrap;

inline Window* window = nullptr;
inline Application* app = nullptr;

inline Action* action;

static void startup(GApplication*)
{
    window = new Window(*app);
    window->set_show_menubar(true);

    action = new Action("global.test_action");
    action->set_function([](auto test2){
    }, "testest");
    action->add_shortcut("<Control>c");
    app->add_action(action);

    auto menu_model = MenuModel();
    menu_model.add_action("test", *action);

    window->connect_signal_close_request([](Window*) -> bool {
        std::cout << "close" << std::endl;
        return false;
    });

    auto* box = new Box(Orientation::VERTICAL);
    auto* spinner = new Spinner();

    auto* button_spin = new Button();

    auto* view = new ListView(Orientation::VERTICAL);
    auto* theme = new IconTheme();

    theme->add_resource_path("/home/clem/Desktop/icons/hicolor/48x48/");
    std::cout << theme->has_icon("rat_icon_desktop") << std::endl;
    exit(0);

    for (auto id : theme->get_icon_names())
    {
        auto* icon = new Icon();
        icon->create_from_theme(*theme, id, 64);
        auto* image = new ImageDisplay();
        image->create_from_icon(*icon);

        auto* box = new Box(Orientation::HORIZONTAL);
        box->set_spacing(10);

        box->push_back(image);
        box->push_back(new Label(id));
        view->push_back(box);
    }

    auto* scrolled_window = new ScrolledWindow();
    scrolled_window->set_child(view);

    window->set_child(scrolled_window);

    window->show();
    window->present();
    window->set_is_focusable(true);
    window->grab_focus();
}

int main()
{
    app = new Application("app.mousetrap");
    app->connect_signal_activate([](Application* app)
    {
        // TODO menubar doesn't show up
    });

    app->connect_signal("startup", startup);

    auto out = app->run();

    delete app;
    delete window;

    return out;
    /*
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(0, 0, 8, 3, 2));
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    initialize_opengl();

    std::set<Vector2f> test;

    std::deque<Shape> shapes;
    for (size_t x = 0; x < 4; ++x)
    {
        shapes.emplace_back();
        shapes.back().as_rectangle(Vector2f(x / 4.f), Vector2f{0.5, 0.5});
        shapes.back().set_color(HSVA(rand() / float(RAND_MAX), 1, 1, 1));
    }

    std::deque<RenderTask> tasks;
    for (auto& shape : shapes)
    {
        tasks.emplace_back(&shape);
    }

    bool running = true;
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                running = false;
            else if (event.type == sf::Event::Resized)
                glViewport(0, 0, event.size.width, event.size.height);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& task : tasks)
            task.render();

        glFlush();
        window.display();
    }

    return 0;
     */
}