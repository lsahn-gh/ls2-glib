/*
 * Copyright 2018 Yi-Soo An <yisooan@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GLUS2_MAINLOOP_H
#define GLUS2_MAINLOOP_H

#if !defined (__GLUS2_HEADER_INCLUDE__) && !defined (GLUS2_COMPILATION)
#   error "Only <glus2.h> can be included directly!"
#endif

#include <glib.h>

#include "glus2-handle.h"

G_BEGIN_DECLS

GMainContext * glus2_g_main_get_context (Glus2Handle   *self);

gboolean glus2_g_main_attach_with_context (Glus2Handle    *self,
                                           GMainContext   *ctx);

gboolean glus2_handle_g_main_attach (Glus2Handle    *self,
                                     GMainLoop      *mainloop);

gboolean glus2_g_main_attach_with_default_context (Glus2Handle *self);

gboolean glus2_g_main_detach (Glus2Handle *self);

gboolean glus2_g_main_set_priority (Glus2Handle  *self,
                                    gint         priority);

G_END_DECLS

#endif
