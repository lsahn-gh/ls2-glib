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

#include <gls2/gls2.h>

gboolean
gls2_subscription_add_default (Gls2Handle      *self,
                               LSMessage       *msg,
                               bool            *ret_subscribed)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    ret = LSSubscriptionProcess (priv->handler, msg, ret_subscribed, priv->lserror);

    if (!ret)
        gls2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
gls2_subscription_set_cancel_callback (Gls2Handle      *self,
                                       LSFilterFunc    callback,
                                       gpointer        user_data)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    ret = LSSubscriptionSetCancelFunction (priv->handler, callback, user_data, priv->lserror);

    if (!ret)
        gls2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
gls2_subscription_add (Gls2Handle      *self,
                       const gchar     *key,
                       LSMessage       *msg)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    ret = LSSubscriptionAdd (priv->handler, key, msg, priv->lserror);

    if (!ret)
        gls2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
gls2_subscription_acquire (Gls2Handle          *self,
                           const gchar         *key,
                           LSSubscriptionIter  **ret_iter)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    ret = LSSubscriptionAcquire (priv->handler, key, ret_iter, priv->lserror);

    if (!ret)
        gls2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
gls2_subscription_reply (Gls2Handle    *self,
                         const gchar   *key,
                         const gchar   *payload)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    ret = LSSubscriptionReply (priv->handler, key, payload, priv->lserror);

    if (!ret)
        gls2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
gls2_subscription_post (Gls2Handle     *self,
                        const gchar    *category,
                        const gchar    *method,
                        const gchar    *payload)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    ret = LSSubscriptionPost (priv->handler,
                              category,
                              method,
                              payload,
                              priv->lserror);

    if (!ret)
        gls2_err_log_if_set (priv->lserror);

    return ret;
}

guint
gls2_subscription_get_subscribers_count (Gls2Handle  *self,
                                         const gchar *key)
{
    Gls2HandlePrivate *priv;
    guint ret;

    gls2_ret_val_if_fail_autodef (self, priv, 0);

    ret = LSSubscriptionGetHandleSubscribersCount (priv->handler, key);

    return ret;
}
