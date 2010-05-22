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

#include "defs.h"

/*
 * call-seq: DIR.mtime => fixnum
 *
 * Returns the mtime of the directory or +0+ if no mtime has been previously
 * stored.
 */
VALUE
notmuch_rb_directory_get_mtime(VALUE self)
{
    notmuch_rb_directory_t *dir;

    Data_Get_Struct(self, notmuch_rb_directory_t, dir);

    return UINT2NUM(notmuch_directory_get_mtime(dir->nm_dir));
}

/*
 * call-seq: DIR.mtime=(fixnum) => nil
 *
 * Store an mtime within the database for the directory object.
 */
VALUE
notmuch_rb_directory_set_mtime(VALUE self, VALUE mtimev)
{
    notmuch_status_t ret;
    notmuch_rb_directory_t *dir;

    Data_Get_Struct(self, notmuch_rb_directory_t, dir);

    if (!FIXNUM_P(mtimev))
        rb_raise(rb_eTypeError, "First argument not a fixnum");

    ret = notmuch_directory_set_mtime(dir->nm_dir, FIX2UINT(mtimev));
    notmuch_rb_status_raise(ret);
    return Qtrue;
}

/*
 * call-seq: DIR.child_files => FILENAMES
 *
 * Return a Notmuch::FileNames object, which is an +Enumerable+ listing all the
 * filenames of messages in the database within the given directory.
 */
VALUE
notmuch_rb_directory_get_child_files(VALUE self)
{
    notmuch_rb_directory_t *dir;
    notmuch_rb_filenames_t *flist;
    VALUE flistv;

    Data_Get_Struct(self, notmuch_rb_directory_t, dir);

    flistv = Data_Make_Struct(notmuch_rb_cFileNames, notmuch_rb_filenames_t,
            notmuch_rb_filenames_mark, notmuch_rb_filenames_free, flist);
    flist->dir = self;
    flist->nm_flist = notmuch_directory_get_child_files(dir->nm_dir);

    return flistv;
}

/*
 * call-seq: DIR.child_directories => FILENAMES
 *
 * Return a Notmuch::FileNames object, which is an +Enumerable+ listing all the
 * directories in the database within the given directory.
 */
VALUE
notmuch_rb_directory_get_child_directories(VALUE self)
{
    notmuch_rb_directory_t *dir;
    notmuch_rb_filenames_t *flist;
    VALUE flistv;

    Data_Get_Struct(self, notmuch_rb_directory_t, dir);

    flistv = Data_Make_Struct(notmuch_rb_cFileNames, notmuch_rb_filenames_t,
            notmuch_rb_filenames_mark, notmuch_rb_filenames_free, flist);
    flist->dir = self;
    flist->nm_flist = notmuch_directory_get_child_directories(dir->nm_dir);

    return flistv;
}
