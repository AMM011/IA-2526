# ==== Configuración ====
TARGET      := programa
BIN_DIR     := bin
SRC_DIR     := src
INC_DIR     := include
BUILD_DIR   := build

CXX         := g++
CXXFLAGS    := -Wall -Wextra -std=c++17 -O2 -I$(INC_DIR) -MMD -MP

# ==== Fuentes y objetos ====
SRC := $(wildcard $(SRC_DIR)/*.cc)
OBJ := $(patsubst $(SRC_DIR)/%.cc,$(BUILD_DIR)/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

# ==== Regla por defecto ====
.PHONY: all
all: $(BIN_DIR)/$(TARGET)

# ==== Link ====
$(BIN_DIR)/$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

# ==== Compilación (con dependencias automáticas) ====
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ==== Directorios auxiliares ====
$(BUILD_DIR):
	@mkdir -p $@

$(BIN_DIR):
	@mkdir -p $@

# ==== Limpieza ====
.PHONY: clean clean_obj run
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

clean_obj:
	@rm -rf $(BUILD_DIR)

# ==== Ejecutar (ejemplo) ====
# Uso: make run ARGS="input/Grafo1.txt 1 5 bfs --acumulada --parar"
run: $(BIN_DIR)/$(TARGET)
	@./$(BIN_DIR)/$(TARGET) $(ARGS)

# Incluir dependencias generadas (-MMD -MP)
-include $(DEP)