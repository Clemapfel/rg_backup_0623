#include <SFML/Window.hpp>

#include <mousetrap/include/shape.hpp>
#include <mousetrap/include/render_task.hpp>
#include <mousetrap/include/image.hpp>
#include <mousetrap/include/sound.hpp>
#include <mousetrap/include/sound_stream.hpp>
#include <mousetrap/include/application.hpp>
#include <mousetrap/include/window.hpp>
#include <mousetrap/include/motion_event_controller.hpp>
#include <mousetrap/include/label.hpp>
#include <mousetrap/include/text_view.hpp>
#include <mousetrap/include/box.hpp>
#include <mousetrap/include/frame.hpp>
#include <mousetrap/include/button.hpp>
#include <mousetrap/include/list_view.hpp>
#include <mousetrap/include/popover_menu_button.hpp>
#include <mousetrap/include/stack.hpp>

#include <deque>
#include <iostream>

using namespace mousetrap;

inline Window* window = nullptr;
inline Application* app = nullptr;

inline Action* action;

static void on_select(GtkSelectionModel* model, int32_t i, int32_t n)
{
    std::cout << "postition: " << i << " | " << "n: " << n << std::endl;
}

static void startup(GApplication*)
{
    window = new Window(*app);

    action = new Action("global.test_action");
    action->set_function([](auto test2){
        std::cout << test2 << std::endl;
    }, "testest");
    action->add_shortcut("<Control>c");
    app->add_action(action);

    auto menu_model = MenuModel();
    menu_model.add_action("test", *action);

    window->connect_signal_close_request([](Window*) -> bool {
        std::cout << "close" << std::endl;
        return false;
    });

    auto* stack = new Stack();
    for (size_t i = 0; i < 10; ++i)
    {
        auto* label = new Label("<span size=\"1000%\">" + std::to_string(i) + "</span>");
        label->set_size_request({300, 300});
        stack->add_child(label, "0" + std::to_string(i));
    }

    stack->get_selection_model()->connect_signal_selection_changed([](SelectionModel*, int32_t i, int32_t n){
        std::cout << "postition: " << i << " | " << "n: " << n << std::endl;
    });

    //g_signal_connect(gtk_stack_get_pages(stack->operator _GtkStack *()), "selection-changed", G_CALLBACK(on_select), nullptr);

    auto switcher = StackSwitcher(stack);
    auto box = Box(Orientation::VERTICAL);
    box.push_back(stack);
    box.push_back(&switcher);
    window->set_child(&box);

    window->show();
    window->present();
    window->set_focusable(true);
    window->grab_focus();
}

int main()
{
    app = new Application();
    app->connect_signal_activate([](Application* app){
        std::cout << "activate " << app << std::endl;
    });

    app->connect_signal("startup", startup);

    std::cout << app << std::endl;
    return app->run();

    delete app;
    delete window;

    return 0;
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