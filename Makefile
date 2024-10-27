# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -I./imgui -I./implot -I./imgui/backends

# Libraries for ImGui, ImPlot, and OpenGL
LIBS = -lglfw -lGLEW -lGL -ldl -pthread

# Source files and object files
SRC = main.cpp Dashboard.cpp Gauge.cpp Chart.cpp Label.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = dashboard

# ImGui and ImPlot paths
IMGUI_DIR = imgui
IMPLOT_DIR = implot

# ImGui and ImPlot source files and their object files
IMGUI_SRC = $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
IMPLOT_SRC = $(IMPLOT_DIR)/implot.cpp $(IMPLOT_DIR)/implot_items.cpp
IMGUI_OBJ = $(IMGUI_SRC:.cpp=.o)
IMPLOT_OBJ = $(IMPLOT_SRC:.cpp=.o)

# Rule to build the project
all: $(TARGET)

# Rule to compile each .cpp file to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile each ImGui source file individually to .o files
$(IMGUI_OBJ): $(IMGUI_SRC)
	$(CXX) $(CXXFLAGS) -c $(@:.o=.cpp) -o $@

# Compile each ImPlot source file individually to .o files
$(IMPLOT_OBJ): $(IMPLOT_SRC)
	$(CXX) $(CXXFLAGS) -c $(@:.o=.cpp) -o $@

# Rule to link all objects and create the executable
$(TARGET): $(OBJ) $(IMGUI_OBJ) $(IMPLOT_OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(IMGUI_OBJ) $(IMPLOT_OBJ) -o $(TARGET) $(LIBS)

# Rule to clean up object files and executable
clean:
	rm -f $(TARGET) $(OBJ) $(IMGUI_OBJ) $(IMPLOT_OBJ)
