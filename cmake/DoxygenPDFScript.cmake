if(OUTPUT)
	message("pdflatex refman")
	execute_process(COMMAND pdflatex refman)
else()
	execute_process(COMMAND pdflatex refman OUTPUT_QUIET ERROR_QUIET)
endif()

if(OUTPUT)
	message("/usr/bin/makeindex refman.idx")
	execute_process(COMMAND /usr/bin/makeindex refman.idx)
else()
	execute_process(COMMAND /usr/bin/makeindex refman.idx OUTPUT_QUIET ERROR_QUIET)
endif()

if(OUTPUT)
	message("pdflatex refman")
	execute_process(COMMAND pdflatex refman)
else()
	execute_process(COMMAND pdflatex refman OUTPUT_QUIET ERROR_QUIET)
endif()

set(latex_count 8)


while(1)
	if(OUTPUT)
		message("egrep -s 'Rerun (LaTeX|to get cross-references right)' refman.log")
		execute_process(
			COMMAND "egrep -s 'Rerun (LaTeX|to get cross-references right)' refman.log"
			RESULT_VARIABLE egrep_output)
	else()
		execute_process(
			COMMAND "egrep -s 'Rerun (LaTeX|to get cross-references right)' refman.log"
			RESULT_VARIABLE egrep_output
			OUTPUT_QUIET
			ERROR_QUIET)
	endif()
	if( egrep_output OR NOT latex_count)
		break()
	endif()
	
	if(OUTPUT)
		message("Rerunning latex...")
		execute_process(COMMAND pdflatex refman)
	else()
		execute_process(COMMAND pdflatex refman OUTPUT_QUIET ERROR_QUIET)
	endif()
	
	math(EXPR latex_count "${latex_count}-1")
	
endwhile()

if(OUTPUT)
	message("Running makeindex...")
	execute_process(COMMAND /usr/bin/makeindex refman.idx)
else()
	execute_process(COMMAND /usr/bin/makeindex refman.idx OUTPUT_QUIET ERROR_QUIET)
endif()

if(OUTPUT)
	message("Running pdflatex...")
else()
	execute_process(COMMAND pdflatex refman OUTPUT_QUIET ERROR_QUIET)
endif()