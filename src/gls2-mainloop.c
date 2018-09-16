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

GMainContext *
gls2_g_main_get_context (Gls2Handle   *self)
{
    Gls2HandlePrivate *priv;
    GMainContext *ctx;

    gls2_ret_null_if_fail_autodef (self, priv);

    if ( (ctx = LSGmainGetContext (priv->handler, priv-lserror)) == NULL )
        gls2_err_log_if_set (priv->lserror);

    return ctx;
}

gboolean
gls2_g_main_attach_with_context (Gls2Handle     *self,
                                 GMainContext   *ctx)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    ret = LSGmainContextAttach (priv->handler, ctx, priv->lserror);

    if (!ret)
        gls2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
gls2_g_main_attach (Gls2Handle     *self,
                    GMainLoop      *mainloop)
{
    GMainContext *ctx;

    gls2_ret_false_if_fail (self != NULL);
    gls2_ret_false_if_fail (mainloop != NULL);

    ctx = g_main_loop_get_context (mainloop);

    return gls2_g_main_attach_with_context (self, ctx);
}

gboolean
gls2_g_main_attach_with_default_context (Gls2Handle *self)
{
    GMainContext *ctx;

    gls2_ret_false_if_fail (self != NULL);
    
    ctx = g_main_context_default ();

    return gls2_g_main_attach_with_context (self, ctx);
}

gboolean
gls2_g_main_detach (Gls2Handle *self)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    if ( !(ret = LSGmainDetach (priv->handler, priv->lserror)) )
        gls2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
gls2_g_main_set_priority (Gls2Handle   *self,
                          gint         priority)
{
    Gls2HandlePrivate *priv;
    gboolean ret;

    gls2_ret_false_if_fail_autodef (self, priv);

    ret = LSGmainSetPriority (priv->handler,
                              priority,
                              priv->lserror);

    if (!ret)
        gls2_err_log_if_set (priv->lserror);

    return ret;
}
