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

#ifndef GLS2_GENERAL_H
#define GLS2_GENERAL_H

#if !defined (__GLS2_HEADER_INCLUDE__) && !defined (GLS2_COMPILATION)
#   error "Only <gls2/gls2.h> can be included directly!"
#endif

#include <glib.h>
#include <luna-service2/lunaservice.h>

#include "gls2-handle.h"

G_BEGIN_DECLS

gboolean        gls2_set_disconnect_handler         (Gls2Handle             *self,
                                                     LSDisconnectHandler    fptr,
                                                     gpointer               user_data);

gboolean        gls2_register_category              (Gls2Handle     *self,
                                                     const gchar    *category,
                                                     LSMethod       *methods,
                                                     LSSignal       *signals,
                                                     LSProperty     *properties);

gboolean        gls2_register_category_append       (Gls2Handle     *self,
                                                     const gchar    *category,
                                                     LSMethod       *methods,
                                                     LSSignal       *signals);

gboolean        gls2_handle_category_set_data       (Gls2Handle     *self,
                                                     const gchar    *category,
                                                     gpointer       user_data);

gboolean        gls2_method_set_data                (Gls2Handle     *self,
                                                     const gchar    *category,
                                                     const gchar    *method,
                                                     gpointer       user_data);

G_END_DECLS

#endif
