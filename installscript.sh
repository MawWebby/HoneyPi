#!/bin/bash

# INSTALL SCRIPT FOR HONEYPI EXPLORATORY SOFTWARE
# MATTHEW WHITWORTH
# REDISTRIBUTION OR MODIFICATION OF THIS CODE FOR MONETARY GAIN IS ILLEGAL

# RUN INTRO TERMINAL COMMAND
echo "Hello, World from 2515!"
echo "  _____     _____     ____________      _____      ____  ________________   ____         ____           ______________     ________________  "
echo "  |   |     |   |    /            \     |   \      |  |  |               |  \   \       /   /           |             \   |               |  "
echo "  |   |     |   |   /              \    |    \     |  |  |  |¯¯¯¯¯¯¯¯¯¯¯¯    \   \     /   /            |   |¯¯¯¯¯¯\   |  |_____    ______|  "
echo "  |   |     |   |  /   /¯¯¯¯¯¯¯¯\   \   |     \    |  |  |  |____________     \   \   /   /             |   |______/   |        |   |        "
echo "  |    ¯¯¯¯¯    |  |   |         |   |  |      \   |  |  |               |     \   \ /   /              |   __________/         |   |        "
echo "  |    _____    |  |   |         |   |  |   |\  \  |  |  |               |      \       /               |   |                   |   |        "
echo "  |   |     |   |  |   |         |   |  |   | \  \ |  |  |  |¯¯¯¯¯¯¯¯¯¯¯¯        |     |                |   |                   |   |        "
echo "  |   |     |   |  |   |         |   |  |   |  \  \|  |  |  |____________        |     |                |   |                   |   |        "
echo "  |   |     |   |  \    ¯¯¯¯¯¯¯¯¯    /  |   |   \     |  |               |       |     |                |   |             |¯¯¯¯¯     ¯¯¯¯¯|  "
echo "  |   |     |   |   \               /   |   |    \    |  |               |       |     |                |   |             |               |  "
echo "  ¯¯¯¯¯     ¯¯¯¯¯    ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯    ¯¯¯¯      ¯¯¯¯   ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯        ¯¯¯¯¯¯                 ¯¯¯¯¯             ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯   "
echo ""
echo ""
echo ""
echo ""
echo "Main HoneyPi Edition"
echo ""
echo "Created by Matthew Whitworth"
echo ""
echo "Install Script Version: 0.1"
echo ""
echo ""
echo "Please Read the Terms of Service Headlines before continuing: "
echo "This software comes with absolutely no warranty!"
echo "As compensation for running this software, you will receive port filtering for free!"
echo "HoneyPi or HoneyPi's developers are not responsible for attacks or hacks that occur as a result of the device not being setup properly on the internet!"
echo ""
read -p "Please enter to continue: [(Y/N)]" tosagreement

previousinstallfound = 0

# TOS/File Checks
if ["$tosagreement" == "Y" || "$tosagreement" == "y" || "$tosagreement" == "yes"]; then
    echo "Checking Filesystem for Existing Install..."
    directorypi="/home/pi"
    directorypi="/home/pi/HoneyPiConfig"
    if [ -d "$directory" ]; then        
        filePIConfig="/home/pi/HoneyPiConfig/config.txt"
        if [ -f "$file" ]; then
            echo "Previous Installation Found"
            previousinstallfound = 1
            echo "This Script Is Not Intended to Be Used For Maintenance!"
            echo "Ending Script"
            return [4]
        else
            echo "No Previous Install Found, Proceeding..."
            previousinstallfound = 0
        fi
    else
        echo "No Previous Install Found, Proceeding..."
        previousinstallfound = 0
    fi
else
    echo "Failed TOS Agreement"
    return [100]
fi

# Previous Install Found Script
if ["$previousinstallfound" == 0]:
    # CODE
    echo "Checking for Network Connectivity..."

    command_output=$(ping -c 5 8.8.8.8 2>&1)
    exit_status=$?
    # Check the exit status
    if [ $exit_status -eq 0 ]; then
        echo "Network Connection Achieved"
    else
        echo "Network Connection Failed with status $exit_status."
        echo "Error message: $command_output"
    fi

    echo "Before Continuing, It is recommended to create a config file at honeypi.baselinux.net/config"
    echo "You can enter this into the command later, but you should create one now."
    read "Continue? (Y/N)" msdos123

    if ["$msdos123" == "Y" || "$msdos123" == ""]:
        echo "Continuing"
    else 
        echo "Quitting"
        return [100]


# SHOULD NEVER REACH HERE
echo "An Unexplanable Error Occurred: 400"
echo "HoneyPi was not successfully installed on this computer!"
return [400]