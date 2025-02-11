all:final
final: finalproject.c
	gcc finalproject.c -o final
run:all
	@./final
clean:
	rm -f final