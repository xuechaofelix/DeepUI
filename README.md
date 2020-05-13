# DeepUI
## dependency for ubuntu
	1）apt-get install libboost-all-dev
	2）apt-get install -yqq libgmp-dev libmpfr-dev
	3）git clone https://github.com/antoinemine/apron 
	   	cd apron
	   	./configure -no-ppl -no-java
       	sudo make 
       	sudo make install

## dependecy for MACOS
	1)安装包管理器 [Homebrew](https://brew.sh/)
	```
	/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
	```

	2)安装 [Boost](https://www.boost.org/)

	```
	brew install boost
	```

	3)编译 Apron 

	```
	git clone https://github.com/antoinemine/apron.git
	cd ./apron
	./configure -no-ocaml -no-ocamlfind -no-ocaml-plugins -no-ppl -no-java 
	make
	make install
	```