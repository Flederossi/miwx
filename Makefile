miwx:
	gcc src/miwx.c -o miwx
install: miwx
	sudo mv miwx /bin
uninstall:
	sudo rm /bin/miwx
