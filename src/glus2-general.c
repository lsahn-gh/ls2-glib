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

gboolean
glus2_set_disconnect_handler (Glus2Handle           *self,
                              LSDisconnectHandler   fptr,
                              gpointer              user_data)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    ret = LSSetDisconnectHandler (priv->handler,
                                  fptr,
                                  user_data,
                                  priv->lserror);

    if (!ret)
        glus2_err_log_if_set (priv->lserror);

    return ret;
}

/*!
 * @brief Register category to Handle
 * 
 * @param  self: Glus2Handle instance
 * @param  category: See Handle docs
 * @param  methods: See Handle docs
 * @param  signals: See Handle docs
 * @param  properties: See Handle docs
 * @return True on success, otherwise failure
 */
gboolean
glus2_register_category (Glus2Handle    *self,
                         const gchar    *category,
                         LSMethod       *methods,
                         LSSignal       *signals,
                         LSProperty     *properties)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    ret = LSRegisterCategory (priv->handler,
                              category,
                              methods,
                              signals,
                              properties,
                              priv->lserror);

    if (!ret)
        glus2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
glus2_register_category_append (Glus2Handle    *self,
                                const gchar    *category,
                                LSMethod       *methods,
                                LSSignal       *signals)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    ret = LSRegisterCategoryAppend (priv->handler,
                                    category,
                                    methods,
                                    signals,
                                    priv->lserror);

    if (!ret)
        glus2_err_log_if_set (priv->lserror);

    return ret;
}

/*!
 * @brief Set a data to the category
 * 
 * @param  self: Glus2Handle instance
 * @param  category: See Handle docs
 * @param  user_data: See Handle docs
 * @return True on success, otherwise failure
 */
gboolean
glus2_category_set_data (Glus2Handle     *self,
                         const gchar     *category,
                         gpointer        user_data)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    ret = LSCategorySetData (priv->handler,
                             category,
                             user_data,
                             priv->lserror);

    if (!ret)
        glus2_err_log_if_set (priv->lserror);

    return ret;
}

gboolean
glus2_method_set_data (Glus2Handle      *self,
                       const gchar      *category,
                       const gchar      *method,
                       gpointer         user_data)
{
    Glus2HandlePrivate *priv;
    gboolean ret;

    glus2_ret_false_if_fail_autodef (self, priv);

    ret = LSCategorySetData (priv->handler,
                             category,
                             user_data,
                             priv->lserror);

    if (!ret)
        glus2_err_log_if_set (priv->lserror);

    return ret;
}
