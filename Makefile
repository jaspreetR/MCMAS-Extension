BUILD_DIR = build

default: all

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -f compile_commands.json

check run all: $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. > /dev/null
	@make -s -C $(BUILD_DIR) $@
	@mv $(BUILD_DIR)/compile_commands.json .

