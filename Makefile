UTILS_DIR = Utils/           
SRC_DIR = src/
TST_DIR = Tests/
BIN_DIR = Bin/
APP_DIR = Application/


all:
	cd $(APP_DIR) && make all
	cd $(SRC_DIR) && make all
	cd $(TST_DIR) && make all

clean:	
	cd $(APP_DIR) && make clean
	cd $(SRC_DIR) && make clean
	cd $(TST_DIR) && make clean
