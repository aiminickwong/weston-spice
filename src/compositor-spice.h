/*
 * Copyright © 2013 Yury Shvedov <shved@lvk.cs.msu.su>
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of the copyright holders not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.  The copyright holders make
 * no representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
 * CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef COMPOSITOR_SPICE_H
#define COMPOSITOR_SPICE_H

#include <spice.h>

#include <weston/compositor.h>
#include <assert.h>

#include "compositor-spice-conf.h"

#define NUM_MEMSLOTS        1
#define NUM_MEMSLOTS_GROUPS 1
#define NUM_SURFACES        2
#define MEMSLOT_ID_BITS     1
#define MEMSLOT_GEN_BITS    1

#define MEMSLOT_GROUP 0

#define MAX_WIDTH 1920
#define MAX_HEIGHT 1080

#define dprint(lvl, fmt, ...) \
    if ((lvl) <= DEBUG) weston_log("%s: " fmt "\n", __func__, ## __VA_ARGS__)
#define weston_log_error(err_str)\
    weston_log("%s: error detected. %s returned.\n", __func__, (err_str));
struct spice_compositor {
    struct weston_compositor base;

    SpiceServer *spice_server;

    QXLInstance display_sin;
    SpiceMouseInstance mouse_sin;
    SpiceKbdInstance kbd_sin;

    SpiceCoreInterface *core;
    SpiceTimer *wakeup_timer;
    QXLWorker *worker;
  
    struct spice_output *primary_output;
    struct weston_seat core_seat;

    void (*produce_command) (struct spice_compositor*);
    int (*push_command) (struct spice_compositor*, QXLCommandExt *);
    void (*release_resource) (struct spice_compositor*, QXLCommandExt *);

    void (*pixman_renderer_repaint_output) (struct weston_output *output_base,
            pixman_region32_t *damage);

};

uint32_t
spice_get_primary_surface_id (struct spice_compositor *c);

#endif //COMPOSITOR_SPICE_H
