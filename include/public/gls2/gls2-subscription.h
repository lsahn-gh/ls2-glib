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

#ifndef GLS2_SUBSCRIPTION_H
#define GLS2_SUBSCRIPTION_H

#if !defined (__GLS2_HEADER_INCLUDE__) && !defined (GLS2_COMPILATION)
#   error "Only <gls2/gls2.h> can be included directly!"
#endif

#include <glib.h>
#include <luna-service2/lunaservice.h>

#include "gls2-handle.h"

G_BEGIN_DECLS

gboolean gls2_subscription_add_default (Gls2Handle     *self,
                                        LSMessage      *msg,
                                        bool           *ret_subscribed);

gboolean gls2_subscription_set_cancel_callback (Gls2Handle      *self,
                                                LSFilterFunc    callback,
                                                gpointer        user_data);

gboolean gls2_subscription_add (Gls2Handle      *self,
                                const gchar     *key,
                                LSMessage       *msg);

gboolean gls2_subscription_acquire (Gls2Handle          *self,
                                    const gchar         *key,
                                    LSSubscriptionIter  **ret_iter);

gboolean gls2_subscription_reply (Gls2Handle    *self,
                                  const gchar   *key,
                                  const gchar   *payload);

gboolean gls2_subscription_post (Gls2Handle     *self,
                                 const gchar    *category,
                                 const gchar    *method,
                                 const gchar    *payload);

guint gls2_subscription_get_subscribers_count (Gls2Handle  *self,
                                               const gchar *key);

/* --- For legacy --- */
static inline gboolean
gls2_subscription_process (Gls2Handle     *self,
                           LSMessage      *msg,
                           bool           *ret_subscribed)
{
    return gls2_subscription_add_default (self, msg, ret_subscribed);
}

static inline gboolean
gls2_subscription_set_cancel_function (Gls2Handle      *self,
                                       LSFilterFunc    callback,
                                       gpointer        user_data)
{
    return gls2_subscription_set_cancel_callback (self, callback, user_data);
}
/* --- End of legacy --- */

static inline void
gls2_subscription_release (LSSubscriptionIter *iter)
{
    LSSubscriptionRelease (iter);
}

static inline gboolean
gls2_subscription_has_next (LSSubscriptionIter *iter)
{
    return LSSubscriptionHasNext (iter);
}

static inline LSMessage *
gls2_subscription_next (LSSubscriptionIter *iter)
{
    return LSSubscriptionNext (iter);
}

static inline void
gls2_subscription_remove (LSSubscriptionIter *iter)
{
    LSSubscriptionRemove (iter);
}

G_END_DECLS

#endif
