# Lem-in - find the quickest way to get n ants across the farm 🐜🐜🐜

Implemented algorithm analyzes a unique input with a variable number of ants and helps the colony navigate from the start of a maze to the. The solver is multi-pathed, recursive, and weighted for distance, as well as includes graphical output to watch the ants find their home.
</br>

## How to run lem-in?
```
git clone https://github.com/psprawka/Lem-in.git lem-in-psprawka
cd lem-in-psprawka
make
./lem-in < <map_example>
```
The exemplary maps are avaliable in ```maps/``` directory.
</br>

## A farm rules
### There are some rules each given farm has to respect:
* all ants start in ```##start``` room,
* lines starting with ```##``` are commands modifying the line that comes right after,
* ```##start``` signals the ant farm’s entrance and ```##end``` its exit,
* ```#``` means comment till the end of the line,
* all unknown commands are ignored,
* non compliant or empty lines will stop the ant farm’s reading,
* each room can contain **only one** ant at a time (excluding ```##start``` and ```##end```).
