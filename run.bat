@echo off
REM --- Change to your frontend directory ---
cd frontend

echo Running npm install...
call npm install

echo Starting npm run dev...
start cmd /k "npm run dev"

REM --- Go back to root folder (optional) ---
cd ..

REM --- Run your .exe file (change path accordingly) ---
echo Launching program.exe...
REM --- start "" "C:\path\to\your\program.exe"