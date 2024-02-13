#include "exile/core/assertNew.h"
#include <exile/core/API.h>
#include <exile/core/assert.h>
#include <exile.window/shared.h>

#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>

struct wl_compositor *compositor = NULL;
struct wl_shell *shell = NULL;
struct wl_shell_surface *shellSurface = NULL;
struct wl_registry* registry = NULL;
struct wl_surface* surface = NULL;

void registryHandleGlobal(void *data, struct wl_registry *registry, uint32_t id, const char *interface, uint32_t version) {
    if (strcmp(interface, "wl_compositor") == 0) {
        compositor = wl_registry_bind(registry, id, &wl_compositor_interface, 1);
    } else if (strcmp(interface, "wl_shell") == 0) {
        shell = wl_registry_bind(registry, id, &wl_shell_interface, 1);
    }
}

void registryHandleGlobalRemove(void *data, struct wl_registry *registry, uint32_t id) {
    // Not implemented
}

const struct wl_registry_listener registryListener = { 
	.global = registryHandleGlobal,
	.global_remove = registryHandleGlobalRemove
};

//struct exWaylandWindowHandle
//{
//	struct wl_shell_surface* surface;
//	
//};

struct wl_display* display = NULL;
EXILE_API_EXPORT u8 exWindowCreate(exWindow* out, const char* title, u32 weight, u32 height, exWindowCreationFlag flags)
{
	if(display == NULL)
	{
		display = wl_display_connect(NULL);
		exAssertR(display == NULL, {}, EX_ERROR, "Can`t connect to wayland display!");
	}

	registry = wl_display_get_registry(display);
	wl_registry_add_listener(registry, &registryListener, NULL);	
	wl_display_roundtrip(display);

	exAssertDebugR(compositor == NULL || shell == NULL, {}, EX_ERROR, "failed to get compositor or shell");


	surface = wl_compositor_create_surface(compositor);
	
	exAssertDebugR(surface == NULL, {}, EX_ERROR, "failed to create surface");


	shellSurface = wl_shell_get_shell_surface(shell, surface);

	wl_shell_surface_set_toplevel(shellSurface);
	wl_display_roundtrip(display);

	return EX_SUCCESS;
}


EXILE_API_EXPORT u8 exWindowUpdate(exWindow* wnd)
{
	int32_t res = wl_display_dispatch(display);

	return res != -1;
}

EXILE_API_EXPORT u8 exWindowShouldClose(exWindow* wnd)
{
	return wnd->closed;	
}

EXILE_API_EXPORT void exWindowClose(exWindow* wnd)
{
	wnd->closed = EX_TRUE;
	wl_shell_surface_destroy(shellSurface);
	wl_surface_destroy(surface);
	wl_shell_destroy(shell);
	wl_compositor_destroy(compositor);
	wl_registry_destroy(registry);
	wl_display_disconnect(display);

}
