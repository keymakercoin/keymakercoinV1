
dnl Copyright (c) 2013-2015 The Bitcoin Core developers
dnl Distributed under the MIT software license, see the accompanying
dnl file COPYING or http://www.opensource.org/licenses/mit-license.php.

AC_DEFUN([BITCOIN_FIND_BDB62],[
  AC_ARG_VAR(BDB_CFLAGS, [C compiler flags for BerkeleyDB, bypasses autodetection])
  AC_ARG_VAR(BDB_LIBS, [Linker flags for BerkeleyDB, bypasses autodetection])
  if test "x$use_bdb" = "xno"; then
    use_bdb=no
  elif test "x$BDB_CFLAGS" = "x"; then
    AC_MSG_CHECKING([for Berkeley DB C++ headers])
    BDB_CPPFLAGS=
    bdbpath=X
    bdb62path=X
    bdbdirlist=
    for _vn in 6.2 62 6 5 5.3 ''; do
      for _pfx in b lib ''; do
        bdbdirlist="$bdbdirlist ${_pfx}db${_vn}"
      done
    done
    for searchpath in $bdbdirlist ''; do
      test -n "${searchpath}" && searchpath="${searchpath}/"
      AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
        #include <${searchpath}db_cxx.h>
      ]],[[
        #if !((DB_VERSION_MAJOR == 6 && DB_VERSION_MINOR >= 2) || DB_VERSION_MAJOR < 6 || DB_VERSION_MAJOR > 6)
          #error "failed to find bdb 6.2+"
        #endif
      ]])],[
        if test "x$bdbpath" = "xX"; then
          bdbpath="${searchpath}"
        fi
      ],[
        continue
      ])
      AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
        #include <${searchpath}db_cxx.h>
      ]],[[
        #if !(DB_VERSION_MAJOR == 6 && DB_VERSION_MINOR == 2)
          #error "failed to find bdb 6.2"
        #endif
      ]])],[
        bdb62path="${searchpath}"
        break
      ],[])
    done
    if test "x$bdbpath" = "xX"; then
      use_bdb=no
      AC_MSG_RESULT([no])
      AC_MSG_ERROR([libdb_cxx headers missing, ]AC_PACKAGE_NAME[ requires this library for BDB wallet support (--without-bdb to disable BDB wallet support)])
    elif test "x$bdb62path" = "xX"; then
      BITCOIN_SUBDIR_TO_INCLUDE(BDB_CPPFLAGS,[${bdbpath}],db_cxx)
      AC_ARG_WITH([incompatible-bdb],[AS_HELP_STRING([--with-incompatible-bdb], [allow using a bdb version other than 6.2])],[
        AC_MSG_WARN([Found Berkeley DB other than 6.2; BDB wallets opened by this build will not be portable!])
      ],[
        AC_MSG_ERROR([Found Berkeley DB other than 6.2, required for portable BDB wallets (--with-incompatible-bdb to ignore or --without-bdb to disable BDB wallet support)])
      ])
      use_bdb=yes
    else
      BITCOIN_SUBDIR_TO_INCLUDE(BDB_CPPFLAGS,[${bdb48path}],db_cxx)
      bdbpath="${bdb62path}"
      use_bdb=yes
    fi
  else
    BDB_CPPFLAGS=${BDB_CFLAGS}
  fi
  AC_SUBST(BDB_CPPFLAGS)
  if test "x$use_bdb" = "xno"; then
    use_bdb=no
  elif test "x$BDB_LIBS" = "x"; then
    # TODO: Ideally this could find the library version and make sure it matches the headers being used
    for searchlib in db_cxx db_cxx-6.2 db_cxx-5.3 db6_cxx db5_cxx; do
      AC_CHECK_LIB([$searchlib],[main],[
        BDB_LIBS="-l${searchlib}"
        break
      ])
    done
    if test "x$BDB_LIBS" = "x"; then
        AC_MSG_ERROR([libdb_cxx missing, ]AC_PACKAGE_NAME[ requires this library for BDB wallet support (--without-bdb to disable BDB wallet support)])
    fi
  fi
  if test "x$use_bdb" != "xno"; then
    AC_SUBST(BDB_LIBS)
    AC_DEFINE([USE_BDB], [1], [Define if BDB support should be compiled in])
    use_bdb=yes
  fi
])