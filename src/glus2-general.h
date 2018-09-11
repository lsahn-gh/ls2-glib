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

#ifndef GLUS2_GENERAL_H
#define GLUS2_GENERAL_H

#if !defined (__GLUS2_HEADER_INCLUDE__) && !defined (GLUS2_COMPILATION)
#   error "Only <glus2.h> can be included directly!"
#endif

#include <glib.h>
#include <luna-service2/lunaservice.h>

#include "glus2-handle.h"

G_BEGIN_DECLS

gboolean        glus2_set_disconnect_handler            (Glus2Handle            *self,
                                                         LSDisconnectHandler    fptr,
                                                         gpointer               user_data);

gboolean        glus2_register_category                 (Glus2Handle    *self,
                                                         const gchar    *category,
                                                         LSMethod       *methods,
                                                         LSSignal       *signals,
                                                         LSProperty     *properties);

gboolean        glus2_register_category_append          (Glus2Handle    *self,
                                                         const gchar    *category,
                                                         LSMethod       *methods,
                                                         LSSignal       *signals);

gboolean        glus2_handle_category_set_data          (Glus2Handle    *self,
                                                         const gchar    *category,
                                                         gpointer       user_data);

gboolean        glus2_method_set_data                   (Glus2Handle    *self,
                                                         const gchar    *category,
                                                         const gchar    *method,
                                                         gpointer       user_data);

G_END_DECLS

#endif
