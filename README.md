# SenseShell
A cute terminal for Bash equiped with an  intelligent code completion tool

## Layers
### Bussines Layer
1. ssAdvisor
1. ssBusinessManager
1. ssInterpreter

### Status
1. main
1. ssStatusTable
1. ssBuffer
1. ssInputBuffer (base Buffer)
1. ssOutputBuffer (base Buffer)
1. ssSugestionBuffer (base Buffer)

### GUI
1. ssGUIManager
    * ::run() -> construieste obiectul QApplication
1. SenseForm
1. textedit

### Data
1. ssDataManager