AC_PREREQ(2.59)
AC_INIT(html2LaTeX, 0.0.1)
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_PROG_CXX
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES(
	[
 		Makefile
 		src/Makefile
 		test/Makefile
 		docs/Doxyfile
 		docs/Makefile
	]
)
AC_LANG_PUSH([C++])

# Check for dependencies
#PKG_CHECK_MODULES([libevent],[libevent])
#PKG_CHECK_MODULES([log4cpp],[log4cpp])
#PKG_CHECK_MODULES([ncurses],[ncurses])

# Test for doxyen's existence.  If true, define the HAVE_DOXYGEN variable. 
AC_CHECK_PROGS([DOXYGEN], [doxygen], true)
if test -z "$DOXYGEN";
   then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi
AM_CONDITIONAL([HAVE_DOXYGEN], 
[test -n "$DOXYGEN"])


# Add command line options for configuring doxygen output.
AC_ARG_ENABLE([doxygen_create_html],
	[  --enable-doxygen_create_html       Enable creation of HTML documentation by doxygen],
	[case "${enableval}" in
		yes)   AC_SUBST(doxygen_create_html,true)  ;;
		no)    AC_SUBST(doxygen_create_html,false) ;;
		true)  AC_SUBST(doxygen_create_html,true)  ;;
		false) AC_SUBST(doxygen_create_html,false) ;;
		*) AC_MSG_ERROR([bad value ${enableval} for --enable-doxygen_create_html]) ;;
	esac],
	[AC_SUBST(doxygen_create_html,true)]
)
AM_CONDITIONAL([DOXYGEN_CREATE_HTML], [test x$doxygen_create_html = xtrue])


AC_ARG_ENABLE([doxygen_create_latex],
	[  --enable-doxygen_create_latex      Enable creation of LaTeX documentation by doxygen],
	[case "${enableval}" in
		yes)   AC_SUBST(doxygen_create_latex,true)  ;;
		no)    AC_SUBST(doxygen_create_latex,false) ;;
		true)  AC_SUBST(doxygen_create_latex,true)  ;;
		false) AC_SUBST(doxygen_create_latex,false) ;;
		*) AC_MSG_ERROR([bad value ${enableval} for --enable-doxygen_create_latex]) ;;
	esac],
	[AC_SUBST(doxygen_create_latex,false)]
)
AM_CONDITIONAL([DOXYGEN_CREATE_LATEX], [test x$doxygen_create_latex = xtrue])


AC_ARG_ENABLE([doxygen_create_man],
	[  --enable-doxygen_create_man        Enable creation of Man documentation by doxygen],
	[case "${enableval}" in
		yes)   AC_SUBST(doxygen_create_man,true)  ;;
		no)    AC_SUBST(doxygen_create_man,false) ;;
		true)  AC_SUBST(doxygen_create_man,true)  ;;
		false) AC_SUBST(doxygen_create_man,false) ;;
		*) AC_MSG_ERROR([bad value ${enableval} for --enable-doxygen_create_man]) ;;
	esac],
	[AC_SUBST(doxygen_create_man,true)]
)
AM_CONDITIONAL([DOXYGEN_CREATE_MAN], [test x$doxygen_create_man = xtrue])


AC_ARG_ENABLE([doxygen_create_rtf],
	[  --enable-doxygen_create_rtf        Enable creation of RTF documentation by doxygen],
	[case "${enableval}" in
		yes)   AC_SUBST(doxygen_create_rtf,true)  ;;
		no)    AC_SUBST(doxygen_create_rtf,false) ;;
		true)  AC_SUBST(doxygen_create_rtf,true)  ;;
		false) AC_SUBST(doxygen_create_rtf,false) ;;
		*) AC_MSG_ERROR([bad value ${enableval} for --enable-doxygen_create_rtf]) ;;
	esac],
	[AC_SUBST(doxygen_create_rtf,false)]
)
AM_CONDITIONAL([DOXYGEN_CREATE_RTF], [test x$doxygen_create_rtf = xtrue])

AC_ARG_ENABLE([doxygen_create_xml],
	[  --enable-doxygen_create_xml        Enable creation of XML documentation by doxygen],
	[case "${enableval}" in
		yes)   AC_SUBST(doxygen_create_xml,true)  ;;
		no)    AC_SUBST(doxygen_create_xml,false) ;;
		true)  AC_SUBST(doxygen_create_xml,true)  ;;
		false) AC_SUBST(doxygen_create_xml,false) ;;
		*) AC_MSG_ERROR([bad value ${enableval} for --enable-doxygen_create_xml]) ;;
	esac],
	[AC_SUBST(doxygen_create_xml,false)]
)
AM_CONDITIONAL([DOXYGEN_CREATE_XML], [test x$doxygen_create_xml = xtrue])

AC_ARG_ENABLE([doxygen_create_docbook],
	[  --enable-doxygen_create_docbook    Enable creation of Docbook documentation by doxygen],
	[case "${enableval}" in
		yes)   AC_SUBST(doxygen_create_docbook,true)  ;;
		no)    AC_SUBST(doxygen_create_docbook,false) ;;
		true)  AC_SUBST(doxygen_create_docbook,true)  ;;
		false) AC_SUBST(doxygen_create_docbook,false) ;;
		*) AC_MSG_ERROR([bad value ${enableval} for --enable-doxygen_create_docbook]) ;;
	esac],
	[AC_SUBST(doxygen_create_docbook,false)]
)
AM_CONDITIONAL([DOXYGEN_CREATE_DOCBOOK], [test x$doxygen_create_docbook = xtrue])

AC_OUTPUT

