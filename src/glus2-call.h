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

#ifndef GLUS2_CALL_H
#define GLUS2_CALL_H

#if !defined (__GLUS2_HEADER_INCLUDE__) && !defined (GLUS2_COMPILATION)
#   error "Only <glus2.h> can be included directly!"
#endif

#include <glib.h>
#include <luna-service2/lunaservice.h>

#include "glus2-handle.h"

G_BEGIN_DECLS

gboolean glus2_call_add_cancel_notification (Glus2Handle                 *self,
                                             LSCancelNotificationFunc    fptr,
                                             gpointer                    user_data);

gboolean glus2_call_remove_cancel_notification (Glus2Handle              *self,
                                                LSCancelNotificationFunc fptr,
                                                gpointer                 user_data);

gboolean glus2_call (Glus2Handle     *self,
                     const gchar     *uri,
                     const gchar     *payload,
                     LSFilterFunc    callback,
                     gpointer        user_data,
                     LSMessageToken  *ret_token,
                     gboolean        one_reply);

gboolean glus2_call_from_application (Glus2Handle        *self,
                                      const gchar        *uri,
                                      const gchar        *payload,
                                      const gchar        *app_id,
                                      LSFilterFunc       callback,
                                      gpointer           user_data,
                                      LSMessageToken     *ret_token,
                                      gboolean           one_reply);

gboolean glus2_call_cancel (Glus2Handle      *self,
                            LSMessageToken   token);

gboolean glus2_call_set_timeout (Glus2Handle     *self,
                                 LSMessageToken  token,
                                 gint            timeout_ms);

gboolean glus2_call_set_timeout_seconds (Glus2Handle       *self,
                                         LSMessageToken    token,
                                         gint              timeout_sec);

gboolean glus2_call_set_timeout_minutes (Glus2Handle       *self,
                                         LSMessageToken    token,
                                         gint              timeout_min);

G_END_DECLS

#endif
