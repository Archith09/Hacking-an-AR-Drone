CXXFLAGS += -Wl,--no-as-needed -std=c++11 -pthread -g -Wall -Wextra

SRC_DIR = .

TARGET = control_panel

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o *~

udpsender.o: $(SRC_DIR)/udpsender.cc
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/udpsender.cc -o $@

controller.o: $(SRC_DIR)/controller.cc $(SRC_DIR)/udpsender.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/controller.cc -o $@

control_panel.o: $(SRC_DIR)/main.cc $(SRC_DIR)/controller.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cc -o $@

control_panel: udpsender.o controller.o control_panel.o
	$(CXX) $(CXXFLAGS) $^ -o $@
