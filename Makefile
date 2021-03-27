all: ce.x

ce.x : calorespecífico.cpp
	g++ $< -o ce.x
	./ce.x

clean:
	rm -f *.x
