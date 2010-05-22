/* The Ruby interface to the notmuch mail library
 *
 * Copyright © 2010 Ali Polatel
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/ .
 *
 * Author: Ali Polatel <alip@exherbo.org>
 */

#ifndef DEFS_H
#define DEFS_H

#include <notmuch.h>
#include <ruby.h>

VALUE notmuch_rb_cDatabase;
VALUE notmuch_rb_cDirectory;
VALUE notmuch_rb_cFileNames;
VALUE notmuch_rb_cQuery;
VALUE notmuch_rb_cThreads;
VALUE notmuch_rb_cThread;
VALUE notmuch_rb_cMessages;
VALUE notmuch_rb_cMessage;
VALUE notmuch_rb_cTags;

VALUE notmuch_rb_eBaseError;
VALUE notmuch_rb_eDatabaseError;
VALUE notmuch_rb_eMemoryError;
VALUE notmuch_rb_eReadOnlyError;
VALUE notmuch_rb_eXapianError;
VALUE notmuch_rb_eFileError;
VALUE notmuch_rb_eFileNotEmailError;
VALUE notmuch_rb_eNullPointerError;
VALUE notmuch_rb_eTagTooLongError;
VALUE notmuch_rb_eUnbalancedFreezeThawError;

ID ID_call;
ID ID_db_create;
ID ID_db_mode;

typedef struct {
    notmuch_database_t *nm_db;
} notmuch_rb_database_t;

typedef struct {
    notmuch_directory_t *nm_dir;
    VALUE db;
} notmuch_rb_directory_t;

typedef struct {
    notmuch_filenames_t *nm_flist;
    VALUE dir;
} notmuch_rb_filenames_t;

typedef struct {
    notmuch_query_t *nm_query;
    VALUE db;
} notmuch_rb_query_t;

typedef struct {
    notmuch_threads_t *nm_threads;
    VALUE query;
} notmuch_rb_threads_t;

typedef struct {
    notmuch_messages_t *nm_messages;
    VALUE parent;
} notmuch_rb_messages_t;

typedef struct {
    notmuch_thread_t *nm_thread;
    VALUE threads;
} notmuch_rb_thread_t;

typedef struct {
    notmuch_message_t *nm_message;
    VALUE parent;
} notmuch_rb_message_t;

typedef struct {
    notmuch_tags_t *nm_tags;
    VALUE parent;
} notmuch_rb_tags_t;

/* status.c */
void
notmuch_rb_status_raise(notmuch_status_t status);

/* gc.c */
void
notmuch_rb_database_free(notmuch_rb_database_t *db);

void
notmuch_rb_directory_mark(notmuch_rb_directory_t *dir);

void
notmuch_rb_directory_free(notmuch_rb_directory_t *dir);

void
notmuch_rb_filenames_mark(notmuch_rb_filenames_t *flist);

void
notmuch_rb_filenames_free(notmuch_rb_filenames_t *flist);

void
notmuch_rb_query_mark(notmuch_rb_query_t *query);

void
notmuch_rb_query_free(notmuch_rb_query_t *query);

void
notmuch_rb_threads_mark(notmuch_rb_threads_t *threads);

void
notmuch_rb_threads_free(notmuch_rb_threads_t *threads);

void
notmuch_rb_messages_mark(notmuch_rb_messages_t *messages);

void
notmuch_rb_messages_free(notmuch_rb_messages_t *messages);

void
notmuch_rb_thread_mark(notmuch_rb_thread_t *thread);

void
notmuch_rb_thread_free(notmuch_rb_thread_t *thread);

void
notmuch_rb_message_mark(notmuch_rb_message_t *message);

void
notmuch_rb_message_free(notmuch_rb_message_t *message);

void
notmuch_rb_tags_mark(notmuch_rb_tags_t *tags);

void
notmuch_rb_tags_free(notmuch_rb_tags_t *tags);

/* database.c */
VALUE
notmuch_rb_database_new(int argc, VALUE *argv, VALUE klass);

VALUE
notmuch_rb_database_close(VALUE self);

VALUE
notmuch_rb_database_path(VALUE self);

VALUE
notmuch_rb_database_version(VALUE self);

VALUE
notmuch_rb_database_needs_upgrade(VALUE self);

VALUE
notmuch_rb_database_upgrade(VALUE self);

VALUE
notmuch_rb_database_get_directory(VALUE self, VALUE pathv);

VALUE
notmuch_rb_database_add_message(VALUE self, VALUE pathv);

VALUE
notmuch_rb_database_remove_message(VALUE self, VALUE pathv);

VALUE
notmuch_rb_database_query_create(VALUE self, VALUE qstrv);

/* directory.c */
VALUE
notmuch_rb_directory_get_mtime(VALUE self);

VALUE
notmuch_rb_directory_set_mtime(VALUE self, VALUE mtimev);

VALUE
notmuch_rb_directory_get_child_files(VALUE self);

VALUE
notmuch_rb_directory_get_child_directories(VALUE self);

/* filenames.c */
VALUE
notmuch_rb_filenames_each(VALUE self);

/* query.c */
VALUE
notmuch_rb_query_set_sort(VALUE self, VALUE sortv);

VALUE
notmuch_rb_query_search_threads(VALUE self);

VALUE
notmuch_rb_query_search_messages(VALUE self);

/* threads.c */
VALUE
notmuch_rb_threads_each(VALUE self);

/* messages.c */
VALUE
notmuch_rb_messages_each(VALUE self);

VALUE
notmuch_rb_messages_collect_tags(VALUE self);

/* thread.c */
VALUE
notmuch_rb_thread_get_thread_id(VALUE self);

VALUE
notmuch_rb_thread_get_total_messages(VALUE self);

VALUE
notmuch_rb_thread_get_toplevel_messages(VALUE self);

VALUE
notmuch_rb_thread_get_matched_messages(VALUE self);

VALUE
notmuch_rb_thread_get_authors(VALUE self);

VALUE
notmuch_rb_thread_get_subject(VALUE self);

VALUE
notmuch_rb_thread_get_oldest_date(VALUE self);

VALUE
notmuch_rb_thread_get_newest_date(VALUE self);

VALUE
notmuch_rb_thread_get_tags(VALUE self);

/* message.c */
VALUE
notmuch_rb_message_get_message_id(VALUE self);

VALUE
notmuch_rb_message_get_thread_id(VALUE self);

VALUE
notmuch_rb_message_get_replies(VALUE self);

VALUE
notmuch_rb_message_get_filename(VALUE self);

VALUE
notmuch_rb_message_get_flag(VALUE self, VALUE flagv);

VALUE
notmuch_rb_message_set_flag(VALUE self, VALUE flagv, VALUE valuev);

VALUE
notmuch_rb_message_get_date(VALUE self);

VALUE
notmuch_rb_message_get_header(VALUE self, VALUE headerv);

VALUE
notmuch_rb_message_get_tags(VALUE self);

VALUE
notmuch_rb_message_add_tag(VALUE self, VALUE tagv);

VALUE
notmuch_rb_message_remove_tag(VALUE self, VALUE tagv);

VALUE
notmuch_rb_message_remove_all_tags(VALUE self);

VALUE
notmuch_rb_message_freeze(VALUE self);

VALUE
notmuch_rb_message_thaw(VALUE self);

/* tags.c */
VALUE
notmuch_rb_tags_each(VALUE self);

/* init.c */
void
Init_notmuch(void);

#endif
