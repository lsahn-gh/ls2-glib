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

#ifndef GLS2_HANDLE_PRIV_H
#define GLS2_HANDLE_PRIV_H

#if !defined (__GLS2_HEADER_INCLUDE__) && !defined (GLS2_COMPILATION)
#   error "Only <gls2/gls2.h> can be included directly!"
#endif

#include <glib.h>
#include <luna-service2/lunaservice.h>

G_BEGIN_DECLS

#define     GLS2_SMALL_PADDING     2
#define     GLS2_PADDING           8

struct _Gls2Handle
{
    /* Private */
    GObject     parent;

    Gls2HandlePrivate *priv;
};

struct _Gls2HandleClass
{
    GObjectClass parent_class;

    /* Private */
    gpointer _reserved[GLS2_PADDING];
};

struct _Gls2HandlePrivate
{
    LSHandle        *handler;
    LSError         *lserror;

    gchar       *service_name;
    gchar       *application_id;
};

G_END_DECLS

#endif
