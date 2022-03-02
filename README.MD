# Gamepass Exe Extractor
This is a small tool to extract the read protected EXE files from modern Xbox Gamepass Games for modding or RE purposes.
ATTENTION: The games need to be installed using the new way that allows installation to any folder, as mentioned in the announcement [here](https://news.xbox.com/en-us/2022/03/01/xbox-game-pass-march-update-2022/).

## How to build this
Open the project in Visual Studio and hit build. No dependencies needed.

## Usage
Launch the game normally. Then use any kind of DLL Injector and inject the DLL into the game process. A console window will appear and the dump will be complete when the word DONE appears. You can find the dumped EXE files in the games directory as <EXE_NAME>.Dumped.exe.