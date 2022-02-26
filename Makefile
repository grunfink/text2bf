all: text2bf minibf

text2bf: text2bf.c
	$(CC) -g -Wall $< -o $@

minibf: minibf.c
	$(CC) -g -Wall $< -o $@

clean:
	rm -f text2bf minibf
