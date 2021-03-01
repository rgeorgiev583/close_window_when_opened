#define WNCK_I_KNOW_THIS_IS_UNSTABLE 1
#include <libwnck/libwnck.h>
#include <stdbool.h>

static char* window_title;
static int window_open_count = 1, current_window_open_count = 0;
static bool allow_inexact_matching_of_window_title = false;

static GMainLoop* main_loop;

static void on_window_opened(WnckScreen* screen, WnckWindow* window, gpointer data)
{
    const char* current_window_title = wnck_window_get_name(window);
    if (allow_inexact_matching_of_window_title && strstr(window_title, current_window_title) || !strcmp(window_title, current_window_title)) {
        wnck_window_close(window, 0);
        current_window_open_count++;
        if (current_window_open_count == window_open_count)
            g_main_loop_quit(main_loop);
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
        exit(EXIT_FAILURE);

    char opt;
    while ((opt = getopt(argc, argv, "c:i")) != -1) {
        switch (opt) {
        case 'c':
            window_open_count = atoi(optarg);
            break;

        case 'i':
            allow_inexact_matching_of_window_title = true;
            break;
        }
    }

    if (optind >= argc || window_open_count <= 0)
        exit(EXIT_FAILURE);

    window_title = argv[optind];

    gdk_init(&argc, &argv);

    WnckScreen* screen = wnck_screen_get_default();
    wnck_screen_force_update(screen);
    g_signal_connect(screen, "window-opened", G_CALLBACK(on_window_opened), NULL);

    main_loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(main_loop);
    g_main_loop_unref(main_loop);
}
