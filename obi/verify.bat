@echo off
SETLOCAL EnableDelayedExpansion
cls

:: This was made by AI because I don't care, it works tho i tested it.
:: i verify all the scripts i make with these oficial solutions from obi you can test it yourself just run this in the root directory of the zip you will download from the obi site and then add the .exe compiled code there and just run it. 1 = it matches, 0 it doesn't
:: you need to name ur output file trofeu.exe for this script to work

:: Outer loop: Finds the main directories (e.g., "1", "2", "3").
for /d %%d in (*) do (

    :: Inner loop: Finds every file ending in ".in" inside the current main directory.
    :: "%%f" will hold the full path to the input file, like "1\1.in", "1\2.in", etc.
    for %%f in (%%d\*.in) do (
        
        :: Get just the name of the file without the extension (e.g., "1", "2", "5").
        set "basename=%%~nf"

        :: Construct the path to the corresponding solution file.
        set "SOLUTION_FILE=%%d\!basename!.sol"
        set "MY_OUTPUT_FILE=minha_saida.txt"

        :: Check if the matching .sol file exists before we run the test.
        if exist "!SOLUTION_FILE!" (

            :: Run the program, using the found .in file and creating the output file.
            trofeu.exe < "%%f" > "!MY_OUTPUT_FILE!"

            :: Compare the result with the solution file. Hide the output of the fc command.
            fc "!MY_OUTPUT_FILE!" "!SOLUTION_FILE!" > NUL

            :: Check the result of the comparison. %errorlevel% is 0 if they are the same.
            if !errorlevel! == 0 (
                echo 1
            ) else (
                echo 0
            )
        )
    )
)

:: Clean up the temporary file created by the last run.
if exist "minha_saida.txt" (
    del "minha_saida.txt"
)

:: Pause the window so it doesn't close, allowing you to see the output.
pause