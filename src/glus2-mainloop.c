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

#include <glus2/glus2.h>

GMainContext *
glus2_g_main_get_context (Glus2Handle   *self)
{
    Glus2HandlePrivate *priv;
    GMainContext *ctx;

    glus2_ret_null_if_fail_autodef (self, priv);

    if ( (ctx = LSGmainGetContext (priv->handler, priv-lserror)) == NULL )
        glus2_err_log_if_set (priv->lserror);

    return ctx;
}

gboolean
glus2_g_main_attach_with_context (Glus2Handle    *self,
                                  GMainContext   *ctx)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    ret = LSGmainContextAttach (priv->handler, ctx, priv->lserror);

    if (!ret)
        glus2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
glus2_g_main_attach (Glus2Handle    *self,
                     GMainLoop      *mainloop)
{
    GMainContext *ctx;

    glus2_ret_false_if_fail (self != NULL);
    glus2_ret_false_if_fail (mainloop != NULL);

    ctx = g_main_loop_get_context (mainloop);

    return glus2_g_main_context_attach (self, ctx);
}

gboolean
glus2_g_main_attach_with_default_context (Glus2Handle *self)
{
    GMainContext *ctx;

    glus2_ret_false_if_fail (self != NULL);
    
    ctx = g_main_context_default ();

    return glus2_g_main_context_attach (self, ctx);
}

gboolean
glus2_g_main_detach (Glus2Handle *self)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    if ( !(ret = LSGmainDetach (priv->handler, priv->lserror)) )
        glus2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
glus2_g_main_set_priority (Glus2Handle  *self,
                           gint         priority)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    ret = LSGmainSetPriority (priv->handler,
                              priority,
                              priv->lserror);

    if (!ret)
        glus2_err_log_if_set (priv->lserror);

    return ret;
}
