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

#ifndef GLUS2_SUBSCRIPTION_H
#define GLUS2_SUBSCRIPTION_H

#if !defined (__GLUS2_HEADER_INCLUDE__) && !defined (GLUS2_COMPILATION)
#   error "Only <glus2.h> can be included directly!"
#endif

#include <glib.h>
#include <luna-service2/lunaservice.h>

#include "glus2-handle.h"

G_BEGIN_DECLS

gboolean glus2_subscription_add_default (Glus2Handle    *self,
                                         LSMessage      *msg,
                                         gboolean       *ret_subscribed);

gboolean glus2_subscription_set_cancel_callback (Glus2Handle     *self,
                                                 LSFilterFunc    callback,
                                                 gpointer        user_data);

gboolean glus2_subscription_add (Glus2Handle     *self,
                                 const gchar     *key,
                                 LSMessage       *msg);

gboolean glus2_subscription_acquire (Glus2Handle         *self,
                                     const gchar         *key,
                                     LSSubscriptionIter  **ret_iter);

gboolean glus2_subscription_reply (Glus2Handle   *self,
                                   const gchar   *key,
                                   const gchar   *payload);

gboolean glus2_subscription_post (Glus2Handle    *self,
                                  const gchar    *category,
                                  const gchar    *method,
                                  const gchar    *payload);

guint glus2_subscription_get_subscribers_count (Glus2Handle *self,
                                                const gchar *key);

/* --- For legacy --- */
static inline gboolean
glus2_subscription_process (Glus2Handle    *self,
                            LSMessage      *msg,
                            gboolean       *ret_subscribed)
{
    return glus2_subscription_add_default (self, msg, ret_subscribed);
}

static inline gboolean
glus2_subscription_set_cancel_function (Glus2Handle     *self,
                                        LSFilterFunc    callback,
                                        gpointer        user_data)
{
    return glus2_subscription_set_cancel_callback (self, callback, user_data);
}
/* --- End of legacy --- */

static inline void
glus2_subscription_release (LSSubscriptionIter *iter)
{
    LSSubscriptionRelease (iter);
}

static inline gboolean
glus2_subscription_has_next (LSSubscriptionIter *iter)
{
    return LSSubscriptionHasNext (iter);
}

static inline LSMessage *
glus2_subscription_next (LSSubscriptionIter *iter)
{
    return LSSubscriptionNext (iter);
}

static inline void
glus2_subscription_remove (LSSubscriptionIter *iter)
{
    LSSubscriptionRemove (iter);
}

G_END_DECLS

#endif
