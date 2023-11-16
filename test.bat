
@IF NOT DEFINED DEBUG @ECHO OFF

FOR /F "TOKENS=*" %%A IN (test.txt) DO (
        SETLOCAL ENABLEDELAYEDEXPANSION
        SET "VAR=%%A"
        SET "VAR=!VAR:\=\\!"
        ECHO !VAR!
        ENDLOCAL
        )
