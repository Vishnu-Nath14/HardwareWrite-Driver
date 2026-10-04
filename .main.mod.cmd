savedcmd_main.mod := printf '%s\n'   main.o | awk '!x[$$0]++ { print("./"$$0) }' > main.mod
