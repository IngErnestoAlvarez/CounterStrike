#!/bin/bash

dependencies (){
    echo "Installing SDL2";
    apt-get install libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev;
    apt-get install libsdl2;
    echo "Installing yaml dependecy";
    apt-get install libyaml-cpp-dev;
    echo "Installing box2d";
    apt-get install libbox2d-dev;
    echo "Installing cimg";
    apt-get install cimg-dev;
}

start (){
    echo "Where do you want to install the bins?\n If you dont pass anything it will install it on /usr/bin"
    read BIN
    if [ -z "$BIN" ]
    then
        BIN="/usr/bin"
    fi
    echo "Where do you want to install the configuration files?\n If you dont pass anything it will install it on /etc"
    read CONFIG
    if [ -z "$CONFIG" ]
    then
        CONFIG="/etc"
    fi
    echo "Where do you want to install the assets?\n If you dont pass anything it will install it on /var"
    read ASSETS
    if [ -z "$ASSETS" ]
    then
        ASSETS="/var"
    fi
    
}


main (){
mkdir -p build;
cd build;
cmake .. -DBINPATH:STRING=$BIN -DCONFIGPATH:STRING=$CONFIG -DASSETSPATH:STRING=$ASSETS;
make;
cd ..;
}

Binary (){
    mkdir -p $BIN;
    cp build/CounterStrike_run $BIN;
    cp build/CounterStrike_server $BIN;
    local run=$BIN"/CounterStrike_run";
    chmod +rx $run;
    local server=$BIN"/CounterStrike_server";
    chmod +rx $server;
}

Config (){
    CONFIG=$CONFIG"/CounterStrike";
    mkdir -p $CONFIG;
    cp -a config/. $CONFIG;
}

Assets (){
    ASSETS=$ASSETS"/CounterStrike";
    mkdir -p $ASSETS;
    cp -a assets/. $ASSETS;
}

dependencies
start
Config
Assets
main
Binary
