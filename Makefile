CPP=g++

SRC=./src
BUILD=./build

server: $(SRC)/server.cpp
	$(CPP) -o $(BUILD)/server $(SRC)/server.cpp

client: $(SRC)/client.cpp
	$(CPP) -o $(BUILD)/client $(SRC)/client.cpp

all: server client

clean:
	rm -rf $(BUILD)/*
