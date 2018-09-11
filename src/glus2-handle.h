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

#ifndef GLUS2_HANDLE_H
#define GLUS2_HANDLE_H

#if !defined (__GLUS2_HEADER_INCLUDE__) && !defined (GLUS2_COMPILATION)
#   error "Only <glus2.h> can be included directly!"
#endif

#include <glib.h>
#include <luna-service2/lunaservice.h>

G_BEGIN_DECLS

typedef struct _Glus2Handle             Glus2Handle;
typedef struct _Glus2HandleClass        Glus2HandleClass;
typedef struct _Glus2HandlePrivate      Glus2HandlePrivate;

G_DEFINE_AUTOPTR_CLEANUP_FUNC (Glus2Handle, g_object_unref)

#define GLUS2_TYPE_HANDLE              (glus2_handle_get_type ())
#define GLUS2_HANDLE(obj)              (G_TYPE_CHECK_INSTANCE_CAST(obj, \
                                                                   GLUS2_TYPE_HANDLE, \
                                                                   Glus2Handle))
#define GLUS2_HANDLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST(klass, \
                                                                GLUS2_TYPE_HANDLE, \
                                                                Glus2HandleClass))
#define GLUS2_IS_HANDLE(obj)           (G_TYPE_CHECK_INSTANCE_TYPE(obj, \
                                                                   GLUS2_TYPE_HANDLE))
#define GLUS2_IS_HANDLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE(klass, \
                                                                GLUS2_TYPE_HANDLE))
#define GLUS2_HANDLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS(obj, \
                                                                  GLUS2_TYPE_HANDLE, \
                                                                  Glus2HandleClass))

GType               glus2_handle_get_type               (void);

Glus2Handle *       glus2_handle_new                    (const gchar    *service_name);
Glus2Handle *       glus2_handle_new_with_app_id        (const gchar    *service_name,
                                                         const gchar    *app_id);

const LSHandle *    glus2_handle_get_lshandle           (Glus2Handle    *self);
const gchar *       glus2_handle_get_service_name       (Glus2Handle    *self);
gchar *             glus2_handle_dup_service_name       (Glus2Handle    *self);
const gchar *       glus2_handle_get_app_id             (Glus2Handle    *self);
gchar *             glus2_handle_dup_app_id             (Glus2Handle    *self);

G_END_DECLS

#endif
